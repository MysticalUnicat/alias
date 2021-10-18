#ifndef _ALIAS_MATH_H_
#define _ALIAS_MATH_H_

#include <math.h>
#include <stdbool.h>
#include <float.h>

#ifndef ALIAS_REAL_PRECISION
#define ALIAS_REAL_PRECISION 32
#endif

#if ALIAS_REAL_PRECISION == 32
typedef float alias_R;

#define alias_sin sinf
#define alias_cos cosf
#define alias_fma fmaf
#define alias_pow powf
#define alias_sqrt sqrtf
#define alias_nan nanf
#define alias_abs fabsf

#define alias_R_EPSILON  FLT_EPSILON
#define alias_R_MIN      FLT_MIN
#define alias_R_MAX      FLT_MAX
#define alias_R_ZERO     0.0f
#define alias_R_ONE      1.0f
#define alias_R_TWO      2.0f
#define alias_R_PI       3.14159265358979323846264338327950288f
#define alias_R_NAN      alias_nan("")
#define alais_R_INFINITY INFINITY

#elif ALIAS_REAL_PRECISION == 64
typedef double alias_R;

#define alias_sin sin
#define alias_cos cos
#define alias_fma fma
#define alias_pow pow

#else
#error "invalid Alias real precision"
#endif

static inline bool alias_R_is_zero(alias_R a) {
  return alias_abs(a) < alias_R_MIN;
}

static inline bool alias_R_fuzzy_eq(alias_R a, alias_R b) {
  return alias_abs(a - b) < alias_R_MIN;
}

#define ALIAS_MIN_PAIR(A, B) ((A) < (B) ? (A) : (B))
#define ALIAS_MAX_PAIR(A, B) ((A) > (B) ? (A) : (B))

#define alias_min(A, B) ALIAS_MIN_PAIR(A, B)
#define alias_max(A, B) ALIAS_MAX_PAIR(A, B)

#include <alias/pga2d.h>

// TODO modify gen program to add these aliases
// something like:
//  --type line:abc a=e1,b=e2,c=e0
//  --type point:xy x=e02,y=e01,1=e12
//  --type direction:xy x=e02,y=e01,0=e12

typedef alias_pga2d_0100 alias_pga2d_Line;
typedef alias_pga2d_0010 alias_pga2d_Point;
typedef alias_pga2d_0010 alias_pga2d_Direction;
typedef alias_pga2d_1010 alias_pga2d_Motor;

#define alias_pga2d_line(a, b, c) ((alias_pga2d_Line) { .e1 = a, .e2 = b, .e0 = c })
#define alias_pga2d_line_a(l) l.e1
#define alias_pga2d_line_b(l) l.e2
#define alias_pga2d_line_c(l) l.e0

#define alias_pga2d_point(x, y) ((alias_pga2d_Point) { .e02 = x, .e01 = y, .e12 = 1 })
#define alias_pga2d_point_x(p) p.e02
#define alias_pga2d_point_y(p) p.e01

#define alias_pga2d_direction(x, y) ((alias_pga2d_Direction) { .e02 = x, .e01 = y })
#define alias_pga2d_direction_x(p) p.e02
#define alias_pga2d_direction_y(p) p.e01

#define alias_pga2d_UP alias_pga2d_direction(-1, 0)
#define alias_pga2d_DOWN alias_pga2d_direction(1, 0)
#define alias_pga2d_LEFT alias_pga2d_direction(0, -1)
#define alias_pga2d_RIGHT alias_pga2d_direction(0, 1)

static inline alias_pga2d_Motor alias_pga2d_rotor(float angle) {
  angle /= 2;
  return (alias_pga2d_Motor) { .one = cos(angle), .e12 = sin(angle) };
}

static inline alias_pga2d_Motor alias_pga2d_translator(float distance, alias_pga2d_Direction direction) {
  distance /= 2;
  return (alias_pga2d_Motor) { .one = 1, .e02 = direction.e02 * distance, .e01 = direction.e01 * distance };
}

#define alias_pga2d_motor(angle, direction) alias_pga2d_mul_mm(alias_pga2d_rotor(angle), alias_pga2d_translator(1, direction))

#define alias_pga2d_sandwich(x, y) alias_pga2d_mul(alias_pga2d_mul(y, x), alias_pga2d_reverse(y))
#define alias_pga2d_lerp(x, y, t) alias_pga2d_add(alias_pga2d_mul(alias_pga2d_s(t), y), alias_pga2d_mul(alias_pga2d_sub(alias_pga2d_s(1), alias_pga2d_s(t)), x))

#define alias_pga2d_sandwich_bm(x, y) alias_pga2d_grade_2(alias_pga2d_sandwich(alias_pga2d_b(x), alias_pga2d_m(y)))
#define alias_pga2d_sandwich_bb(x, y) alias_pga2d_grade_2(alias_pga2d_sandwich(alias_pga2d_b(x), alias_pga2d_b(y)))
#define alias_pga2d_lerp_b(x, y, t) alias_pga2d_lerp(alias_pga2d_b(x), alias_pga2d_b(y), t)

#endif

