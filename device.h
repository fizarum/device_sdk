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
  TypePower,
  TypeEnv,
  TypeClock,
  TypeGeneric,
  TypeNA,
} DeviceType_t;

/**
 * @brief Contains some data based on device needs. For example,
 * for joystic it can have prevous and current keymap.
 * For display - frame, sync state, etc.
 */
typedef struct DeviceData_t DeviceData_t;

typedef struct DeviceSpecification_t {
  const char *name;
  const DeviceType_t type;

  bool (*onInit)(void);
  void (*onUpdate)(void);
  void (*onEnable)(bool enable);
  DeviceData_t *(*getData)(void);
} DeviceSpecification_t;

typedef struct Device_t Device_t;

Device_t *DeviceCreate(uint16_t id, DeviceSpecification_t *specification);
void DeviceDestroy(Device_t *device);
bool DeviceInit(Device_t *device);
void DeviceUpdate(Device_t *device);
void DeviceEnable(Device_t *device, const bool enable);

const char *DeviceGetName(const Device_t *device);
_u16 DeviceGetId(const Device_t *device);
DeviceType_t DeviceGetType(const Device_t *device);
const DeviceData_t *DeviceGetData(const Device_t *device);

#ifdef __cplusplus
}
#endif

#endif  // DEVICE_H