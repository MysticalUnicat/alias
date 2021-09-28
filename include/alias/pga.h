#ifndef _ALIAS_PGA_H_
#define _ALIAS_PGA_H_

// https://bivector.net/

#include <alias/pga/bits.h>
#include <alias/pga/types.h>

#include <alias/pga/unary.h>
#include <alias/pga/binary.h>
#include <alias/pga/operators.h>

// C functions of operators
#define ALIAS_PGA_GENERATE_UNARY_EXTERN(op, Xa,Xb,Xc,Xd,Xe, Za,Zb,Zc,Zd,Ze, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) \
ALIAS_CPP_IF1(ALIAS_PGA_HAS_GRADES(Za,Zb,Zc,Zd,Ze))( \
  extern void ALIAS_PGA_UNARY_NAME(op,Xa,Xb,Xc,Xd,Xe)(ALIAS_PGA_TYPENAME_FROM_BITS(Xa,Xb,Xc,Xd,Xe) x, ALIAS_PGA_TYPENAME_FROM_BITS(Za,Zb,Zc,Zd,Ze) * z); \
)( \
  static inline void ALIAS_PGA_UNARY_NAME(op,Xa,Xb,Xc,Xd,Xe)(ALIAS_PGA_TYPENAME_FROM_BITS(Xa,Xb,Xc,Xd,Xe) x, alias_pga_Multigrade00000 * z) { (void)x; (void)z; } \
)

#define ALIAS_PGA_GENERATE_BINARY_EXTERN(op, Xa,Xb,Xc,Xd,Xe, Ya,Yb,Yc,Yd,Ye, Za,Zb,Zc,Zd,Ze, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) \
ALIAS_CPP_IF1(ALIAS_PGA_HAS_GRADES(Za,Zb,Zc,Zd,Ze))( \
  extern ALIAS_PGA_BINARY_NAME(op,Xa,Xb,Xc,Xd,Xe,Ya,Yb,Yc,Yd,Ye)(ALIAS_PGA_TYPENAME_FROM_BITS(Xa,Xb,Xc,Xd,Xe) x, ALIAS_PGA_TYPENAME_FROM_BITS(Ya,Yb,Yc,Yd,Ye) y, ALIAS_PGA_TYPENAME_FROM_BITS(Za,Zb,Zc,Zd,Ze) * z); \
)( \
  static inline void ALIAS_PGA_BINARY_NAME(op,Xa,Xb,Xc,Xd,Xe,Ya,Yb,Yc,Yd,Ye)(ALIAS_PGA_TYPENAME_FROM_BITS(Xa,Xb,Xc,Xd,Xe) x, ALIAS_PGA_TYPENAME_FROM_BITS(Ya,Yb,Yc,Yd,Ye) y, alias_pga_Multigrade00000 * z) { (void)x; (void)y; (void)z; } \
)

ALIAS_PGA_UNARY_OPERATORS(ALIAS_PGA_GENERATE_UNARY, ALIAS_PGA_GENERATE_UNARY_EXTERN)
ALIAS_PGA_UNARY_OPERATORS(ALIAS_PGA_GENERATE_BINARY, ALIAS_PGA_GENERATE_BINARY_EXTERN)

// C interface generation
#define ALIAS_PGA_UNARY_NAME(op, A,B,C,D,E) alias_pga__##op##_##A##B##C##D##E

#define ALIAS_PGA_GENERIC_CALL_UNARY(op, X,Z) _Generic((X) ALIAS_PGA_BITS_1(ALIAS_PGA_GENERIC_CALL_UNARY_1, op))(X, Z)
#define ALIAS_PGA_GENERIC_CALL_UNARY_1(A,B,C,D,E, op)      , ALIAS_PGA_TYPENAME_FROM_BITS(A,B,C,D,E): ALIAS_PGA_UNARY_NAME(op, A,B,C,D,E)

#define ALIAS_PGA_GENERIC_CALL_BINARY(op, X,Y,Z)    _Generic((X) ALIAS_PGA_BITS_1(ALIAS_PGA_GENERIC_CALL_BINARY_1, op,Y))(X, Y, Z)
#define ALIAS_PGA_GENERIC_CALL_BINARY_1(A,B,C,D,E, op,Y)         , ALIAS_PGA_TYPENAME_FROM_BITS(A,B,C,D,E): _Generic((Y) ALIAS_PGA_BITS_2(ALIAS_PGA_GENERIC_CALL_BINARY_2, op,A,B,C,D,E))
#define ALIAS_PGA_GENERIC_CALL_BINARY_2(a,b,c,d,e, op,A,B,C,D,E) , ALIAS_PGA_TYPENAME_FROM_BITS(a,b,c,d,e): ALIAS_PGA_BINARY_NAME(op, A,B,C,D,E, a,b,c,d,e)

