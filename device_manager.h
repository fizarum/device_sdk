#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

#include "device.h"

#define MAX_DEVICES_COUNT 20
#define DEVICE_ID_NONE UINT16_MAX

typedef struct DeviceManager DeviceManager;

DeviceManager* DeviceManagerGetInstance();

void DeviceManagerUpdate(const DeviceManager* deviceManager);

/**
 * @brief Adds device to device manager for further management. If device can
 * not be added DEVICE_ID_NONE is returned as device id
 *
 * @param device to add
 * @return id if device is added, DEVICE_ID_NONE otherwise
 */
_u16 DeviceManagerAdd(DeviceManager* deviceManager, Device* device);

Device* DeviceManagerGet(const DeviceManager* deviceManager,
                         const _u16 deviceId);

Device* DeviceManagerGetByType(const DeviceManager* deviceManager,
                               const DeviceType deviceType);

_u16 DeviceManagerNextDeviceId(DeviceManager* deviceManager);

#ifdef __cplusplus
}
#endif

#endif  // DEVICE_MANAGER_H