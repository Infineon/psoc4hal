/***************************************************************************//**
* \file cyhal_triggers_psoc4100smax.c
*
* \brief
* PSoC4100Smax family HAL triggers header
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

#include "cy_device_headers.h"
#include "cyhal_hw_types.h"

#ifdef CY_DEVICE_PSOC4AS4
#include "triggers/cyhal_triggers_psoc4100smax.h"

const uint8_t cyhal_dest_to_mux[30] =
{
    0, /* TRIGGER_CANFD_TR_DBG_DMA_ACK0 */
    0, /* TRIGGER_CANFD_TR_EVT_SWT_IN0 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN0 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN1 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN2 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN3 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN4 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN5 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN6 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN7 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN8 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN9 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN10 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN11 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN12 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN13 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN14 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN15 */
    3, /* TRIGGER_MSC0_TR_RD_REQ_IN */
    3, /* TRIGGER_MSC1_TR_RD_REQ_IN */
    3, /* TRIGGER_MSC0_TR_WR_REQ_IN */
    3, /* TRIGGER_MSC1_TR_WR_REQ_IN */
    2, /* TRIGGER_PASS_TR_SAR_IN */
    1, /* TRIGGER_TCPWM_TR_IN7 */
    1, /* TRIGGER_TCPWM_TR_IN8 */
    1, /* TRIGGER_TCPWM_TR_IN9 */
    1, /* TRIGGER_TCPWM_TR_IN10 */
    1, /* TRIGGER_TCPWM_TR_IN11 */
    1, /* TRIGGER_TCPWM_TR_IN12 */
    1, /* TRIGGER_TCPWM_TR_IN13 */
};

const uint8_t cyhal_mux_dest_index[30] =
{
    17, /* TRIGGER_CANFD_TR_DBG_DMA_ACK0 */
    16, /* TRIGGER_CANFD_TR_EVT_SWT_IN0 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN0 */
    1, /* TRIGGER_CPUSS_DMAC_TR_IN1 */
    2, /* TRIGGER_CPUSS_DMAC_TR_IN2 */
    3, /* TRIGGER_CPUSS_DMAC_TR_IN3 */
    4, /* TRIGGER_CPUSS_DMAC_TR_IN4 */
    5, /* TRIGGER_CPUSS_DMAC_TR_IN5 */
    6, /* TRIGGER_CPUSS_DMAC_TR_IN6 */
    7, /* TRIGGER_CPUSS_DMAC_TR_IN7 */
    8, /* TRIGGER_CPUSS_DMAC_TR_IN8 */
    9, /* TRIGGER_CPUSS_DMAC_TR_IN9 */
    10, /* TRIGGER_CPUSS_DMAC_TR_IN10 */
    11, /* TRIGGER_CPUSS_DMAC_TR_IN11 */
    12, /* TRIGGER_CPUSS_DMAC_TR_IN12 */
    13, /* TRIGGER_CPUSS_DMAC_TR_IN13 */
    14, /* TRIGGER_CPUSS_DMAC_TR_IN14 */
    15, /* TRIGGER_CPUSS_DMAC_TR_IN15 */
    1, /* TRIGGER_MSC0_TR_RD_REQ_IN */
    3, /* TRIGGER_MSC1_TR_RD_REQ_IN */
    0, /* TRIGGER_MSC0_TR_WR_REQ_IN */
    2, /* TRIGGER_MSC1_TR_WR_REQ_IN */
    0, /* TRIGGER_PASS_TR_SAR_IN */
    0, /* TRIGGER_TCPWM_TR_IN7 */
    1, /* TRIGGER_TCPWM_TR_IN8 */
    2, /* TRIGGER_TCPWM_TR_IN9 */
    3, /* TRIGGER_TCPWM_TR_IN10 */
    4, /* TRIGGER_TCPWM_TR_IN11 */
    5, /* TRIGGER_TCPWM_TR_IN12 */
    6, /* TRIGGER_TCPWM_TR_IN13 */
};
#endif /* CY_DEVICE_PSOC4AS4 */
