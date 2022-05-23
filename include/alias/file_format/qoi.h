// https://qoiformat.org/qoi-specification.pdf
#include <alias/file_format/image.h>

typedef struct alias_image_QOI {
  alias_image_RGBA previous;
  alias_image_RGBA array[64];
  uint32_t run_length;
} alias_image_QOI;

alias_image_Result alias_image_QOI_read_header(const uint8_t * input, size_t input_size, size_t * input_count, alias_image_Info * info);
alias_image_Result alias_image_QOI_write_header(const alias_image_Info * info, uint8_t * output, size_t output_size, size_t * output_count);

alias_image_Result alias_image_QOI_init(alias_image_QOI * qoi);
alias_image_Result alias_image_QOI_decode(alias_image_QOI * qoi, const uint8_t * input, size_t input_size, size_t * input_count, alias_image_RGBA * output, size_t output_size, size_t * output_count);
alias_image_Result alias_image_QOI_encode(alias_image_QOI * qoi, const alias_image_RGBA * input, size_t input_size, size_t * input_count, uint8_t * output, size_t output_size, size_t * output_count);
alias_image_Result alias_image_QOI_end_encoding(alias_image_QOI * qoi, uint8_t * output, size_t output_size, size_t * output_count);

alias_image_Result alias_image_QOI_read_footer(const uint8_t * input, size_t input_size, size_t * input_count);
alias_image_Result alias_image_QOI_write_footer(uint8_t * output, size_t output_size, size_t * output_count);
