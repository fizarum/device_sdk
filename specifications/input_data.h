#ifndef INPUT_DATA_H
#define INPUT_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../device.h"

typedef struct DeviceData_t {
  _u16 keymap;
  _u16 previousKeymap;
} InputDeviceData_t;

#define isPressed(keymap, mask) ((keymap & mask) == mask)

static inline bool IsButtonPressed(const DeviceData_t *data,
                                   const _u16 keycode) {
  return isPressed(data->keymap, keycode);
}

static inline bool IsButtonReleased(const DeviceData_t *data,
                                    const _u16 keycode) {
  return isPressed(data->keymap, keycode) == false &&
         isPressed(data->previousKeymap, keycode) == true;
}

static inline bool IsButtonLongPressed(const DeviceData_t *data,
                                       const _u16 keycode) {
  return isPressed(data->keymap, keycode) == true &&
         isPressed(data->previousKeymap, keycode) == true;
}

#ifdef __cplusplus
}
#endif

#endif  // INPUT_DATA_H