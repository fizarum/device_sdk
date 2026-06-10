#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "device.h"

#define MAX_DEVICES_COUNT 20
#define DEVICE_ID_NONE UINT16_MAX

void device_manager_init();
void device_manager_update();

/**
 * @brief Adds device to device manager for further management. If device
 * can not be added DEVICE_ID_NONE is returned as device id
 *
 * @param device to add
 * @return id if device is added, DEVICE_ID_NONE otherwise
 */
_u16 device_manager_register(device_specification_t* specs);

/**
 * @brief Gets device by id
 * @returns ref on device_t or null if device not registered
 */
device_t* device_manager_get(const _u16 device_id);

void* device_manager_get_extension(const device_type_t deviceType);

device_t* device_manager_get_by_type(const device_type_t deviceType);

#ifdef __cplusplus
}
#endif