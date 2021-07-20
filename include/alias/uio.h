#ifndef _ALIAS_UIO_H_
#define _ALIAS_UIO_H_

// User I/O
// 
// provides a raw like interface to get input as signals in a device agnostic way
// each signal (button/axes etc..) come with two signals (active value)
// 
// provide a high level API for handling input in games, handling many-to-many pairing of device to player
// 
// Provides a number of filters on the signals before and after routing in the layer

#include <alias/math.h>
#include <alias/memory.h>

#ifndef ALIAS_UIO_MAX_USERS
#define ALIAS_UIO_MAX_USERS 32
#endif

#ifndef ALIAS_UIO_MAX_INPUT_NAME_SIZE
#define ALIAS_UIO_MAX_INPUT_NAME_SIZE 256
#endif

typedef struct alias_uio_Window alias_uio_Window;
typedef uint32_t alias_uio_InputProfile;

typedef enum alias_uio_Result {
  ALIAS_UIO_SUCCESS
} alias_uio_Result;

typedef enum alias_uio_DeviceType {
    ALIAS_UIO_KEYBOARD
  , ALIAS_UIO_MOUSE
  , ALIAS_UIO_JOYSTICK
  , ALIAS_UIO_GAMEPAD
  , ALIAS_UIO_TOUCH
} alias_uio_DeviceType;

