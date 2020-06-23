/*******************************************************************************
* File Name: cyhal_clock.c
*
* Description:
* Provides an implementation for high level interface for interacting with the
* Cypress Clocks. This is a wrapper around the lower level PDL API.
*
********************************************************************************
* \copyright
* Copyright 2018-2020 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <stdlib.h>
#include "cy_sysclk.h"
#include "cy_utils.h"
#include "cyhal_clock.h"
#include "cyhal_utils.h"
#include "cyhal_hwmgr.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define PLL_LOCK_TIME (10000UL)

/******************************************************************************
 ****************************** Clock Resources *******************************
 *****************************************************************************/
const cyhal_resource_inst_t CYHAL_CLOCK_IMO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_IMO, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_EXT = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_EXT, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_ILO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_ILO, 0 };
#if defined(CY_IP_M0S8EXCO)
const cyhal_resource_inst_t CYHAL_CLOCK_ECO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_ECO, 0 };
#endif
#if defined(CY_IP_M0S8WCO)
const cyhal_resource_inst_t CYHAL_CLOCK_WCO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_WCO, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_WDCSEL = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_WDCSEL, 0 };
#endif

#if (EXCO_PLL_PRESENT > 0)
const cyhal_resource_inst_t CYHAL_CLOCK_PLL = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_PLLSEL = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLLSEL, 0 };
#endif

const cyhal_resource_inst_t CYHAL_CLOCK_LF = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_LF, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_HF = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_PUMP = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PUMP, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_SYS = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_SYS, 0 };

/******************************************************************************
 ***************************** Support Functions*******************************
 *****************************************************************************/
static void setup_clock_inst(cyhal_clock_t *clock, const cyhal_resource_inst_t* resource, bool reserved)
{
    clock->block = (cyhal_clock_block_t)resource->block_num;
    clock->channel = resource->channel_num;
    clock->reserved = reserved;
}

static cy_rslt_t compute_div(uint32_t input_hz, uint32_t desired_hz, uint32_t divider_bits, const cyhal_clock_tolerance_t *tolerance, uint32_t *div)
{
    uint32_t max_div = (1 << divider_bits);
    *div = (input_hz + (desired_hz / 2)) / desired_hz;
    if (*div > max_div)
        *div = max_div;

    uint32_t diff = (tolerance != NULL)
                    ? (uint32_t)abs(_cyhal_utils_calculate_tolerance(tolerance->type, desired_hz, input_hz / *div))
                    : 0;
    return (tolerance != NULL && diff > tolerance->value)
        ? CYHAL_CLOCK_RSLT_ERR_FREQ
        : CY_RSLT_SUCCESS;
}

static uint32_t get_channel_count(cyhal_clock_block_t block)
{
    switch (block)
    {
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT:
            return PERI_PCLK_DIV_8_NR;
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT:
            return PERI_PCLK_DIV_16_NR;
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT:
            return PERI_PCLK_DIV_16_5_NR;
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT:
            return PERI_PCLK_DIV_24_5_NR;
        default:
            return 1;
    }
}

static void cyhal_update_system_state(bool before_change, uint32_t old_hfclk_freq_hz, uint32_t new_hfclk_freq_hz)
{
    // If increasing the clock frequency we need to update the speeds
    // before the change. If decreasing the frequency we need to update
    // after the change.
    if ((before_change == (bool)(new_hfclk_freq_hz > old_hfclk_freq_hz)) ||
        (!before_change == (new_hfclk_freq_hz < old_hfclk_freq_hz)))
    {
        Cy_SysLib_SetWaitStates(new_hfclk_freq_hz / 1000000);
    }

    // If after the change, update the clock
    if (!before_change)
        SystemCoreClockUpdate();
}

static uint32_t cyhal_get_path_freq(cy_en_sysclk_clkhf_src_t clk)
{
    switch (clk)
    {
        case CY_SYSCLK_CLKHF_IN_IMO:
            return Cy_SysClk_ImoGetFrequency();
        case CY_SYSCLK_CLKHF_IN_EXT:
            return Cy_SysClk_ExtClkGetFrequency();
#if defined(CY_IP_M0S8EXCO)
        case CY_SYSCLK_CLKHF_IN_ECO:
            return Cy_SysClk_EcoGetFrequency();
#endif
#if (EXCO_PLL_PRESENT > 0)
        case CY_SYSCLK_CLKHF_IN_PLL:
            return Cy_SysClk_PllGetFrequency(0);
#endif
        default:
            return CYHAL_CLOCK_RSLT_ERR_FREQ;
    }
}

