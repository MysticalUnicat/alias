#ifndef _ALIAS_PGA_H_
#define _ALIAS_PGA_H_

// https://bivector.net/

#include <alias/pga/operators.h>

// types for combinations of 16-dimensional mulivectors
#include <alias/pga/types.h>

// simple operators
#include <alias/pga/negate.h>
#include <alias/pga/add.h>
#include <alias/pga/subtract.h>

// operators
#include <alias/pga/geometric_product.h>
#include <alias/pga/dual.h>
#include <alias/pga/polarity.h>
#include <alias/pga/reverse.h>
// #include <alias/pga/normalization.h>
#include <alias/pga/select_grade.h>
#include <alias/pga/outer_product.h>
#include <alias/pga/regressive_product.h>
#include <alias/pga/inner_product.h>
#include <alias/pga/commutator_product.h>

// geometric objects and other operators
#include <alias/pga/meet.h>
#include <alias/pga/join.h>
#include <alias/pga/sandwich.h>

#if 0
ALIAS_PGA_GENERATE_UNARY(ALIAS_PGA_UNARY_NEGATE, negate)
#define alias_pga_negate(A) ALIAS_PGA_USE_UNARY(ALIAS_PGA_UNARY_NEGATE, negate, A)

ALIAS_PGA_GENERATE_BINARY_FUNCTIONS(ALIAS_PGA_BINARY_ADD, add)
#define alias_pga_add(A, B) ALIAS_PGA_USE_BINARY(ALIAS_PGA_BINARY_ADD, add, A, B)

ALIAS_PGA_GENERATE_BINARY_FUNCTIONS(ALIAS_PGA_BINARY_SUBTRACT, subtract)
#define alias_pga_subtract(A, B) ALIAS_PGA_USE_BINARY(ALIAS_PGA_BINARY_SUBTRACT, subtract, A, B)

ALIAS_PGA_GENERATE_BINARY_FUNCTIONS(ALIAS_PGA_BINARY_GEOMETRIC_PRODUCT, geometric_product)
#define alias_pga_geometric_product(A, B) ALIAS_PGA_USE_BINARY(ALIAS_PGA_BINARY_GEOMETRIC_PRODUCT, geometric_product, A, B)

ALIAS_PGA_GENERATE_UNARY(ALIAS_PGA_UNARY_DUAL, dual)
#define alias_pga_dual(A) ALIAS_PGA_USE_UNARY(ALIAS_PGA_UNARY_DUAL, dual, A)

ALIAS_PGA_GENERATE_UNARY(ALIAS_PGA_UNARY_POLARITY, polarity)
#define alias_pga_polarity(A) ALIAS_PGA_USE_UNARY(ALIAS_PGA_UNARY_POLARITY, polarity, A)

ALIAS_PGA_GENERATE_UNARY(ALIAS_PGA_UNARY_REVERSE, reverse)
#define alias_pga_reverse(A) ALIAS_PGA_USE_UNARY(ALIAS_PGA_UNARY_REVERSE, reverse, A)

ALIAS_PGA_GENERATE_UNARY(ALIAS_PGA_UNARY_SELECT_GRADE_0, select_grade_0)
ALIAS_PGA_GENERATE_UNARY(ALIAS_PGA_UNARY_SELECT_GRADE_1, select_grade_1)
ALIAS_PGA_GENERATE_UNARY(ALIAS_PGA_UNARY_SELECT_GRADE_2, select_grade_2)
ALIAS_PGA_GENERATE_UNARY(ALIAS_PGA_UNARY_SELECT_GRADE_3, select_grade_3)
ALIAS_PGA_GENERATE_UNARY(ALIAS_PGA_UNARY_SELECT_GRADE_4, select_grade_4)

#define alias_pga_select_grade_0(A) ALIAS_PGA_USE_UNARY(ALIAS_PGA_UNARY_SELECT_GRADE_0, select_grade_0, A)
#define alias_pga_select_grade_1(A) ALIAS_PGA_USE_UNARY(ALIAS_PGA_UNARY_SELECT_GRADE_1, select_grade_1, A)
#define alias_pga_select_grade_2(A) ALIAS_PGA_USE_UNARY(ALIAS_PGA_UNARY_SELECT_GRADE_2, select_grade_2, A)
#define alias_pga_select_grade_3(A) ALIAS_PGA_USE_UNARY(ALIAS_PGA_UNARY_SELECT_GRADE_3, select_grade_3, A)
#define alias_pga_select_grade_4(A) ALIAS_PGA_USE_UNARY(ALIAS_PGA_UNARY_SELECT_GRADE_4, select_grade_4, A)

ALIAS_PGA_GENERATE_BINARY_FUNCTIONS(ALIAS_PGA_BINARY_OUTER_PRODUCT, outer_product)
#define alias_pga_outer_product(A, B) ALIAS_PGA_USE_BINARY(ALIAS_PGA_BINARY_OUTER_PRODUCT, outer_product, A, B)

