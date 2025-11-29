#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef struct DisplayExtension {
  /**
   * @brief Set brightness in percents
   * @param brightness - acceptable value from 1 to 100. Its set to 100 if input
   * param exeeds max
   * @return true if operation completed sucessfully
   */
  bool (*changeBrightness)(_u8 brightness);
} DisplayExtension;

#ifdef __cplusplus
}
#endif