/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for STMicroelectronics NUCLEO-F030R8 board.
 */

/*
 * Board identifier.
 */
#define BOARD_ST_NUCLEO_F030R8
#define BOARD_NAME                  "STMicroelectronics NUCLEO-F030R8"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 * NOTE: HSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0
#endif

#define STM32_LSEDRV                (3 << 3)

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                0
#endif

#define STM32_HSE_BYPASS

/*
 * MCU type as defined in the ST header.
 */
#define STM32F030

/*
 * IO pins assignments.
 */
#define GPIOA_ENC_WOL			0
#define GPIOA_ENC_INT			1
#define GPIOA_ENC_RST			2
#define GPIOA_PIN3				3
#define GPIOA_ENC_CS			4
#define GPIOA_ENC_SCK			5
#define GPIOA_ENC_MISO			6
#define GPIOA_LED_PRG			7
#define GPIOA_PIN8				8
#define GPIOA_USART1_TX			9
#define GPIOA_USART1_RX			10
#define GPIOA_PIN11				11
#define GPIOA_PIN12				12
#define GPIOA_SWDIO				13
#define GPIOA_SWCLK				14
#define GPIOA_HEAT_TOP			15

#define GPIOB_LED_HEAT			0
#define GPIOB_LED_SYS			1
#define GPIOB_LM75_OVER			2
#define GPIOB_HEAT_BOT			3
#define GPIOB_PIN4				4
#define GPIOB_ENC_MOSI			5
#define GPIOB_PIN6				6
#define GPIOB_PIN7				7
#define GPIOB_PIN8				8
#define GPIOB_PIN9				9
#define GPIOB_LM75_SCL			10
#define GPIOB_LM75_SDA			11
#define GPIOB_MAX_CS			12
#define GPIOB_MAX_SCK			13
#define GPIOB_MAX_MISO			14
#define GPIOB_PIN15				15

#define GPIOC_PIN0				0
#define GPIOC_PIN1				1
#define GPIOC_PIN2				2
#define GPIOC_PIN3				3
#define GPIOC_PIN4				4
#define GPIOC_PIN5				5
#define GPIOC_PIN6				6
#define GPIOC_PIN7				7
#define GPIOC_PIN8				8
#define GPIOC_PIN9				9
#define GPIOC_PIN10				10
#define GPIOC_PIN11				11
#define GPIOC_PIN12				12
#define GPIOC_PIN13				13
#define GPIOC_PIN14				14
#define GPIOC_PIN15				15

#define GPIOD_PIN0				0
#define GPIOD_PIN1				1
#define GPIOD_PIN2				2
#define GPIOD_PIN3				3
#define GPIOD_PIN4				4
#define GPIOD_PIN5				5
#define GPIOD_PIN6				6
#define GPIOD_PIN7				7
#define GPIOD_PIN8				8
#define GPIOD_PIN9				9
#define GPIOD_PIN10				10
#define GPIOD_PIN11				11
#define GPIOD_PIN12				12
#define GPIOD_PIN13				13
#define GPIOD_PIN14				14
#define GPIOD_PIN15				15

#define GPIOF_OSC_IN			0
#define GPIOF_OSC_OUT			1
#define GPIOF_PIN2				2
#define GPIOF_PIN3				3
#define GPIOF_PIN4				4
#define GPIOF_PIN5				5
#define GPIOF_PIN6				6
#define GPIOF_PIN7				7
#define GPIOF_PIN8				8
#define GPIOF_PIN9				9
#define GPIOF_PIN10				10
#define GPIOF_PIN11				11
#define GPIOF_PIN12				12
#define GPIOF_PIN13				13
#define GPIOF_PIN14				14
#define GPIOF_PIN15				15

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_2M(n)            (0U << ((n) * 2))
#define PIN_OSPEED_10M(n)           (1U << ((n) * 2))
#define PIN_OSPEED_40M(n)           (3U << ((n) * 2))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2))
#define PIN_AFIO_AF(n, v)           ((v##U) << ((n % 8) * 4))

