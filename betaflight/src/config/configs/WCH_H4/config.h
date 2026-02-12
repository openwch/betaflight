/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define FC_TARGET_MCU                       CH32H415

#define BOARD_NAME                          WCH_H4
#define MANUFACTURER_ID                     WCH

// #define USE_INTERNAL_OSD
// #define V5_V3_CLOCK_RATE                    4

#define USE_ACC
#define USE_ACC_SPI_ICM42688P

#define USE_BARO
#define USE_BARO_DPS310

#define USE_OPTICALFLOW
#define USE_OPTICALFLOW_MT
#define USE_RANGEFINDER
#define USE_RANGEFINDER_MT

#define USE_GYRO
#define USE_GYRO_SPI_ICM42688P
#define USE_ACCGYRO_LSM6DSV16X
// #define USE_ACCGYRO_LSM6DSK320X   

#define USE_FLASH
#define USE_FLASH_M25P16

#define CAMERA_CONTROL_PIN                  PA4

#define USE_SDCARD
#define SDCARD_SPI_CS_PIN                   PB11

///#define USE_MAX7456
//#define MAX7456_SPI_CS_PIN                  PH2
//#define MAX7456_SPI_INSTANCE                SPI2

// #define USE_GYRO_CLKIN
// #define GYRO_1_CLKIN_PIN                    PC9

#define BEEPER_PIN                          PF4
#define MOTOR1_PIN                          PE3
#define MOTOR2_PIN                          PE4
#define MOTOR3_PIN                          PE5
#define MOTOR4_PIN                          PE6

// #define SERVO1_PIN                          PD3
// #define SERVO2_PIN                          PE11


#define LED_STRIP_PIN                       PB6

#define UART1_TX_PIN                        PA9
#define UART2_TX_PIN                        PA2
#define UART3_TX_PIN                        PA13
#define UART4_TX_PIN                        PC6
#define UART5_TX_PIN                        PE0
#define UART6_TX_PIN                        PA0
//#define UART7_TX_PIN                        PA0
#define UART8_TX_PIN                        PB4

#define UART1_RX_PIN                        PA10
#define UART2_RX_PIN                        PA3
#define UART3_RX_PIN                        PA14
#define UART4_RX_PIN                        PC7
#define UART5_RX_PIN                        PF5
#define UART6_RX_PIN                        PA1
#define UART7_RX_PIN                        PB12
#define UART8_RX_PIN                        PB3

#define I2C2_SCL_PIN                        PC0
#define I2C2_SDA_PIN                        PC1

#define LED0_PIN                            PC4

#define SPI2_SCK_PIN                        PB13
#define SPI3_SCK_PIN                        PC10
#define SPI4_SCK_PIN                        PE12

#define SPI2_SDO_PIN                        PB15
#define SPI3_SDO_PIN                        PC12
#define SPI4_SDO_PIN                        PE14

#define SPI2_SDI_PIN                        PB14
#define SPI3_SDI_PIN                        PC11
#define SPI4_SDI_PIN                        PE13

#define ADC_VBAT_PIN                        PC3
#define ADC_CURR_PIN                        PC2

#define PINIO1_PIN                          PD3
//TODO #define PINIO2_PIN                          PH3

#define FLASH_CS_PIN                        PB10
#define FLASH_SPI_INSTANCE                  SPI4

#define GYRO_1_EXTI_PIN                     PA15
#define GYRO_1_CS_PIN                       PF3
#define GYRO_1_SPI_INSTANCE                 SPI3


#define TIMER_PIN_MAPPING                   TIMER_PIN_MAP( 0, LED_STRIP_PIN, 1, 1 )  \
                                            TIMER_PIN_MAP( 1, MOTOR1_PIN, 1,  4 ) \
                                            TIMER_PIN_MAP( 2, MOTOR2_PIN, 1,  5 ) \
                                            TIMER_PIN_MAP( 3, MOTOR3_PIN, 1,  6 ) \
                                            TIMER_PIN_MAP( 4, MOTOR4_PIN, 1,  7 ) 
                                            // TIMER_PIN_MAP( 5, GYRO_1_CLKIN_PIN, 2,  -1 ) 

                                            // TIMER_PIN_MAP( 6, SERVO1_PIN, 1,  -1 ) \
                                            // TIMER_PIN_MAP( 7, SERVO2_PIN, 1,  -1 ) 

// #define USE_DMA_REGISTER_CACHE
#define DEFAULT_DSHOT_BITBANG               DSHOT_BITBANG_ON

#define ADC1_DMA_OPT                        0


#define ADC_INSTANCE                        ADC1

#define BARO_I2C_INSTANCE                   I2CDEV_2
#define MAG_I2C_INSTANCE                    I2CDEV_2

#define DEFAULT_BLACKBOX_DEVICE             BLACKBOX_DEVICE_FLASH // BLACKBOX_DEVICE_SDCARD  //BLACKBOX_DEVICE_FLASH

#define MSP_UART                            SERIAL_PORT_UART3


#define DEFAULT_CURRENT_METER_SOURCE        CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE        VOLTAGE_METER_ADC

#define BEEPER_INVERTED
#define SYSTEM_HSE_MHZ                      25


#define SERIALRX_PROVIDER   SERIALRX_CRSF
#define SERIALRX_UART       SERIAL_PORT_USART1


#define USE_LED_STRIP


#define USE_SDCARD_SPI
#define SDCARD_SPI_INSTANCE SPI2

// #define USE_SERVOS

//just for debug
// #define USE_DEBUG_PIN
// #define DEBUG_PIN_COUNT     2
// #define DEBUG_PIN0          PA9
// #define DEBUG_PIN1          PA10

