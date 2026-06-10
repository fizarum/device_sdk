#include "device_manager.h"

#include <map.h>
#include <stdlib.h>

static _u16 next_id;
static Map_t* devices;

static void _update_devices(const _u16 key, const void* value);
static bool _find_by_type(const void* expected, const void* value);

void device_manager_init() {
  devices = MapCreate(MAX_DEVICES_COUNT);
  next_id = 0;
}

void device_manager_update() {
  _u16 size = MapSize(devices);
  MapForeach(devices, &_update_devices);
}

_u16 device_manager_register(device_specification_t* specs) {
  _u16 id = next_id++;
  device_t* device = device_create(id, specs);
  if (device == NULL) {
    return DEVICE_ID_NONE;
  }

  if (MapSet(devices, id, device) == false) {
    return DEVICE_ID_NONE;
  }

  return device_init(device) ? id : DEVICE_ID_NONE;
}

device_t* device_manager_get(const _u16 device_id) {
  if (device_id == DEVICE_ID_NONE) {
    return NULL;
  }
  return (device_t*)MapGet(devices, device_id);
}

void* device_manager_get_extension(const device_type_t deviceType) {
  device_t* dev = device_manager_get_by_type(deviceType);
  return device_get_extension(dev);
}

device_t* device_manager_get_by_type(const device_type_t deviceType) {
  return MapFind(devices, (void*)deviceType, &_find_by_type);
}

// private part
void _update_devices(const _u16 key, const void* value) {
  device_update((device_t*)value);
}

bool _find_by_type(const void* expected, const void* value) {
  const device_type_t deviceType = (device_type_t)expected;
  device_t* device = (device_t*)value;
  return deviceType == device_get_type(device);
}