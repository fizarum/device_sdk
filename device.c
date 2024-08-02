#include "device.h"

#include <stdlib.h>

typedef struct Device_t {
  uint16_t id;
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
  bool initOk = device->specification->onInit();
  device->specification->onEnable(initOk);

  return initOk;
}

void DeviceUpdate(Device_t *device) { device->specification->onUpdate(); }

void DeviceEnable(Device_t *device, const bool enable) {
  device->specification->onEnable(enable);
}

const char *DeviceGetName(const Device_t *device) {
  return device->specification->name;
}

const _u16 DeviceGetId(const Device_t *device) { return device->id; }

const DeviceType_t DeviceGetType(const Device_t *device) {
  return device->specification->type;
}

const DeviceData_t *DeviceGetData(const Device_t *device) {
  return device->specification->getData();
}
