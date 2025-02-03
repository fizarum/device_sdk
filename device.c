#include "device.h"

#include <stdlib.h>

typedef struct Device_t {
  uint16_t id;
  bool enabled;
  DeviceSpecification_t *specification;
} Device_t;

Device_t *DeviceCreate(uint16_t id, DeviceSpecification_t *specification) {
  Device_t *device = (Device_t *)malloc(sizeof(Device_t));

  device->id = id;
  device->specification = specification;

  return device;
}

void DeviceDestroy(Device_t *device) {
  if (device == NULL) return;

  free(device);
}

bool DeviceInit(Device_t *device) {
  bool initialized = device->specification->onInit();
  if (initialized == true) {
    DeviceEnable(device, true);
  }

  return initialized;
}

void DeviceUpdate(Device_t *device) { device->specification->onUpdate(); }

void DeviceEnable(Device_t *device, const bool enable) {
  if (device->specification->onEnable(enable) == true) {
    device->enabled = enable;
  } else {
    device->enabled = false;
  }
}

bool DeviceIsEnabled(const Device_t *device) { return device->enabled; }

const char *DeviceGetName(const Device_t *device) {
  return device->specification->name;
}

_u16 DeviceGetId(const Device_t *device) { return device->id; }

DeviceType_t DeviceGetType(const Device_t *device) {
  return device->specification->type;
}

const void *DeviceGetData(const Device_t *device) {
  if (device == NULL) {
    return NULL;
  }
  return device->specification->data;
}
