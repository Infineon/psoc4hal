/***************************************************************************//**
* \file cyhal_psoc4000s_32_qfn.h
*
* \brief
* PSoC4000S device GPIO HAL header for 32-QFN package
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

#ifndef _CYHAL_PSOC4000S_32_QFN_H_
#define _CYHAL_PSOC4000S_32_QFN_H_

#include "cyhal_hw_resources.h"

/**
 * \addtogroup group_hal_impl_pin_package_psoc4000s_32_qfn PSoC4000S 32-QFN
 * \ingroup group_hal_impl_pin_package
 * \{
 * Pin definitions and connections specific to the PSoC4000S 32-QFN package.
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

/** Definitions for all of the pins that are bonded out on in the 32-QFN package for the PSoC4000S series. */
typedef enum {
    NC = 0xFF, //!< No Connect/Invalid Pin

    P0_0 = CYHAL_GET_GPIO(CYHAL_PORT_0, 0), //!< Port 0 Pin 0
    P0_1 = CYHAL_GET_GPIO(CYHAL_PORT_0, 1), //!< Port 0 Pin 1
    P0_2 = CYHAL_GET_GPIO(CYHAL_PORT_0, 2), //!< Port 0 Pin 2
    P0_3 = CYHAL_GET_GPIO(CYHAL_PORT_0, 3), //!< Port 0 Pin 3
    P0_4 = CYHAL_GET_GPIO(CYHAL_PORT_0, 4), //!< Port 0 Pin 4
    P0_5 = CYHAL_GET_GPIO(CYHAL_PORT_0, 5), //!< Port 0 Pin 5
    P0_6 = CYHAL_GET_GPIO(CYHAL_PORT_0, 6), //!< Port 0 Pin 6

    P1_0 = CYHAL_GET_GPIO(CYHAL_PORT_1, 0), //!< Port 1 Pin 0
    P1_1 = CYHAL_GET_GPIO(CYHAL_PORT_1, 1), //!< Port 1 Pin 1
    P1_2 = CYHAL_GET_GPIO(CYHAL_PORT_1, 2), //!< Port 1 Pin 2
    P1_3 = CYHAL_GET_GPIO(CYHAL_PORT_1, 3), //!< Port 1 Pin 3
    P1_7 = CYHAL_GET_GPIO(CYHAL_PORT_1, 7), //!< Port 1 Pin 7

    P2_0 = CYHAL_GET_GPIO(CYHAL_PORT_2, 0), //!< Port 2 Pin 0
    P2_1 = CYHAL_GET_GPIO(CYHAL_PORT_2, 1), //!< Port 2 Pin 1
    P2_2 = CYHAL_GET_GPIO(CYHAL_PORT_2, 2), //!< Port 2 Pin 2
    P2_3 = CYHAL_GET_GPIO(CYHAL_PORT_2, 3), //!< Port 2 Pin 3
    P2_5 = CYHAL_GET_GPIO(CYHAL_PORT_2, 5), //!< Port 2 Pin 5
    P2_6 = CYHAL_GET_GPIO(CYHAL_PORT_2, 6), //!< Port 2 Pin 6
    P2_7 = CYHAL_GET_GPIO(CYHAL_PORT_2, 7), //!< Port 2 Pin 7

    P3_0 = CYHAL_GET_GPIO(CYHAL_PORT_3, 0), //!< Port 3 Pin 0
    P3_1 = CYHAL_GET_GPIO(CYHAL_PORT_3, 1), //!< Port 3 Pin 1
    P3_2 = CYHAL_GET_GPIO(CYHAL_PORT_3, 2), //!< Port 3 Pin 2
    P3_3 = CYHAL_GET_GPIO(CYHAL_PORT_3, 3), //!< Port 3 Pin 3

    P4_0 = CYHAL_GET_GPIO(CYHAL_PORT_4, 0), //!< Port 4 Pin 0
    P4_1 = CYHAL_GET_GPIO(CYHAL_PORT_4, 1), //!< Port 4 Pin 1
    P4_2 = CYHAL_GET_GPIO(CYHAL_PORT_4, 2), //!< Port 4 Pin 2
    P4_3 = CYHAL_GET_GPIO(CYHAL_PORT_4, 3), //!< Port 4 Pin 3
} cyhal_gpio_psoc4000s_32_qfn_t;

