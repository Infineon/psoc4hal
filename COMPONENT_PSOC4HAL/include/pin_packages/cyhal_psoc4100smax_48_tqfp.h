/***************************************************************************//**
* \file cyhal_psoc4100smax_48_tqfp.h
*
* \brief
* PSoC4100Smax device GPIO HAL header for 48-TQFP package
*
* \note
* Generator version: 1.6.7465.21978
*
********************************************************************************
* \copyright
* Copyright 2016-2020 Cypress Semiconductor Corporation
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

#ifndef _CYHAL_PSOC4100SMAX_48_TQFP_H_
#define _CYHAL_PSOC4100SMAX_48_TQFP_H_

#include "cyhal_hw_resources.h"

/**
 * \addtogroup group_hal_impl_pin_package_psoc4100smax_48_tqfp PSoC4100Smax 48-TQFP
 * \ingroup group_hal_impl_pin_package
 * \{
 * Pin definitions and connections specific to the PSoC4100Smax 48-TQFP package.
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/** Gets a pin definition from the provided port and pin numbers */
#define CYHAL_GET_GPIO(port, pin)   ((((uint8_t)(port)) << 3U) + ((uint8_t)(pin)))

/** Macro that, given a gpio, will extract the pin number */
#define CYHAL_GET_PIN(pin)          ((uint8_t)(((uint8_t)pin) & 0x07U))
/** Macro that, given a gpio, will extract the port number */
#define CYHAL_GET_PORT(pin)         ((uint8_t)((((uint8_t)pin) >> 3U) & 0x1FU))

/** Definitions for all of the pins that are bonded out on in the 48-TQFP package for the PSoC4100Smax series. */
typedef enum {
    NC = 0xFF, //!< No Connect/Invalid Pin

    P0_0 = CYHAL_GET_GPIO(CYHAL_PORT_0, 0), //!< Port 0 Pin 0
    P0_1 = CYHAL_GET_GPIO(CYHAL_PORT_0, 1), //!< Port 0 Pin 1
    P0_2 = CYHAL_GET_GPIO(CYHAL_PORT_0, 2), //!< Port 0 Pin 2
    P0_3 = CYHAL_GET_GPIO(CYHAL_PORT_0, 3), //!< Port 0 Pin 3
    P0_4 = CYHAL_GET_GPIO(CYHAL_PORT_0, 4), //!< Port 0 Pin 4
    P0_5 = CYHAL_GET_GPIO(CYHAL_PORT_0, 5), //!< Port 0 Pin 5
    P0_6 = CYHAL_GET_GPIO(CYHAL_PORT_0, 6), //!< Port 0 Pin 6
    P0_7 = CYHAL_GET_GPIO(CYHAL_PORT_0, 7), //!< Port 0 Pin 7

    P1_0 = CYHAL_GET_GPIO(CYHAL_PORT_1, 0), //!< Port 1 Pin 0
    P1_1 = CYHAL_GET_GPIO(CYHAL_PORT_1, 1), //!< Port 1 Pin 1
    P1_2 = CYHAL_GET_GPIO(CYHAL_PORT_1, 2), //!< Port 1 Pin 2
    P1_3 = CYHAL_GET_GPIO(CYHAL_PORT_1, 3), //!< Port 1 Pin 3
    P1_4 = CYHAL_GET_GPIO(CYHAL_PORT_1, 4), //!< Port 1 Pin 4
    P1_5 = CYHAL_GET_GPIO(CYHAL_PORT_1, 5), //!< Port 1 Pin 5
    P1_6 = CYHAL_GET_GPIO(CYHAL_PORT_1, 6), //!< Port 1 Pin 6
    P1_7 = CYHAL_GET_GPIO(CYHAL_PORT_1, 7), //!< Port 1 Pin 7

    P2_0 = CYHAL_GET_GPIO(CYHAL_PORT_2, 0), //!< Port 2 Pin 0
    P2_1 = CYHAL_GET_GPIO(CYHAL_PORT_2, 1), //!< Port 2 Pin 1
    P2_2 = CYHAL_GET_GPIO(CYHAL_PORT_2, 2), //!< Port 2 Pin 2
    P2_3 = CYHAL_GET_GPIO(CYHAL_PORT_2, 3), //!< Port 2 Pin 3
    P2_4 = CYHAL_GET_GPIO(CYHAL_PORT_2, 4), //!< Port 2 Pin 4
    P2_5 = CYHAL_GET_GPIO(CYHAL_PORT_2, 5), //!< Port 2 Pin 5
    P2_6 = CYHAL_GET_GPIO(CYHAL_PORT_2, 6), //!< Port 2 Pin 6
    P2_7 = CYHAL_GET_GPIO(CYHAL_PORT_2, 7), //!< Port 2 Pin 7

    P3_0 = CYHAL_GET_GPIO(CYHAL_PORT_3, 0), //!< Port 3 Pin 0
    P3_1 = CYHAL_GET_GPIO(CYHAL_PORT_3, 1), //!< Port 3 Pin 1
    P3_2 = CYHAL_GET_GPIO(CYHAL_PORT_3, 2), //!< Port 3 Pin 2
    P3_3 = CYHAL_GET_GPIO(CYHAL_PORT_3, 3), //!< Port 3 Pin 3
    P3_4 = CYHAL_GET_GPIO(CYHAL_PORT_3, 4), //!< Port 3 Pin 4
    P3_5 = CYHAL_GET_GPIO(CYHAL_PORT_3, 5), //!< Port 3 Pin 5
    P3_6 = CYHAL_GET_GPIO(CYHAL_PORT_3, 6), //!< Port 3 Pin 6
    P3_7 = CYHAL_GET_GPIO(CYHAL_PORT_3, 7), //!< Port 3 Pin 7

    P4_0 = CYHAL_GET_GPIO(CYHAL_PORT_4, 0), //!< Port 4 Pin 0
    P4_1 = CYHAL_GET_GPIO(CYHAL_PORT_4, 1), //!< Port 4 Pin 1
    P4_2 = CYHAL_GET_GPIO(CYHAL_PORT_4, 2), //!< Port 4 Pin 2
    P4_3 = CYHAL_GET_GPIO(CYHAL_PORT_4, 3), //!< Port 4 Pin 3

    P7_0 = CYHAL_GET_GPIO(CYHAL_PORT_7, 0), //!< Port 7 Pin 0
    P7_1 = CYHAL_GET_GPIO(CYHAL_PORT_7, 1), //!< Port 7 Pin 1
} cyhal_gpio_psoc4100smax_48_tqfp_t;

