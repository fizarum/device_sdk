#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef enum DeviceType {
  TypeInput,
  TypeDisplay,
  TypeStorage,
  TypePower,
  TypeEnv,
  TypeClock,
  TypeGeneric,
  TypeAudio,
  TypeNA,
} DeviceType;

typedef struct Device Device;

typedef struct DeviceSpecification {
  const char* name;
  const DeviceType type;

  /**
   * @brief Link to "parent" object. Its assigned during device creation:
   * DeviceCreate() function
   */
  Device* device;

  /**
   * @brief Contains some data based on device type. For example,
   * for joystic it can have prevous and current keymap.
   * For display - frame, sync state, etc.
   * Check "specifications" folder for details
   */
  void* data;

  /**
   * @brief used to access to a structure of specific device API. For example,
   * for display it can have: setBrightness(), setRotation(), invertColors, etc.
   *
   */
  void* extension;

  /**
   * @brief Called to initialize hardware
   * @returns true if init procedure completes successfully
   */
  bool (*onInit)(void);
  void (*onUpdate)(void);
  bool (*onEnable)(bool enable);
  bool (*isEnabled)(void);
} DeviceSpecification;

Device* DeviceCreate(uint16_t id, DeviceSpecification* specification);
void DeviceDestroy(Device* device);
bool DeviceInit(Device* device);
void DeviceUpdate(Device* device);
void DeviceEnable(Device* device, const bool enable);
bool DeviceIsEnabled(const Device* device);

const char* DeviceGetName(const Device* device);
_u16 DeviceGetId(const Device* device);
DeviceType DeviceGetType(const Device* device);
void* DeviceGetData(const Device* device);

DeviceSpecification* Device_GetSpecification(const Device* device);

#ifdef __cplusplus
}
#endif