/** Create generic name for the series/package specific type. */
typedef cyhal_gpio_psoc4000s_32_qfn_t cyhal_gpio_t;

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
/** Indicates that a pin map exists for lpcomp_comp*/
#define CYHAL_PIN_MAP_LPCOMP_COMP
/** List of valid pin to peripheral connections for the lpcomp_comp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_comp[3];
/** Indicates that a pin map exists for lpcomp_in_n*/
#define CYHAL_PIN_MAP_LPCOMP_IN_N
/** List of valid pin to peripheral connections for the lpcomp_in_n signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_in_n[2];
/** Indicates that a pin map exists for lpcomp_in_p*/
#define CYHAL_PIN_MAP_LPCOMP_IN_P
/** List of valid pin to peripheral connections for the lpcomp_in_p signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_in_p[2];
/** Indicates that a pin map exists for scb_i2c_scl*/
#define CYHAL_PIN_MAP_SCB_I2C_SCL
/** List of valid pin to peripheral connections for the scb_i2c_scl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[5];
/** Indicates that a pin map exists for scb_i2c_sda*/
#define CYHAL_PIN_MAP_SCB_I2C_SDA
/** List of valid pin to peripheral connections for the scb_i2c_sda signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[5];
/** Indicates that a pin map exists for scb_spi_m_clk*/
#define CYHAL_PIN_MAP_SCB_SPI_M_CLK
/** List of valid pin to peripheral connections for the scb_spi_m_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[5];
/** Indicates that a pin map exists for scb_spi_m_miso*/
#define CYHAL_PIN_MAP_SCB_SPI_M_MISO
/** List of valid pin to peripheral connections for the scb_spi_m_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[5];
/** Indicates that a pin map exists for scb_spi_m_mosi*/
#define CYHAL_PIN_MAP_SCB_SPI_M_MOSI
/** List of valid pin to peripheral connections for the scb_spi_m_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[5];
/** Indicates that a pin map exists for scb_spi_m_select0*/
#define CYHAL_PIN_MAP_SCB_SPI_M_SELECT0
/** List of valid pin to peripheral connections for the scb_spi_m_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[4];
/** Indicates that a pin map exists for scb_spi_m_select1*/
#define CYHAL_PIN_MAP_SCB_SPI_M_SELECT1
/** List of valid pin to peripheral connections for the scb_spi_m_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select1[1];
/** Indicates that a pin map exists for scb_spi_m_select2*/
#define CYHAL_PIN_MAP_SCB_SPI_M_SELECT2
/** List of valid pin to peripheral connections for the scb_spi_m_select2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select2[2];
/** Indicates that a pin map exists for scb_spi_m_select3*/
#define CYHAL_PIN_MAP_SCB_SPI_M_SELECT3
/** List of valid pin to peripheral connections for the scb_spi_m_select3 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select3[2];
/** Indicates that a pin map exists for scb_spi_s_clk*/
#define CYHAL_PIN_MAP_SCB_SPI_S_CLK
/** List of valid pin to peripheral connections for the scb_spi_s_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[5];
/** Indicates that a pin map exists for scb_spi_s_miso*/
#define CYHAL_PIN_MAP_SCB_SPI_S_MISO
/** List of valid pin to peripheral connections for the scb_spi_s_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[5];
/** Indicates that a pin map exists for scb_spi_s_mosi*/
#define CYHAL_PIN_MAP_SCB_SPI_S_MOSI
/** List of valid pin to peripheral connections for the scb_spi_s_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[5];
/** Indicates that a pin map exists for scb_spi_s_select0*/
#define CYHAL_PIN_MAP_SCB_SPI_S_SELECT0
/** List of valid pin to peripheral connections for the scb_spi_s_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[4];
/** Indicates that a pin map exists for scb_spi_s_select1*/
#define CYHAL_PIN_MAP_SCB_SPI_S_SELECT1
/** List of valid pin to peripheral connections for the scb_spi_s_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select1[1];
/** Indicates that a pin map exists for scb_spi_s_select2*/
#define CYHAL_PIN_MAP_SCB_SPI_S_SELECT2
/** List of valid pin to peripheral connections for the scb_spi_s_select2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select2[2];
/** Indicates that a pin map exists for scb_spi_s_select3*/
#define CYHAL_PIN_MAP_SCB_SPI_S_SELECT3
/** List of valid pin to peripheral connections for the scb_spi_s_select3 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select3[2];
/** Indicates that a pin map exists for scb_uart_cts*/
#define CYHAL_PIN_MAP_SCB_UART_CTS
/** List of valid pin to peripheral connections for the scb_uart_cts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[4];
/** Indicates that a pin map exists for scb_uart_rts*/
#define CYHAL_PIN_MAP_SCB_UART_RTS
/** List of valid pin to peripheral connections for the scb_uart_rts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[3];
/** Indicates that a pin map exists for scb_uart_rx*/
#define CYHAL_PIN_MAP_SCB_UART_RX
/** List of valid pin to peripheral connections for the scb_uart_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[4];
/** Indicates that a pin map exists for scb_uart_tx*/
#define CYHAL_PIN_MAP_SCB_UART_TX
/** List of valid pin to peripheral connections for the scb_uart_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[4];
/** Indicates that a pin map exists for tcpwm_line*/
#define CYHAL_PIN_MAP_TCPWM_LINE
/** List of valid pin to peripheral connections for the tcpwm_line signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[6];
/** Indicates that a pin map exists for tcpwm_line_compl*/
#define CYHAL_PIN_MAP_TCPWM_LINE_COMPL
/** List of valid pin to peripheral connections for the tcpwm_line_compl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line_compl[7];
/** Indicates that a pin map exists for tcpwm_tr_in*/
#define CYHAL_PIN_MAP_TCPWM_TR_IN
/** List of valid pin to peripheral connections for the tcpwm_tr_in signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_in[8];

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl_pin_package */

#endif /* _CYHAL_PSOC4000S_32_QFN_H_ */


/* [] END OF FILE */
