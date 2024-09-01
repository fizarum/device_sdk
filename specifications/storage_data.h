#ifndef STORAGE_DATA_H
#define STORAGE_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

#include "driver/sdmmc_types.h"

typedef struct StorageDeviceData_t {
  const char* const mountPoint;
  sdmmc_card_t* card;
} StorageDeviceData_t;

#ifdef __cplusplus
}
#endif

#endif  // STORAGE_DATA_H