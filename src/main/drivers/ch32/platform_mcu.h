/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Betaflight is distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */
/*
 * porting for ch32h41x by Temperslee
 */
#pragma once

#if defined(CH32H415)


#include "ch32h417.h"
#include "ch32_debug.h"


// Chip Unique ID on H41X
#define U_ID_0 (*(uint32_t*)0x1ffff7e8)
#define U_ID_1 (*(uint32_t*)0x1ffff7ec)
#define U_ID_2 (*(uint32_t*)0x1ffff7f0)

// #define FLASH_CONFIG_STREAMER_BUFFER_SIZE   256     // fast program is 256bytes
// #define FLASH_CONFIG_BUFFER_TYPE            uint32_t

#define __FAST_INTERRUPT       __attribute__((interrupt("WCH-Interrupt-fast")))


#ifndef CH32H4
#define CH32H4
#endif

// #define SPI_TRAIT_AF_PIN 1
// #define I2C_TRAIT_AF_PIN 1
// #define I2C_TRAIT_STATE 1

#define USE_PIN_AF


#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#endif


#ifdef CH32H4

#define USE_ITCM_RAM
#define ITCM_RAM_OPTIMISATION "-O2", "-freorder-blocks-algorithm=simple"
#define USE_FAST_DATA
#define USE_RPM_FILTER
#define USE_DYN_IDLE
#define USE_DYN_NOTCH_FILTER
// #define USE_OVERCLOCK
#define USE_ADC_INTERNAL
#define ADC_VOLTAGE_REFERENCE_MV  3300  //maybe better  cali internal
#define USE_USB_MSC
#define USE_PERSISTENT_MSC_RTC
// #define USE_MCO
#define USE_DMA_SPEC
#define USE_PERSISTENT_OBJECTS
#define USE_LATE_TASK_STATISTICS

#endif

#define TASK_GYROPID_DESIRED_PERIOD     1000 // 1000us = 1kHz
#define SCHEDULER_DELAY_LIMIT           100

#define DEFAULT_CPU_OVERCLOCK 0

#ifdef CH32H4
// Move ISRs to fast ram to avoid flash latency.
#define FAST_IRQ_HANDLER FAST_CODE 
#else 
#define FAST_IRQ_HANDLER  
#endif

//load all data to DTCM
#define DMA_DATA_ZERO_INIT __attribute__((aligned(32)))
#define DMA_DATA   __attribute__((aligned(32)))
#define STATIC_DMA_DATA_AUTO      __attribute__((aligned(32)))  static

#define DMA_RAM      __attribute__((aligned(32)))
#define DMA_RW_AXI  
#define DMA_RAM_R
#define DMA_RAM_W
#define DMA_RAM_RW
//--------------------------

#define USE_TIMER_MGMT
#define USE_TIMER_AF


#if defined(CH32H4)
 
// #define USE_TX_IRQ_HANDLER  


// #define PLATFORM_TRAIT_RCC      1
// #define UART_TRAIT_AF_PIN       1
// #define UART_TRAIT_PINSWAP      1
// #define SERIAL_TRAIT_PIN_CONFIG 1
// #define I2C_TRAIT_AF_PIN        1

// #define I2CDEV_COUNT            4

// #define I2C_TRAIT_HANDLE        1

// #define SPI_TRAIT_AF_PIN        1
// #define UARTHARDWARE_MAX_PINS   5

// #define UART_REG_RXD(base) ((base)->DATAR)
// #define UART_REG_TXD(base) ((base)->DATAR)

// #define DMA_TRAIT_MUX 1

// #define DMA_TRAIT_CHANNEL 1

// #define MAX_MSP_PORT_COUNT 4  //default msp count is 3, it would not be enough for us

#endif

#define FLASH_CONFIG_BUFFER_TYPE      uint32_t
#define USB_DP_PIN PB8
