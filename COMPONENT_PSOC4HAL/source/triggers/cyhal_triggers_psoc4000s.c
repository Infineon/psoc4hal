/***************************************************************************//**
* \file cyhal_triggers_psoc4000s.c
*
* \brief
* PSoC4000S family HAL triggers header
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

#ifdef CY_DEVICE_PSOC4AS1
#include "triggers/cyhal_triggers_psoc4000s.h"

const uint8_t cyhal_dest_to_mux[2] =
{
    0, /* TRIGGER_TCPWM_TR_IN12 */
    0, /* TRIGGER_TCPWM_TR_IN13 */
};

const uint8_t cyhal_mux_dest_index[2] =
{
    0, /* TRIGGER_TCPWM_TR_IN12 */
    1, /* TRIGGER_TCPWM_TR_IN13 */
};
#endif /* CY_DEVICE_PSOC4AS1 */
