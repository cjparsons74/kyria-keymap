OLED_DRIVER_ENABLE = no   # Enables the use of OLED displays
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow
CAPS_WORD_ENABLE = yes
QUANTUM_LIB_SRC += i2c_master.c
ifeq ($(DEBUG), yes)
	MOUSEKEY_ENABLE = no
	ENCODER_ENABLE = no
	CONSOLE_ENABLE = yes
	EXTRAKEY_ENABLE = no
else
	MOUSEKEY_ENABLE = yes
	ENCODER_ENABLE = yes
	CONSOLE_ENABLE = no
	EXTRAKEY_ENABLE = yes
endif
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pimoroni_trackball
SRC += drivers/sensors/pimoroni_trackball.c
QUANTUM_LIB_SRC += i2c_master.c
DEFERRED_EXEC_ENABLE = yes
