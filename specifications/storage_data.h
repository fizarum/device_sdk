#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

#include "driver/sdmmc_types.h"

typedef struct StorageDeviceExtension {
  const char* const mountPoint;
  bool mounted;
  sdmmc_card_t* card;
  bool (*setMounted)(_u8 mounted);
} StorageDeviceExtension;

#ifdef __cplusplus
}
#endif