ALIAS_PGA_GENERATE_BINARY_FUNCTIONS(ALIAS_PGA_BINARY_REGRESSIVE_PRODUCT, regressive_product)
#define alias_pga_regressive_product(A, B) ALIAS_PGA_USE_BINARY(ALIAS_PGA_BINARY_REGRESSIVE_PRODUCT, regressive_product, A, B)

ALIAS_PGA_GENERATE_BINARY_FUNCTIONS(ALIAS_PGA_BINARY_INNER_PRODUCT, inner_product)
#define alias_pga_inner_product(A, B) ALIAS_PGA_USE_BINARY(ALIAS_PGA_BINARY_INNER_PRODUCT, inner_product, A, B)

ALIAS_PGA_GENERATE_BINARY_FUNCTIONS(ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT, commutator_product)
#define alias_pga_commutator_product(A, B) ALIAS_PGA_USE_BINARY(ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT, commutator_product, A, B)

ALIAS_PGA_GENERATE_BINARY_FUNCTIONS(ALIAS_PGA_SANDWICH, sandwich)
#define alias_pga_sandwich(A, B) ALIAS_PGA_USE_BINARY(ALIAS_PGA_SANDWICH, sandwich, A, B)
#endif

// ----------------------------------------------------------------------------
#define ALIAS_CPP_PACK(...) ( __VA_ARGS__ )
#define ALIAS_CPP_UNPACK(...) __VA_ARGS__

#define ALIAS_CPP_APPLY_1(F, A1) F ## A1
#define ALIAS_CPP_APPLY_2(F, A1, A2) ALIAS_CPP_APPLY_1(F, (ALIAS_CPP_UNPACK ## A1 , ALIAS_CPP_UNPACK ## A2))

#define ALIAS_CPP_APPEND(RETURN, A, B, ...) RETURN((ALIAS_CPP_UNPACK ## A , ALIAS_CPP_UNPACK ## B), ## __VA_ARGS__)

ALIAS_CPP_APPEND(ret2, (ret1), (0,0,0,0,0,0,0,0,0,0,0,x,y,z,o,0), extra)

#define ALIAS_PGA_CPP_UNARY(OP, A) ALIAS_CPP_APPEND(ALIAS_PGA_CPP_UNARY_1, (ALIAS_CPP_PACK),A, OP)
#define ALIAS_PGA_CPP_UNARY_1(OP_ARGS, OP) ALIAS_CPP_APPLY_1(OP, OP_ARGS)

#define alias_pga_NEGATE(A) ALIAS_PGA_CPP_UNARY(ALIAS_PGA_UNARY_NEGATE, A)

<_ALIAS_CPP_EVAL( alias_pga_NEGATE((0,0,0,0,0,0,0,0,0,0,0,x,y,z,o,0)) )>

< ALIAS_PGA_UNARY_NEGATE (ALIAS_CPP_PACK , 0,0,0,0,0,0,0,0,0,0,0,x,y,z,o,0) >

static inline alias_pga_Scalar alias_pga_scalar(alias_R s) {
  return (alias_pga_Scalar) { .one = s };
}

static inline alias_pga_Point alias_pga_point(alias_R x, alias_R y, alias_R z) {
  return (alias_pga_Point) { .e032 = x, .e013 = y, .e021 = z, .e123 = alias_R_ONE };
}

static inline alias_pga_Direction alias_pga_direction(alias_R x, alias_R y, alias_R z) {
  return (alias_pga_Point) { .e032 = x, .e013 = y, .e021 = z, .e123 = alias_R_ZERO };
}

static inline alias_pga_Plane alias_pga_plane(alias_R a, alias_R b, alias_R c, alias_R d) {
  return (alias_pga_Plane) { .e1 = a, .e2 = b, .e3 = c, .e0 = d };
}

inline PGA3D PGA3D::Conjugate () {
 PGA3D res;
 res[0]=this->mvec[0];
 res[1]=-this->mvec[1];
 res[2]=-this->mvec[2];
 res[3]=-this->mvec[3];
 res[4]=-this->mvec[4];
 res[5]=-this->mvec[5];
 res[6]=-this->mvec[6];
 res[7]=-this->mvec[7];
 res[8]=-this->mvec[8];
 res[9]=-this->mvec[9];
 res[10]=-this->mvec[10];
 res[11]=this->mvec[11];
 res[12]=this->mvec[12];
 res[13]=this->mvec[13];
 res[14]=this->mvec[14];
 res[15]=this->mvec[15];
 return res;
};

#define alias_pga_norm(A) 

nline float PGA3D::norm() { return sqrt(abs(((*this)*Conjugate()).mvec[0])); }
inline float PGA3D::inorm() { return (!(*this)).norm(); }
inline PGA3D PGA3D::normalized() { return (*this) * (1/norm()); }

static inline alias_pga_Rotor alias_pga_rotor(alias_R angle, alias_pga_Bivector bivector) {
  alias_pga_Scalar c = alias_pga_scalar(alias_cos(angle / alias_R_TWO));
  alias_pga_Scalar s = alias_pga_scalar(alias_sin(angle / alias_R_TWO));
  return alias_pga_add(c, alias_pga_mul(s, alias_pga_normalize(bivector)));
}

static inline alias_pga_test(void) {
}

#endif

