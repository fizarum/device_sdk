#include "device_manager.h"

#include <map.h>
#include <stdlib.h>

typedef struct DeviceManager {
  _u16 nextDeviceId;
  Map_t* devices;
} DeviceManager;

static DeviceManager* deviceManager = NULL;

static inline void _UpdateDevices(const _u16 key, const void* value) {
  Device* device = (Device*)value;
  DeviceUpdate(device);
}
static inline bool _FindDeviceByTypePredicate(const void* expected,
                                              const void* value) {
  const DeviceType deviceType = (DeviceType)expected;
  Device* device = (Device*)value;
  return deviceType == DeviceGetType(device);
}

DeviceManager* DeviceManagerGetInstance() {
  if (deviceManager == NULL) {
    deviceManager = (DeviceManager*)malloc(sizeof(DeviceManager));

    if (deviceManager == NULL) {
      return NULL;
    }

    deviceManager->devices = MapCreate(MAX_DEVICES_COUNT);
    deviceManager->nextDeviceId = 0;
  }

  return deviceManager;
}

void DeviceManagerUpdate(const DeviceManager* deviceManager) {
  MapForeach(deviceManager->devices, &_UpdateDevices);
}

_u16 DeviceManagerAdd(DeviceManager* deviceManager, Device* device) {
  if (device == NULL) {
    return DEVICE_ID_NONE;
  }

  _u16 deviceId = DeviceGetId(device);
  bool added = MapSet(deviceManager->devices, deviceId, device);
  bool initOk = false;
  if (added == true) {
    initOk = DeviceInit(device);
  }

  return (added == true && initOk == true) ? deviceId : DEVICE_ID_NONE;
}

Device* DeviceManagerGet(const DeviceManager* deviceManager,
                         const _u16 deviceId) {
  return MapGet(deviceManager->devices, deviceId);
}

DeviceSpecification* DeviceManager_GetSpecification(
    const DeviceType deviceType) {
  Device* dev = DeviceManager_GetByType(deviceType);
  return Device_GetSpecification(dev);
}

void* DeviceManager_GetData(const DeviceType deviceType) {
  Device* dev = DeviceManager_GetByType(deviceType);
  return DeviceGetData(dev);
}

void* DeviceManager_GetExtension(const DeviceType deviceType) {
  DeviceSpecification* specs = DeviceManager_GetSpecification(deviceType);
  return specs->extension;
}

Device* DeviceManager_GetByType(const DeviceType deviceType) {
  if (deviceManager == NULL) {
    return NULL;
  }

  return MapFind(deviceManager->devices, (void*)deviceType,
                 &_FindDeviceByTypePredicate);
}

_u16 DeviceManagerNextDeviceId(DeviceManager* deviceManager) {
  deviceManager->nextDeviceId++;
  return deviceManager->nextDeviceId;
}