# qmk flash -kb splitkb/kyria/rev1 -km cjparsons74 -e TRACKBALL_VERSION=yes
# qmk compile -kb splitkb/halcyon/kyria/rev4 -km cjparsons74

OLED_DRIVER_ENABLE = no   # Enables the use of OLED displays
OLED_ENABLE = no
CAPS_WORD_ENABLE = yes
MOUSEKEY_ENABLE = yes
ENCODER_ENABLE = yes
EXTRAKEY_ENABLE = yes
# Check for trackball variant
ifeq ($(strip $(TRACKBALL_VERSION)), yes)
    POINTING_DEVICE_ENABLE = yes
	QUANTUM_LIB_SRC += i2c_master.c
	POINTING_DEVICE_DRIVER = pimoroni_trackball
	SRC += drivers/sensors/pimoroni_trackball.c
	OPT_DEFS += -DTRACKBALL_VERSION
endif
