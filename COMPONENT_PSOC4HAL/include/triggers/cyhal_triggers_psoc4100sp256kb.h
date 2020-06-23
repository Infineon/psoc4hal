/***************************************************************************//**
* \file cyhal_triggers_psoc4100sp256kb.h
*
* \brief
* PSoC4100Sp256KB family HAL triggers header
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

#ifndef _CYHAL_TRIGGERS_PSOC4100SP256KB_H_
#define _CYHAL_TRIGGERS_PSOC4100SP256KB_H_

/**
 * \addtogroup group_hal_impl_triggers_psoc4100sp256kb PSOC4100SP256KB
 * \ingroup group_hal_impl_triggers
 * \{
 * Trigger connections for psoc4100sp256kb
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/** @brief Name of each output trigger. */
typedef enum
{
    TRIGGER_CPUSS_DMAC_TR_IN0 = 0, //!< GP_DMA_Requests - cpuss.dmac_tr_in[0]
    TRIGGER_CPUSS_DMAC_TR_IN1 = 1, //!< GP_DMA_Requests - cpuss.dmac_tr_in[1]
    TRIGGER_CPUSS_DMAC_TR_IN2 = 2, //!< GP_DMA_Requests - cpuss.dmac_tr_in[2]
    TRIGGER_CPUSS_DMAC_TR_IN3 = 3, //!< GP_DMA_Requests - cpuss.dmac_tr_in[3]
    TRIGGER_CPUSS_DMAC_TR_IN4 = 4, //!< GP_DMA_Requests - cpuss.dmac_tr_in[4]
    TRIGGER_CPUSS_DMAC_TR_IN5 = 5, //!< GP_DMA_Requests - cpuss.dmac_tr_in[5]
    TRIGGER_CPUSS_DMAC_TR_IN6 = 6, //!< GP_DMA_Requests - cpuss.dmac_tr_in[6]
    TRIGGER_CPUSS_DMAC_TR_IN7 = 7, //!< GP_DMA_Requests - cpuss.dmac_tr_in[7]
    TRIGGER_CSD_DSI_START = 8, //!< CSD Trigger Mux - csd.dsi_start
    TRIGGER_PASS0_TR_SAR_IN = 9, //!< PASS[0] Triggers - pass[0].tr_sar_in
    TRIGGER_PASS1_TR_SAR_IN = 10, //!< PASS[1] Triggers - pass[1].tr_sar_in
    TRIGGER_TCPWM_TR_IN7 = 11, //!< TCPWM Triggers - tcpwm.tr_in[7]
    TRIGGER_TCPWM_TR_IN8 = 12, //!< TCPWM Triggers - tcpwm.tr_in[8]
    TRIGGER_TCPWM_TR_IN9 = 13, //!< TCPWM Triggers - tcpwm.tr_in[9]
    TRIGGER_TCPWM_TR_IN10 = 14, //!< TCPWM Triggers - tcpwm.tr_in[10]
    TRIGGER_TCPWM_TR_IN11 = 15, //!< TCPWM Triggers - tcpwm.tr_in[11]
    TRIGGER_TCPWM_TR_IN12 = 16, //!< TCPWM Triggers - tcpwm.tr_in[12]
    TRIGGER_TCPWM_TR_IN13 = 17, //!< TCPWM Triggers - tcpwm.tr_in[13]
} cyhal_trigger_dest_psoc4100sp256kb_t;

/** Typedef from device family specific trigger dest to generic trigger dest */
typedef cyhal_trigger_dest_psoc4100sp256kb_t cyhal_dest_t;

/** \cond INTERNAL */
/** Maps each cyhal_destination_t to a mux index.
 * If bit 8 of the mux index is set, this denotes that the trigger is a
 * one to one trigger.
 */
extern const uint8_t cyhal_dest_to_mux[18];

/* Maps each cyhal_destination_t to a specific output in its mux */
extern const uint8_t cyhal_mux_dest_index[18];
/** \endcond */

#if defined(__cplusplus)
}
#endif /* __cplusplus */
/** \} group_hal_impl_triggers_psoc4100sp256kb */
#endif /* _CYHAL_TRIGGERS_PSOC4100SP256KB_H_ */


/* [] END OF FILE */
