#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef struct InputDeviceExtension {
  _u16 keymap;
  _u16 previousKeymap;
} InputDeviceExtension;

#ifdef __cplusplus
}
#endif