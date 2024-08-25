#ifndef BATTERY_DATA_H
#define BATTERY_DATA_H

#ifdef __cplusplus
extern "C" {
#endif
#include "../device.h"

typedef struct DeviceData_t {
  _u8 levelPercents;
  // todo: update this field in new version of pcb
  bool charging;
} BatteryDeviceData_t;

#ifdef __cplusplus
}
#endif

#endif  // BATTERY_DATA_H