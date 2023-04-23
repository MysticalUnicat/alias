// https://qoiformat.org/qoi-specification.pdf
#include <alias/file_format/qoi.h>

#define INDEX_POSITION(R, G, B, A) (((uint_least16_t)(R) * 3 + (uint_least16_t)(G) * 5 + (uint_least16_t)(B) * 7 + (uint_least16_t)(A) * 11) & 63)
#define ASSERT(X) do { if(!(X)) { return alias_image_Result_invalid_state; } } while(0)

static inline alias_image_Result decode_rgb(alias_image_QOI * qoi, const uint8_t * input, size_t input_size, size_t * input_count, alias_image_RGBA * out, uint_least8_t * out_count) {
  if(input_size <= 4) {
    return alias_image_Result_need_more_input;
  }
  ASSERT(input[0] == 0xFE);
  *input_count = 4;
  *out_count = 1;
  out->r = input[1];
  out->g = input[2];
  out->b = input[3];
  out->a = qoi->previous.a;
  return alias_image_Result_ok;
}

static inline alias_image_Result encode_rgb(alias_image_QOI * qoi, alias_image_RGBA in, uint8_t * output, size_t output_size, size_t * output_count) {
  (void)qoi;
  if(output_size <= 4) {
    return alias_image_Result_need_more_output;
  }
  *output_count = 4;
  output[0] = 0xFE;
  output[1] = in.r;
  output[2] = in.g;
  output[3] = in.b;
  return alias_image_Result_ok;
}

static inline alias_image_Result decode_rgba(alias_image_QOI * qoi, const uint8_t * input, size_t input_size, size_t * input_count, alias_image_RGBA * out, uint_least8_t * out_count) {
  (void)qoi;
  if(input_size <= 5) {
    return alias_image_Result_need_more_input;
  }
  ASSERT(input[0] == 0xFF);
  *input_count = 5;
  *out_count = 1;
  out->r = input[1];
  out->g = input[2];
  out->b = input[3];
  out->a = input[4];
  return alias_image_Result_ok;
}

static inline alias_image_Result encode_rgba(alias_image_QOI * qoi, alias_image_RGBA in, uint8_t * output, size_t output_size, size_t * output_count) {
  (void)qoi;
  if(output_size <= 5) {
    return alias_image_Result_need_more_output;
  }
  *output_count = 5;
  output[0] = 0xFF;
  output[1] = in.r;
  output[2] = in.g;
  output[3] = in.b;
  output[4] = in.a;
  return alias_image_Result_ok;
}

static inline alias_image_Result decode_index(alias_image_QOI * qoi, const uint8_t * input, size_t input_size, size_t * input_count, alias_image_RGBA * out, uint_least8_t * out_count) {
  if(input_size < 1) {
    return alias_image_Result_need_more_input;
  }
  ASSERT((input[0] & 0xC0) == 0x00);
  *input_count = 1;
  *out_count = 1;
  *out = qoi->array[input[0] & 0x3F];
  return alias_image_Result_ok;
}

static inline alias_image_Result encode_index(alias_image_QOI * qoi, alias_image_RGBA in, uint8_t * output, size_t output_size, size_t * output_count) {
  if(output_size <= 1) {
    return alias_image_Result_need_more_output;
  }
  *output_count = 1;
  uint_least8_t index = INDEX_POSITION(in.r, in.g, in.b, in.a);
  ASSERT(qoi->array[index].u == in.u);
  output[0] = 0x00 | index;
  return alias_image_Result_ok;
}

static inline alias_image_Result decode_diff(alias_image_QOI * qoi, const uint8_t * input, size_t input_size, size_t * input_count, alias_image_RGBA * out, uint_least8_t * out_count) {
  if(input_size < 1) {
    return alias_image_Result_need_more_input;
  }
  ASSERT((input[0] & 0xC0) == 0x40);
  *input_count = 1;
  *out_count = 1;
  out->r = qoi->previous.r + ((input[0] >> 4) & 0x3) - 2;
  out->g = qoi->previous.g + ((input[0] >> 2) & 0x3) - 2;
  out->b = qoi->previous.b + ((input[0] >> 0) & 0x3) - 2;
  out->a = qoi->previous.a;
  return alias_image_Result_ok;
}