// C interface
#define alias_pga_negate(a, r)                ALIAS_PGA_GENERIC_CALL_UNARY(negate,              a, r)
#define alias_pga_dual(a, r)                  ALIAS_PGA_GENERIC_CALL_UNARY(dual,                a, r)
#define alias_pga_hodge_dual(a, r)            ALIAS_PGA_GENERIC_CALL_UNARY(hodge_dual,          a, r)
#define alias_pga_polarity(a, r)              ALIAS_PGA_GENERIC_CALL_UNARY(polarity,            a, r)
#define alias_pga_reverse(a, r)               ALIAS_PGA_GENERIC_CALL_UNARY(reverse,             a, r)
#define alias_pga_select_grade_0(a, r)        ALIAS_PGA_GENERIC_CALL_UNARY(select_grade_0,      a, r)
#define alias_pga_select_grade_1(a, r)        ALIAS_PGA_GENERIC_CALL_UNARY(select_grade_1,      a, r)
#define alias_pga_select_grade_2(a, r)        ALIAS_PGA_GENERIC_CALL_UNARY(select_grade_2,      a, r)
#define alias_pga_select_grade_3(a, r)        ALIAS_PGA_GENERIC_CALL_UNARY(select_grade_3,      a, r)
#define alias_pga_select_grade_4(a, r)        ALIAS_PGA_GENERIC_CALL_UNARY(select_grade_4,      a, r)
#define alias_pga_add(a, b, r)                ALIAS_PGA_GENERIC_CALL_BINARY(add,                a, b, r)
#define alias_pga_subtract(a, b, r)           ALIAS_PGA_GENERIC_CALL_BINARY(subtract,           a, b, r)
#define alias_pga_geometric_product(a, b, r)  ALIAS_PGA_GENERIC_CALL_BINARY(geometric_product,  a, b, r)
#define alias_pga_outer_product(a, b, r)      ALIAS_PGA_GENERIC_CALL_BINARY(outer_product,      a, b, r)
#define alias_pga_regressive_product(a, b, r) ALIAS_PGA_GENERIC_CALL_BINARY(regressive_product, a, b, r)
#define alias_pga_inner_product(a, b, r)      ALIAS_PGA_GENERIC_CALL_BINARY(inner_product,      a, b, r)
#define alias_pga_commutator_product(a, b, r) ALIAS_PGA_GENERIC_CALL_BINARY(commutator_product, a, b, r)
#define alias_pga_divide(a, b, r)             ALIAS_PGA_GENERIC_CALL_BINARY(divide,             a, b, r)
#define alias_pga_sandwich(a, b, r)           ALIAS_PGA_GENERIC_CALL_BINARY(sandwich,           a, b, r)

#define alias_pga_sub            alias_pga_subtract
#define alias_pga_mul            alias_pga_geometric_product
#define alias_pga_div            alias_pga_divide

#define alias_pga_dot            alias_pga_inner_product
#define alias_pga_meet           alias_pga_outer_product
#define alias_pga_join           alias_pga_regressive_product

#define alias_pga_scalar(a, r) do { r.one = a; } while(0)
#define alias_pga_plane(a, b, c, d, r) do { r.e1 = a; r.e2 = b; r.e3 = c; r.e0 = d; } while(0)
#define alias_pga_point(x, y, z, r) do { r.e032 = x; r.e013 = y; r.e021 = z; r.e123 = alias_R_ONE; } while(0)
#define alias_pga_antiscalar(a, r) do { r.e0123 = p; } while(0)

#define alias_pga_norm_squared(a, r) \
  do { \
    typeof(a) _t; \
    alias_pga_reverse(a, _t); \
    alias_pga_mul(a, _t, r); \
  } while(0)

#define alias_pga_inf_norm_squared(a, r) \
  do { \
    typeof(*(a)._dual_type) _d; \
    alias_pga_hodge_dual(a, _d); \
    alias_pga_norm_squared(_d, r); \
  } while(0)

#define alias_pga_norm(a, r) \
  do { \
    alias_pga_Scalar _norm_squared; \
    alias_pga_norm_squared(a, _norm_squared); \
    alias_pga_sqrt(_norm_squared, r); \
  } while(0)

#define alias_pga_inf_norm(a) \
  do { \
    alias_pga_Scalar _norm_squared; \
    alias_pga_inf_norm_squared(a, _norm_squared); \
    alias_pga_sqrt(_norm_squared, r); \
  } while(0)

#define alias_pga_normalize(a, r) \
  do { \
    alias_pga_Scalar _norm_squared, _inv_norm; \
    alias_pga_norm_squared(a, _norm_squared); \
    alias_pga_inverse_sqrt(_norm_squared, _inv_norm); \
    alias_pga_mul(a, _inv_norm, r); \
  } while(0)

#define alias_pga_normalize_to(a, to, r) \
  do { \
    alias_pga_Scalar _norm_squared, _inv_norm, _inv_norm_scaled; \
    alias_pga_norm_squared(a, _norm_squared); \
    alias_pga_inverse_sqrt(_norm_squared, _inv_norm); \
    alias_pga_mul(to, _inv_norm, _inv_norm_scaled); \
    alias_pga_mul(a, _inv_norm_scaled, r); \
  } while(0)

#define ALIAS_PGA_IMPORT_CODE(a) _Generic((a) ALIAS_PGA_ALL_BITS(ALIAS_PGA_IMPORT_CODE_1))
#define ALIAS_PGA_IMPORT_CODE_1(A,B,C,D,E) , ALIAS_PGA_TYPENAME_FROM_BITS(A,B,C,D,E): 0b##A##B##C##D##E

static inline alias_pga_Rotor alias_pga_rotor(alias_pga_Scalar angle, alias_pga_Line line) {
  alias_pga_Rotor rotor;

  ALIAS_PGA_IMPORT_CODE(angle);
  ALIAS_PGA_IMPORT_CODE(line);
  
  alias_pga_Scalar s = alias_pga_sin_cos(angle / 2, s, c);
  alias_pga_normalize_to(line, s, line);
  alias_pga_add(c, line, rotor);
  return rotor;
}

#endif