typedef enum alias_uio_KeyboardSignal {
    ALIAS_UIO_KEYBOARD_TAB
  , ALIAS_UIO_KEYBOARD_SPACE
  , ALIAS_UIO_KEYBOARD_APOSTROPHE
  , ALIAS_UIO_KEYBOARD_COMMA
  , ALIAS_UIO_KEYBOARD_MINUS
  , ALIAS_UIO_KEYBOARD_PERIOD
  , ALIAS_UIO_KEYBOARD_SLASH
  , ALIAS_UIO_KEYBOARD_0
  , ALIAS_UIO_KEYBOARD_1
  , ALIAS_UIO_KEYBOARD_2
  , ALIAS_UIO_KEYBOARD_3
  , ALIAS_UIO_KEYBOARD_4
  , ALIAS_UIO_KEYBOARD_5
  , ALIAS_UIO_KEYBOARD_6
  , ALIAS_UIO_KEYBOARD_7
  , ALIAS_UIO_KEYBOARD_8
  , ALIAS_UIO_KEYBOARD_9
  , ALIAS_UIO_KEYBOARD_SEMICOLON
  , ALIAS_UIO_KEYBOARD_EQUAL
  , ALIAS_UIO_KEYBOARD_A
  , ALIAS_UIO_KEYBOARD_B
  , ALIAS_UIO_KEYBOARD_C
  , ALIAS_UIO_KEYBOARD_D
  , ALIAS_UIO_KEYBOARD_E
  , ALIAS_UIO_KEYBOARD_F
  , ALIAS_UIO_KEYBOARD_G
  , ALIAS_UIO_KEYBOARD_H
  , ALIAS_UIO_KEYBOARD_I
  , ALIAS_UIO_KEYBOARD_J
  , ALIAS_UIO_KEYBOARD_K
  , ALIAS_UIO_KEYBOARD_L
  , ALIAS_UIO_KEYBOARD_M
  , ALIAS_UIO_KEYBOARD_N
  , ALIAS_UIO_KEYBOARD_O
  , ALIAS_UIO_KEYBOARD_P
  , ALIAS_UIO_KEYBOARD_Q
  , ALIAS_UIO_KEYBOARD_R
  , ALIAS_UIO_KEYBOARD_S
  , ALIAS_UIO_KEYBOARD_T
  , ALIAS_UIO_KEYBOARD_U
  , ALIAS_UIO_KEYBOARD_V
  , ALIAS_UIO_KEYBOARD_W
  , ALIAS_UIO_KEYBOARD_X
  , ALIAS_UIO_KEYBOARD_Y
  , ALIAS_UIO_KEYBOARD_Z
  , ALIAS_UIO_KEYBOARD_LEFT_BRACKET
  , ALIAS_UIO_KEYBOARD_BACKSLASH
  , ALIAS_UIO_KEYBOARD_RIGHT_BRACKET
  , ALIAS_UIO_KEYBOARD_GRAVE
  , ALIAS_UIO_KEYBOARD_WORLD_1
  , ALIAS_UIO_KEYBOARD_WORLD_2
  , ALIAS_UIO_KEYBOARD_LEFT_CONTROL
  , ALIAS_UIO_KEYBOARD_LEFT_SHIFT
  , ALIAS_UIO_KEYBOARD_LEFT_ALT
  , ALIAS_UIO_KEYBOARD_LEFT_META
  , ALIAS_UIO_KEYBOARD_RIGHT_CONTROL
  , ALIAS_UIO_KEYBOARD_RIGHT_SHIFT
  , ALIAS_UIO_KEYBOARD_RIGHT_ALT
  , ALIAS_UIO_KEYBOARD_RIGHT_META
  , ALIAS_UIO_KEYBOARD_ENTER
  , ALIAS_UIO_KEYBOARD_ESCAPE
  , ALIAS_UIO_KEYBOARD_BACKSPACE
  , ALIAS_UIO_KEYBOARD_CAPS_LOCK
  , ALIAS_UIO_KEYBOARD_F1
  , ALIAS_UIO_KEYBOARD_F2
  , ALIAS_UIO_KEYBOARD_F3
  , ALIAS_UIO_KEYBOARD_F4
  , ALIAS_UIO_KEYBOARD_F5
  , ALIAS_UIO_KEYBOARD_F6
  , ALIAS_UIO_KEYBOARD_F7
  , ALIAS_UIO_KEYBOARD_F8
  , ALIAS_UIO_KEYBOARD_F9
  , ALIAS_UIO_KEYBOARD_F10
  , ALIAS_UIO_KEYBOARD_F11
  , ALIAS_UIO_KEYBOARD_F12
  , ALIAS_UIO_KEYBOARD_F13
  , ALIAS_UIO_KEYBOARD_F14
  , ALIAS_UIO_KEYBOARD_F15
  , ALIAS_UIO_KEYBOARD_F16
  , ALIAS_UIO_KEYBOARD_F17
  , ALIAS_UIO_KEYBOARD_F18
  , ALIAS_UIO_KEYBOARD_F19
  , ALIAS_UIO_KEYBOARD_F20
  , ALIAS_UIO_KEYBOARD_F21
  , ALIAS_UIO_KEYBOARD_F22
  , ALIAS_UIO_KEYBOARD_F23
  , ALIAS_UIO_KEYBOARD_F24
  , ALIAS_UIO_KEYBOARD_F25
  , ALIAS_UIO_KEYBOARD_SCROLL_LOCK
  , ALIAS_UIO_KEYBOARD_PAUSE
  , ALIAS_UIO_KEYBOARD_INSERT
  , ALIAS_UIO_KEYBOARD_HOME
  , ALIAS_UIO_KEYBOARD_PAGE_UP
  , ALIAS_UIO_KEYBOARD_DELETE
  , ALIAS_UIO_KEYBOARD_END
  , ALIAS_UIO_KEYBOARD_PAGE_DOWN
  , ALIAS_UIO_KEYBOARD_RIGHT
  , ALIAS_UIO_KEYBOARD_LEFT
  , ALIAS_UIO_KEYBOARD_DOWN
  , ALAIS_UIO_KEYBOARD_UP
  , ALIAS_UIO_KEYBOARD_NUM_LOCK
  , ALIAS_UIO_KEYBOARD_KP_SLASH
  , ALIAS_UIO_KEYBOARD_KP_ASTERISK
  , ALIAS_UIO_KEYBOARD_KP_MINUS
  , ALIAS_UIO_KEYBOARD_KP_PLUS
  , ALIAS_UIO_KEYBOARD_KP_ENTER
  , ALIAS_UIO_KEYBOARD_KP_0
  , ALIAS_UIO_KEYBOARD_KP_1
  , ALIAS_UIO_KEYBOARD_KP_2
  , ALIAS_UIO_KEYBOARD_KP_3
  , ALIAS_UIO_KEYBOARD_KP_4
  , ALIAS_UIO_KEYBOARD_KP_5
  , ALIAS_UIO_KEYBOARD_KP_6
  , ALIAS_UIO_KEYBOARD_KP_7
  , ALIAS_UIO_KEYBOARD_KP_8
  , ALIAS_UIO_KEYBOARD_KP_9
  , ALIAS_UIO_KEYBOARD_KP_PERIOD
  , ALIAS_UIO_KEYBOARD_KP_EQUAL
} alias_uio_KeyboardSignal;

