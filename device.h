#ifndef DEVICE_H
#define DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <types.h>

typedef enum DeviceType_t {
  TypeInput,
  TypeDisplay,
  TypeStorage,
  TypeEnv,
  TypeClock,
  TypeGeneric,
  TypeNA,
} DeviceType_t;

typedef struct DeviceSpecification_t {
  const char *name;
  const DeviceType_t type;

  bool (*onInit)(void);
  void (*onUpdate)(void);
  void (*onEnable)(bool enable);
  void *(*getData)(void);
} DeviceSpecification_t;

typedef struct Device_t Device_t;

Device_t *DeviceCreate(uint16_t id, DeviceSpecification_t *specification);
void DeviceDestroy(Device_t *device);
bool DeviceInit(Device_t *device);
void DeviceUpdate(Device_t *device);
void DeviceEnable(Device_t *device, const bool enable);

const char *DeviceGetName(const Device_t *device);
const _u16 DeviceGetId(const Device_t *device);
const DeviceType_t DeviceGetType(const Device_t *device);
void *DeviceGetData(const Device_t *device);

#ifdef __cplusplus
}
#endif

#endif  // DEVICE_H