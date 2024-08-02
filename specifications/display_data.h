#ifndef DISPLAY_DATA_H
#define DISPLAY_DATA_H

#ifdef __cplusplus
extern "C" {
#endif
#include "../device.h"

typedef struct DeviceData_t {
  _u16 width;
  _u16 height;
} DisplayDeviceData_t;

#ifdef __cplusplus
}
#endif

#endif  // DISPLAY_DATA_H