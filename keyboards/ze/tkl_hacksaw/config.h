#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5A45
#define PRODUCT_ID      0x1000
#define DEVICE_VER      0x0001
#define MANUFACTURER    Ze
#define PRODUCT         TKL Hacksaw

/* key matrix size */
#define MATRIX_MUX_ROWS 5
#define MATRIX_COLS 8
#define MATRIX_ROWS 13

/*  #define MATRIX_ROW_PINS { D3, D2, B7, F1, C7, D5 } */
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7 }
#define MATRIX_ROW_MUX_PINS { B8, B7, B6, B5, B4}
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define LED_NUM_LOCK_PIN B0
#define LED_CAPS_LOCK_PIN B1
#define LED_SCROLL_LOCK_PIN C15
#define LED_PIN_ON_STATE 1

#define BACKLIGHT_PIN B9
#define BACKLIGHT_LEVELS 5
#define BACKLIGHT_PWM_DRIVER PWMD4
#define BACKLIGHT_BREATHING

