/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdbool.h>

#include "platform.h"
#include "drivers/io_types.h"
#include "drivers/time.h"

#if PLATFORM_TRAIT_ADC_DEVICE
typedef enum {
    ADCINVALID = -1,
    ADCDEV_1   = 0,
#if defined(ADC2)
    ADCDEV_2,
#endif
#if defined(ADC3)
    ADCDEV_3,
#endif
#if defined(ADC4)
    ADCDEV_4,
#endif
#if defined(ADC5)
    ADCDEV_5,
#endif
    ADCDEV_COUNT
} adcDevice_e;
#endif

typedef enum {
    ADC_NONE = -1,
    ADC_BATTERY = 0,
    ADC_CURRENT = 1,
    ADC_EXTERNAL1 = 2,
    ADC_RSSI = 3,
#if defined(STM32H7) || defined(STM32G4)
    // On H7 and G4, internal sensors are treated in the similar fashion as regular ADC inputs
    ADC_CHANNEL_INTERNAL_FIRST_ID = 4,

    ADC_TEMPSENSOR = 4,
    ADC_VREFINT = 5,
    ADC_VBAT4 = 6,
#elif defined(AT32F435) || defined(CH32H415)
    ADC_CHANNEL_INTERNAL_FIRST_ID = 4,

    ADC_TEMPSENSOR = 4,
    ADC_VREFINT = 5,
    // ADC_VBAT4 = 6,

#endif
    ADC_CHANNEL_COUNT
} AdcChannel;

typedef struct adcOperatingConfig_s {
    ioTag_t tag;
#if defined(STM32H7) || defined(STM32G4) || defined(AT32F435) || defined(CH32H415)
    ADCDevice adcDevice;        // ADCDEV_x for this input
    uint32_t adcChannel;        // Channel number for this input. Note that H7 and G4 HAL requires this to be 32-bit encoded number.
#else
    ADC_SOURCE_COUNT = ADC_EXTERNAL_COUNT
#endif
} adcSource_e;

struct adcConfig_s;
void adcInit(const struct adcConfig_s *config);
uint16_t adcGetValue(adcSource_e source);

#ifdef USE_ADC_INTERNAL
bool adcInternalIsBusy(void);
void adcInternalStartConversion(void);
uint16_t adcInternalCompensateVref(uint16_t vrefAdcValue);
int16_t adcInternalComputeTemperature(uint16_t tempAdcValue, uint16_t vrefValue);
#endif