static cy_rslt_t cyhal_get_sysclk_div(uint32_t div_val, cy_en_sysclk_dividers_t *div)
{
    switch (div_val)
    {
        case 1:
            *div = CY_SYSCLK_NO_DIV;
            break;
        case 2:
            *div = CY_SYSCLK_DIV_2;
            break;
        case 4:
            *div = CY_SYSCLK_DIV_4;
            break;
        case 8:
            *div = CY_SYSCLK_DIV_8;
            break;
        default:
            return CYHAL_CLOCK_RSLT_ERR_FREQ;
    }
    return CY_RSLT_SUCCESS;
}

static inline cy_rslt_t cyhal_set_hfclk_div(uint32_t div_val)
{
    cy_en_sysclk_dividers_t new_div;
    cy_rslt_t rslt = cyhal_get_sysclk_div(div_val, &new_div);

    if (CY_RSLT_SUCCESS == rslt)
    {
        uint32_t old_div = (uint32_t)Cy_SysClk_ClkHfGetDivider();
        cy_en_sysclk_clkhf_src_t src = Cy_SysClk_ClkHfGetSource();
        uint32_t path_freq = cyhal_get_path_freq(src);
        uint32_t old_freq = path_freq >> old_div;
        uint32_t new_freq = path_freq >> ((uint32_t)new_div);

        cyhal_update_system_state(true, old_freq, new_freq);
        Cy_SysClk_ClkHfSetDivider(new_div);
        cyhal_update_system_state(false, old_freq, new_freq);
    }

    return rslt;
}

static inline cy_rslt_t cyhal_set_hfclk_source(cyhal_clock_block_t block)
{
    cy_en_sysclk_clkhf_src_t new_src;
    switch (block)
    {
        case CYHAL_CLOCK_BLOCK_IMO:
            new_src = CY_SYSCLK_CLKHF_IN_IMO;
            break;
        case CYHAL_CLOCK_BLOCK_EXT:
            new_src = CY_SYSCLK_CLKHF_IN_EXT;
            break;
#if defined(CY_IP_M0S8EXCO)
        case CYHAL_CLOCK_BLOCK_ECO:
            new_src = CY_SYSCLK_CLKHF_IN_ECO;
            break;
#endif
#if (EXCO_PLL_PRESENT > 0)
        case CYHAL_CLOCK_BLOCK_PLL:
            new_src = CY_SYSCLK_CLKHF_IN_PLL;
            break;
#endif
        default:
            return CYHAL_CLOCK_RSLT_ERR_SOURCE;
    }

    /* Only used if updating HFClk 0 */
    uint32_t div = (uint32_t)Cy_SysClk_ClkHfGetDivider();
    cy_en_sysclk_clkhf_src_t old_src = Cy_SysClk_ClkHfGetSource();
    uint32_t old_freq = cyhal_get_path_freq(old_src) >> div;
    uint32_t new_freq = cyhal_get_path_freq(new_src) >> div;

    cyhal_update_system_state(true, old_freq, new_freq);
    Cy_SysClk_ClkHfSetSource(new_src);
    cyhal_update_system_state(false, old_freq, new_freq);

    return CY_RSLT_SUCCESS;
}

#if (EXCO_PLL_PRESENT > 0)
static uint32_t cyhal_get_pll_in_freq()
{
    cy_en_sysclk_pll_src_t src = Cy_SysClk_PllGetSource(0);
    if (src == CY_SYSCLK_PLL_SRC_IMO)
        return Cy_SysClk_ImoGetFrequency();
    else
    {
#if defined(CY_IP_M0S8EXCO)
        return Cy_SysClk_EcoGetFrequency();
#else
        return 0;
#endif
    }
}

