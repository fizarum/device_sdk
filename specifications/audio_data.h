#ifndef AUDIO_DATA_H
#define AUDIO_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef struct AudioDeviceData_t {
  float volume;
} AudioDeviceData_t;

#ifdef __cplusplus
}
#endif

#endif  // AUDIO_DATA_H