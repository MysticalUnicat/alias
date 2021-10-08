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

#define alias_pga2d_motor(angle, x, y) ((alias_pga2d_Transform) { .one = cos(angle / 2), .e02 = x, .e01 = y, .e12 = sin(angle / 2) })

// TODO: nuke this
#if 0
typedef struct alias_Point2D {
  alias_R x;
  alias_R y;
} alias_Point2D;

typedef struct alias_Vector2D {
  alias_R x;
  alias_R y;
} alias_Vector2D;

static inline alias_R alias_Vector2D_dot_product(alias_Vector2D a, alias_Vector2D b) {
  return (a.x*b.x + a.y*b.y);
}

static inline alias_R alias_Vector2D_length(alias_Vector2D v) {
  return alias_sqrt(alias_Vector2D_dot_product(v, v));
}

static inline alias_Vector2D alias_add_Vector2D_Vector2D(alias_Vector2D a, alias_Vector2D b) {
  return (alias_Vector2D) {
      a.x + b.x
    , a.y + b.y
  };
}

static inline alias_Vector2D alias_subtract_Vector2D_Vector2D(alias_Vector2D a, alias_Vector2D b) {
  return (alias_Vector2D) {
      a.x - b.x
    , a.y - b.y
  };
}

static inline alias_Vector2D alias_multiply_Vector2D_R(alias_Vector2D v, alias_R s) {
  return (alias_Vector2D) { v.x * s, v.y * s };
}

static inline alias_Vector2D alias_divide_Vector2D_R(alias_Vector2D v, alias_R s) {
  if(alias_R_is_zero(s)) {
    return (alias_Vector2D) { alias_nan("_ / 0"), alias_nan("_ / 0") };
  }
  s = alias_R_ONE / s;
  return (alias_Vector2D) { v.x * s, v.y * s };
}

typedef struct alias_Normal2D {
  alias_R x;
  alias_R y;
} alias_Normal2D;

static inline bool alias_Vector2D_normalize(alias_Vector2D v, alias_R * length, alias_Normal2D * normal) {
  *length = alias_Vector2D_length(v);
  if(*length > alias_R_MIN) {
    alias_R scale = alias_R_ONE / *length; 
    normal->x = v.x * scale;
    normal->y = v.y * scale;
    return true;
  }
  normal->x = alias_nan("0 = |v|");
  normal->y = alias_nan("0 = |v|");
  return false;
}

typedef struct alias_Angle2D {
  alias_R angle;
} alias_Angle2D;

// row-major affine 3x3 matrix without storing the last row: 0 ... 0 | 1
typedef struct alias_Affine2D {
  alias_R _11, _12, _13;
  alias_R _21, _22, _23;
} alias_Affine2D;

static inline alias_Affine2D alias_construct_Affine2D(alias_R x, alias_R y, alias_R a) {
  alias_R s = sin(a);
  alias_R c = cos(a);
  return (alias_Affine2D) {
      c, -s, x
    , s,  c, y
  };
}

static inline alias_Affine2D alias_construct_Affine2D_inverse(alias_R x, alias_R y, alias_R a) {
  alias_R s = alias_sin(a);
  alias_R c = alias_cos(a);
  return (alias_Affine2D) {
       c, s, (-x *  c + -y * s)
    , -s, c, (-x * -s + -y * c)
  };
}

static inline alias_R alias_Affine2D_determinate(alias_Affine2D m) {
  return m._11*m._22 - m._12*m._21;
}

static inline alias_Affine2D alias_Affine2D_inverse(alias_Affine2D m) {
  alias_R i_det = alias_R_ONE / alias_Affine2D_determinate(m);
  return (alias_Affine2D) {
       m._22 * i_det, -m._12 * i_det, (m._22 * m._13 - m._12 * m._23) * i_det
    , -m._21 * i_det,  m._11 * i_det, (m._21 * m._13 - m._11 * m._23) * i_det
  };
}

static inline alias_Affine2D alias_multiply_Affine2D_Affine2D(alias_Affine2D m1, alias_Affine2D m2) {
  return (alias_Affine2D) {
      m1._11*m2._11 + m1._12*m2._21
    , m1._11*m2._12 + m1._12*m2._22
    , m1._11*m2._13 + m1._12*m2._23 + m1._13
    , m1._21*m2._11 + m1._22*m2._21
    , m1._21*m2._12 + m1._22*m2._22
    , m1._21*m2._13 + m1._22*m2._23 + m1._23
  };
}

static inline alias_Point2D alias_multiply_Affine2D_Point2D(alias_Affine2D m, alias_Point2D p) {
  return (alias_Point2D) {
      m._11 * p.x + m._12 * p.y + m._13
    , m._21 * p.x + m._22 * p.y + m._23
  };
}

static inline alias_Vector2D alias_multiply_Affine2D_Vector2D(alias_Affine2D m, alias_Vector2D v) {
  return (alias_Vector2D) {
      m._11 * v.x + m._12 * v.y
    , m._21 * v.x + m._22 * v.y
  };
}

typedef struct alias_Point3D {
  alias_R x;
  alias_R y;
  alias_R z;
} alias_Point3D;

typedef struct alias_Vector3D {
  alias_R x;
  alias_R y;
  alias_R z;
} alias_Vector3D;

static inline alias_R alias_Vector3D_dot_product(alias_Vector3D a, alias_Vector3D b) {
  return (a.x*b.x + a.y*b.y + a.z*b.z);
}
#endif

#endif