static inline cy_rslt_t cyhal_change_pll_enablement(bool enable, bool wait_for_lock)
{
    cy_stc_sysclk_pll_manual_config_t cfg;
    Cy_SysClk_PllGetConfiguration(0, &cfg);

    uint32_t new_freq, old_freq;
    uint32_t div = (uint32_t)Cy_SysClk_ClkHfGetDivider();
    uint32_t src_freq = cyhal_get_pll_in_freq();
    uint32_t pll_freq = CY_SYSLIB_DIV_ROUND((uint64_t)src_freq * (uint64_t)cfg.feedbackDiv, (uint32_t)cfg.referenceDiv * (uint32_t)cfg.outputDiv);
    if (enable)
    {
        new_freq = pll_freq >> div;
        old_freq = src_freq >> div;
    }
    else
    {
        new_freq = src_freq >> div;
        old_freq = pll_freq >> div;
    }

    bool pll_sources_hf = (CY_SYSCLK_CLKHF_IN_PLL == Cy_SysClk_ClkHfGetSource());
    if (pll_sources_hf)
        cyhal_update_system_state(true, old_freq, new_freq);

    cy_rslt_t rslt = CY_RSLT_SUCCESS;
    if (enable)
        rslt = Cy_SysClk_PllEnable(0, wait_for_lock ? PLL_LOCK_TIME : 0UL);
    else
        Cy_SysClk_PllDisable(0);

    if (pll_sources_hf)
    {
        if (CY_RSLT_SUCCESS == rslt)
            cyhal_update_system_state(false, old_freq, new_freq);
        else // revert the change if there was one
            cyhal_update_system_state(false, new_freq, old_freq);
    }

    return rslt;
}

static inline cy_rslt_t cyhal_set_pll_freq(uint32_t new_freq)
{
    cy_stc_sysclk_pll_manual_config_t cfg;
    Cy_SysClk_PllGetConfiguration(0, &cfg);

    bool enabled = Cy_SysClk_PllIsEnabled(0);
    if (enabled)
        Cy_SysClk_PllDisable(0);

    uint32_t src_freq = cyhal_get_pll_in_freq();
    uint32_t old_freq = CY_SYSLIB_DIV_ROUND((uint64_t)src_freq * (uint64_t)cfg.feedbackDiv, (uint32_t)cfg.referenceDiv * (uint32_t)cfg.outputDiv);

    uint32_t div = (uint32_t)Cy_SysClk_ClkHfGetDivider();
    uint32_t old_hf_freq = old_freq >> div;
    uint32_t new_hf_freq = new_freq >> div;

    bool pll_sources_hf = (CY_SYSCLK_CLKHF_IN_PLL == Cy_SysClk_ClkHfGetSource());
    if (pll_sources_hf)
        cyhal_update_system_state(true, old_hf_freq, new_hf_freq);

    cy_stc_sysclk_pll_config_t new_cfg =
    {
        .inputFreq = src_freq,
        .outputFreq = new_freq,
    };
    cy_rslt_t rslt = Cy_SysClk_PllConfigure(0, &new_cfg);

    if (enabled)
    {
        cy_rslt_t rslt2 = Cy_SysClk_PllEnable(0, PLL_LOCK_TIME);
        if (CY_RSLT_SUCCESS == rslt)
            rslt = rslt2;
    }

    if (pll_sources_hf)
    {
        if (CY_RSLT_SUCCESS == rslt)
            cyhal_update_system_state(false, old_hf_freq, new_hf_freq);
        else // revert the change if there was one
            cyhal_update_system_state(false, new_hf_freq, old_hf_freq);
    }

    return rslt;
}
#endif

/******************************************************************************
 **************************** Public API (clocks) *****************************
 *****************************************************************************/