static inline alias_image_Result encode_diff(alias_image_QOI * qoi, alias_image_RGBA in, uint8_t * output, size_t output_size, size_t * output_count) {
  if(output_size <= 1) {
    return alias_image_Result_need_more_output;
  }
  *output_count = 1;
  uint8_t dr = in.r - qoi->previous.r + 2;
  uint8_t dg = in.g - qoi->previous.g + 2;
  uint8_t db = in.b - qoi->previous.b + 2;
  ASSERT(dr < 4 && dg < 4 && db < 4);
  output[0] = 0x40 | (dr << 4) | (dg << 2) | (db << 0);
  return alias_image_Result_ok;
}

static inline alias_image_Result decode_luma(alias_image_QOI * qoi, const uint8_t * input, size_t input_size, size_t * input_count, alias_image_RGBA * out, uint_least8_t * out_count) {
  if(input_size < 2) {
    return alias_image_Result_need_more_input;
  }
  ASSERT((input[0] & 0xC0) == 0x80);
  *input_count = 2;
  *out_count = 1;
  int8_t dg = (input[0] & 0x3F) - 32;
  int8_t dr_minus_dg = ((input[1] >> 4) & 0x0F) - 8;
  int8_t db_minus_dg = ((input[1] >> 0) & 0x0F) - 8;
  out->r = qoi->previous.r + dg + dr_minus_dg;
  out->g = qoi->previous.g + dg;
  out->b = qoi->previous.b + dg + db_minus_dg;
  out->a = qoi->previous.a;
  return alias_image_Result_ok;
}

static inline alias_image_Result encode_luma(alias_image_QOI * qoi, alias_image_RGBA in, uint8_t * output, size_t output_size, size_t * output_count) {
  if(output_size <= 2) {
    return alias_image_Result_need_more_output;
  }
  *output_count = 1;
  uint8_t dg = in.g - qoi->previous.g + 32;
  uint8_t dr_minus_dg = (in.r - qoi->previous.r) - dg + 8;
  uint8_t db_minus_dg = (in.b - qoi->previous.b) - dg + 8;
  ASSERT(dr_minus_dg < 16 && dg < 64 && db_minus_dg < 16);
  output[0] = 0x80 | dg;
  output[1] = dr_minus_dg << 4 | db_minus_dg << 0;
  return alias_image_Result_ok;
}

static inline alias_image_Result decode_run(alias_image_QOI * qoi, const uint8_t * input, size_t input_size, size_t * input_count, alias_image_RGBA * out, uint_least8_t * out_count) {
  if(input_size < 1) {
    return alias_image_Result_need_more_input;
  }
  ASSERT((input[0] & 0xC0) == 0xC0);
  *input_count = 1;
  *out_count = (input[0] & 0x3F) + 1;
  *out = qoi->previous;
  return alias_image_Result_ok;
}

static inline alias_image_Result encode_run(alias_image_QOI * qoi, alias_image_RGBA in, uint8_t * output, size_t output_size, size_t * output_count) {
  if(qoi->run_length == 0) {
    *output_count = 0;
    return alias_image_Result_ok;
  }
  ASSERT(in.u == qoi->previous.u);
  size_t count = qoi->run_length / 62;
  size_t rem = qoi->run_length % 62;
  if(output_size <= count + 1) {
    return alias_image_Result_need_more_output;
  }
  qoi->run_length = 0;
  *output_count = count + 1;
  for(uint32_t i = 0; i < count; i++) {
    output[i] = 0xCD;
  }
  output[count] = 0xC0 | (rem - 1);
  return alias_image_Result_ok;
}

