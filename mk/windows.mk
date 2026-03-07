# windows.mk
#
# Goals:
#   Configure an environment that will allow Taulabs GCS and firmware to be built
#   on a Windows system. The environment will support the current version of the
#   ARM toolchain installed to either their respective default installation
#   locations, the tools directory or made available on the system path.
#
# Requirements:
#   msysGit
#   Python

FIND_TARGET_MCU_VALUE = $(word 3,$(shell findstr 'TARGET_MCU' src/config/configs/$(1)/config.h))
PYTHON := python
export PYTHON
