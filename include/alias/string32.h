// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_STRING32_H_
#define _ALIAS_STRING32_H_

#include <tabula.h>

// character classification
bool alias_char32_is_alnum(char32_t);
bool alias_char32_is_alpha(char32_t);
bool alias_char32_is_lower(char32_t);
bool alias_char32_is_upper(char32_t);
bool alias_char32_is_digit(char32_t);
bool alias_char32_is_xdigit(char32_t);
bool alias_char32_is_cntrl(char32_t);
bool alias_char32_is_graph(char32_t);
bool alias_char32_is_space(char32_t);
bool alias_char32_is_blank(char32_t);
bool alias_char32_is_print(char32_t);
bool alias_char32_is_punct(char32_t);

// character manipulation
char32_t alias_char32_to_lower(char32_t);
char32_t alias_char32_to_upper(char32_t);

// conversion to numeric formats
uint32_t alias_string32_to_uint32(const char32_t * restrict string, char32_t * * restrict end, uint_least8_t base);
uint64_t alias_string32_to_uint64(const char32_t * restrict string, char32_t * * restrict end, uint_least8_t base);

int32_t alias_string32_to_int32(const char32_t * restrict string, char32_t * * restrict end, uint_least8_t base);
int64_t alias_string32_to_int64(const char32_t * restrict string, char32_t * * restrict end, uint_least8_t base);

float alias_string32_to_float32(const char32_t * restrict string, char32_t * * restrict end);
double alias_string32_to_float64(const char32_t * restrict string, char32_t * * restrict end);

// string manipulation
void alias_string32_copy(char32_t * restrict dst, uintmax_t dst_size, const char32_t * restrict src);
void alias_string32_copy_n(char32_t * restrict dst, uintmax_t dst_size, const char32_t * restrict src, uintmax_t n);
void alias_string32_concat(char32_t * restrict dst, uintmax_t dst_size, const char32_t * restrict src);
void alias_string32_concat_n(char32_t * restrict dst, uintmax_t dst_size, const char32_t * restrict src, uintmax_t count);

// string examination
size_t alias_string32_length(const char32_t * str, uintmax_t src_size);
int_least32_t alias_string32_compare(const char32_t * lhs, const char32_t * rhs);
int_least32_t alias_string32_collate(const char32_t * lhs, const char32_t * rhs);
size_t alias_string32_char(const char32_t * str, char32_t test);
size_t alias_string32_char_reverse(const char32_t * str, char32_t test);
size_t alias_string32_span(const char32_t * str, const char32_t * test);
size_t alias_string32_span_reverse(const char32_t * str, const char32_t * test);
size_t alias_string32_break(const char32_t * str, const char32_t * test);
size_t alias_string32_break_reverse(const char32_t * str, const char32_t * test);
size_t alias_string32_string(const char32_t * str, const char32_t * test);
size_t alias_string32_string_reverse(const char32_t * str, const char32_t * test);

#endif // _ALIAS_STRING32_H_

