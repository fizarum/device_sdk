#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef struct AudioDeviceExtension {
  float volume;

  bool (*changeVolume)(_u8 volume);
} AudioDeviceExtension;

#ifdef __cplusplus
}
#endif