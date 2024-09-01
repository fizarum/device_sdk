#ifndef DISPLAY_DATA_H
#define DISPLAY_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef struct DisplayDeviceData_t {
  _u16 width;
  _u16 height;
} DisplayDeviceData_t;

#ifdef __cplusplus
}
#endif

#endif  // DISPLAY_DATA_H