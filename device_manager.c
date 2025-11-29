#include "device_manager.h"

#include <map.h>
#include <stdlib.h>

typedef struct DeviceManager {
  _u16 nextDeviceId;
  Map_t* devices;
} DeviceManager;

static DeviceManager* deviceManager = NULL;

static void _UpdateDevices(const _u16 key, const void* value);
static bool _FindDeviceByTypePredicate(const void* expected, const void* value);

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

Device* DeviceManagerGetByType(const DeviceManager* deviceManager,
                               const DeviceType deviceType) {
  return MapFind(deviceManager->devices, (void*)deviceType,
                 &_FindDeviceByTypePredicate);
}

_u16 DeviceManagerNextDeviceId(DeviceManager* deviceManager) {
  deviceManager->nextDeviceId++;
  return deviceManager->nextDeviceId;
}

//
static void _UpdateDevices(const _u16 key, const void* value) {
  Device* device = (Device*)value;
  if (DeviceIsEnabled(device) == true) {
    DeviceUpdate(device);
  }
}

static bool _FindDeviceByTypePredicate(const void* expected,
                                       const void* value) {
  const DeviceType deviceType = (DeviceType)expected;
  Device* device = (Device*)value;
  return deviceType == DeviceGetType(device);
}