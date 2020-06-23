/***************************************************************************//**
* \file cyhal_triggers_psoc4100smax.h
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

#ifndef _CYHAL_TRIGGERS_PSOC4100SMAX_H_
#define _CYHAL_TRIGGERS_PSOC4100SMAX_H_

/**
 * \addtogroup group_hal_impl_triggers_psoc4100smax PSOC4100SMAX
 * \ingroup group_hal_impl_triggers
 * \{
 * Trigger connections for psoc4100smax
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/** @brief Name of each output trigger. */
typedef enum
{
    TRIGGER_CANFD_TR_DBG_DMA_ACK0 = 0, //!< DMA_Requests - canfd.tr_dbg_dma_ack[0]
    TRIGGER_CANFD_TR_EVT_SWT_IN0 = 1, //!< DMA_Requests - canfd.tr_evt_swt_in[0]
    TRIGGER_CPUSS_DMAC_TR_IN0 = 2, //!< DMA_Requests - cpuss.dmac_tr_in[0]
    TRIGGER_CPUSS_DMAC_TR_IN1 = 3, //!< DMA_Requests - cpuss.dmac_tr_in[1]
    TRIGGER_CPUSS_DMAC_TR_IN2 = 4, //!< DMA_Requests - cpuss.dmac_tr_in[2]
    TRIGGER_CPUSS_DMAC_TR_IN3 = 5, //!< DMA_Requests - cpuss.dmac_tr_in[3]
    TRIGGER_CPUSS_DMAC_TR_IN4 = 6, //!< DMA_Requests - cpuss.dmac_tr_in[4]
    TRIGGER_CPUSS_DMAC_TR_IN5 = 7, //!< DMA_Requests - cpuss.dmac_tr_in[5]
    TRIGGER_CPUSS_DMAC_TR_IN6 = 8, //!< DMA_Requests - cpuss.dmac_tr_in[6]
    TRIGGER_CPUSS_DMAC_TR_IN7 = 9, //!< DMA_Requests - cpuss.dmac_tr_in[7]
    TRIGGER_CPUSS_DMAC_TR_IN8 = 10, //!< DMA_Requests - cpuss.dmac_tr_in[8]
    TRIGGER_CPUSS_DMAC_TR_IN9 = 11, //!< DMA_Requests - cpuss.dmac_tr_in[9]
    TRIGGER_CPUSS_DMAC_TR_IN10 = 12, //!< DMA_Requests - cpuss.dmac_tr_in[10]
    TRIGGER_CPUSS_DMAC_TR_IN11 = 13, //!< DMA_Requests - cpuss.dmac_tr_in[11]
    TRIGGER_CPUSS_DMAC_TR_IN12 = 14, //!< DMA_Requests - cpuss.dmac_tr_in[12]
    TRIGGER_CPUSS_DMAC_TR_IN13 = 15, //!< DMA_Requests - cpuss.dmac_tr_in[13]
    TRIGGER_CPUSS_DMAC_TR_IN14 = 16, //!< DMA_Requests - cpuss.dmac_tr_in[14]
    TRIGGER_CPUSS_DMAC_TR_IN15 = 17, //!< DMA_Requests - cpuss.dmac_tr_in[15]
    TRIGGER_MSC0_TR_RD_REQ_IN = 18, //!< CSD Triggers - msc[0].tr_rd_req_in
    TRIGGER_MSC1_TR_RD_REQ_IN = 19, //!< CSD Triggers - msc[1].tr_rd_req_in
    TRIGGER_MSC0_TR_WR_REQ_IN = 20, //!< CSD Triggers - msc[0].tr_wr_req_in
    TRIGGER_MSC1_TR_WR_REQ_IN = 21, //!< CSD Triggers - msc[1].tr_wr_req_in
    TRIGGER_PASS_TR_SAR_IN = 22, //!< PASS Triggers - pass.tr_sar_in
    TRIGGER_TCPWM_TR_IN7 = 23, //!< TCPWM Triggers - tcpwm.tr_in[7]
    TRIGGER_TCPWM_TR_IN8 = 24, //!< TCPWM Triggers - tcpwm.tr_in[8]
    TRIGGER_TCPWM_TR_IN9 = 25, //!< TCPWM Triggers - tcpwm.tr_in[9]
    TRIGGER_TCPWM_TR_IN10 = 26, //!< TCPWM Triggers - tcpwm.tr_in[10]
    TRIGGER_TCPWM_TR_IN11 = 27, //!< TCPWM Triggers - tcpwm.tr_in[11]
    TRIGGER_TCPWM_TR_IN12 = 28, //!< TCPWM Triggers - tcpwm.tr_in[12]
    TRIGGER_TCPWM_TR_IN13 = 29, //!< TCPWM Triggers - tcpwm.tr_in[13]
} cyhal_trigger_dest_psoc4100smax_t;

/** Typedef from device family specific trigger dest to generic trigger dest */
typedef cyhal_trigger_dest_psoc4100smax_t cyhal_dest_t;

/** \cond INTERNAL */
/** Maps each cyhal_destination_t to a mux index.
 * If bit 8 of the mux index is set, this denotes that the trigger is a
 * one to one trigger.
 */
extern const uint8_t cyhal_dest_to_mux[30];

/* Maps each cyhal_destination_t to a specific output in its mux */
extern const uint8_t cyhal_mux_dest_index[30];
/** \endcond */

#if defined(__cplusplus)
}
#endif /* __cplusplus */
/** \} group_hal_impl_triggers_psoc4100smax */
#endif /* _CYHAL_TRIGGERS_PSOC4100SMAX_H_ */


/* [] END OF FILE */
