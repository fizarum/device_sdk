#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef struct BatteryDeviceExtension {
  _u8 chargeLevelPercents;
  bool charging;
  bool charginStatusChanged;
} BatteryDeviceExtension;

#ifdef __cplusplus
}
#endif