#include "device_manager.h"

#include <map.h>
#include <stdlib.h>

typedef struct DeviceManager_t {
  _u16 nextDeviceId;
  Map_t *devices;
} DeviceManager_t;

static DeviceManager_t *deviceManager = NULL;

static void _UpdateDevices(const _u16 key, const void *value);
static bool _FindDeviceByTypePredicate(const void *expected, const void *value);

DeviceManager_t *DeviceManagerGetInstance() {
  if (deviceManager == NULL) {
    deviceManager = (DeviceManager_t *)malloc(sizeof(DeviceManager_t));

    if (deviceManager == NULL) {
      return NULL;
    }

    deviceManager->devices = MapCreate(MAX_DEVICES_COUNT);
    deviceManager->nextDeviceId = 0;
  }

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
  bool initOk = false;
  if (added == true) {
    initOk = DeviceInit(device);
  }

  return (added == true && initOk == true) ? deviceId : DEVICE_ID_NONE;
}

Device_t *DeviceManagerGet(const DeviceManager_t *deviceManager,
                           const _u16 deviceId) {
  return MapGet(deviceManager->devices, deviceId);
}

Device_t *DeviceManagerGetByType(const DeviceManager_t *deviceManager,
                                 const DeviceType_t deviceType) {
  return MapFind(deviceManager->devices, (void *)deviceType,
                 &_FindDeviceByTypePredicate);
}

_u16 DeviceManagerNextDeviceId(DeviceManager_t *deviceManager) {
  deviceManager->nextDeviceId++;
  return deviceManager->nextDeviceId;
}

//
static void _UpdateDevices(const _u16 key, const void *value) {
  Device_t *device = (Device_t *)value;
  if (DeviceIsEnabled(device) == true) {
    DeviceUpdate(device);
  }
}

static bool _FindDeviceByTypePredicate(const void *expected,
                                       const void *value) {
  const DeviceType_t deviceType = (DeviceType_t)expected;
  Device_t *device = (Device_t *)value;
  return deviceType == DeviceGetType(device);
}