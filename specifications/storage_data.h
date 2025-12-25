#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

#include "driver/sdmmc_types.h"

typedef struct StorageDeviceExtension {
  const char* const mountPoint;
  sdmmc_card_t* card;
} StorageDeviceExtension;

#ifdef __cplusplus
}
#endif