cy_rslt_t cyhal_clock_get(cyhal_clock_t *clock, const cyhal_resource_inst_t *resource)
{
    CY_ASSERT(NULL != clock);
    CY_ASSERT(NULL != resource);
    CY_ASSERT(CYHAL_RSC_CLOCK == resource->type);

    setup_clock_inst(clock, resource, false);

    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_clock_allocate(cyhal_clock_t *clock, cyhal_clock_block_t block)
{
    CY_ASSERT(NULL != clock);

    uint8_t maxChannels = (uint8_t)get_channel_count(block);
    for (uint8_t i = 0; i < maxChannels; i++)
    {
        cyhal_resource_inst_t clock_resource = { CYHAL_RSC_CLOCK, block, i };
        if (CY_RSLT_SUCCESS == cyhal_hwmgr_reserve(&clock_resource))
        {
            setup_clock_inst(clock, &clock_resource, true);
            return CY_RSLT_SUCCESS;
        }
    }
    return CYHAL_HWMGR_RSLT_ERR_NONE_FREE;
}

cy_rslt_t cyhal_clock_init(cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != clock);

    cyhal_resource_inst_t resource = { CYHAL_RSC_CLOCK, clock->block, clock->channel };
    cy_rslt_t rslt = cyhal_hwmgr_reserve(&resource);
    if (CY_RSLT_SUCCESS == rslt)
    {
        clock->reserved = true;
    }

    return rslt;
}

cyhal_clock_feature_t cyhal_clock_get_features(const cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != clock);

    switch (clock->block)
    {
        case CYHAL_CLOCK_BLOCK_LF:
            return CYHAL_CLOCK_FEATURE_NONE;

        case CYHAL_CLOCK_BLOCK_IMO:
            return (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_FREQUENCY);

#if defined(CY_IP_M0S8WCO)
        case CYHAL_CLOCK_BLOCK_WDCSEL:
            return (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_SOURCE);
        case CYHAL_CLOCK_BLOCK_WCO:
#endif
#if defined(CY_IP_M0S8EXCO)
        case CYHAL_CLOCK_BLOCK_ECO: //We don't allow setting frequency because we don't have the necessary args
#endif
        case CYHAL_CLOCK_BLOCK_ILO:
            return CYHAL_CLOCK_FEATURE_ENABLE;

        case CYHAL_CLOCK_BLOCK_EXT:
            return CYHAL_CLOCK_FEATURE_FREQUENCY;

#if (EXCO_PLL_PRESENT > 0)
        case CYHAL_CLOCK_BLOCK_PLL:
            return (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_FREQUENCY);
        case CYHAL_CLOCK_BLOCK_PLLSEL:
            return (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_SOURCE);
#endif

        case CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT:
            return (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_DIVIDER | CYHAL_CLOCK_FEATURE_FREQUENCY);

        case CYHAL_CLOCK_BLOCK_HF:
            return (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_SOURCE | CYHAL_CLOCK_FEATURE_DIVIDER);
        case CYHAL_CLOCK_BLOCK_PUMP:
            return (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_SOURCE);
        case CYHAL_CLOCK_BLOCK_SYS:
            return CYHAL_CLOCK_FEATURE_DIVIDER;

        default:
            CY_ASSERT(false); //Unhandled clock
            return CYHAL_CLOCK_FEATURE_NONE;
    }
}

bool cyhal_clock_is_enabled(const cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != clock);

    switch (clock->block)
    {
        case CYHAL_CLOCK_BLOCK_IMO:
            return Cy_SysClk_ImoIsEnabled();
        case CYHAL_CLOCK_BLOCK_EXT:
            return (Cy_SysClk_ExtClkGetFrequency() > 0);
        case CYHAL_CLOCK_BLOCK_ILO:
            return Cy_SysClk_IloIsEnabled();
#if defined(CY_IP_M0S8EXCO)
        case CYHAL_CLOCK_BLOCK_ECO:
            return Cy_SysClk_EcoIsEnabled();
#endif
#if defined(CY_IP_M0S8WCO)
        case CYHAL_CLOCK_BLOCK_WCO:
            return Cy_SysClk_WcoIsEnabled();
#endif
#if (EXCO_PLL_PRESENT > 0)
        case CYHAL_CLOCK_BLOCK_PLL:
            return Cy_SysClk_PllIsEnabled(clock->channel + 1);
#endif

        case CYHAL_CLOCK_BLOCK_PUMP:
            return (CY_SYSCLK_PUMP_IN_GND != Cy_SysClk_ClkPumpGetSource());
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT:
            return Cy_SysClk_PeriphDividerIsEnabled((cy_en_divider_types_t)clock->block, clock->channel);
#if (EXCO_PLL_PRESENT > 0)
        case CYHAL_CLOCK_BLOCK_PLLSEL:
#endif
#if defined(CY_IP_M0S8WCO)
        case CYHAL_CLOCK_BLOCK_WDCSEL:
#endif
        case CYHAL_CLOCK_BLOCK_LF:
        case CYHAL_CLOCK_BLOCK_HF:
        case CYHAL_CLOCK_BLOCK_SYS:
            return true;
        default:
            CY_ASSERT(false); //Unhandled clock
            return false;
    }
}