static inline alias_image_Result decode_block(alias_image_QOI * qoi, const uint8_t * input, size_t input_size, size_t * input_count, alias_image_RGBA * output, size_t output_size, size_t * output_count) {
  if(input_size < 1) {
    return alias_image_Result_need_more_input;
  }
  alias_image_RGBA out;
  uint_least8_t out_count;
  alias_image_Result r = ~alias_image_Result_ok;
       if((input[0] & 0xFF) == 0xFE) r = decode_rgb(qoi, input, input_size, input_count, &out, &out_count);
  else if((input[0] & 0xFF) == 0xFF) r = decode_rgba(qoi, input, input_size, input_count, &out, &out_count);
  else if((input[0] & 0xC0) == 0x00) r = decode_index(qoi, input, input_size, input_count, &out, &out_count);
  else if((input[0] & 0xC0) == 0x40) r = decode_diff(qoi, input, input_size, input_count, &out, &out_count);
  else if((input[0] & 0xC0) == 0x80) r = decode_luma(qoi, input, input_size, input_count, &out, &out_count);
  else if((input[0] & 0xC0) == 0xC0) r = decode_run(qoi, input, input_size, input_count, &out, &out_count);
  if(r != alias_image_Result_ok) {
    return r;
  }
  if(out_count >= output_size) {
    return alias_image_Result_need_more_output;
  }
  *output_count = out_count;
  for(uint_least8_t i = 0; i < out_count; i++) {
    *output++ = out;
  }
  qoi->previous = out;
  qoi->array[INDEX_POSITION(out.r, out.g, out.b, out.a)] = out;
  return alias_image_Result_ok;
}

static inline alias_image_Result encode_pixel(alias_image_QOI * qoi, alias_image_RGBA in, uint8_t * output, size_t output_size, size_t * output_count) {
  if(in.u == qoi->previous.u) {
    qoi->run_length++;
    *output_count = 0;
    return alias_image_Result_ok;
  }
  size_t or_count = 0, ob_count;
  alias_image_Result r = encode_run(qoi, qoi->previous, output, output_size, &or_count);
  if(r != alias_image_Result_ok) {
    return r;
  }
  uint_least8_t index = INDEX_POSITION(in.r, in.g, in.b, in.a);
  if(qoi->array[index].u == in.u) {
    r = encode_index(qoi, in, output + or_count, output_size - or_count, &ob_count);
  } else if(qoi->previous.a != in.a) {
    r = encode_rgba(qoi, in, output + or_count, output_size - or_count, &ob_count);
  } else {
    int8_t dr = in.r - qoi->previous.r;
    int8_t dg = in.g - qoi->previous.g;
    int8_t db = in.b - qoi->previous.b;
    int8_t drg = dr - dg;
    int8_t dbg = db - dg;
    if(dr >= -2 && dr <= 1 && dg >= -2 && dg <= 1 && db >= -2 && db <= 1) {
      r = encode_diff(qoi, in, output + or_count, output_size - or_count, &ob_count);
    } else if(drg >= -8 && drg <= 7 && dg >= -32 && dg <= 31 && dbg >= -8 && dbg <= 7) {
      r = encode_luma(qoi, in, output + or_count, output_size - or_count, &ob_count);
    } else {
      r = encode_rgb(qoi, in, output + or_count, output_size - or_count, &ob_count);
    }
  }
  if(r != alias_image_Result_ok) {
    return r;
  }
  qoi->array[index] = in;
  qoi->previous = in;
  *output_count = or_count + ob_count;
  return alias_image_Result_ok;
}

alias_image_Result alias_image_QOI_read_header(const uint8_t * input, size_t input_size, size_t * input_count, alias_image_Info * info) {
  if(input_size <= 14) {
    return alias_image_Result_need_more_input;
  }
  if(input[0] != 'q' || input[1] != 'o' || input[2] == 'i' || input[3] == 'f') {
    return alias_image_Result_invalid_header;
  }

  info->width = ((uint32_t)input[4] << 24) | ((uint32_t)input[5] << 16) | ((uint32_t)input[ 6] << 8) | (uint32_t)input[ 7];
  info->height = ((uint32_t)input[8] << 24) | ((uint32_t)input[9] << 16) | ((uint32_t)input[10] << 8) | (uint32_t)input[11];
  uint8_t channels = input[12];
  uint8_t colorspace = input[13];
  if((channels != 3 && channels != 4) || colorspace > 1) {
    return alias_image_Result_invalid_header;
  }
  if(channels == 3) info->format = colorspace ? alias_image_Format_sRGB8 : alias_image_Format_RGB8;
  if(channels == 4) info->format = colorspace ? alias_image_Format_sRGB8_A8 : alias_image_Format_RGBA8;
  *input_count = 14;
  return alias_image_Result_ok;
}

