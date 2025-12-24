#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef struct InputDeviceData {
  _u16 keymap;
  _u16 previousKeymap;
} InputDeviceData;

#define isPressed(keymap, mask) ((keymap & mask) == mask)

static inline bool IsButtonPressed(const InputDeviceData* data,
                                   const _u16 keycode) {
  return isPressed(data->keymap, keycode);
}

static inline bool IsButtonReleased(const InputDeviceData* data,
                                    const _u16 keycode) {
  return isPressed(data->keymap, keycode) == false &&
         isPressed(data->previousKeymap, keycode) == true;
}

static inline bool IsButtonLongPressed(const InputDeviceData* data,
                                       const _u16 keycode) {
  return isPressed(data->keymap, keycode) == true &&
         isPressed(data->previousKeymap, keycode) == true;
}

static inline bool IsAnyButtonPressed(const InputDeviceData* data) {
  return data->keymap > 0 || data->previousKeymap > 0;
}

#ifdef __cplusplus
}
#endif