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
   * For display - frame, sync state, etc. Also used to access to a structure of
   * specific device API. For example, for display it can have: setBrightness(),
   * setRotation(), invertColors, etc.
   *
   * Check "specifications" folder for details.
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

Device* Device_Create(uint16_t id, DeviceSpecification* specification);
void Device_Destroy(Device* device);
bool Device_Init(Device* device);
void Device_Update(Device* device);
void Device_Enable(Device* device, const bool enable);
bool Device_IsEnabled(const Device* device);

const char* Device_GetName(const Device* device);
_u16 Device_GetId(const Device* device);
DeviceType Device_GetType(const Device* device);
void* Device_GetExtension(const Device* device);

DeviceSpecification* Device_GetSpecification(const Device* device);

#ifdef __cplusplus
}
#endif