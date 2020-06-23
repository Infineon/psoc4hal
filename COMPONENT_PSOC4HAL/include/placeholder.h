/*
 * This is a placeholder file to allow builds to complete. As M0S8 implementation is filled in, items from this file
 * should be removed, until the entire file is deleted.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup group_hal_impl_dma DMA (Direct Memory Access)
 * \ingroup group_hal_impl
 * \{
 */

/** Default DMA channel priority */
#define CYHAL_DMA_PRIORITY_DEFAULT    CYHAL_DMA_PRIORITY_LOW
/** High DMA channel priority */
#define CYHAL_DMA_PRIORITY_HIGH       0
/** Medium DMA channel priority */
#define CYHAL_DMA_PRIORITY_MEDIUM     1
/** Low DMA channel priority */
#define CYHAL_DMA_PRIORITY_LOW        3

/** \} group_hal_impl_dma */


/**
 * \addtogroup group_hal_impl_pwm PWM (Pulse Width Modulator)
 * \ingroup group_hal_impl
 * \{
 * \section section_psoc6_pwm_compl_pins Complementary PWM output
 * The PWM HAL driver allows generation of a normal and an inverted output. PSoC 6 devices support complementary pin pairs to which the normal and
 * inverted signals can be routed. To identify the complementary pin for a given pin, open the PSoC 6 device datasheet and navigate to the 'Multiple Alternate Functions' table. Each
 * column represents an alternate function of the pin in the corresponding row. Find your pin and make a note of the tcpwm[X].line[Y]:Z. The
 * complementary pin is found by looking up the pin against tcpwm[X].line_<b>compl</b>[Y]:Z from the same column.
 * For example, the image below shows a pair of complementary pins (P0.0 and P0.1) identified by the tcpwm[0].line[0]:0 and tcpwm[0].line_compl[0]:0 mapping.
 * These complementary pins can be supplied to \ref cyhal_pwm_init_adv using <b>pin</b> and <b>compl_pin</b> parameters in any order.
 * \image html pwm_compl_pins.png "Complementary PWM pins"
 *
 * \} group_hal_impl_pwm
 */

#if defined(__cplusplus)
}
#endif /* __cplusplus */