/* GPIOA */
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_ENC_WOL) |           \
                                     PIN_MODE_INPUT(GPIOA_ENC_INT) |           \
                                     PIN_MODE_OUTPUT(GPIOA_ENC_RST) |   \
                                     PIN_MODE_INPUT(GPIOA_PIN3) |   \
                                     PIN_MODE_OUTPUT(GPIOA_ENC_CS) |           \
                                     PIN_MODE_ALTERNATE(GPIOA_ENC_SCK) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_ENC_MISO) |           \
                                     PIN_MODE_OUTPUT(GPIOA_LED_PRG) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN8) |           \
                                     PIN_MODE_ALTERNATE(GPIOA_USART1_TX) |           \
                                     PIN_MODE_ALTERNATE(GPIOA_USART1_RX) |          \
                                     PIN_MODE_INPUT(GPIOA_PIN11) |  \
                                     PIN_MODE_INPUT(GPIOA_PIN12) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_OUTPUT(GPIOA_HEAT_TOP))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_ENC_WOL) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ENC_INT) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ENC_RST) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN3) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ENC_CS) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ENC_SCK) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ENC_MISO) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_LED_PRG) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USART1_TX) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USART1_RX) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN11) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN12) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_OPENDRAIN(GPIOA_HEAT_TOP))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_40M(GPIOA_ENC_WOL) |           \
                                     PIN_OSPEED_40M(GPIOA_ENC_INT) |           \
                                     PIN_OSPEED_10M(GPIOA_ENC_RST) |       \
                                     PIN_OSPEED_10M(GPIOA_PIN3) |       \
                                     PIN_OSPEED_40M(GPIOA_ENC_CS) |           \
                                     PIN_OSPEED_10M(GPIOA_ENC_SCK) |      \
                                     PIN_OSPEED_40M(GPIOA_ENC_MISO) |           \
                                     PIN_OSPEED_40M(GPIOA_LED_PRG) |           \
                                     PIN_OSPEED_40M(GPIOA_PIN8) |           \
                                     PIN_OSPEED_40M(GPIOA_USART1_TX) |           \
                                     PIN_OSPEED_40M(GPIOA_USART1_RX) |          \
                                     PIN_OSPEED_40M(GPIOA_PIN11) |      \
                                     PIN_OSPEED_40M(GPIOA_PIN12) |      \
                                     PIN_OSPEED_40M(GPIOA_SWDIO) |          \
                                     PIN_OSPEED_40M(GPIOA_SWCLK) |          \
                                     PIN_OSPEED_2M(GPIOA_HEAT_TOP))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_ENC_WOL) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_ENC_INT) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_ENC_RST) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN3) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_ENC_CS) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_ENC_SCK) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_ENC_MISO) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_LED_PRG) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_USART1_TX) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_USART1_RX) |        \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN11) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN12) |  \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_HEAT_TOP))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_ENC_WOL) |             \
                                     PIN_ODR_HIGH(GPIOA_ENC_INT) |             \
                                     PIN_ODR_HIGH(GPIOA_ENC_RST) |         \
                                     PIN_ODR_HIGH(GPIOA_PIN3) |         \
                                     PIN_ODR_HIGH(GPIOA_ENC_CS) |             \
                                     PIN_ODR_HIGH(GPIOA_ENC_SCK) |         \
                                     PIN_ODR_HIGH(GPIOA_ENC_MISO) |             \
                                     PIN_ODR_LOW(GPIOA_LED_PRG) |             \
                                     PIN_ODR_HIGH(GPIOA_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOA_USART1_TX) |             \
                                     PIN_ODR_HIGH(GPIOA_USART1_RX) |            \
                                     PIN_ODR_HIGH(GPIOA_PIN11) |        \
                                     PIN_ODR_HIGH(GPIOA_PIN12) |        \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_HEAT_TOP))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_ENC_WOL, 0) |           \
                                     PIN_AFIO_AF(GPIOA_ENC_INT, 0) |           \
                                     PIN_AFIO_AF(GPIOA_ENC_RST, 0) |       \
                                     PIN_AFIO_AF(GPIOA_PIN3, 0) |       \
                                     PIN_AFIO_AF(GPIOA_ENC_CS, 0) |           \
                                     PIN_AFIO_AF(GPIOA_ENC_SCK, 0) |      \
                                     PIN_AFIO_AF(GPIOA_ENC_MISO, 0) |           \
                                     PIN_AFIO_AF(GPIOA_LED_PRG, 0))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOA_USART1_TX, 1) |           \
                                     PIN_AFIO_AF(GPIOA_USART1_RX, 1) |          \
                                     PIN_AFIO_AF(GPIOA_PIN11, 0) |     \
                                     PIN_AFIO_AF(GPIOA_PIN12, 0) |     \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0) |          \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0) |          \
                                     PIN_AFIO_AF(GPIOA_HEAT_TOP, 0))

