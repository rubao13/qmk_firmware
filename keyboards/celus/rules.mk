OLED_ENABLE = yes
OLED_DRIVER = ssd1306
OLED_DRIVER_ENABLE = yes

OPT_DEFS += -DHAL_USE_I2C=TRUE

SRC += ./lib/logos.c \
        ./lib/wpm.c
