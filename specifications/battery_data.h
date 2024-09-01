#ifndef BATTERY_DATA_H
#define BATTERY_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef struct BatteryDeviceData_t {
  _u8 chargeLevelPercents;
  // todo: update this field in new version of pcb
  bool charging;
} BatteryDeviceData_t;

#ifdef __cplusplus
}
#endif

#endif  // BATTERY_DATA_H