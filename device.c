#include "device.h"

#include <stdlib.h>

typedef struct Device {
  uint16_t id;
  bool enabled;
  DeviceSpecification* specification;
} Device;

Device* Device_Create(uint16_t id, DeviceSpecification* specification) {
  Device* device = (Device*)malloc(sizeof(Device));

  device->id = id;
  // set a ref of device to specification, so it knows its parent
  specification->device = device;

  device->specification = specification;

  return device;
}

void Device_Destroy(Device* device) {
  if (device == NULL) return;

  free(device);
}

bool Device_Init(Device* device) {
  bool initialized = device->specification->onInit();
  if (initialized == true) {
    Device_Enable(device, true);
  }

  return initialized;
}

void Device_Update(Device* device) {
  if (device->enabled) {
    device->specification->onUpdate();
  }
}

void Device_Enable(Device* device, const bool enable) {
  if (device->specification->onEnable(enable) == true) {
    device->enabled = enable;
  } else {
    device->enabled = false;
  }
}

bool Device_IsEnabled(const Device* device) { return device->enabled; }

const char* Device_GetName(const Device* device) {
  return device->specification->name;
}

_u16 Device_GetId(const Device* device) { return device->id; }

DeviceType Device_GetType(const Device* device) {
  return device->specification->type;
}

void* Device_GetExtension(const Device* device) {
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