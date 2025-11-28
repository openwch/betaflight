#
# CH32H4 Make file include
#
CMSIS_DIR       :=$(ROOT)/lib/main/CH32H41x/Cmsis
STDPERIPH_DIR   = $(ROOT)/lib/main/CH32H41x/Peripheral
MIDDLEWARES_DIR = $(ROOT)/lib/main/CH32H41x/middlewares
STDPERIPH_SRC   = \
        ch32h417_adc.c \
        ch32h417_can.c \
        ch32h417_crc.c \
        ch32h417_dac.c \
        ch32h417_dbgmcu.c \
        ch32h417_dfsdm.c \
        ch32h417_dma.c \
        ch32h417_dvp.c \
        ch32h417_ecdc.c \
        ch32h417_eth.c \
        ch32h417_exti.c \
        ch32h417_flash.c \
        ch32h417_fmc.c \
        ch32h417_gpha.c \
        ch32h417_gpio.c \
        ch32h417_hsadc.c \
        ch32h417_hsem.c \
        ch32h417_i2c.c \
        ch32h417_i3c.c \
        ch32h417_ipc.c \
        ch32h417_iwdg.c \
        ch32h417_lptim.c \
        ch32h417_ltdc.c \
        ch32h417_opa.c \
        ch32h417_pwr.c  \
        ch32h417_qspi.c \
        ch32h417_rcc.c \
        ch32h417_rng.c \
        ch32h417_rtc.c \
        ch32h417_sai.c \
        ch32h417_sdio.c \
        ch32h417_sdmmc.c \
        ch32h417_serdes.c \
        ch32h417_spi.c \
        ch32h417_swpmi.c \
        ch32h417_tim.c \
        ch32h417_usart.c \
        ch32h417_wwdg.c

STARTUP_SRC     = ch32/startup_ch32h417_v5f.S

VPATH           := $(VPATH):$(ROOT)/lib/main/CH32H41x/Cmsis/Core:$(ROOT)/lib/main/CH32H41x/Cmsis/Debug:$(STDPERIPH_DIR)/src:$(STDPERIPH_DIR)/inc:$(MIDDLEWARES_DIR):$(SRC_DIR)/startup/ch32

VCP_SRC =  \
           ch32h41x_hs/usb_ch32h41x_usbhs_reg.c \
           class/cdc/usbd_cdc_acm.c \
           class/msc/usbd_msc.c \
           core/usbd_core.c \
           board/cdc_vcp_ch32h41x.c 

VCP_INCLUDES = \
        $(MIDDLEWARES_DIR)/ch32h41x_hs \
        $(MIDDLEWARES_DIR)/class/cdc \
        $(MIDDLEWARES_DIR)/common \
        $(MIDDLEWARES_DIR)/board \
        $(MIDDLEWARES_DIR)/core

DEVICE_STDPERIPH_SRC = $(STDPERIPH_SRC)

INCLUDE_DIRS    := $(INCLUDE_DIRS) \
                   $(SRC_DIR)/startup/ch32 \
                   $(SRC_DIR)/drivers \
                   $(SRC_DIR)/drivers/ch32 \
                   $(STDPERIPH_DIR)/inc \
                   $(CMSIS_DIR)/Core \
                   $(CMSIS_DIR)/Debug \
                   $(MIDDLEWARES_DIR)/class/msc \
                   $(VCP_INCLUDES)

#                    $(TARGET_PLATFORM_DIR) \
#                    $(TARGET_PLATFORM_DIR)/include \
#                    $(TARGET_PLATFORM_DIR)/startup \
#                    $(PLATFORM_DIR)/common/stm32 \
                   

LD_SCRIPT       = $(LINKER_DIR)/ch32h41x_v5f.ld

############################################################################
ARCH_FLAGS      = -std=c99 -march=rv32imafc_zba_zbb_zbc_zbs_xw -mabi=ilp32f -msmall-data-limit=8 -msave-restore -fmessage-length=0 -fmax-errors=5 -fsigned-char -fsingle-precision-constant -Wunused -Wuninitialized -lprintfloat -g
DEVICE_FLAGS    += -DUSE_CHBSP_DRIVER -DCH32H415 -DCH32H41x -DHSE_VALUE=$(HSE_VALUE) -DCH32 -DUSE_OTG_HOST_MODE

MCU_COMMON_SRC = \
        $(addprefix startup/ch32/,$(notdir $(wildcard $(SRC_DIR)/startup/ch32/*.c))) \
        $(addprefix drivers/ch32/,$(notdir $(wildcard $(SRC_DIR)/drivers/ch32/*.c))) \
        drivers/accgyro/accgyro_mpu.c \
        drivers/dshot_bitbang_decode.c \
        drivers/inverter.c \
        drivers/pwm_output_dshot_shared.c \
        drivers/bus_i2c_timing.c \
        drivers/usb_msc_common.c \
        msc/usbd_storage.c \
        msc/usbd_storage_emfat.c \
        msc/emfat.c \
        msc/emfat_file.c \
        drivers/usb_io.c

MCU_EXCLUDES =

#         \
#         msc/usbd_storage_sd_spi.c


# SPEED_OPTIMISED_SRC += \
#             common/stm32/system.c \
#             CH32/exti_ch32.c \
#             common/stm32/bus_spi_hw.c \
#             common/stm32/pwm_output_dshot_shared.c \
#             common/stm32/dshot_bitbang_shared.c \
#             common/stm32/io_impl.c


# SIZE_OPTIMISED_SRC += \
#             drivers/bus_i2c_timing.c \
#             drivers/inverter.c \
#             drivers/bus_spi_config.c \
#             common/stm32/bus_i2c_pinconfig.c \
#             common/stm32/bus_spi_pinconfig.c \
#             drivers/serial_escserial.c \
#             drivers/serial_pinconfig.c \
#             drivers/serial_uart_pinconfig.c
