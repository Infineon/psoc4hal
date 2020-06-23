/***************************************************************************//**
* \file cyhal_triggers_psoc4100s.c
*
* \brief
* PSoC4100S family HAL triggers header
*
* \note
* Generator version: 1.6.7458.30860
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

#ifdef CY_DEVICE_PSOC4AS2
#include "triggers/cyhal_triggers_psoc4100s.h"

const uint8_t cyhal_dest_to_mux[8] =
{
    1, /* TRIGGER_PASS_TR_SAR_IN */
    0, /* TRIGGER_TCPWM_TR_IN7 */
    0, /* TRIGGER_TCPWM_TR_IN8 */
    0, /* TRIGGER_TCPWM_TR_IN9 */
    0, /* TRIGGER_TCPWM_TR_IN10 */
    0, /* TRIGGER_TCPWM_TR_IN11 */
    0, /* TRIGGER_TCPWM_TR_IN12 */
    0, /* TRIGGER_TCPWM_TR_IN13 */
};

const uint8_t cyhal_mux_dest_index[8] =
{
    0, /* TRIGGER_PASS_TR_SAR_IN */
    0, /* TRIGGER_TCPWM_TR_IN7 */
    1, /* TRIGGER_TCPWM_TR_IN8 */
    2, /* TRIGGER_TCPWM_TR_IN9 */
    3, /* TRIGGER_TCPWM_TR_IN10 */
    4, /* TRIGGER_TCPWM_TR_IN11 */
    5, /* TRIGGER_TCPWM_TR_IN12 */
    6, /* TRIGGER_TCPWM_TR_IN13 */
};
#endif /* CY_DEVICE_PSOC4AS2 */
