// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <alias/memory.h>

#include <alias/cpp.h>
#include <alias/math.h>

static struct {
  uint32_t size;
} _format_info[] = {
    [alias_memory_Format_Unknown] = {0},   [alias_memory_Format_Uint8] = {1},    [alias_memory_Format_Uint16] = {2},    [alias_memory_Format_Uint32] = {4},
    [alias_memory_Format_Uint64] = {8},    [alias_memory_Format_Sint8] = {1},    [alias_memory_Format_Sint16] = {2},    [alias_memory_Format_Sint32] = {4},
    [alias_memory_Format_Sint64] = {8},    [alias_memory_Format_Unorm8] = {1},   [alias_memory_Format_Unorm16] = {2},   [alias_memory_Format_Snorm8] = {1},
    [alias_memory_Format_Snorm16] = {2},   [alias_memory_Format_Uscaled8] = {1}, [alias_memory_Format_Uscaled16] = {2}, [alias_memory_Format_Sscaled8] = {1},
    [alias_memory_Format_Sscaled16] = {2}, [alias_memory_Format_Urgb8] = {1},    [alias_memory_Format_Float16] = {2},   [alias_memory_Format_Float32] = {4},
    [alias_memory_Format_Float64] = {8}};

uint32_t alias_memory_Format_size(alias_memory_Format format) { return _format_info[format].size; }

typedef void (*ConvertFn)(void *dst, uint32_t dst_stride, const void *src, uint32_t src_stride, uint32_t length, uint32_t count);

