OLED_DRIVER_ENABLE = no   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow
QUANTUM_LIB_SRC += i2c_master.c
MOUSEKEY_ENABLE = no
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pimoroni_trackball
SRC += drivers/sensors/pimoroni_trackball.c
QUANTUM_LIB_SRC += i2c_master.c