/* GPIOB */
#define VAL_GPIOB_MODER             (PIN_MODE_OUTPUT(GPIOB_LED_HEAT) |           \
                                     PIN_MODE_OUTPUT(GPIOB_LED_SYS) |           \
                                     PIN_MODE_INPUT(GPIOB_LM75_OVER) |           \
                                     PIN_MODE_OUTPUT(GPIOB_HEAT_BOT) |        \
                                     PIN_MODE_INPUT(GPIOB_PIN4) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_ENC_MOSI) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN9) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_LM75_SCL) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_LM75_SDA) |          \
                                     PIN_MODE_OUTPUT(GPIOB_MAX_CS) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_MAX_SCK) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_MAX_MISO) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN15))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_LED_HEAT) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LED_SYS) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LM75_OVER) |       \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_HEAT_BOT) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ENC_MOSI) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN9) |       \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_LM75_SCL) |      \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_LM75_SDA) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_MAX_CS) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_MAX_SCK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_MAX_MISO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN15))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_40M(GPIOB_LED_HEAT) |           \
                                     PIN_OSPEED_2M(GPIOB_LED_SYS) |           \
                                     PIN_OSPEED_40M(GPIOB_LM75_OVER) |           \
                                     PIN_OSPEED_2M(GPIOB_HEAT_BOT) |            \
                                     PIN_OSPEED_40M(GPIOB_PIN4) |           \
                                     PIN_OSPEED_40M(GPIOB_ENC_MOSI) |           \
                                     PIN_OSPEED_40M(GPIOB_PIN6) |           \
                                     PIN_OSPEED_40M(GPIOB_PIN7) |           \
                                     PIN_OSPEED_40M(GPIOB_PIN8) |           \
                                     PIN_OSPEED_40M(GPIOB_PIN9) |           \
                                     PIN_OSPEED_40M(GPIOB_LM75_SCL) |          \
                                     PIN_OSPEED_40M(GPIOB_LM75_SDA) |          \
                                     PIN_OSPEED_40M(GPIOB_MAX_CS) |          \
                                     PIN_OSPEED_40M(GPIOB_MAX_SCK) |          \
                                     PIN_OSPEED_40M(GPIOB_MAX_MISO) |          \
                                     PIN_OSPEED_40M(GPIOB_PIN15))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(GPIOB_LED_HEAT) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_LED_SYS) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_LM75_OVER) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_HEAT_BOT) |          \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN4) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_ENC_MOSI) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN9) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_LM75_SCL) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_LM75_SDA) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_MAX_CS) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_MAX_SCK) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_MAX_MISO) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN15))
#define VAL_GPIOB_ODR               (PIN_ODR_LOW(GPIOB_LED_HEAT) |             \
                                     PIN_ODR_LOW(GPIOB_LED_SYS) |             \
                                     PIN_ODR_HIGH(GPIOB_LM75_OVER) |             \
                                     PIN_ODR_HIGH(GPIOB_HEAT_BOT) |              \
                                     PIN_ODR_HIGH(GPIOB_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOB_ENC_MOSI) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOB_LM75_SCL) |            \
                                     PIN_ODR_HIGH(GPIOB_LM75_SDA) |            \
                                     PIN_ODR_HIGH(GPIOB_MAX_CS) |            \
                                     PIN_ODR_HIGH(GPIOB_MAX_SCK) |            \
                                     PIN_ODR_HIGH(GPIOB_MAX_MISO) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN15))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_LED_HEAT, 0) |           \
                                     PIN_AFIO_AF(GPIOB_LED_SYS, 0) |           \
                                     PIN_AFIO_AF(GPIOB_LM75_OVER, 0) |           \
                                     PIN_AFIO_AF(GPIOB_HEAT_BOT, 0) |            \
                                     PIN_AFIO_AF(GPIOB_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOB_ENC_MOSI, 0) |           \
                                     PIN_AFIO_AF(GPIOB_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOB_PIN7, 0))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOB_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOB_LM75_SCL, 1) |          \
                                     PIN_AFIO_AF(GPIOB_LM75_SDA, 1) |          \
                                     PIN_AFIO_AF(GPIOB_MAX_CS, 0) |          \
                                     PIN_AFIO_AF(GPIOB_MAX_SCK, 0) |          \
                                     PIN_AFIO_AF(GPIOB_MAX_MISO, 0) |          \
                                     PIN_AFIO_AF(GPIOB_PIN15, 0))