cy_rslt_t cyhal_clock_set_enabled(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_ASSERT(NULL != clock);

    /* Timeout values are from the device datasheet. */

    switch (clock->block)
    {
        case CYHAL_CLOCK_BLOCK_IMO:
            if (enabled)
                Cy_SysClk_ImoEnable();
            else
                Cy_SysClk_ImoDisable();
            return CY_RSLT_SUCCESS;
        case CYHAL_CLOCK_BLOCK_ILO:
            if (enabled)
                Cy_SysClk_IloEnable();
            else
                Cy_SysClk_IloDisable();
            return CY_RSLT_SUCCESS;
#if defined(CY_IP_M0S8EXCO)
        case CYHAL_CLOCK_BLOCK_ECO:
            if (enabled)
            {
                if (Cy_SysClk_EcoIsEnabled())
                {
                    // Already enabled
                    if (wait_for_lock)
                    {
                        for (int t = 0; t < 3 && Cy_SysClk_EcoGetStatus() != CY_SYSCLK_ECO_STABLE; ++t)
                        {
                            Cy_SysLib_DelayUs(1000UL);
                        }
                        return (Cy_SysClk_EcoGetStatus() == CY_SYSCLK_ECO_STABLE)
                            ? CY_RSLT_SUCCESS
                            : CY_SYSCLK_TIMEOUT;
                    }
                    return CY_RSLT_SUCCESS;
                }
                else
                {
                    return Cy_SysClk_EcoEnable(wait_for_lock ? 3000UL : 0UL);
                }
            }
            else
            {
                Cy_SysClk_EcoDisable();
                return CY_RSLT_SUCCESS;
            }
#endif
#if defined(CY_IP_M0S8WCO)
        case CYHAL_CLOCK_BLOCK_WCO:
            if (enabled)
            {
                Cy_SysClk_WcoEnable(wait_for_lock ? CY_SYSCLK_WCO_TIMEOUT_US : 0UL);
                // Ignore CY_SYSCLK_TIMEOUT unless wait_for_lock is true
                return (wait_for_lock && !Cy_SysClk_WcoIsEnabled())
                    ? CYHAL_CLOCK_RSLT_ERR_LOCK
                    : CY_RSLT_SUCCESS;
            }
            else
            {
                Cy_SysClk_WcoDisable();
                return CY_RSLT_SUCCESS;
            }
#endif
#if (EXCO_PLL_PRESENT > 0)
        case CYHAL_CLOCK_BLOCK_PLL:
            return cyhal_change_pll_enablement(enabled, wait_for_lock);
#endif
        case CYHAL_CLOCK_BLOCK_PUMP:
            if (enabled)
                Cy_SysClk_ClkPumpSetSource(CY_SYSCLK_PUMP_IN_HFCLK);
            else
                Cy_SysClk_ClkPumpSetSource(CY_SYSCLK_PUMP_IN_GND);
            return CY_RSLT_SUCCESS;
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT:
            return (enabled)
                ? Cy_SysClk_PeriphEnableDivider((cy_en_divider_types_t)clock->block, clock->channel)
                : Cy_SysClk_PeriphDisableDivider((cy_en_divider_types_t)clock->block, clock->channel);
        default:
            CY_ASSERT(false); //Unhandled clock
            return CYHAL_CLOCK_RSLT_ERR_RESOURCE;
    }
}

