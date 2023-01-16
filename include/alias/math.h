// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_MATH_H_
#define _ALIAS_MATH_H_

#include <float.h>
#include <math.h>
#include <stdbool.h>

#ifndef ALIAS_REAL_PRECISION
#define ALIAS_REAL_PRECISION 32
#endif

#if ALIAS_REAL_PRECISION == 32
typedef float alias_R;

#define alias_R_sin sinf
#define alias_R_cos cosf
#define alias_R_fma fmaf
#define alias_R_pow powf
#define alias_R_sqrt sqrtf
#define alias_R_nan nanf
#define alias_R_abs fabsf
#define alias_R_isnan isnan

#define alias_R_EPSILON FLT_EPSILON
#define alias_R_MIN FLT_MIN
#define alias_R_MAX FLT_MAX
#define alias_R_ZERO 0.0f
#define alias_R_ONE 1.0f
#define alias_R_TWO 2.0f
#define alias_R_PI 3.14159265358979323846264338327950288f
#define alias_R_NAN alias_R_nan("")
#define alais_R_INFINITY INFINITY

#elif ALIAS_REAL_PRECISION == 64
typedef double alias_R;

#define alias_R_sin sin
#define alias_R_cos cos
#define alias_R_fma fma
#define alias_R_pow pow

#else
#error "invalid Alias real precision"
#endif

#define alias_R_isqrt(X) alias_R_pow(X, -0.5)

static inline bool alias_R_is_zero(alias_R a) { return alias_R_abs(a) < alias_R_MIN; }

static inline bool alias_R_fuzzy_eq(alias_R a, alias_R b) { return alias_R_abs(a - b) < alias_R_MIN; }

#define ALIAS_MIN_PAIR(A, B) ((A) < (B) ? (A) : (B))
#define ALIAS_MAX_PAIR(A, B) ((A) > (B) ? (A) : (B))

#define alias_min(A, B) ALIAS_MIN_PAIR(A, B)
#define alias_max(A, B) ALIAS_MAX_PAIR(A, B)

#include <alias/pga2d.h>
#include <alias/pga3d.h>

// TODO modify gen program to add these aliases
// something like:
//  --type line:abc a=e1,b=e2,c=e0
//  --type point:xy x=e02,y=e01,1=e12
//  --type direction:xy x=e02,y=e01,0=e12

typedef alias_pga2d_0100 alias_pga2d_Line;
typedef alias_pga2d_0010 alias_pga2d_Point;
typedef alias_pga2d_0010 alias_pga2d_Direction;
typedef alias_pga2d_1010 alias_pga2d_Motor;

typedef alias_pga3d_01000 alias_pga3d_Plane;
typedef alias_pga3d_00100 alias_pga3d_Line;
typedef alias_pga3d_00010 alias_pga3d_Point;
typedef alias_pga3d_00010 alias_pga3d_Direction;
typedef alias_pga3d_10101 alias_pga3d_Motor;

#define alias_pga2d_Motor_IDENTITY ((alias_pga2d_Motor){.one = 1})
#define alias_pga3d_Motor_IDENTITY ((alias_pga3d_Motor){.one = 1})

#define alias_pga2d_line(a, b, c) ((alias_pga2d_Line){.e1 = a, .e2 = b, .e0 = c})
#define alias_pga2d_line_a(l) l.e1
#define alias_pga2d_line_b(l) l.e2
#define alias_pga2d_line_c(l) l.e0

#define alias_pga2d_point(x, y) ((alias_pga2d_Point){.e02 = -x, .e01 = y, .e12 = 1})
#define alias_pga2d_point_x(p) -p.e02
#define alias_pga2d_point_y(p) p.e01

#define alias_pga3d_point(x, y, z) ((alias_pga3d_Point){.e023 = x, .e013 = y, .e012 = z, .e123 = 1})
#define alias_pga3d_point_x(p) p.e023
#define alias_pga3d_point_y(p) p.e013
#define alias_pga3d_point_z(p) p.e012

#define alias_pga2d_direction(x, y) ((alias_pga2d_Direction){.e02 = -x, .e01 = y})
#define alias_pga2d_direction_x(p) -p.e02
#define alias_pga2d_direction_y(p) p.e01

#define alias_pga3d_direction(x, y, z) ((alias_pga3d_Direction){.e023 = x, .e013 = y, .e012 = z})
#define alias_pga3d_direction_x(p) p.e023
#define alias_pga3d_direction_y(p) p.e013
#define alias_pga3d_direction_z(p) p.e012

#define alias_pga2d_UP alias_pga2d_direction(-1, 0)
#define alias_pga2d_DOWN alias_pga2d_direction(1, 0)
#define alias_pga2d_LEFT alias_pga2d_direction(0, -1)
#define alias_pga2d_RIGHT alias_pga2d_direction(0, 1)

#define alias_pga2d_motor(angle, distance, direction) alias_pga2d_mul_mm(alias_pga2d_rotor(angle), alias_pga2d_translator(distance, direction))
#define alias_pga3d_motor(angle, line, distance, direction) alias_pga3d_mul_mm(alias_pga3d_rotor(angle, line), alias_pga3d_translator(distance, direction))
#define alias_pga3d_motor_to(angle, line, point) alias_pga3d_mul_mm(alias_pga3d_rotor(angle, line), alias_pga3d_translator_to(point))