typedef enum alias_uio_MouseSignal {
    ALIAS_UIO_MOUSE_POSITION_X
  , ALIAS_UIO_MOUSE_POSITION_Y
  , ALIAS_UIO_MOUSE_DELTA_Y
  , ALIAS_UIO_MOUSE_DELTA_X
  , ALIAS_UIO_MOUSE_SCROLL_X
  , ALIAS_UIO_MOUSE_SCROLL_Y
  , ALIAS_UIO_MOUSE_LEFT
  , ALIAS_UIO_MOUSE_RIGHT
  , ALIAS_UIO_MOUSE_MIDDLE
  , ALIAS_UIO_MOUSE_EXT_4
  , ALIAS_UIO_MOUSE_EXT_5
  , ALIAS_UIO_MOUSE_EXT_6
  , ALIAS_UIO_MOUSE_EXT_7
  , ALIAS_UIO_MOUSE_EXT_8
} alias_uio_MouseSignal;

typedef struct alias_uio_JoystickInfo {
  uint32_t axis_count;
  uint32_t button_count;
  uint32_t hat_count;
} alias_uio_JoystickInfo;

static inline uint32_t alias_uio_joystick_axis_signal(uint32_t axis) {
  return (axis << 2) | 0;
}

static inline uint32_t alias_uio_joystick_button_signal(uint32_t button) {
  return (button << 2) | 1;
}

static inline uint32_t alias_uio_joystick_hat_x_signal(uint32_t hat) {
  return (hat << 2) | 2;
}

static inline uint32_t alias_uio_joystick_hat_y_signal(uint32_t hat) {
  return (hat << 2) | 3;
}

typedef enum alias_uio_GamepadSignal {
    ALIAS_UIO_GAMEPAD_A
  , ALIAS_UIO_GAMEPAD_B
  , ALIAS_UIO_GAMEPAD_X
  , ALAIS_UIO_GAMEPAD_Y
  , ALAIS_UIO_GAMEPAD_LEFT_BUMPER
  , ALAIS_UIO_GAMEPAD_RIGHT_BUMPER
  , ALAIS_UIO_GAMEPAD_BACK
  , ALAIS_UIO_GAMEPAD_START
  , ALAIS_UIO_GAMEPAD_GUIDE
  , ALAIS_UIO_GAMEPAD_LEFT_THUMB
  , ALAIS_UIO_GAMEPAD_RIGHT_THUMB
  , ALAIS_UIO_GAMEPAD_DPAD_UP
  , ALAIS_UIO_GAMEPAD_DPAD_RIGHT
  , ALAIS_UIO_GAMEPAD_DPAD_DOWN
  , ALAIS_UIO_GAMEPAD_DPAD_LEFT
  , ALAIS_UIO_GAMEPAD_LEFT_X
  , ALAIS_UIO_GAMEPAD_LEFT_Y
  , ALIAS_UIO_GAMEPAD_LEFT_TRIGGER
  , ALAIS_UIO_GAMEPAD_RIGHT_X
  , ALAIS_UIO_GAMEPAD_RIGHT_Y
  , ALIAS_UIO_GAMEPAD_RIGHT_TRIGGER
} alais_uio_GamepadSignal;

