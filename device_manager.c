#include "device_manager.h"

#include <map.h>
#include <stdlib.h>

typedef struct DeviceManager_t {
  _u16 nextDeviceId;
  Map_t *devices;
} DeviceManager_t;

static void _UpdateDevices(const _u16 key, const void *value);

DeviceManager_t *DeviceManagerCreate() {
  DeviceManager_t *deviceManager =
      (DeviceManager_t *)malloc(sizeof(DeviceManager_t));

  if (deviceManager == NULL) {
    return NULL;
  }

  deviceManager->devices = MapCreate(MAX_DEVICES_COUNT);
  deviceManager->nextDeviceId = 0;

  return deviceManager;
}

void DeviceManagerUpdate(const DeviceManager_t *deviceManager) {
  MapForeach(deviceManager->devices, &_UpdateDevices);
}

_u16 DeviceManagerAdd(DeviceManager_t *deviceManager, Device_t *device) {
  if (device == NULL) {
    return DEVICE_ID_NONE;
  }

  _u16 deviceId = DeviceGetId(device);
  bool added = MapSet(deviceManager->devices, deviceId, device);
  if (added == true) {
    DeviceInit(device);
  }

  return (added == true) ? deviceId : DEVICE_ID_NONE;
}

Device_t *DeviceManagerGet(const DeviceManager_t *deviceManager,
                           const _u16 deviceId) {
  return MapGet(deviceManager->devices, deviceId);
}

_u16 DeviceManagerNextDeviceId(DeviceManager_t *deviceManager) {
  deviceManager->nextDeviceId++;
  return deviceManager->nextDeviceId;
}

static void _UpdateDevices(const _u16 key, const void *value) {
  Device_t *device = (Device_t *)value;
  DeviceUpdate(device);
}