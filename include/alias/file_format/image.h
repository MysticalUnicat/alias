#ifndef _ALIAS_FILE_FORMAT_IMAGE_H_
#define _ALIAS_FILE_FORMAT_IMAGE_H_

#include <alias/memory.h>

typedef union alias_image_RGBA {
  struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
  };
  uint32_t u;
} alias_image_RGBA;

typedef enum alias_image_Format {
  alias_image_Format_RGB8,
  alias_image_Format_RGBA8,
  alias_image_Format_sRGB8,
  alias_image_Format_sRGB8_A8,
} alias_image_Format;

typedef enum alias_image_Result {
  alias_image_Result_ok,
  alias_image_Result_invalid_header,
  alias_image_Result_invalid_file_structure,
  alias_image_Result_invalid_state,
  alias_image_Result_need_more_input,
  alias_image_Result_need_more_output,
} alias_image_Result;

typedef struct alias_image_Info {
  uint32_t width;
  uint32_t height;
  alias_image_Format format;
} alias_image_Info;

#endif

