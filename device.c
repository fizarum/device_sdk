#include "device.h"

#include <stdlib.h>

typedef struct device_t {
  uint16_t id;
  bool enabled;
  device_specification_t* specification;
} device_t;

device_t* device_create(uint16_t id, device_specification_t* specification) {
  assert(specification);
  device_t* device = (device_t*)malloc(sizeof(device_t));
  if (device == NULL) {
    return NULL;
  }

  device->id = id;
  // set a ref of device to specification, so it knows its parent
  specification->device = device;

  device->specification = specification;

  return device;
}

void device_destroy(device_t* device) {
  if (device == NULL) return;
  device->specification->device = NULL;

  free(device);
}

bool device_init(device_t* device) {
  if (device == NULL || device->specification == NULL ||
      device->specification->onInit == NULL) {
    return false;
  }

  bool initialized = device->specification->onInit(device->specification);
  if (initialized == true) {
    device_enable(device, true);
  }

  return initialized;
}

void device_update(device_t* device) {
  if (device == NULL || device->specification == NULL ||
      device->specification->onUpdate == NULL) {
    return;
  }

  if (device->enabled && device->specification->onUpdate != NULL) {
    device->specification->onUpdate(device->specification);
  }
}

void device_enable(device_t* device, const bool enable) {
  if (device == NULL || device->specification == NULL ||
      device->specification->onEnable == NULL) {
    return;
  }

  if (device->enabled == enable) {
    return;
  }

  if (device->specification->onEnable(device->specification, enable) == true) {
    device->enabled = enable;
  } else {
    device->enabled = false;
  }
}

bool device_is_enabled(const device_t* device) { return device->enabled; }

const char* device_get_name(const device_t* device) {
  return device->specification->name;
}

_u16 device_get_id(const device_t* device) { return device->id; }

device_type_t device_get_type(const device_t* device) {
  return device->specification->type;
}

void* device_get_extension(const device_t* device) {
  if (device == NULL) {
    return NULL;
  }

  return device->specification->extension;
}

device_specification_t* device_get_specification(const device_t* device) {
  if (device == NULL) {
    return NULL;
  }

  return device->specification;
}