#define _READS(X, ...)                                                                                                                                         \
  X(Unknown, uint8_t, 0, 0, 0, ##__VA_ARGS__)                                                                                                                  \
  X(Uint8, uint8_t, *r, *r, *r, ##__VA_ARGS__)                                                                                                                 \
  X(Uint16, uint16_t, *r, *r, *r, ##__VA_ARGS__)                                                                                                               \
  X(Uint32, uint32_t, *r, *r, *r, ##__VA_ARGS__)                                                                                                               \
  X(Uint64, uint64_t, *r, *r, *r, ##__VA_ARGS__)                                                                                                               \
  X(Sint8, int8_t, *r, *r, *r, ##__VA_ARGS__)                                                                                                                  \
  X(Sint16, int16_t, *r, *r, *r, ##__VA_ARGS__)                                                                                                                \
  X(Sint32, int32_t, *r, *r, *r, ##__VA_ARGS__)                                                                                                                \
  X(Sint64, int64_t, *r, *r, *r, ##__VA_ARGS__)                                                                                                                \
  X(Unorm8, uint8_t, 0, 0, (*r) / 255.0, ##__VA_ARGS__)                                                                                                        \
  X(Unorm16, uint16_t, 0, 0, (*r) / 65535.0, ##__VA_ARGS__)                                                                                                    \
  X(Snorm8, int8_t, 0, 0, (*r) / 127.0, ##__VA_ARGS__)                                                                                                         \
  X(Snorm16, int16_t, 0, 0, (*r) / 32767.0, ##__VA_ARGS__)                                                                                                     \
  X(Uscaled8, uint8_t, 0, 0, *r, ##__VA_ARGS__)                                                                                                                \
  X(Uscaled16, uint16_t, 0, 0, *r, ##__VA_ARGS__)                                                                                                              \
  X(Sscaled8, int8_t, 0, 0, *r, ##__VA_ARGS__)                                                                                                                 \
  X(Sscaled16, int16_t, 0, 0, *r, ##__VA_ARGS__)                                                                                                               \
  X(Urgb8, uint8_t, 0, 0, *r, ##__VA_ARGS__)                                                                                                                   \
  X(Float16, uint16_t, 0, 0, *r, ##__VA_ARGS__)                                                                                                                \
  X(Float32, float, 0, 0, *r, ##__VA_ARGS__)                                                                                                                   \
  X(Float64, double, 0, 0, *r, ##__VA_ARGS__)

#define _WRITES(X, ...)                                                                                                                                        \
  X(Unknown, uint8_t, 0, 0, 0, ##__VA_ARGS__)                                                                                                                  \
  X(Uint8, uint8_t, in, in, in, ##__VA_ARGS__)                                                                                                                 \
  X(Uint16, uint16_t, in, in, in, ##__VA_ARGS__)                                                                                                               \
  X(Uint32, uint32_t, in, in, in, ##__VA_ARGS__)                                                                                                               \
  X(Uint64, uint64_t, in, in, in, ##__VA_ARGS__)                                                                                                               \
  X(Sint8, int8_t, in, in, in, ##__VA_ARGS__)                                                                                                                  \
  X(Sint16, int16_t, in, in, in, ##__VA_ARGS__)                                                                                                                \
  X(Sint32, int32_t, in, in, in, ##__VA_ARGS__)                                                                                                                \
  X(Sint64, int64_t, in, in, in, ##__VA_ARGS__)                                                                                                                \
  X(Unorm8, uint8_t, 0, 0, (uint8_t)(in * 255.0), ##__VA_ARGS__)                                                                                               \
  X(Unorm16, uint16_t, 0, 0, (uint16_t)(in * 65535.0), ##__VA_ARGS__)                                                                                          \
  X(Snorm8, int8_t, 0, 0, (int8_t)(in * 127.0), ##__VA_ARGS__)                                                                                                 \
  X(Snorm16, int16_t, 0, 0, (int16_t)(in * 32767.0), ##__VA_ARGS__)                                                                                            \
  X(Uscaled8, uint8_t, 0, 0, in, ##__VA_ARGS__)                                                                                                                \
  X(Uscaled16, uint16_t, 0, 0, in, ##__VA_ARGS__)                                                                                                              \
  X(Sscaled8, int8_t, 0, 0, in, ##__VA_ARGS__)                                                                                                                 \
  X(Sscaled16, int16_t, 0, 0, in, ##__VA_ARGS__)                                                                                                               \
  X(Urgb8, uint8_t, 0, 0, in, ##__VA_ARGS__)                                                                                                                   \
  X(Float16, uint16_t, 0, 0, in, ##__VA_ARGS__)                                                                                                                \
  X(Float32, float, 0, 0, in, ##__VA_ARGS__)                                                                                                                   \
  X(Float64, double, 0, 0, in, ##__VA_ARGS__)

#define _GEN_CONVERT_1(R_NAME, R_TYPE, R_U, R_S, R_F) _WRITES(_GEN_CONVERT_2, R_NAME, R_TYPE, R_U, R_S, R_F)

#define _GEN_CONVERT_2(W_NAME, W_TYPE, W_U, W_S, W_F, R_NAME, R_TYPE, R_U, R_S, R_F)                                                                           \
  static inline void _##R_NAME##_to_##W_NAME(void *dst, uint32_t dst_stride, const void *src, uint32_t src_stride, uint32_t length, uint32_t count) {          \
    W_TYPE *wp = (W_TYPE *)dst;                                                                                                                                \
    const R_TYPE *rp = (R_TYPE *)src;                                                                                                                          \
    for(uint32_t i = 0; i < count; i++) {                                                                                                                      \
      W_TYPE *w = wp;                                                                                                                                          \
      const R_TYPE *r = rp;                                                                                                                                    \
      for(uint32_t j = 0; j < length; j++) {                                                                                                                   \
        ALIAS_CPP_IF1(ALIAS_CPP_IS_ZERO(W_S))                                                                                                                  \
        (ALIAS_CPP_IF1(ALIAS_CPP_IS_ZERO(W_U))(float in = R_F; (void)in; *w = W_F;)(uint64_t in = R_U; (void)in; *w = W_U;))(int64_t in = R_S; (void)in;       \
                                                                                                                             *w = W_S;) w++;                   \
        r++;                                                                                                                                                   \
      }                                                                                                                                                        \
      wp = (W_TYPE *)((uint8_t *)wp + dst_stride);                                                                                                             \
      rp = (R_TYPE *)((uint8_t *)rp + src_stride);                                                                                                             \
    }                                                                                                                                                          \
  }

_READS(_GEN_CONVERT_1)

#define _CONVERT_FN_1(R_NAME, R_TYPE, R_U, R_S, R_F) _WRITES(_CONVERT_FN_2, R_NAME)
#define _CONVERT_FN_2(W_NAME, W_TYPE, W_U, W_S, W_F, R_NAME)                                                                                                   \
  [alias_memory_Format_##W_NAME * alias_memory_Format_COUNT + alias_memory_Format_##R_NAME] = _##R_NAME##_to_##W_NAME,

static ConvertFn _convert_functions[alias_memory_Format_COUNT * alias_memory_Format_COUNT] = {_READS(_CONVERT_FN_1)};

static inline void _copy(void *dst_pointer, uint32_t dst_stride, alias_memory_Format dst_format, const void *src_pointer, uint32_t src_stride,
                         alias_memory_Format src_format, uint32_t length, uint32_t count) {
  _convert_functions[dst_format * alias_memory_Format_COUNT + src_format](dst_pointer, dst_stride, src_pointer, src_stride, length, count);
}

void alias_memory_SubBuffer_copy_from_SubBuffer(alias_memory_SubBuffer *dst, const alias_memory_SubBuffer *src, uint32_t count) {
  _copy(dst->pointer, dst->stride, dst->type_format, src->pointer, src->stride, src->type_format, dst->type_length, count);
}

int alias_memory_SubBuffer_write(alias_memory_SubBuffer *dst, uint32_t index, uint32_t count, alias_memory_Format src_format, uint32_t src_stride,
                                 const void *src) {
  uint32_t length = dst->type_length, dst_stride = dst->stride ? dst->stride : _format_info[dst->type_format].size * length;
  src_stride = src_stride ? src_stride : _format_info[src_format].size * length;

  uint32_t end = alias_min(index + count, dst->count);
  count = end - index;

  _copy((uint8_t *)dst->pointer + index * dst_stride, dst->stride, dst->type_format, src, src_stride, src_format, length, count);

  return count;
}

int alias_memory_SubBuffer_read(const alias_memory_SubBuffer *src, uint32_t index, uint32_t count, alias_memory_Format dst_format, uint32_t dst_stride,
                                void *dst) {
  uint32_t length = src->type_length, src_stride = src->stride ? src->stride : _format_info[src->type_format].size * length;
  dst_stride = dst_stride ? dst_stride : _format_info[dst_format].size * length;

  uint32_t end = alias_min(index + count, src->count);
  count = end - index;

  _copy(dst, dst_stride, dst_format, (uint8_t *)src->pointer + index * dst_stride, src_stride, src->type_format, length, count);

  return count;
}