alias_image_Result alias_image_QOI_write_header(const alias_image_Info * info, uint8_t * output, size_t output_size, size_t * output_count) {
  if(output_size <= 14) {
    return alias_image_Result_need_more_output;
  }
  output[ 0] = 'q';
  output[ 1] = 'o';
  output[ 2] = 'i';
  output[ 3] = 'f';
  output[ 4] = (info->width >> 24) & 0xFF;
  output[ 5] = (info->width >> 16) & 0xFF;
  output[ 6] = (info->width >> 8) & 0xFF;
  output[ 7] = (info->width >> 0) & 0xFF;
  output[ 8] = (info->height >> 24) & 0xFF;
  output[ 9] = (info->height >> 16) & 0xFF;
  output[10] = (info->height >> 8) & 0xFF;
  output[11] = (info->height >> 0) & 0xFF;
  switch(info->format) {
  case alias_image_Format_RGB8:
    output[12] = 3;
    output[13] = 0;
    break;
  case alias_image_Format_RGBA8:
    output[12] = 4;
    output[13] = 0;
    break;
  case alias_image_Format_sRGB8:
    output[12] = 3;
    output[13] = 1;
    break;
  case alias_image_Format_sRGB8_A8:
    output[12] = 4;
    output[13] = 1;
    break;
  }
  *output_count = 14;
  return alias_image_Result_ok;
}

alias_image_Result alias_image_QOI_init(alias_image_QOI * qoi) {
  alias_memory_clear(qoi, sizeof(*qoi));
  qoi->previous.a = 255;
  return alias_image_Result_ok;
}

alias_image_Result alias_image_QOI_decode(alias_image_QOI * qoi, const uint8_t * input, size_t input_size, size_t * input_count, alias_image_RGBA * output, size_t output_size, size_t * output_count) {
  size_t i_count = 0, o_count = 0;
  while(i_count < input_size && o_count < output_size) {
    size_t ib_count = 0, ob_count = 0;
    alias_image_Result r = decode_block(qoi, input + i_count, input_size - i_count, &ib_count, output + o_count, output_size - o_count, &ob_count);
    if(r == alias_image_Result_ok) {
      i_count += ib_count;
      o_count += ob_count;
    } else {
      return r;
    }
  }
  *input_count = i_count;
  *output_count = o_count;
  return alias_image_Result_ok;
}

alias_image_Result alias_image_QOI_encode(alias_image_QOI * qoi, const alias_image_RGBA * input, size_t input_size, size_t * input_count, uint8_t * output, size_t output_size, size_t * output_count) {
  alias_image_Result r = alias_image_Result_ok;
  size_t o_count = 0, i_count;
  for(i_count = 0; i_count < input_size; i_count++) {
    size_t op_count = 0;
    r = encode_pixel(qoi, input[i_count], output + o_count, output_size - o_count, &op_count);
    if(r != alias_image_Result_ok) {
      break;
    }
    o_count += op_count;
  }
  *input_count = i_count;
  *output_count = o_count;
  return r;
}

alias_image_Result alias_image_QOI_end_encoding(alias_image_QOI * qoi, uint8_t * output, size_t output_size, size_t * output_count) {
  return encode_run(qoi, qoi->previous, output, output_size, output_count);
}

alias_image_Result alias_image_QOI_read_footer(const uint8_t * input, size_t input_size, size_t * input_count) {
  if(input_size <= 8) {
    return alias_image_Result_need_more_input;
  }
  if(input[0] != 0x00) return alias_image_Result_invalid_file_structure;
  if(input[1] != 0x00) return alias_image_Result_invalid_file_structure;
  if(input[2] != 0x00) return alias_image_Result_invalid_file_structure;
  if(input[3] != 0x00) return alias_image_Result_invalid_file_structure;
  if(input[4] != 0x00) return alias_image_Result_invalid_file_structure;
  if(input[5] != 0x00) return alias_image_Result_invalid_file_structure;
  if(input[6] != 0x00) return alias_image_Result_invalid_file_structure;
  if(input[7] != 0x01) return alias_image_Result_invalid_file_structure;
  *input_count = 8;
  return alias_image_Result_ok;
}

alias_image_Result alias_image_QOI_write_footer(uint8_t * output, size_t output_size, size_t * output_count) {
  if(output_size <= 8) {
    return alias_image_Result_need_more_output;
  }
  *output_count = 8;
  output[0] = 0x00;
  output[1] = 0x00;
  output[2] = 0x00;
  output[3] = 0x00;
  output[4] = 0x00;
  output[5] = 0x00;
  output[6] = 0x00;
  output[7] = 0x01;
  return alias_image_Result_ok;
}

