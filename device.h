#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef enum device_type_t {
  TypeInput,
  TypeDisplay,
  TypeStorage,
  TypePower,
  TypeEnv,
  TypeClock,
  TypeGeneric,
  TypeAudio,
  TypeNA,
} device_type_t;

typedef struct device_t device_t;
typedef struct device_specification_t device_specification_t;

typedef struct device_specification_t {
  const char* name;
  device_type_t type;

  /**
   * @brief Link to "parent" object. Its assigned during device creation:
   * DeviceCreate() function
   */
  device_t* device;

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
   * @brief reference to real device, spi_display_t for example
   * */
  void* device_ref;

  /**
   * @brief Called to initialize hardware
   * @returns true if init procedure completes successfully
   */
  bool (*onInit)(device_specification_t*);
  void (*onUpdate)(device_specification_t*);
  bool (*onEnable)(device_specification_t*, bool enable);
  bool (*isEnabled)(device_specification_t*);
} device_specification_t;

device_t* device_create(uint16_t id, device_specification_t* specification);
void device_destroy(device_t* device);
bool device_init(device_t* device);
void device_update(device_t* device);
void device_enable(device_t* device, const bool enable);
bool device_is_enabled(const device_t* device);

const char* device_get_name(const device_t* device);
_u16 device_get_id(const device_t* device);
device_type_t device_get_type(const device_t* device);
void* device_get_extension(const device_t* device);

device_specification_t* device_get_specification(const device_t* device);

#ifdef __cplusplus
}
#endif