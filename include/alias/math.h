#ifndef _ALIAS_MATH_H_
#define _ALIAS_MATH_H_

#include <math.h>

#ifndef ALIAS_REAL_PRECISION
#define ALIAS_REAL_PRECISION 32
#endif

#if ALIAS_REAL_PRECISION == 32
typedef float alias_R;

#define alias_sin sinf
#define alias_cos cosf
#elif ALIAS_REAL_PRECISION == 64
typedef double alias_R;

#define alias_sin sin
#define alias_cos cos
#else
#error "invalid Alias real precision"
#endif

typedef struct alias_Point2D {
  alias_R x;
  alias_R y;
} alias_Point2D;

typedef struct alias_Vector2D {
  alias_R x;
  alias_R y;
} alias_Vector2D;

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
  alias_R i_det = 1.0f / alias_Affine2D_determinate(m);
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

typedef struct alias_Quaternion {
  alias_R x;
  alias_R y;
  alias_R z;
  alias_R w;
} alias_Quaternion;

#endif