uint32_t cyhal_clock_get_frequency(const cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != clock);

    if (!cyhal_clock_is_enabled(clock))
    {
        return 0;
    }

    switch (clock->block)
    {
        case CYHAL_CLOCK_BLOCK_IMO:
            return Cy_SysClk_ImoGetFrequency();
        case CYHAL_CLOCK_BLOCK_EXT:
            return Cy_SysClk_ExtClkGetFrequency();
        case CYHAL_CLOCK_BLOCK_LF:
        case CYHAL_CLOCK_BLOCK_ILO:
            return CY_SYSCLK_ILO_FREQ;
#if defined(CY_IP_M0S8EXCO)
        case CYHAL_CLOCK_BLOCK_ECO:
            return Cy_SysClk_EcoGetFrequency();
#endif
#if defined(CY_IP_M0S8WCO)
        case CYHAL_CLOCK_BLOCK_WCO:
            return CY_SYSCLK_WCO_FREQ;
        case CYHAL_CLOCK_BLOCK_WDCSEL:
            return 0; // Not yet implemented by PDL
#endif
#if (EXCO_PLL_PRESENT > 0)
        case CYHAL_CLOCK_BLOCK_PLL:
            return Cy_SysClk_PllIsEnabled(0)
                ? Cy_SysClk_PllGetFrequency(0)
                : 0;
        case CYHAL_CLOCK_BLOCK_PLLSEL:
            return cyhal_get_pll_in_freq();
#endif
        case CYHAL_CLOCK_BLOCK_HF:
            return Cy_SysClk_ClkHfGetFrequency();
        case CYHAL_CLOCK_BLOCK_SYS:
            return Cy_SysClk_ClkSysGetFrequency();
        case CYHAL_CLOCK_BLOCK_PUMP:
            switch (Cy_SysClk_ClkPumpGetSource())
            {
                case CY_SYSCLK_PUMP_IN_IMO:
                    return Cy_SysClk_ImoGetFrequency();
                case CY_SYSCLK_PUMP_IN_HFCLK:
                    return Cy_SysClk_ClkHfGetFrequency();
                case CY_SYSCLK_PUMP_IN_GND:
                default:
                    return 0;
            }
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT:
            return Cy_SysClk_PeriphGetFrequency((cy_en_sysclk_divider_types_t)clock->block, clock->channel);
        default:
            CY_ASSERT(false); //Unhandled clock
            return 0;
    }
}

cy_rslt_t cyhal_clock_set_frequency(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_ASSERT(NULL != clock);

    switch (clock->block)
    {
        case CYHAL_CLOCK_BLOCK_IMO:
        {
            if (hz < CY_SYSCLK_IMO_24MHZ || hz > CY_SYSCLK_IMO_48MHZ || ((hz % 4000000) != 0))
                return CYHAL_CLOCK_RSLT_ERR_FREQ;

            uint32_t hf_freq = Cy_SysClk_ClkHfGetFrequency();
            uint32_t div = 1 << (uint8_t)Cy_SysClk_ClkHfGetDivider();
            if (Cy_SysClk_ClkHfGetSource() == CY_SYSCLK_CLKHF_IN_IMO)
            	cyhal_update_system_state(true, hf_freq, hz / div);
            Cy_SysClk_ImoSetFrequency((cy_en_sysclk_imo_freq_t)hz);
            if (Cy_SysClk_ClkHfGetSource() == CY_SYSCLK_CLKHF_IN_IMO)
            	cyhal_update_system_state(false, hf_freq, hz / div);
            return CY_RSLT_SUCCESS;
        }
        case CYHAL_CLOCK_BLOCK_EXT:
            Cy_SysClk_ExtClkSetFrequency(hz);
            return CY_RSLT_SUCCESS;
#if (EXCO_PLL_PRESENT > 0)
        case CYHAL_CLOCK_BLOCK_PLL:
            return cyhal_set_pll_freq(hz);
#endif
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT:
        {
            uint32_t div;
            uint32_t input_hz = Cy_SysClk_ClkSysGetFrequency();
            uint32_t bits = (clock->block == CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT) ? 8 : 16;
            cy_rslt_t rslt = compute_div(input_hz, hz, bits, tolerance, &div);
            return (CY_RSLT_SUCCESS == rslt)
                ? Cy_SysClk_PeriphSetDivider((cy_en_sysclk_divider_types_t)clock->block, clock->channel, (div - 1))
                : rslt;
        }
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT:
        {
            uint32_t div;
            uint32_t input_hz = Cy_SysClk_ClkSysGetFrequency();
            // Multiply input by 32 so we can treat the 5 fractional bits as though they are extentions of the integer divider
            // Leave the the desired frequency alone, so we can just strip out the integer & fractional bits at the end.
            uint32_t bits = (clock->block == CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT) ? 21 : 29; // Integer bits + 5
            cy_rslt_t rslt = compute_div(input_hz << 5, hz, bits, tolerance, &div);
            if (CY_RSLT_SUCCESS == rslt)
            {
                uint32_t div_int = (div >> 5) - 1;
                uint32_t div_frac = div & 0x1F;
                return Cy_SysClk_PeriphSetFracDivider((cy_en_sysclk_divider_types_t)clock->block, clock->channel, div_int, div_frac);
            }
            else
                return rslt;
        }
        default:
            CY_ASSERT(false); //Unhandled clock
            return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
    }
}

