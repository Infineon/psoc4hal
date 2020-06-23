# PSoC 4 Hardware Abstraction Layer (HAL) Release Notes
The PSoC 4 Hardware Abstraction Layer (HAL) provides an implementation of the Hardware Abstraction Layer for the PSoC 4 family of chips. This API provides convenience methods for initializing and manipulating different hardware peripherals. Depending on the specific chip being used, not all features may be supported.

### What's Included?
This release of the PSoC 4 HAL includes support for the following drivers:
* Clock
* EZ-I2C
* GPIO
* Hardware Manager
* I2C
* PWM
* SPI
* System
* Timer
* UART
* WDT
The following HAL drivers are planned for a future release:
* ADC
* CRC
* DMA
* Flash
* I2S
* LowPower Timer (LPTimer)
* Power Management (SysPM)
* True Random Number Generator (TRNG)
The following HAL drivers are not supported on PSoC 4 as there is no hardware support:
* DAC
* PDM/PCM
* QSPI
* RTC
* SDHC
* SDIO
* USB Device

### What Changed?
#### v0.5.0
* Initial pre-production release (Clock, EZ-I2C, GPIO, Hardware Manager, I2C, PWM, SPI, System, Timer, UART, WDT)

### Supported Software and Tools
This version of the PSoC 4 Hardware Abstraction Layer was validated for compatibility with the following Software and Tools:

| Software and Tools                        | Version |
| :---                                      | :----:  |
| ModusToolbox Software Environment         | 2.0     |
| GCC Compiler                              | 7.4     |
| IAR Compiler                              | 8.32    |
| ARM Compiler                              | 6.11    |

### More information
Use the following links for more information, as needed:
* [API Reference Guide](https://cypresssemiconductorco.github.io/psoc4hal/html/modules.html)
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [Cypress Semiconductor GitHub](https://github.com/cypresssemiconductorco)
* [ModusToolbox](https://www.cypress.com/products/modustoolbox-software-environment)

---
© Cypress Semiconductor Corporation, 2019-2020.