/** Create generic name for the series/package specific type. */
typedef cyhal_gpio_psoc4100smax_48_tqfp_t cyhal_gpio_t;

/* Connection type definition */
/** Represents an association between a pin and a resource */
typedef struct
{
    const cyhal_resource_inst_t  *inst;      //!< The associated resource instance
    cyhal_gpio_t                 pin;        //!< The GPIO pin
    uint8_t                      drive_mode; //!< The DriveMode configuration value
    en_hsiom_sel_t               hsiom;      //!< The HSIOM configuration value
} cyhal_resource_pin_mapping_t;

/* Pin connections */
/** List of valid pin to peripheral connections for the audioss_clk_i2s_if signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_clk_i2s_if[2];
/** List of valid pin to peripheral connections for the audioss_tx_sck signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_tx_sck[2];
/** List of valid pin to peripheral connections for the audioss_tx_sdo signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_tx_sdo[2];
/** List of valid pin to peripheral connections for the audioss_tx_ws signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_tx_ws[2];
/** List of valid pin to peripheral connections for the canfd_ttcan_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_rx[1];
/** List of valid pin to peripheral connections for the canfd_ttcan_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_tx[1];
/** List of valid pin to peripheral connections for the lpcomp_comp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_comp[4];
/** List of valid pin to peripheral connections for the lpcomp_in_n signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_in_n[2];
/** List of valid pin to peripheral connections for the lpcomp_in_p signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_in_p[2];
/** List of valid pin to peripheral connections for the opamp_dsi_ctb_cmp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_dsi_ctb_cmp[2];
/** List of valid pin to peripheral connections for the opamp_out_10x signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_out_10x[2];
/** List of valid pin to peripheral connections for the opamp_vin_m signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_m[2];
/** List of valid pin to peripheral connections for the opamp_vin_p0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_p0[2];
/** List of valid pin to peripheral connections for the opamp_vin_p1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_p1[2];
/** List of valid pin to peripheral connections for the pass_dsi_sar_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_data[12];
/** List of valid pin to peripheral connections for the pass_dsi_sar_data_valid signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_data_valid[1];
/** List of valid pin to peripheral connections for the pass_dsi_sar_sample_done signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_sample_done[1];
/** List of valid pin to peripheral connections for the pass_sar_ext_vref0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_vref0[1];
/** List of valid pin to peripheral connections for the pass_sar_ext_vref1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_vref1[1];
/** List of valid pin to peripheral connections for the pass_sarmux_pads signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sarmux_pads[8];
/** List of valid pin to peripheral connections for the pass_tr_sar_out signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_tr_sar_out[1];
/** List of valid pin to peripheral connections for the scb_i2c_scl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[9];
/** List of valid pin to peripheral connections for the scb_i2c_sda signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[9];
/** List of valid pin to peripheral connections for the scb_spi_m_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[6];
/** List of valid pin to peripheral connections for the scb_spi_m_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[7];
/** List of valid pin to peripheral connections for the scb_spi_m_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[7];
/** List of valid pin to peripheral connections for the scb_spi_m_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[6];
/** List of valid pin to peripheral connections for the scb_spi_m_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select1[4];
/** List of valid pin to peripheral connections for the scb_spi_m_select2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select2[4];
/** List of valid pin to peripheral connections for the scb_spi_m_select3 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select3[5];
/** List of valid pin to peripheral connections for the scb_spi_s_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[6];
/** List of valid pin to peripheral connections for the scb_spi_s_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[7];
/** List of valid pin to peripheral connections for the scb_spi_s_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[7];
/** List of valid pin to peripheral connections for the scb_spi_s_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[6];
/** List of valid pin to peripheral connections for the scb_spi_s_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select1[4];
/** List of valid pin to peripheral connections for the scb_spi_s_select2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select2[4];
/** List of valid pin to peripheral connections for the scb_spi_s_select3 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select3[5];
/** List of valid pin to peripheral connections for the scb_uart_cts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[6];
/** List of valid pin to peripheral connections for the scb_uart_rts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[6];
/** List of valid pin to peripheral connections for the scb_uart_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[7];
/** List of valid pin to peripheral connections for the scb_uart_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[8];
/** List of valid pin to peripheral connections for the tcpwm_line signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[14];
/** List of valid pin to peripheral connections for the tcpwm_line_compl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line_compl[13];
/** List of valid pin to peripheral connections for the tcpwm_tr_in signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_in[7];

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl_pin_package */

#endif /* _CYHAL_PSOC4100SMAX_48_TQFP_H_ */


/* [] END OF FILE */
