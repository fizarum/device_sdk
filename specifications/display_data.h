#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef struct DisplayDeviceExtension {
  _u16 width;
  _u16 height;
  _u8 brightness;

  /**
   * @brief Set brightness in percents
   * @param brightness - acceptable value from 1 to 100. Its set to 100 if input
   * param exeeds max
   * @return true if operation completed sucessfully
   */
  bool (*changeBrightness)(_u8 brightness);
} DisplayDeviceExtension;

#ifdef __cplusplus
}
#endif