static inline uint32_t alias_uio_touch_active_signal(uint32_t touch) {
  return (touch << 2) | 0;
}

static inline uint32_t alias_uio_touch_x_signal(uint32_t touch) {
  return (touch << 2) | 1;
}

static inline uint32_t alias_uio_touch_y_signal(uint32_t touch) {
  return (touch << 2) | 2;
}

static inline uint32_t alias_uio_touch_pressure_signal(uint32_t touch) {
  return (touch << 2) | 3;
}

typedef struct alias_uio_DeviceInfo {
  alias_uio_DeviceType   type;
  char                   name[ALIAS_UIO_MAX_INPUT_NAME_SIZE];
  alias_uio_JoystickInfo joystick;
} alias_uio_DeviceInfo;

typedef struct alias_uio_WindowCreateInfo {
  uint32_t     width;
  uint32_t     height;
  const char * title;
} alias_uio_WindowCreateInfo;

typedef struct alias_uio_Read {
  uint32_t         device;
  uint32_t         num_signals;
  const uint32_t * signals;
} alias_uio_Read;

// TODO: fill with real things
typedef struct alias_uio_Write {
  uint32_t        device;
  uint32_t        num_rumble_samples;
  const alias_R * rumble_samples;
} alias_uio_Write;

typedef struct alias_uio_BackendDeviceCreateInfo {
  alias_uio_DeviceType type;
  uint32_t num_signals;
  const uint32_t * signal;
} alias_uio_BackendDeviceCreateInfo;

typedef struct alias_uio_BackendCreateInfo {
  const char * name;

  uint32_t num_devices;
  const alias_uio_BackendDeviceCreateInfo devices;
} alias_uio_BackendCreateInfo;

typedef struct alias_uio_FrontendCreateInfo {
  const char * name;
} alias_uio_FrontendCreateInfo;

typedef struct alias_uio_InputProfileCreateInfo {
  uint32_t num_backends;
  const alias_uio_BackendCreateInfo * backends;

  uint32_t num_frontends;
  const alias_uio_FrontendCreateInfo * frontend;
} alias_uio_InputProfileCreateInfo;

alias_uio_Result alias_uio_create_window(alias_uio_WindowCreateInfo * create_info, alias_MemoryCB * mcb, alias_uio_Window ** window);

void alias_uio_destroy_window(alias_uio_Window * window, alias_MemoryCB * mcb);

alias_uio_Result alias_uio_get_devices(alias_uio_Window * window, uint32_t * count, alias_uio_DeviceInfo * infos);

// TODO: when doing async I/O integrate this into it
alias_uio_Result alias_uio_read(
    alias_uio_Window     * window
  , alias_MemoryCB       * mcb
  , uint32_t               num_reads
  , const alias_uio_Read * reads
  , alias_R *            * signal
  );

// TODO: when doing async I/O integrate this into it
alias_uio_Result alias_uio_write(
    alias_uio_Window      * window
  , alias_MemoryCB        * mcb
  , uint32_t                num_writes
  , const alias_uio_Write * writes
  );

bool alias_uio_should_close(alias_uio_Window * window);

alias_uio_Result alias_uio_set_user_backend(
    alias_uio_Window * window
  , alias_MemoryCB * mcb
  , uint32_t user
  , uint32_t backend
  );

alias_uio_Result alias_uio_set_user_frontend(
    alias_uio_Window * window
  , alias_MemoryCB * mcb
  , uint32_t user
  , uint32_t frontend
  );

alias_uio_Result alias_uio_update(alias_uio_Window * window);

#endif
