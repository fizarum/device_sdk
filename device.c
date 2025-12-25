#include "device.h"

#include <stdlib.h>

typedef struct Device {
  uint16_t id;
  bool enabled;
  DeviceSpecification* specification;
} Device;

Device* DeviceCreate(uint16_t id, DeviceSpecification* specification) {
  Device* device = (Device*)malloc(sizeof(Device));

  device->id = id;
  // set a ref of device to specification, so it knows its parent
  specification->device = device;

  device->specification = specification;

  return device;
}

void DeviceDestroy(Device* device) {
  if (device == NULL) return;

  free(device);
}

bool DeviceInit(Device* device) {
  bool initialized = device->specification->onInit();
  if (initialized == true) {
    DeviceEnable(device, true);
  }

  return initialized;
}

void DeviceUpdate(Device* device) {
  if (device->enabled) {
    device->specification->onUpdate();
  }
}

void DeviceEnable(Device* device, const bool enable) {
  if (device->specification->onEnable(enable) == true) {
    device->enabled = enable;
  } else {
    device->enabled = false;
  }
}

bool DeviceIsEnabled(const Device* device) { return device->enabled; }

const char* DeviceGetName(const Device* device) {
  return device->specification->name;
}

_u16 DeviceGetId(const Device* device) { return device->id; }

DeviceType DeviceGetType(const Device* device) {
  return device->specification->type;
}

void* DeviceGetExtension(const Device* device) {
  if (device == NULL) {
    return NULL;
  }
  return device->specification->extension;
}

DeviceSpecification* Device_GetSpecification(const Device* device) {
  if (device == NULL) {
    return NULL;
  }
  return device->specification;
}