cy_rslt_t cyhal_clock_set_divider(cyhal_clock_t *clock, uint32_t divider)
{
    CY_ASSERT(NULL != clock);

    switch (clock->block)
    {
        case CYHAL_CLOCK_BLOCK_HF:
            return cyhal_set_hfclk_div(divider);
        case CYHAL_CLOCK_BLOCK_SYS:
        {
            cy_en_sysclk_dividers_t new_div;
            cy_rslt_t rslt = cyhal_get_sysclk_div(divider, &new_div);
            Cy_SysClk_ClkSysSetDivider(new_div);
            return rslt;
        }
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT:
            return Cy_SysClk_PeriphSetDivider((cy_en_sysclk_divider_types_t)clock->block, clock->channel, divider - 1);
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT:
            return Cy_SysClk_PeriphSetFracDivider((cy_en_sysclk_divider_types_t)clock->block, clock->channel, divider - 1, 0);
        default:
            CY_ASSERT(false); //Unhandled clock
            return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
    }
}

cy_rslt_t cyhal_clock_get_sources(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    #if defined(CY_IP_M0S8WCO)
    const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_WDCSEL[] =
    {
        &CYHAL_CLOCK_ILO,
        &CYHAL_CLOCK_WCO,
    };
    #endif
    #if (EXCO_PLL_PRESENT > 0)
    const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_PLLSEL[] =
    {
        &CYHAL_CLOCK_IMO,
        &CYHAL_CLOCK_ECO,
    };
    const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_PLL[] =
    {
        &CYHAL_CLOCK_PLLSEL,
    };
    #endif
    const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_LF[] =
    {
        &CYHAL_CLOCK_ILO,
    };
    const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_HF[] =
    {
        &CYHAL_CLOCK_IMO,
        &CYHAL_CLOCK_EXT,
    #if (EXCO_PLL_PRESENT > 0)
        &CYHAL_CLOCK_PLLSEL,
        &CYHAL_CLOCK_PLL,
    #elif defined(CY_IP_M0S8EXCO)
        &CYHAL_CLOCK_ECO,
    #endif
    };
    const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_PUMP[] =
    {
        &CYHAL_CLOCK_IMO,
        &CYHAL_CLOCK_HF,
    };
    const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_SYS[] =
    {
        &CYHAL_CLOCK_HF,
    };
    const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_PERIPHERAL[] =
    {
        &CYHAL_CLOCK_SYS,
    };

    CY_ASSERT(NULL != clock);

    switch (clock->block)
    {
        case CYHAL_CLOCK_BLOCK_IMO:
        case CYHAL_CLOCK_BLOCK_EXT:
        case CYHAL_CLOCK_BLOCK_ILO:
#if defined(CY_IP_M0S8EXCO)
        case CYHAL_CLOCK_BLOCK_ECO:
#endif
#if defined(CY_IP_M0S8WCO)
        case CYHAL_CLOCK_BLOCK_WCO:
            *count = 0;
            break;
        case CYHAL_CLOCK_BLOCK_WDCSEL:
            *sources = CYHAL_CLOCK_SOURCE_WDCSEL;
            *count = sizeof(CYHAL_CLOCK_SOURCE_WDCSEL) / sizeof(CYHAL_CLOCK_SOURCE_WDCSEL[0]);
            break;
#endif
#if (EXCO_PLL_PRESENT > 0)
        case CYHAL_CLOCK_BLOCK_PLLSEL:
            *sources = CYHAL_CLOCK_SOURCE_PLLSEL;
            *count = sizeof(CYHAL_CLOCK_SOURCE_PLLSEL) / sizeof(CYHAL_CLOCK_SOURCE_PLLSEL[0]);
            break;
        case CYHAL_CLOCK_BLOCK_PLL:
            *sources = CYHAL_CLOCK_SOURCE_PLL;
            *count = sizeof(CYHAL_CLOCK_SOURCE_PLL) / sizeof(CYHAL_CLOCK_SOURCE_PLL[0]);
            break;
#endif
        case CYHAL_CLOCK_BLOCK_LF:
            *sources = CYHAL_CLOCK_SOURCE_LF;
            *count = sizeof(CYHAL_CLOCK_SOURCE_LF) / sizeof(CYHAL_CLOCK_SOURCE_LF[0]);
            break;
        case CYHAL_CLOCK_BLOCK_HF:
            *sources = CYHAL_CLOCK_SOURCE_HF;
            *count = sizeof(CYHAL_CLOCK_SOURCE_HF) / sizeof(CYHAL_CLOCK_SOURCE_HF[0]);
            break;
        case CYHAL_CLOCK_BLOCK_PUMP:
            *sources = CYHAL_CLOCK_SOURCE_PUMP;
            *count = sizeof(CYHAL_CLOCK_SOURCE_PUMP) / sizeof(CYHAL_CLOCK_SOURCE_PUMP[0]);
            break;
        case CYHAL_CLOCK_BLOCK_SYS:
            *sources = CYHAL_CLOCK_SOURCE_SYS;
            *count = sizeof(CYHAL_CLOCK_SOURCE_SYS) / sizeof(CYHAL_CLOCK_SOURCE_SYS[0]);
            break;
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT:
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT:
            *sources = CYHAL_CLOCK_SOURCE_PERIPHERAL;
            *count = sizeof(CYHAL_CLOCK_SOURCE_PERIPHERAL) / sizeof(CYHAL_CLOCK_SOURCE_PERIPHERAL[0]);
            break;
        default:
            CY_ASSERT(false); //Unhandled clock
            *count = 0;
            return CYHAL_CLOCK_RSLT_ERR_RESOURCE;
    }
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_clock_set_source(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_ASSERT(NULL != clock && NULL != source);

    switch (clock->block)
    {
        case CYHAL_CLOCK_BLOCK_HF:
            return cyhal_set_hfclk_source(source->block);
        case CYHAL_CLOCK_BLOCK_PUMP:
            if (source->block == CYHAL_CLOCK_BLOCK_IMO)
            {
                Cy_SysClk_ClkPumpSetSource(CY_SYSCLK_PUMP_IN_IMO);
                return CY_RSLT_SUCCESS;
            }
            else if (source->block == CYHAL_CLOCK_BLOCK_HF)
            {
                Cy_SysClk_ClkPumpSetSource(CY_SYSCLK_PUMP_IN_HFCLK);
                return CY_RSLT_SUCCESS;
            }
            else
                return CYHAL_CLOCK_RSLT_ERR_SOURCE;
#if (EXCO_PLL_PRESENT > 0)
        case CYHAL_CLOCK_BLOCK_PLLSEL:
            if (source->block == CYHAL_CLOCK_BLOCK_IMO)
            {
                Cy_SysClk_PllSetSource(0, CY_SYSCLK_PLL_SRC_IMO);
                return CY_RSLT_SUCCESS;
            }
            else if (source->block == CYHAL_CLOCK_BLOCK_ECO)
            {
                Cy_SysClk_PllSetSource(0, CY_SYSCLK_PLL_SRC_ECO);
                return CY_RSLT_SUCCESS;
            }
            else
                return CYHAL_CLOCK_RSLT_ERR_SOURCE;
#endif
#if defined(CY_IP_M0S8WCO)
        case CYHAL_CLOCK_BLOCK_WDCSEL:
            // Not yet implemented in PDL
#endif
        default:
            CY_ASSERT(false); //Unhandled clock
            return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
    }
}

void cyhal_clock_free(cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != clock);

    cyhal_resource_inst_t rsc = { CYHAL_RSC_CLOCK, clock->block, clock->channel };
    cyhal_hwmgr_free(&rsc);
    clock->reserved = false;
}

#if defined(__cplusplus)
}
#endif
