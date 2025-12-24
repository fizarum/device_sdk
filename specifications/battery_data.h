#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef struct BatteryDeviceData {
  _u8 chargeLevelPercents;
  bool charging;
  bool charginStatusChanged;
} BatteryDeviceData;

#ifdef __cplusplus
}
#endif