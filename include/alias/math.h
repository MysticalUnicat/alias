#ifndef _ALIAS_MATH_H_
#define _ALIAS_MATH_H_

#include <math.h>

typedef struct alias_Point2D {
  float x;
  float y;
} alias_Point2D;

typedef struct alias_Vector2D {
  float x;
  float y;
} alias_Vector2D;

typedef struct alias_Angle2D {
  float angle;
} alias_Angle2D;

// affine 3x3 matrix
typedef struct alias_Affine2D {
  float _11, _12, _13;
  float _21, _22, _23;
} alias_Affine2D;

static inline alias_Affine2D alias_construct_Affine2D(float x, float y, float a) {
  float s = sin(a);
  float c = cos(a);
  return (alias_Affine2D) {
       c, s, x
    , -s, c, y
  };
}

static inline alias_Affine2D alias_construct_Affine2D_inverse(float x, float y, float a) {
  float s = sin(a);
  float c = cos(a);
  return (alias_Affine2D) {
      c, -s, -( c*x) - (s*y)
    , s,  c, -(-s*x) - (c*y)
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

static inline alias_Affine2D alias_Affine2D_inverse(alias_Affine2D m) {
  return (alias_Affine2D) {
      m._11, m._21, -(m._11*m._13) - (m._12*m._23)
    , m._12, m._22, -(m._21*m._13) - (m._22*m._23)
  };
}

static inline alias_Point2D alias_multiply_Affine2D_Point2D(alias_Affine2D m, alias_Point2D p) {
  return (alias_Point2D) {
      m._11*p.x + m._12*p.y + m._13
    , m._21*p.x + m._22*p.y + m._23
  };
}

static inline alias_Vector2D alias_multiply_Affine2D_Vector2D(alias_Affine2D m, alias_Vector2D v) {
  return (alias_Vector2D) {
      m._11*v.x + m._12*v.y
    , m._21*v.x + m._22*v.y
  };
}

typedef struct alias_Point3D {
  float x;
  float y;
  float z;
} alias_Point3D;

typedef struct alias_Vector3D {
  float x;
  float y;
  float z;
} alias_Vector3D;

static inline float alias_Vector3D_dot_product(alias_Vector3D a, alias_Vector3D b) {
  return (a.x*b.x + a.y*b.y + a.z*b.z);
}

typedef struct alias_Quaternion {
  float x;
  float y;
  float z;
  float w;
} alias_Quaternion;

#endif