/* GPIOC */
#define VAL_GPIOC_MODER             (PIN_MODE_INPUT(GPIOC_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN13) |         \
                                     PIN_MODE_INPUT(GPIOC_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN15))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN15))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_40M(GPIOC_PIN0) |           \
                                     PIN_OSPEED_40M(GPIOC_PIN1) |           \
                                     PIN_OSPEED_40M(GPIOC_PIN2) |           \
                                     PIN_OSPEED_40M(GPIOC_PIN3) |           \
                                     PIN_OSPEED_40M(GPIOC_PIN4) |           \
                                     PIN_OSPEED_40M(GPIOC_PIN5) |           \
                                     PIN_OSPEED_40M(GPIOC_PIN6) |           \
                                     PIN_OSPEED_40M(GPIOC_PIN7) |           \
                                     PIN_OSPEED_40M(GPIOC_PIN8) |           \
                                     PIN_OSPEED_40M(GPIOC_PIN9) |           \
                                     PIN_OSPEED_40M(GPIOC_PIN10) |          \
                                     PIN_OSPEED_40M(GPIOC_PIN11) |          \
                                     PIN_OSPEED_40M(GPIOC_PIN12) |          \
                                     PIN_OSPEED_40M(GPIOC_PIN13) |         \
                                     PIN_OSPEED_40M(GPIOC_PIN14) |          \
                                     PIN_OSPEED_40M(GPIOC_PIN15))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLUP(GPIOC_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN12) |        \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN13) |     \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN15))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN13) |           \
                                     PIN_ODR_HIGH(GPIOC_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN15))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN7, 0))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOC_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOC_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOC_PIN13, 0) |         \
                                     PIN_AFIO_AF(GPIOC_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOC_PIN15, 0))
/* GPIOD */
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_40M(GPIOD_PIN0) |           \
                                     PIN_OSPEED_40M(GPIOD_PIN1) |           \
                                     PIN_OSPEED_40M(GPIOD_PIN2) |           \
                                     PIN_OSPEED_40M(GPIOD_PIN3) |           \
                                     PIN_OSPEED_40M(GPIOD_PIN4) |           \
                                     PIN_OSPEED_40M(GPIOD_PIN5) |           \
                                     PIN_OSPEED_40M(GPIOD_PIN6) |           \
                                     PIN_OSPEED_40M(GPIOD_PIN7) |           \
                                     PIN_OSPEED_40M(GPIOD_PIN8) |           \
                                     PIN_OSPEED_40M(GPIOD_PIN9) |           \
                                     PIN_OSPEED_40M(GPIOD_PIN10) |          \
                                     PIN_OSPEED_40M(GPIOD_PIN11) |          \
                                     PIN_OSPEED_40M(GPIOD_PIN12) |          \
                                     PIN_OSPEED_40M(GPIOD_PIN13) |          \
                                     PIN_OSPEED_40M(GPIOD_PIN14) |          \
                                     PIN_OSPEED_40M(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLUP(GPIOD_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN15, 0))
/* GPIOF */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOF_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOF_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN15))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN15))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_2M(GPIOF_OSC_IN) |          \
                                     PIN_OSPEED_2M(GPIOF_OSC_OUT) |         \
                                     PIN_OSPEED_2M(GPIOF_PIN2) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN3) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN4) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN5) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN6) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN7) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN8) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN9) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN10) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN11) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN12) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN13) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN14) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN15))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_OSC_OUT) |    \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN15))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOF_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOF_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_OSC_IN, 0) |         \
                                     PIN_AFIO_AF(GPIOF_OSC_OUT, 0) |        \
                                     PIN_AFIO_AF(GPIOF_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN7, 0))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN15, 0))

#endif