#define alias_pga2d_sandwich(x, y) alias_pga2d_mul(alias_pga2d_mul(y, x), alias_pga2d_reverse(y))
#define alias_pga3d_sandwich(x, y) alias_pga3d_mul(alias_pga3d_mul(y, x), alias_pga3d_reverse(y))

#define alias_pga2d_lerp(x, y, t) alias_pga2d_add(alias_pga2d_mul(alias_pga2d_s(t), y), alias_pga2d_mul(alias_pga2d_sub(alias_pga2d_s(1), alias_pga2d_s(t)), x))
#define alias_pga3d_lerp(x, y, t) alias_pga3d_add(alias_pga3d_mul(alias_pga3d_s(t), y), alias_pga3d_mul(alias_pga3d_sub(alias_pga3d_s(1), alias_pga3d_s(t)), x))

#define alias_pga2d_norm(x) alias_R_sqrt(alias_R_abs(alias_pga2d_mul(x, alias_pga2d_conjugate(x)).one))
#define alias_pga3d_norm(x) alias_R_sqrt(alias_R_abs(alias_pga3d_mul(x, alias_pga3d_conjugate(x)).one))

#define alias_pga2d_inorm(x) alias_pga2d_norm(alias_pga2d_dual(x))
#define alias_pga3d_inorm(x) alias_pga3d_norm(alias_pga3d_dual(x))

#define alias_pga3d_normalize(x) alias_pga3d_mul(alias_pga3d_s(1.0f / alias_pga3d_norm(x)), x)
#define alias_pga3d_inormalize(x) alias_pga3d_mul(alias_pga3d_s(1.0f / alias_pga3d_inorm(x)), x)

#define alias_pga2d_sandwich_vm(x, y) alias_pga2d_grade_1(alias_pga2d_sandwich(alias_pga2d_v(x), alias_pga2d_m(y)))
#define alias_pga2d_sandwich_vb(x, y) alias_pga2d_grade_1(alias_pga2d_sandwich(alias_pga2d_v(x), alias_pga2d_b(y)))
#define alias_pga2d_sandwich_bm(x, y) alias_pga2d_grade_2(alias_pga2d_sandwich(alias_pga2d_b(x), alias_pga2d_m(y)))
#define alias_pga2d_sandwich_bb(x, y) alias_pga2d_grade_2(alias_pga2d_sandwich(alias_pga2d_b(x), alias_pga2d_b(y)))

#define alias_pga3d_sandwich_tm(x, y) alias_pga3d_grade_3(alias_pga3d_sandwich(alias_pga3d_t(x), alias_pga3d_m(y)))

#define alias_pga2d_lerp_b(x, y, t) alias_pga2d_lerp(alias_pga2d_b(x), alias_pga2d_b(y), t)
#define alias_pga2d_lerp_m(x, y, t) alias_pga2d_lerp(alias_pga2d_m(x), alias_pga2d_m(y), t)

#define alias_pga3d_lerp_m(x, y, t) alias_pga3d_lerp(alias_pga3d_m(x), alias_pga3d_m(y), t)

static inline alias_pga2d_Motor alias_pga2d_rotor(float angle) {
  angle /= 2;
  return (alias_pga2d_Motor){.one = cos(angle), .e12 = sin(angle)};
}

static inline alias_pga3d_Motor alias_pga3d_rotor(float angle, alias_pga3d_Line line) {
  angle /= 2;
  float s = sin(angle);
  return (alias_pga3d_Motor){.one = cos(angle), .e01 = 0, .e02 = 0, .e03 = 0, .e12 = line.e12 * s, .e13 = line.e13 * s, .e23 = line.e23 * s, .e0123 = 0};
}

static inline alias_pga2d_Motor alias_pga2d_translator(float distance, alias_pga2d_Direction direction) {
  distance /= 2;
  return (alias_pga2d_Motor){.one = 1, .e02 = direction.e02 * distance, .e01 = direction.e01 * distance, .e12 = alias_R_ZERO};
}

static inline alias_pga3d_Motor alias_pga3d_translator(float distance, alias_pga3d_Direction direction) {
  distance /= 2;
  return (alias_pga3d_Motor){
      .one = 1, .e01 = direction.e023 * distance, .e02 = direction.e013 * distance, .e03 = direction.e012 * distance, .e12 = 0, .e13 = 0, .e23 = 0, .e0123 = 0};
}

static inline alias_pga2d_Motor alias_pga2d_translator_to(alias_pga2d_Point point) {
  float distance = 0.5f;
  return (alias_pga2d_Motor){.one = 1, .e02 = point.e02 * distance, .e01 = point.e01 * distance, .e12 = alias_R_ZERO};
}

static inline alias_pga3d_Motor alias_pga3d_translator_to(alias_pga3d_Point point) {
  alias_pga3d_Line line = alias_pga3d_grade_2(alias_pga3d_mul(alias_pga3d_t(point), alias_pga3d_negate_t(alias_pga3d_point(0, 0, 0))));
  return (alias_pga3d_Motor){.one = 1, .e01 = line.e01 * 0.5f, .e02 = line.e02 * 0.5f, .e03 = line.e03 * 0.5f, .e12 = 0, .e13 = 0, .e23 = 0, .e0123 = 0};
}

#endif
