#ifndef _ALIAS_PGA_H_
#define _ALIAS_PGA_H_

#include <alias/math.h>
#include <alias/cpp.h>

/*
3D Projective Geometric Algebra (reference. https://projectivegeometricalgebra.org/)
note: `e4` is the degenerate metric

+----+-------------------+-----------------------------------+---------------------------+-------+
| 0  | GRADE 1           | GRADE 2                           | GRADE 3                   | 4     |
+----+----+----+----+----+-----+-----+-----+-----+-----+-----+------+------+------+------+-------+
| e_ | e1 | e2 | e3 | e4 | e23 | e31 | e12 | e43 | e42 | e41 | e321 | e124 | e314 | e234 | e1234 |
+----+----+----+----+----+-----+-----+-----+-----+-----+-----+------+------+------+------+-------+
|    | VECTOR            | BIVECTOR                          | TRIVECTOR                 |       |
|    | Point P           | Line l                            | Plane P                   |       |
+----+-------------------+-----------------------------------+---------------------------+-------+
*/

#define ALIAS_PGA__GENERATE_MULTIGRADE(B0, B1, B2, B3, B4)                                      \
typedef struct alias_PGA_Multigrade ## B0 ## B1 ## B2 ## B3 ## B4 {                             \
  ALIAS_IFF(B0)(alias_R e_;,)                                                                   \
  ALIAS_IFF(B1)(alias_R e1; alias_R e2; alias_R e3; alias_R e4;,)                               \
  ALIAS_IFF(B2)(alias_R e23; alias_R e31; alias_R e12; alias_R e43; alias_R e42; alias_R e41;,) \
  ALIAS_IFF(B3)(alias_R e321; alias_R e124; alias_R e314; alias_R e234;,)                       \
  ALIAS_IFF(B4)(alias_R e1234;,)                                                                \
} alias_PGA_Multigrade ## B0 ## B1 ## B2 ## B3 ## B4;

//ALIAS_PGA__GENERATE_MULTIGRADE(0,0,0,0,0)
ALIAS_PGA__GENERATE_MULTIGRADE(0,0,0,0,1)
ALIAS_PGA__GENERATE_MULTIGRADE(0,0,0,1,0)
ALIAS_PGA__GENERATE_MULTIGRADE(0,0,0,1,1)
ALIAS_PGA__GENERATE_MULTIGRADE(0,0,1,0,0)
ALIAS_PGA__GENERATE_MULTIGRADE(0,0,1,0,1)
ALIAS_PGA__GENERATE_MULTIGRADE(0,0,1,1,0)
ALIAS_PGA__GENERATE_MULTIGRADE(0,0,1,1,1)
ALIAS_PGA__GENERATE_MULTIGRADE(0,1,0,0,0)
ALIAS_PGA__GENERATE_MULTIGRADE(0,1,0,0,1)
ALIAS_PGA__GENERATE_MULTIGRADE(0,1,0,1,0)
ALIAS_PGA__GENERATE_MULTIGRADE(0,1,0,1,1)
ALIAS_PGA__GENERATE_MULTIGRADE(0,1,1,0,0)
ALIAS_PGA__GENERATE_MULTIGRADE(0,1,1,0,1)
ALIAS_PGA__GENERATE_MULTIGRADE(0,1,1,1,0)
ALIAS_PGA__GENERATE_MULTIGRADE(0,1,1,1,1)
ALIAS_PGA__GENERATE_MULTIGRADE(1,0,0,0,0)
ALIAS_PGA__GENERATE_MULTIGRADE(1,0,0,0,1)
ALIAS_PGA__GENERATE_MULTIGRADE(1,0,0,1,0)
ALIAS_PGA__GENERATE_MULTIGRADE(1,0,0,1,1)
ALIAS_PGA__GENERATE_MULTIGRADE(1,0,1,0,0)
ALIAS_PGA__GENERATE_MULTIGRADE(1,0,1,0,1)
ALIAS_PGA__GENERATE_MULTIGRADE(1,0,1,1,0)
ALIAS_PGA__GENERATE_MULTIGRADE(1,0,1,1,1)
ALIAS_PGA__GENERATE_MULTIGRADE(1,1,0,0,0)
ALIAS_PGA__GENERATE_MULTIGRADE(1,1,0,0,1)
ALIAS_PGA__GENERATE_MULTIGRADE(1,1,0,1,0)
ALIAS_PGA__GENERATE_MULTIGRADE(1,1,0,1,1)
ALIAS_PGA__GENERATE_MULTIGRADE(1,1,1,0,0)
ALIAS_PGA__GENERATE_MULTIGRADE(1,1,1,0,1)
ALIAS_PGA__GENERATE_MULTIGRADE(1,1,1,1,0)
ALIAS_PGA__GENERATE_MULTIGRADE(1,1,1,1,1)

typedef alias_PGA_Multigrade10000 alias_PGA_Grade0, alias_PGA_Scalar;
typedef alias_PGA_Multigrade01000 alias_PGA_Grade1, alias_PGA_Point, alias_PGA_Vector; // note: not the Geometric Algebra 'VECTOR' as above, its a dimensionless point
typedef alias_PGA_Multigrade00100 alias_PGA_Grade2, alias_PGA_Line;
typedef alias_PGA_Multigrade00010 alias_PGA_Grade3, alias_PGA_Plane;
typedef alias_PGA_Multigrade00001 alias_PGA_Grade4, alias_PGA_Antiscalar;

// = math token generation
// - outputs 0 or an expression for each element.
// - uses 0 token to remove expressions

// == unary operators 
#define ALIAS_PGA__R_NEGATE(A) ALIAS_IFF(ALIAS_IS_ZERO(A))(0,-A)

// right complement
#define ALIAS_PGA__RIGHT_COMPLEMENT(A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234) ALIAS_PGA__RIGHT_COMPLEMENT_(ALIAS_PGA__R_NEGATE,A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234)
#define ALIAS_PGA__RIGHT_COMPLEMENT_(N,A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234) g11111(A1234,A234,A314,A124,A321,N(A41),N(A42),N(A43),N(A12),N(A31),N(A23),N(A4),N(A3),N(A2),N(A1),A_)

// left complement
#define ALIAS_PGA__LEFT_COMPLEMENT(A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234) ALIAS_PGA__LEFT_COMPLEMENT_(ALIAS_PGA__R_NEGATE,A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234)
#define ALIAS_PGA__LEFT_COMPLEMENT_(N,A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234) g11111(A1234,N(A234),N(A314),N(A124),N(A321),N(A41),N(A42),N(A43),N(A12),N(A31),N(A23),A4,A3,A2,A1,A_)

// double complement
#define ALIAS_PGA__DOUBLE_COMPLEMENT(A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234) ALIAS_PGA__DOUBLE_COMPLEMENT_(ALIAS_PGA__R_NEGATE,A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234)
#define ALIAS_PGA__DOUBLE_COMPLEMENT_(N,A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234) g11111(A_,N(A1),N(A2),N(A3),N(A4),A23,A31,A12,A43,A42,A41,N(A321),N(A124),N(A314),N(A234),A1234)

// reverse
#define ALIAS_PGA__REVERSE(A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234) ALIAS_PGA__REVERSE_(ALIAS_PGA__R_NEGATE,A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234)
#define ALIAS_PGA__REVERSE_(N,A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234) g11111(A_,A1,A2,A3,A4,N(A23),N(A31),N(A12),N(A43),N(A42),N(A41),N(A321),N(A124),N(A314),N(A234),A1234)

// antireverse
#define ALIAS_PGA__ANTIREVERSE(A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234) ALIAS_PGA__ANTIREVERSE_(ALIAS_PGA__R_NEGATE,A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234)
#define ALIAS_PGA__ANTIREVERSE_(N,A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234) g11111(A_,A1,A2,A3,A4,N(A23),N(A31),N(A12),N(A43),N(A42),N(A41),N(A321),N(A124),N(A314),N(A234),A1234)

// == binary operators
#define ALIAS_PGA__R_ADD(A, B) ALIAS_IFF(ALIAS_AND(ALIAS_IS_ZERO(A),ALIAS_IS_ZERO(B)))(0,A+B)
#define ALIAS_PGA__R_SUB(A, B) ALIAS_IFF(ALIAS_AND(ALIAS_IS_ZERO(A),ALIAS_IS_ZERO(B)))(0,A-B)
#define ALIAS_PGA__R_ADD_MUL(A, B) ALIAS_IFF(ALIAS_OR(ALIAS_IS_ZERO(A),ALIAS_IS_ZERO(B)))(,+A*B)
#define ALIAS_PGA__R_SUB_MUL(A, B) ALIAS_IFF(ALIAS_OR(ALIAS_IS_ZERO(A),ALIAS_IS_ZERO(B)))(,-A*B)

// add
#define ALIAS_PGA__ADD(                                             \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234, \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234  \
) ALIAS_PGA__ADD_(                                                  \
  ALIAS_PGA__R_ADD,                                                 \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234, \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234  \
)
#define ALIAS_PGA__ADD_(                                            \
  P,                                                                \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234, \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234  \
) g11111(                                                           \
/*    _ */ P(A_,B_),                                                \
/*    1 */ P(A1,B1),                                                \
/*    2 */ P(A2,B2),                                                \
/*    3 */ P(A3,B3),                                                \
/*    4 */ P(A4,B4),                                                \
/*   23 */ P(A23,B23),                                              \
/*   31 */ P(A31,B31),                                              \
/*   12 */ P(A12,B12),                                              \
/*   43 */ P(A43,B43),                                              \
/*   42 */ P(A42,B42),                                              \
/*   41 */ P(A41,B41),                                              \
/*  321 */ P(A321,B321),                                            \
/*  124 */ P(A124,B124),                                            \
/*  314 */ P(A314,B314),                                            \
/*  234 */ P(A234,B234),                                            \
/* 1234 */ P(A1234,B1234)                                           \
  )

// subtract
#define ALIAS_PGA__SUBTRACT(                                        \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234, \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234  \
) ALIAS_PGA__SUBTRACT_(                                             \
  ALIAS_PGA__R_SUB,                                                 \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234, \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234  \
)
#define ALIAS_PGA__SUBTRACT_(                                       \
  M,                                                                \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234, \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234  \
) g11111(                                                           \
/*    _ */ M(A_,B_),                                                \
/*    1 */ M(A1,B1),                                                \
/*    2 */ M(A2,B2),                                                \
/*    3 */ M(A3,B3),                                                \
/*    4 */ M(A4,B4),                                                \
/*   23 */ M(A23,B23),                                              \
/*   31 */ M(A31,B31),                                              \
/*   12 */ M(A12,B12),                                              \
/*   43 */ M(A43,B43),                                              \
/*   42 */ M(A42,B42),                                              \
/*   41 */ M(A41,B41),                                              \
/*  321 */ M(A321,B321),                                            \
/*  124 */ M(A124,B124),                                            \
/*  314 */ M(A314,B314),                                            \
/*  234 */ M(A234,B234),                                            \
/* 1234 */ M(A1234,B1234)                                           \
  )

// exterior product
#define ALIAS_PGA__EXTERIOR_PRODUCT(                                    \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234,     \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234      \
) ALIAS_PGA__EXTERIOR_PRODUCT_(                                         \
  ALIAS_PGA__R_ADD_MUL, ALIAS_PGA__R_SUB_MUL,                           \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234,     \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234      \
)
#define ALIAS_PGA__EXTERIOR_PRODUCT_(                                   \
  P, M,                                                                 \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234,     \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234      \
) g11111( \
/*    _ */ 0,\
/*    1 */ 0 P(A_,B1)    P(A1,B_),\
/*    2 */ 0 P(A_,B2)                P(A2,B_),\
/*    3 */ 0 P(A_,B3)                            P(A3,B_),\
/*    4 */ 0 P(A_,B4)                                        P(A4,B_),\
/*   23 */ 0 P(A_,B23)               P(A2,B3)    M(A3,B2)                P(A23,B_),\
/*   31 */ 0 P(A_,B31)   M(A1,B3)                P(A3,B1)                             P(A31,B_),\
/*   12 */ 0 P(A_,B12)   P(A1,B2)    M(A2,B1)                                                      P(A12,B_),\
/*   43 */ 0 P(A_,B43)                           M(A3,B4)    P(A4,B3)                                           P(A43,B_),\
/*   42 */ 0 P(A_,B42)               M(A2,B4)                P(A4,B2)                                                        P(A42,B_),\
/*   41 */ 0 P(A_,B41)   M(A1,B4)                            P(A4,B1)                                                                     P(A41,B_),\
/*  321 */ 0 P(A_,B321)  M(A1,B23)   M(A2,B31)   M(A3,B12)               M(A23,B1)    M(A31,B2)    M(A12,B3)                                           P(A321,B_),\
/*  124 */ 0 P(A_,B124)  M(A1,B42)   P(A2,B41)               P(A4,B12)                             P(A12,B4)                 M(A42,B1)    P(A41,B2)                  P(A124,B_),\
/*  314 */ 0 P(A_,B314)  P(A1,B43)               M(A3,B41)   P(A4,B31)                P(A31,B4)                 P(A43,B1)                 M(A41,B3)                                P(A314,B_),\
/*  234 */ 0 P(A_,B234)              M(A2,B43)   P(A3,B42)   P(A4,B23)   P(A23,B4)                              M(A43,B2)    P(A42,B3)                                                           P(A234,B_),\
/* 1234 */ 0 P(A_,B1234) P(A1,B234)  P(A2,B314)  P(A3,B124)  P(A4,B321)  M(A23,B41)   M(A31,B42)   M(A12,B43)   M(A43,B12)   M(A42,B31)   M(A41,B23)   M(A321,B4)    M(A124,B3)    M(A314,B2)    M(A234,B1)    P(A1234,B_)\
  )

// exterior antiproduct
#define ALIAS_PGA__EXTERIOR_ANTIPRODUCT(                                \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234,     \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234      \
) ALIAS_PGA__EXTERIOR_ANTIPRODUCT_(                                     \
  ALIAS_PGA__R_ADD_MUL, ALIAS_PGA__R_SUB_MUL,                           \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234,     \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234      \
)
#define ALIAS_PGA__EXTERIOR_ANTIPRODUCT_(                               \
  P, M,                                                                 \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234,     \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234      \
) g11111( \
/*    _ */ 0 P(A_,B1234) P(A1,B234)  P(A2,B314)  P(A3,124)   P(A4,B321)  M(A23,B41)   M(A31,B42)   M(A12,B43)   M(A43,B12)   M(A42,B31)   M(A41,B23)   M(A321,B4)    M(A124,B3)    M(A314,B2)    M(A234,B1)    P(A1234,B_)  ,\
/*    1 */ 0             P(A1,B1234)                                                  P(A31,B124)  M(A12,B314)                            P(A41,B321)  P(A321,B41)   P(A124,B31)   M(A314,B12)                 P(A1234,B1)  ,\
/*    2 */ 0                         P(A2,B1234)                         M(A23,B124)               P(A12,B234)               P(A42,B321)               P(A321,B42)   M(A124,B23)                 P(A234,B12)   P(A1234,B2)  ,\
/*    3 */ 0                                     P(A3,B1234)             P(A23,B314)  M(A31,B234)               P(A43,B321)                            P(A321,B43)                 P(A314,B23)   M(A234,B31)   P(A1234,B3)  ,\
/*    4 */ 0                                                 P(A4,B1234)                                        M(A43,B124)  M(A42,B314)  M(A41,B234)                M(A124,B43)   M(A314,B42)   M(A234,B41)   P(A1234,B4)  ,\
/*   23 */ 0                                                             M(A23,B1234)                                                                  M(A321,B234)                              P(A234,B321)  P(A1234,B23) ,\
/*   31 */ 0                                                                          M(A31,B1234)                                                     M(A321,B314)                P(A314,B321)                P(A1234,B31) ,\
/*   12 */ 0                                                                                       P(A12,B1234)                                        M(A321,B124)  P(A124,B321)                              P(A1234,B12) ,\
/*   43 */ 0                                                                                                    P(A43,B1234)                                                       P(A314,B234)  M(A234,B314)  P(A1234,B43) ,\
/*   42 */ 0                                                                                                                 P(A42,B1234)                            M(A124,B234)                P(A234,B124)  P(A1234,B42) ,\
/*   41 */ 0                                                                                                                              P(A41,B1234)               P(A124,B314)  M(A314,B124)                P(A1234,B41) ,\
/*  321 */ 0                                                                                                                                           P(A321,B1234)                                           P(A1234,B321),\
/*  124 */ 0                                                                                                                                                         P(A124,B1234)                             P(A1234,B124),\
/*  314 */ 0                                                                                                                                                                       P(A314,B1234)               P(A1234,B314),\
/*  234 */ 0                                                                                                                                                                                     P(A234,B1234) P(A1234,B234),\
/* 1234 */ 0\
  )

// geometric product
#define ALIAS_PGA__GEOMETRIC_PRODUCT(                                   \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234,     \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234      \
) ALIAS_PGA__GEOMETRIC_PRODUCT_(                                        \
  ALIAS_PGA__R_ADD_MUL, ALIAS_PGA__R_SUB_MUL,                           \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234,     \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234      \
)
#define ALIAS_PGA__GEOMETRIC_PRODUCT_(                                  \
  P, M,                                                                 \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234,     \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234      \
) g11111( \
/*    _ */ 0 P(A_,B_)    P(A1,B1)    P(A2,B2)    P(A3,B3)                M(A23,B23)   M(A31,B31)   M(A12,B12)                                          M(A321,B321),\
/*    1 */ 0 P(A_,B1)    P(A1,B_)    M(A2,B12)   P(A3,B31)               P(A23,B321)  M(A31,B3)    P(A12,B2)                                           P(A321,B23),\
/*    2 */ 0 P(A_,B2)    P(A1,B12)   P(A2,B_)    M(A3,B2)                P(A23,B3)    P(A31,B321)  M(A12,B1)                                           P(A321,B31),\
/*    3 */ 0 P(A_,B3)    M(A1,B31)   P(A2,B23)   P(A3,B_)                M(A23,B2)    P(A31,B1)    P(A12,B321)                                         P(A321,B12),\
/*    4 */ 0 P(A_,B4)    M(A1,B41)   M(A2,B42)   M(A3,B43)   P(A4,B_)    M(A23,B234)  M(A31,B314)  M(A12,B124)  P(A43,B3)    P(A42,B2)    P(A41,B1)    P(A321,B1234) M(A124,B12)   M(A314,B31)   P(A234,B23)   M(A1234,B321),\
/*   23 */ 0 P(A_,B23)   M(A1,B321)  P(A2,B3)    M(A3,B2)                P(A23,B_)    M(A31,B12)   P(A12,B31)                                          M(A321,B1),\
/*   31 */ 0 P(A_,B31)   M(A1,B3)    M(A2,B321)  P(A3,B1)                P(A23,B12)   P(A31,B_)    M(A12,B23)                                          M(A321,B2),\
/*   12 */ 0 P(A_,B12)   P(A1,B2)    M(A2,B1)    M(A3,B321)              M(A23,B31)   P(A31,B23)   P(A12,B_)                                           M(A321,B3),\
/*   43 */ 0 P(A_,B43)   P(A1,B314)  M(A2,B234)  M(A3,B4)    P(A4,B3)    M(A23,B42)   P(A31,B41)   P(A12,B1234) P(A43,B_)    P(A42,B23)   M(A41,B31)   M(A321,B124)  P(A124,B321)  P(A314,B1)    M(A234,B2)    P(A1234,B12),\
/*   42 */ 0 P(A_,B42)   M(A1,B124)  M(A2,B4)    P(A3,B234)  P(A4,B2)    P(A23,B43)   M(A31,B1234) M(A12,B41)   M(A43,B23)   P(A42,B_)    P(A41,B12)   M(A321,B314)  M(A124,B1)    P(A314,B321)  P(A234,B3)    P(A1234,B31),\
/*   41 */ 0 P(A_,B41)   M(A1,B4)    P(A2,B124)  M(A3,B314)  P(A4,B1)    P(A23,B1234) M(A31,B43)   P(A12,B42)   P(A43,B31)   M(A42,B12)   P(A41,B_)    M(A321,B234)  P(A124,B2)    M(A314,B3)    P(A234,B321)  P(A1234,B23),\
/*  321 */ 0 P(A_,B321)  M(A1,B23)   M(A2,B31)   M(A3,B12)               M(A23,B321)  P(A31,B2)    M(A12,B3)                                           P(A321,B_),\
/*  124 */ 0 P(A_,B124)  M(A1,B42)   P(A2,B41)   P(A3,B1234) P(A4,B12)   M(A23,B314)  P(A31,B234)  P(A12,B4)    M(A43,B321)  M(A42,B1)    P(A41,B2)    P(A321,B43)   P(A124,B_)    P(A314,B23)   M(A234,B31)   M(A1234,B3),\
/*  314 */ 0 P(A_,B314)  P(A1,B43)   P(A2,B1234) M(A3,B41)   P(A4,B31)   P(A23,B124)  P(A31,B4)    M(A12,B234)  P(A43,B1)    M(A42,B321)  M(A41,B3)    P(A321,B42)   M(A124,B23)   P(A314,B_)    P(A234,B12)   M(A1234,B2),\
/*  234 */ 0 P(A_,B234)  P(A1,B1234) M(A2,B43)   P(A3,B42)   P(A4,B23)   P(A23,B4)    M(A31,B124)  P(A12,B314)  M(A43,B2)    P(A42,B3)    M(A41,B321)  P(A321,B41)   P(A124,B31)   M(A314,B12)   P(A234,B_)    M(A1234,B1),\
/* 1234 */ 0 P(A_,B1234) P(A1,B234)  P(A2,B314)  P(A3,B124)  P(A4,B321)  M(A23,B41)   M(A31,B42)   M(A12,B43)   M(A43,B12)   M(A42,B31)   M(A41,B23)   M(A321,B4)    M(A124,B3)    M(A314,B2)    M(A234,B1)    P(A1234,B_)\
  )

// geometric antiproduct
#define ALIAS_PGA__GEOMETRIC_ANTIPRODUCT(                               \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234,     \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234      \
) ALIAS_PGA__GEOMETRIC_ANTIPRODUCT_(                                    \
  ALIAS_PGA__R_ADD_MUL, ALIAS_PGA__R_SUB_MUL,                           \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234,     \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234      \
)
#define ALIAS_PGA__GEOMETRIC_ANTIPRODUCT_(                              \
  P, M,                                                                 \
  A_,A1,A2,A3,A4,A23,A31,A12,A43,A42,A41,A321,A124,A314,A234,A1234,     \
  B_,B1,B2,B3,B4,B23,B31,B12,B43,B42,B41,B321,B124,B314,B234,B1234      \
) g11111( \
/*    _ */ 0 P(A_,B_)    P(A1,B1)    P(A2,B2)    P(A3,B3)                M(A23,B23)   M(A31,B31)   M(A12,B12)                                          M(A321,B321),\
/*    1 */ 0 P(A_,B1)    P(A1,B_)    M(A2,B12)   P(A3,B31)               P(A23,B321)  M(A31,B3)    P(A12,B2)                                           P(A321,B23),\
/*    2 */ 0 P(A_,B2)    P(A1,B12)   P(A2,B_)    M(A3,B2)                P(A23,B3)    P(A31,B321)  M(A12,B1)                                           P(A321,B31),\
/*    3 */ 0 P(A_,B3)    M(A1,B31)   P(A2,B23)   P(A3,B_)                M(A23,B2)    P(A31,B1)    P(A12,B321)                                         P(A321,B12),\
/*    4 */ 0 P(A_,B4)    M(A1,B41)   M(A2,B42)   M(A3,B43)   P(A4,B_)    M(A23,B234)  M(A31,B314)  M(A12,B124)  P(A43,B3)    P(A42,B2)    P(A41,B1)    P(A321,B1234) M(A124,B12)   M(A314,B31)   P(A234,B23)   M(A1234,B321),\
/*   23 */ 0 P(A_,B23)   M(A1,B321)  P(A2,B3)    M(A3,B2)                P(A23,B_)    M(A31,B12)   P(A12,B31)                                          M(A321,B1),\
/*   31 */ 0 P(A_,B31)   M(A1,B3)    M(A2,B321)  P(A3,B1)                P(A23,B12)   P(A31,B_)    M(A12,B23)                                          M(A321,B2),\
/*   12 */ 0 P(A_,B12)   P(A1,B2)    M(A2,B1)    M(A3,B321)              M(A23,B31)   P(A31,B23)   P(A12,B_)                                           M(A321,B3),\
/*   43 */ 0 P(A_,B43)   P(A1,B314)  M(A2,B234)  M(A3,B4)    P(A4,B3)    M(A23,B42)   P(A31,B41)   P(A12,B1234) P(A43,B_)    P(A42,B23)   M(A41,B31)   M(A321,B124)  P(A124,B321)  P(A314,B1)    M(A234,B2)    P(A1234,B12),\
/*   42 */ 0 P(A_,B42)   M(A1,B124)  M(A2,B4)    P(A3,B234)  P(A4,B2)    P(A23,B43)   M(A31,B1234) M(A12,B41)   M(A43,B23)   P(A42,B_)    P(A41,B12)   M(A321,B314)  M(A124,B1)    P(A314,B321)  P(A234,B3)    P(A1234,B31),\
/*   41 */ 0 P(A_,B41)   M(A1,B4)    P(A2,B124)  M(A3,B314)  P(A4,B1)    P(A23,B1234) M(A31,B43)   P(A12,B42)   P(A43,B31)   M(A42,B12)   P(A41,B_)    M(A321,B234)  P(A124,B2)    M(A314,B3)    P(A234,B321)  P(A1234,B23),\
/*  321 */ 0 P(A_,B321)  M(A1,B23)   M(A2,B31)   M(A3,B12)               M(A23,B321)  P(A31,B2)    M(A12,B3)                                           P(A321,B_),\
/*  124 */ 0 P(A_,B124)  M(A1,B42)   P(A2,B41)   P(A3,B1234) P(A4,B12)   M(A23,B314)  P(A31,B234)  P(A12,B4)    M(A43,B321)  M(A42,B1)    P(A41,B2)    P(A321,B43)   P(A124,B_)    P(A314,B23)   M(A234,B31)   M(A1234,B3),\
/*  314 */ 0 P(A_,B314)  P(A1,B43)   P(A2,B1234) M(A3,B41)   P(A4,B31)   P(A23,B124)  P(A31,B4)    M(A12,B234)  P(A43,B1)    M(A42,B321)  M(A41,B3)    P(A321,B42)   M(A124,B23)   P(A314,B_)    P(A234,B12)   M(A1234,B2),\
/*  234 */ 0 P(A_,B234)  P(A1,B1234) M(A2,B43)   P(A3,B42)   P(A4,B23)   P(A23,B4)    M(A31,B124)  P(A12,B314)  M(A43,B2)    P(A42,B3)    M(A41,B321)  P(A321,B41)   P(A124,B31)   M(A314,B12)   P(A234,B_)    M(A1234,B1),\
/* 1234 */ 0 P(A_,B1234) P(A1,B234)  P(A2,B314)  P(A3,B124)  P(A4,B321)  M(A23,B41)   M(A31,B42)   M(A12,B43)   M(A43,B12)   M(A42,B31)   M(A41,B23)   M(A321,B4)    M(A124,B3)    M(A314,B2)    M(A234,B1)    P(A1234,B_)\
  )

// = tagged multivectors
// one bit per grade
// g<grade bits>(values in those grades)
// also an intermediate cpp form is bits(<grade bits,>)
#define ALIAS_PGA_BITS_TO_TAG(BITS) ALIAS_CAT(ALIAS_PGA_BITS_TO_TAG_, BITS)
#define ALIAS_PGA_BITS_TO_TAG_bits(B0, B1, B2, B3, B4) g ## B0 ## B1 ## B2 ## B3 ## B4

// convert a tag `g<abcde>` to bits(a,b,c,d,e)
#define ALIAS_PGA_TAG_TO_BITS(TAG) ALIAS_CAT(ALIAS_PGA_TAG_TO_BITS_, TAG)
#define ALIAS_PGA_TAG_TO_BITS_g00000 bits(0,0,0,0,0)
#define ALIAS_PGA_TAG_TO_BITS_g00001 bits(0,0,0,0,1)
#define ALIAS_PGA_TAG_TO_BITS_g00010 bits(0,0,0,1,0)
#define ALIAS_PGA_TAG_TO_BITS_g00011 bits(0,0,0,1,1)
#define ALIAS_PGA_TAG_TO_BITS_g00100 bits(0,0,1,0,0)
#define ALIAS_PGA_TAG_TO_BITS_g00101 bits(0,0,1,0,1)
#define ALIAS_PGA_TAG_TO_BITS_g00110 bits(0,0,1,1,0)
#define ALIAS_PGA_TAG_TO_BITS_g00111 bits(0,0,1,1,1)
#define ALIAS_PGA_TAG_TO_BITS_g01000 bits(0,1,0,0,0)
#define ALIAS_PGA_TAG_TO_BITS_g01001 bits(0,1,0,0,1)
#define ALIAS_PGA_TAG_TO_BITS_g01010 bits(0,1,0,1,0)
#define ALIAS_PGA_TAG_TO_BITS_g01011 bits(0,1,0,1,1)
#define ALIAS_PGA_TAG_TO_BITS_g01100 bits(0,1,1,0,0)
#define ALIAS_PGA_TAG_TO_BITS_g01101 bits(0,1,1,0,1)
#define ALIAS_PGA_TAG_TO_BITS_g01110 bits(0,1,1,1,0)
#define ALIAS_PGA_TAG_TO_BITS_g01111 bits(0,1,1,1,1)
#define ALIAS_PGA_TAG_TO_BITS_g10000 bits(1,0,0,0,0)
#define ALIAS_PGA_TAG_TO_BITS_g10001 bits(1,0,0,0,1)
#define ALIAS_PGA_TAG_TO_BITS_g10010 bits(1,0,0,1,0)
#define ALIAS_PGA_TAG_TO_BITS_g10011 bits(1,0,0,1,1)
#define ALIAS_PGA_TAG_TO_BITS_g10100 bits(1,0,1,0,0)
#define ALIAS_PGA_TAG_TO_BITS_g10101 bits(1,0,1,0,1)
#define ALIAS_PGA_TAG_TO_BITS_g10110 bits(1,0,1,1,0)
#define ALIAS_PGA_TAG_TO_BITS_g10111 bits(1,0,1,1,1)
#define ALIAS_PGA_TAG_TO_BITS_g11000 bits(1,1,0,0,0)
#define ALIAS_PGA_TAG_TO_BITS_g11001 bits(1,1,0,0,1)
#define ALIAS_PGA_TAG_TO_BITS_g11010 bits(1,1,0,1,0)
#define ALIAS_PGA_TAG_TO_BITS_g11011 bits(1,1,0,1,1)
#define ALIAS_PGA_TAG_TO_BITS_g11100 bits(1,1,1,0,0)
#define ALIAS_PGA_TAG_TO_BITS_g11101 bits(1,1,1,0,1)
#define ALIAS_PGA_TAG_TO_BITS_g11110 bits(1,1,1,1,0)
#define ALIAS_PGA_TAG_TO_BITS_g11111 bits(1,1,1,1,1)

// get the bits representation of values from a math expression
#define ALIAS_PGA_VALUES_TO_BITS(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) \
  bits( \
    ALIAS_PGA_VALUES_TO_BITS_0(A), \
    ALIAS_PGA_VALUES_TO_BITS_1(B, C, D, E), \
    ALIAS_PGA_VALUES_TO_BITS_2(F, G, H, I, J, K), \
    ALIAS_PGA_VALUES_TO_BITS_3(L, M, N, O), \
    ALIAS_PGA_VALUES_TO_BITS_4(P) \
  )
#define ALIAS_PGA_VALUES_TO_BITS_0(A)                ALIAS_IS_NOT_ZERO(A)
#define ALIAS_PGA_VALUES_TO_BITS_1(B, C, D, E)       ALIAS_OR(ALIAS_IS_NOT_ZERO(B), ALIAS_OR(ALIAS_IS_NOT_ZERO(C), ALIAS_OR(ALIAS_IS_NOT_ZERO(D), ALIAS_IS_NOT_ZERO(E))))
#define ALIAS_PGA_VALUES_TO_BITS_2(F, G, H, I, J, K) ALIAS_OR(ALIAS_IS_NOT_ZERO(F), ALIAS_OR(ALIAS_IS_NOT_ZERO(G), ALIAS_OR(ALIAS_IS_NOT_ZERO(H), ALIAS_OR(ALIAS_IS_NOT_ZERO(I), ALIAS_OR(ALIAS_IS_NOT_ZERO(J), ALIAS_IS_NOT_ZERO(K))))))
#define ALIAS_PGA_VALUES_TO_BITS_3(L, M, N, O)       ALIAS_OR(ALIAS_IS_NOT_ZERO(L), ALIAS_OR(ALIAS_IS_NOT_ZERO(M), ALIAS_OR(ALIAS_IS_NOT_ZERO(N), ALIAS_IS_NOT_ZERO(O))))
#define ALIAS_PGA_VALUES_TO_BITS_4(P)                ALIAS_IS_NOT_ZERO(P)

// convert a tagged expression to a tag. removing the values.
#define ALIAS_PGA_GET_TAG(X) ALIAS_CAT(ALIAS_PGA_GET_TAG_, X)
#define ALIAS_PGA_GET_TAG_g00000(...) g00000
#define ALIAS_PGA_GET_TAG_g00001(...) g00001
#define ALIAS_PGA_GET_TAG_g00010(...) g00010
#define ALIAS_PGA_GET_TAG_g00011(...) g00011
#define ALIAS_PGA_GET_TAG_g00100(...) g00100
#define ALIAS_PGA_GET_TAG_g00101(...) g00101
#define ALIAS_PGA_GET_TAG_g00110(...) g00110
#define ALIAS_PGA_GET_TAG_g00111(...) g00111
#define ALIAS_PGA_GET_TAG_g01000(...) g01000
#define ALIAS_PGA_GET_TAG_g01001(...) g01001
#define ALIAS_PGA_GET_TAG_g01010(...) g01010
#define ALIAS_PGA_GET_TAG_g01011(...) g01011
#define ALIAS_PGA_GET_TAG_g01100(...) g01100
#define ALIAS_PGA_GET_TAG_g01101(...) g01101
#define ALIAS_PGA_GET_TAG_g01110(...) g01110
#define ALIAS_PGA_GET_TAG_g01111(...) g01111
#define ALIAS_PGA_GET_TAG_g10000(...) g10000
#define ALIAS_PGA_GET_TAG_g10001(...) g10001
#define ALIAS_PGA_GET_TAG_g10010(...) g10010
#define ALIAS_PGA_GET_TAG_g10011(...) g10011
#define ALIAS_PGA_GET_TAG_g10100(...) g10100
#define ALIAS_PGA_GET_TAG_g10101(...) g10101
#define ALIAS_PGA_GET_TAG_g10110(...) g10110
#define ALIAS_PGA_GET_TAG_g10111(...) g10111
#define ALIAS_PGA_GET_TAG_g11000(...) g11000
#define ALIAS_PGA_GET_TAG_g11001(...) g11001
#define ALIAS_PGA_GET_TAG_g11010(...) g11010
#define ALIAS_PGA_GET_TAG_g11011(...) g11011
#define ALIAS_PGA_GET_TAG_g11100(...) g11100
#define ALIAS_PGA_GET_TAG_g11101(...) g11101
#define ALIAS_PGA_GET_TAG_g11110(...) g11110
#define ALIAS_PGA_GET_TAG_g11111(...) g11111

// get the values in a tagged expression.
#define ALIAS_PGA_GET_VALUES(X) ALIAS_CAT(ALIAS_PGA_GET_VALUES_, X)
#define ALIAS_PGA_GET_VALUES_g00000(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g00001(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g00010(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g00011(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g00100(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g00101(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g00110(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g00111(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g01000(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g01001(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g01010(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g01011(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g01100(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g01101(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g01110(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g01111(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g10000(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g10001(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g10010(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g10011(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g10100(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g10101(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g10110(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g10111(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g11000(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g11001(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g11010(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g11011(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g11100(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g11101(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g11110(...) __VA_ARGS__
#define ALIAS_PGA_GET_VALUES_g11111(...) __VA_ARGS__

// construct a tagged expression from a tag and all 16 values
#define ALIAS_PGA_CONSTRUCT(TAG, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) ALIAS_CAT(ALIAS_PGA_CONSTRUCT_, TAG)(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)
#define ALIAS_PGA_CONSTRUCT_g00000(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g00000()
#define ALIAS_PGA_CONSTRUCT_g00001(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g00001(P)
#define ALIAS_PGA_CONSTRUCT_g00010(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g00010(L, M, N, O)
#define ALIAS_PGA_CONSTRUCT_g00011(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g00011(L, M, N, O, P)
#define ALIAS_PGA_CONSTRUCT_g00100(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g00100(F, G, H, I, J, K)
#define ALIAS_PGA_CONSTRUCT_g00101(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g00101(F, G, H, I, J, K, P)
#define ALIAS_PGA_CONSTRUCT_g00110(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g00110(F, G, H, I, J, K, L, M, N, O)
#define ALIAS_PGA_CONSTRUCT_g00111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g00111(F, G, H, I, J, K, L, M, N, O, P)
#define ALIAS_PGA_CONSTRUCT_g01000(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g01000(B, C, D, E)
#define ALIAS_PGA_CONSTRUCT_g01001(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g01001(B, C, D, E, P)
#define ALIAS_PGA_CONSTRUCT_g01010(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g01010(B, C, D, E, L, M, N, O)
#define ALIAS_PGA_CONSTRUCT_g01011(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g01011(B, C, D, E, L, M, N, O, P)
#define ALIAS_PGA_CONSTRUCT_g01100(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g01100(B, C, D, E, F, G, H, I, J, K)
#define ALIAS_PGA_CONSTRUCT_g01101(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g01101(B, C, D, E, F, G, H, I, J, K, P)
#define ALIAS_PGA_CONSTRUCT_g01110(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g01110(B, C, D, E, F, G, H, I, J, K, L, M, N, O)
#define ALIAS_PGA_CONSTRUCT_g01111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g01111(B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)
#define ALIAS_PGA_CONSTRUCT_g10000(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g10000(A)
#define ALIAS_PGA_CONSTRUCT_g10001(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g10001(A, P)
#define ALIAS_PGA_CONSTRUCT_g10010(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g10010(A, L, M, N, O)
#define ALIAS_PGA_CONSTRUCT_g10011(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g10011(A, L, M, N, O, P)
#define ALIAS_PGA_CONSTRUCT_g10100(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g10100(A, F, G, H, I, J, K)
#define ALIAS_PGA_CONSTRUCT_g10101(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g10101(A, F, G, H, I, J, K, P)
#define ALIAS_PGA_CONSTRUCT_g10110(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g10110(A, F, G, H, I, J, K, L, M, N, O)
#define ALIAS_PGA_CONSTRUCT_g10111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g10111(A, F, G, H, I, J, K, L, M, N, O, P)
#define ALIAS_PGA_CONSTRUCT_g11000(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g11000(A, B, C, D, E)
#define ALIAS_PGA_CONSTRUCT_g11001(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g11001(A, B, C, D, E, P)
#define ALIAS_PGA_CONSTRUCT_g11010(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g11010(A, B, C, D, E, L, M, N, O)
#define ALIAS_PGA_CONSTRUCT_g11011(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g11011(A, B, C, D, E, L, M, N, O, P)
#define ALIAS_PGA_CONSTRUCT_g11100(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g11100(A, B, C, D, E, F, G, H, I, J, K)
#define ALIAS_PGA_CONSTRUCT_g11101(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g11101(A, B, C, D, E, F, G, H, I, J, K, P)
#define ALIAS_PGA_CONSTRUCT_g11110(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g11110(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O)
#define ALIAS_PGA_CONSTRUCT_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)

// construct a non-zero multivector from a tag
#define ALIAS_PGA_ONES_FROM_TAG(TAG) ALIAS_PGA_CONSTRUCT(TAG, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)

// construct a non-zero multivector from bits
// this is used to determine if a binary operation is valid
#define ALIAS_PGA_ONES_FROM_BITS(TAG) ALIAS_PGA_ONES_FROM_TAG(ALIAS_PGA_BITS_TO_TAG(TAG))

// check if this tagged expression is a valid multivector (not g00000)
#define ALIAS_PGA_IS_VALID_MULTIVECTOR(X) ALIAS_PGA_IS_VALID_MULTIVECTOR_(ALIAS_PGA_GET_TAG(X))
#define ALIAS_PGA_IS_VALID_MULTIVECTOR_(TAG) ALIAS_BNOT(ALIAS_EQ(PGA, g00000, TAG))
#define ALIAS__EQ__PGAg00000__PGAg00000 ALIAS__PROBE

// convert a any tagged expression into the largest representation (g11111)
#define ALIAS_PGA_EXPAND(X) ALIAS_CAT(ALIAS_PGA_EXPAND_, X)
#define ALIAS_PGA_EXPAND_g00000(P)                                              g11111(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define ALIAS_PGA_EXPAND_g00001(P)                                              g11111(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, P)
#define ALIAS_PGA_EXPAND_g00010(L, M, N, O)                                     g11111(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L, M, N, O, 0)
#define ALIAS_PGA_EXPAND_g00011(L, M, N, O, P)                                  g11111(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L, M, N, O, P)
#define ALIAS_PGA_EXPAND_g00100(F, G, H, I, J, K)                               g11111(0, 0, 0, 0, 0, F, G, H, I, J, K, 0, 0, 0, 0, 0)
#define ALIAS_PGA_EXPAND_g00101(F, G, H, I, J, K, P)                            g11111(0, 0, 0, 0, 0, F, G, H, I, J, K, 0, 0, 0, 0, P)
#define ALIAS_PGA_EXPAND_g00110(F, G, H, I, J, K, L, M, N, O)                   g11111(0, 0, 0, 0, 0, F, G, H, I, J, K, L, M, N, O, 0)
#define ALIAS_PGA_EXPAND_g00111(F, G, H, I, J, K, L, M, N, O, P)                g11111(0, 0, 0, 0, 0, F, G, H, I, J, K, L, M, N, O, P)
#define ALIAS_PGA_EXPAND_g01000(B, C, D, E)                                     g11111(0, B, C, D, E, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define ALIAS_PGA_EXPAND_g01001(B, C, D, E, P)                                  g11111(0, B, C, D, E, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, P)
#define ALIAS_PGA_EXPAND_g01010(B, C, D, E, L, M, N, O)                         g11111(0, B, C, D, E, 0, 0, 0, 0, 0, 0, L, M, N, O, 0)
#define ALIAS_PGA_EXPAND_g01011(B, C, D, E, L, M, N, O, P)                      g11111(0, B, C, D, E, 0, 0, 0, 0, 0, 0, L, M, N, O, P)
#define ALIAS_PGA_EXPAND_g01100(B, C, D, E, F, G, H, I, J, K)                   g11111(0, B, C, D, E, F, G, H, I, 0, 0, 0, 0, 0, 0, 0)
#define ALIAS_PGA_EXPAND_g01101(B, C, D, E, F, G, H, I, J, K, P)                g11111(0, B, C, D, E, F, G, H, I, 0, 0, 0, 0, 0, 0, P)
#define ALIAS_PGA_EXPAND_g01110(B, C, D, E, F, G, H, I, J, K, L, M, N, O)       g11111(0, B, C, D, E, F, G, H, I, 0, 0, L, M, N, O, 0)
#define ALIAS_PGA_EXPAND_g01111(B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)    g11111(0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)
#define ALIAS_PGA_EXPAND_g10000(A)                                              g11111(A, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define ALIAS_PGA_EXPAND_g10001(A, P)                                           g11111(A, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, P)
#define ALIAS_PGA_EXPAND_g10010(A, L, M, N, O)                                  g11111(A, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L, M, N, O, 0)
#define ALIAS_PGA_EXPAND_g10011(A, L, M, N, O, P)                               g11111(A, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L, M, N, O, P)
#define ALIAS_PGA_EXPAND_g10100(A, F, G, H, I, J, K)                            g11111(A, 0, 0, 0, 0, F, G, H, I, J, K, 0, 0, 0, 0, 0)
#define ALIAS_PGA_EXPAND_g10101(A, F, G, H, I, J, K, P)                         g11111(A, 0, 0, 0, 0, F, G, H, I, J, K, 0, 0, 0, 0, P)
#define ALIAS_PGA_EXPAND_g10110(A, F, G, H, I, J, K, L, M, N, O)                g11111(A, 0, 0, 0, 0, F, G, H, I, J, K, L, M, N, O, 0)
#define ALIAS_PGA_EXPAND_g10111(A, F, G, H, I, J, K, L, M, N, O, P)             g11111(A, 0, 0, 0, 0, F, G, H, I, J, K, L, M, N, O, P)
#define ALIAS_PGA_EXPAND_g11000(A, B, C, D, E)                                  g11111(A, B, C, D, E, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define ALIAS_PGA_EXPAND_g11001(A, B, C, D, E, P)                               g11111(A, B, C, D, E, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, P)
#define ALIAS_PGA_EXPAND_g11010(A, B, C, D, E, L, M, N, O)                      g11111(A, B, C, D, E, 0, 0, 0, 0, 0, 0, L, M, N, O, 0)
#define ALIAS_PGA_EXPAND_g11011(A, B, C, D, E, L, M, N, O, P)                   g11111(A, B, C, D, E, 0, 0, 0, 0, 0, 0, L, M, N, O, P)
#define ALIAS_PGA_EXPAND_g11100(A, B, C, D, E, F, G, H, I, J, K)                g11111(A, B, C, D, E, F, G, H, I, 0, 0, 0, 0, 0, 0, 0)
#define ALIAS_PGA_EXPAND_g11101(A, B, C, D, E, F, G, H, I, J, K, P)             g11111(A, B, C, D, E, F, G, H, I, 0, 0, 0, 0, 0, 0, P)
#define ALIAS_PGA_EXPAND_g11110(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O)    g11111(A, B, C, D, E, F, G, H, I, 0, 0, L, M, N, O, 0)
#define ALIAS_PGA_EXPAND_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)

// get element E from X
// note: requires g11111 form
#define ALIAS_PGA_GET(E, X) ALIAS_PGA_GET_(ALIAS_PGA_TAKE_ ## E ## _, X)
#define ALIAS_PGA_GET_(E, X) ALIAS_CAT(E, X)

// raw get macros
// note: requires g11111 form
#define ALIAS_PGA_TAKE_E__g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)    A
#define ALIAS_PGA_TAKE_E1_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)    B
#define ALIAS_PGA_TAKE_E2_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)    C
#define ALIAS_PGA_TAKE_E3_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)    D
#define ALIAS_PGA_TAKE_E4_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)    E
#define ALIAS_PGA_TAKE_E23_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)   F
#define ALIAS_PGA_TAKE_E31_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)   G
#define ALIAS_PGA_TAKE_E12_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)   H
#define ALIAS_PGA_TAKE_E43_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)   I
#define ALIAS_PGA_TAKE_E42_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)   J
#define ALIAS_PGA_TAKE_E41_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)   K
#define ALIAS_PGA_TAKE_E321_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)  L
#define ALIAS_PGA_TAKE_E124_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)  M
#define ALIAS_PGA_TAKE_E314_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)  N
#define ALIAS_PGA_TAKE_E234_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)  O
#define ALIAS_PGA_TAKE_E1234_g11111(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) P

// predefined version of ALIAS_PGA_GET for brevity later
// note: requires g11111 form
#define ALIAS_PGA_GET_E_(X)    ALIAS_PGA_GET(E_, X)
#define ALIAS_PGA_GET_E1(X)    ALIAS_PGA_GET(E1, X)
#define ALIAS_PGA_GET_E2(X)    ALIAS_PGA_GET(E2, X)
#define ALIAS_PGA_GET_E3(X)    ALIAS_PGA_GET(E3, X)
#define ALIAS_PGA_GET_E4(X)    ALIAS_PGA_GET(E4, X)
#define ALIAS_PGA_GET_E23(X)   ALIAS_PGA_GET(E23, X)
#define ALIAS_PGA_GET_E31(X)   ALIAS_PGA_GET(E31, X)
#define ALIAS_PGA_GET_E12(X)   ALIAS_PGA_GET(E12, X)
#define ALIAS_PGA_GET_E43(X)   ALIAS_PGA_GET(E43, X)
#define ALIAS_PGA_GET_E42(X)   ALIAS_PGA_GET(E42, X)
#define ALIAS_PGA_GET_E41(X)   ALIAS_PGA_GET(E41, X)
#define ALIAS_PGA_GET_E321(X)  ALIAS_PGA_GET(E321, X)
#define ALIAS_PGA_GET_E124(X)  ALIAS_PGA_GET(E124, X)
#define ALIAS_PGA_GET_E314(X)  ALIAS_PGA_GET(E314, X)
#define ALIAS_PGA_GET_E234(X)  ALIAS_PGA_GET(E234, X)
#define ALIAS_PGA_GET_E1234(X) ALIAS_PGA_GET(E1234, X)

// turn bits form into the structure form for C
#define ALIAS_PGA_BITS_TO_MULTIGRADE(BITS) ALIAS_CAT(ALIAS_PGA_BITS_TO_MULTIGRADE_, BITS)
#define ALIAS_PGA_BITS_TO_MULTIGRADE_bits(B0, B1, B2, B3, B4) alias_PGA_Multigrade ## B0 ## B1 ## B2 ## B3 ## B4

// classify the tagged expression and construct the smallest version
#define ALIAS_PGA_SHRINK(X) ALIAS_PGA_SHRINK_1(ALIAS_PGA_GET_E_(X), \
  ALIAS_PGA_GET_E1(X), ALIAS_PGA_GET_E2(X), ALIAS_PGA_GET_E3(X), ALIAS_PGA_GET_E4(X), \
  ALIAS_PGA_GET_E23(X), ALIAS_PGA_GET_E31(X), ALIAS_PGA_GET_E12(X), ALIAS_PGA_GET_E43(X), ALIAS_PGA_GET_E42(X), ALIAS_PGA_GET_E41(X), \
  ALIAS_PGA_GET_E321(X), ALIAS_PGA_GET_E124(X), ALIAS_PGA_GET_E314(X), ALIAS_PGA_GET_E234(X), \
  ALIAS_PGA_GET_E1234(X))
#define ALIAS_PGA_SHRINK_1(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) ALIAS_PGA_SHRINK_2(ALIAS_PGA_VALUES_TO_BITS(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P), A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)
#define ALIAS_PGA_SHRINK_2(BITS, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) ALIAS_PGA_SHRINK_3(ALIAS_PGA_BITS_TO_TAG(BITS), A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)
#define ALIAS_PGA_SHRINK_3(TAG, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P) ALIAS_PGA_CONSTRUCT(TAG, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)

// perform the C-PP unary operator using a math token generator
#define ALIAS_PGA_UNARY(F, A) ALIAS_PGA_UNARY_(F, ALIAS_PGA_EXPAND(A))
#define ALIAS_PGA_UNARY_(F, A) ALIAS_PGA_SHRINK(F( \
  ALIAS_PGA_GET_E_(A), \
  ALIAS_PGA_GET_E1(A), ALIAS_PGA_GET_E2(A), ALIAS_PGA_GET_E3(A), ALIAS_PGA_GET_E4(A), \
  ALIAS_PGA_GET_E23(A), ALIAS_PGA_GET_E31(A), ALIAS_PGA_GET_E12(A), ALIAS_PGA_GET_E43(A), ALIAS_PGA_GET_E42(A), ALIAS_PGA_GET_E41(A), \
  ALIAS_PGA_GET_E321(A), ALIAS_PGA_GET_E124(A), ALIAS_PGA_GET_E314(A), ALIAS_PGA_GET_E234(A), \
  ALIAS_PGA_GET_E1234(A) \
))

// perform the C-PP binary operator using a math token generator
#define ALIAS_PGA_BINARY(F, A, B) ALIAS_PGA_BINARY_(F, ALIAS_PGA_EXPAND(A), ALIAS_PGA_EXPAND(B))
#define ALIAS_PGA_BINARY_(F, A, B) ALIAS_PGA_SHRINK(F( \
  ALIAS_PGA_GET_E_(A), \
  ALIAS_PGA_GET_E1(A), ALIAS_PGA_GET_E2(A), ALIAS_PGA_GET_E3(A), ALIAS_PGA_GET_E4(A), \
  ALIAS_PGA_GET_E23(A), ALIAS_PGA_GET_E31(A), ALIAS_PGA_GET_E12(A), ALIAS_PGA_GET_E43(A), ALIAS_PGA_GET_E42(A), ALIAS_PGA_GET_E41(A), \
  ALIAS_PGA_GET_E321(A), ALIAS_PGA_GET_E124(A), ALIAS_PGA_GET_E314(A), ALIAS_PGA_GET_E234(A), \
  ALIAS_PGA_GET_E1234(A), \
  ALIAS_PGA_GET_E_(B), \
  ALIAS_PGA_GET_E1(B), ALIAS_PGA_GET_E2(B), ALIAS_PGA_GET_E3(B), ALIAS_PGA_GET_E4(B), \
  ALIAS_PGA_GET_E23(B), ALIAS_PGA_GET_E31(B), ALIAS_PGA_GET_E12(B), ALIAS_PGA_GET_E43(B), ALIAS_PGA_GET_E42(B), ALIAS_PGA_GET_E41(B), \
  ALIAS_PGA_GET_E321(B), ALIAS_PGA_GET_E124(B), ALIAS_PGA_GET_E314(B), ALIAS_PGA_GET_E234(B), \
  ALIAS_PGA_GET_E1234(B) \
))

// used for importing
#define ALIAS_PGA_HAS_GRADE0(BITS) ALIAS_CAT(ALIAS_PGA_HAS_GRADE0_, BITS)
#define ALIAS_PGA_HAS_GRADE0_bits(B0, B1, B2, B3, B4) B0

#define ALIAS_PGA_HAS_GRADE1(BITS) ALIAS_CAT(ALIAS_PGA_HAS_GRADE1_, BITS)
#define ALIAS_PGA_HAS_GRADE1_bits(B0, B1, B2, B3, B4) B1

#define ALIAS_PGA_HAS_GRADE2(BITS) ALIAS_CAT(ALIAS_PGA_HAS_GRADE2_, BITS)
#define ALIAS_PGA_HAS_GRADE2_bits(B0, B1, B2, B3, B4) B2

#define ALIAS_PGA_HAS_GRADE3(BITS) ALIAS_CAT(ALIAS_PGA_HAS_GRADE3_, BITS)
#define ALIAS_PGA_HAS_GRADE3_bits(B0, B1, B2, B3, B4) B3

#define ALIAS_PGA_HAS_GRADE4(BITS) ALIAS_CAT(ALIAS_PGA_HAS_GRADE4_, BITS)
#define ALIAS_PGA_HAS_GRADE4_bits(B0, B1, B2, B3, B4) B4

// = c-pp interface
#define ALIAS_PGA_RIGHT_COMPLEMENT(A)  ALIAS_PGA_UNARY(ALIAS_PGA__RIGHT_COMPLEMENT, A)
#define ALIAS_PGA_LEFT_COMPLEMENT(A)   ALIAS_PGA_UNARY(ALIAS_PGA__LEFT_COMPLEMENT, A)
#define ALIAS_PGA_DOUBLE_COMPLEMENT(A) ALIAS_PGA_UNARY(ALIAS_PGA__DOUBLE_COMPLEMENT, A)
#define ALIAS_PGA_REVERSE(A)           ALIAS_PGA_UNARY(ALIAS_PGA__REVERSE, A)
#define ALIAS_PGA_ANTIREVERSE(A)       ALIAS_PGA_UNARY(ALIAS_PGA__ANTIREVERSE, A)

#define ALIAS_PGA_ADD(A, B)                   ALIAS_PGA_BINARY(ALIAS_PGA__ADD, A, B)
#define ALIAS_PGA_SUBTRACT(A, B)              ALIAS_PGA_BINARY(ALIAS_PGA__SUBTRACT, A, B)
#define ALIAS_PGA_EXTERIOR_PRODUCT(A, B)      ALIAS_PGA_BINARY(ALIAS_PGA__EXTERIOR_PRODUCT, A, B)
#define ALIAS_PGA_EXTERIOR_ANTIPRODUCT(A, B)  ALIAS_PGA_BINARY(ALIAS_PGA__EXTERIOR_ANTIPRODUCT, A, B)
#define ALIAS_PGA_GEOMETRIC_PRODUCT(A, B)     ALIAS_PGA_BINARY(ALIAS_PGA__GEOMETRIC_PRODUCT, A, B)
#define ALIAS_PGA_GEOMETRIC_ANTIPRODUCT(A, B) ALIAS_PGA_BINARY(ALIAS_PGA__GEOMETRIC_ANTIPRODUCT, A, B)

#define ALIAS_PGA_TO_TYPE(X) ALIAS_PGA_BITS_TO_MULTIGRADE(ALIAS_PGA_TAG_TO_BITS(ALIAS_PGA_GET_TAG(X)))

#define ALIAS_PGA_TO_C(X) ((ALIAS_PGA_TO_TYPE(X)){ ALIAS_PGA_GET_VALUES(X) })

#define ALIAS_PGA_IMPORT(BITS, X) \
  ALIAS_PGA_CONSTRUCT( \
    ALIAS_PGA_BITS_TO_TAG(BITS), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE0(BITS))(X.e_,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE1(BITS))(X.e1,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE1(BITS))(X.e2,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE1(BITS))(X.e3,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE1(BITS))(X.e4,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE2(BITS))(X.e23,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE2(BITS))(X.e31,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE2(BITS))(X.e12,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE2(BITS))(X.e43,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE2(BITS))(X.e42,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE2(BITS))(X.e41,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE3(BITS))(X.e321,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE3(BITS))(X.e124,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE3(BITS))(X.e314,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE3(BITS))(X.e234,0), \
    ALIAS_IFF(ALIAS_PGA_HAS_GRADE4(BITS))(X.e1234,0) \
  )

#define ALIAS_PGA_SCALAR(S) g10000(S)
#define ALIAS_PGA_POINT(X, Y, Z) g01000(X, Y, Z, 1)

// the basis elements using the c-pp math
#define ALIAS_PGA_E1    g01000(1, 0, 0, 0)
#define ALIAS_PGA_E2    g01000(0, 1, 0, 0)
#define ALIAS_PGA_E3    g01000(0, 0, 1, 0)
#define ALIAS_PGA_E4    g01000(0, 0, 0, 1)
#define ALIAS_PGA_E23   ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E2, ALIAS_PGA_E3)
#define ALIAS_PGA_E31   ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E3, ALIAS_PGA_E1)
#define ALIAS_PGA_E12   ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E1, ALIAS_PGA_E2)
#define ALIAS_PGA_E43   ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E4, ALIAS_PGA_E3)
#define ALIAS_PGA_E42   ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E4, ALIAS_PGA_E2)
#define ALIAS_PGA_E41   ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E4, ALIAS_PGA_E1)
#define ALIAS_PGA_E321  ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E3, ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E2, ALIAS_PGA_E1))
#define ALIAS_PGA_E124  ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E1, ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E2, ALIAS_PGA_E4))
#define ALIAS_PGA_E314  ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E3, ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E1, ALIAS_PGA_E4))
#define ALIAS_PGA_E234  ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E2, ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E3, ALIAS_PGA_E4))
#define ALIAS_PGA_E1234 ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E1, ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E2, ALIAS_PGA_EXTERIOR_PRODUCT(ALIAS_PGA_E3, ALIAS_PGA_E4)))

// = c predefined
extern alias_PGA_Grade1 alias_pga_e1;
extern alias_PGA_Grade1 alias_pga_e2;
extern alias_PGA_Grade1 alias_pga_e3;
extern alias_PGA_Grade1 alias_pga_e4;
extern alias_PGA_Grade2 alias_pga_e23;
extern alias_PGA_Grade2 alias_pga_e31;
extern alias_PGA_Grade2 alias_pga_e12;
extern alias_PGA_Grade2 alias_pga_e43;
extern alias_PGA_Grade2 alias_pga_e42;
extern alias_PGA_Grade2 alias_pga_e41;
extern alias_PGA_Grade3 alias_pga_e321;
extern alias_PGA_Grade3 alias_pga_e124;
extern alias_PGA_Grade3 alias_pga_e314;
extern alias_PGA_Grade3 alias_pga_e234;
extern alias_PGA_Grade4 alias_pga_e1234;

static inline alias_PGA_Grade1 alias_pga_point(alias_R x, alias_R y, alias_R z) {
  return ALIAS_PGA_TO_C(ALIAS_PGA_POINT(x, y, z));
}

#define ALIAS_PGA_GEN_BITS_1(X, Y) \
    X(bits(0,0,0,0,1), Y) \
    X(bits(0,0,0,1,0), Y) \
  /*X(bits(0,0,0,1,1), Y)*/ \
    X(bits(0,0,1,0,0), Y) \
  /*X(bits(0,0,1,0,1), Y)*/ \
  /*X(bits(0,0,1,1,0), Y)*/ \
  /*X(bits(0,0,1,1,1), Y)*/ \
    X(bits(0,1,0,0,0), Y) \
  /*X(bits(0,1,0,0,1), Y)*/ \
  /*X(bits(0,1,0,1,0), Y)*/ \
  /*X(bits(0,1,0,1,1), Y)*/ \
  /*X(bits(0,1,1,0,0), Y)*/ \
  /*X(bits(0,1,1,0,1), Y)*/ \
  /*X(bits(0,1,1,1,0), Y)*/ \
  /*X(bits(0,1,1,1,1), Y)*/ \
    X(bits(1,0,0,0,0), Y) \
  /*X(bits(1,0,0,0,1), Y)*/ \
  /*X(bits(1,0,0,1,0), Y)*/ \
  /*X(bits(1,0,0,1,1), Y)*/ \
  /*X(bits(1,0,1,0,0), Y)*/ \
  /*X(bits(1,0,1,0,1), Y)*/ \
  /*X(bits(1,0,1,1,0), Y)*/ \
  /*X(bits(1,0,1,1,1), Y)*/ \
  /*X(bits(1,1,0,0,0), Y)*/ \
  /*X(bits(1,1,0,0,1), Y)*/ \
  /*X(bits(1,1,0,1,0), Y)*/ \
  /*X(bits(1,1,0,1,1), Y)*/ \
  /*X(bits(1,1,1,0,0), Y)*/ \
  /*X(bits(1,1,1,0,1), Y)*/ \
  /*X(bits(1,1,1,1,0), Y)*/ \
  /*X(bits(1,1,1,1,1), Y)*/

#define ALIAS_PGA_GEN_BITS_2(X, Y) \
    X(bits(0,0,0,0,1), Y) \
    X(bits(0,0,0,1,0), Y) \
  /*X(bits(0,0,0,1,1), Y)*/ \
    X(bits(0,0,1,0,0), Y) \
  /*X(bits(0,0,1,0,1), Y)*/ \
  /*X(bits(0,0,1,1,0), Y)*/ \
  /*X(bits(0,0,1,1,1), Y)*/ \
    X(bits(0,1,0,0,0), Y) \
  /*X(bits(0,1,0,0,1), Y)*/ \
  /*X(bits(0,1,0,1,0), Y)*/ \
  /*X(bits(0,1,0,1,1), Y)*/ \
  /*X(bits(0,1,1,0,0), Y)*/ \
  /*X(bits(0,1,1,0,1), Y)*/ \
  /*X(bits(0,1,1,1,0), Y)*/ \
  /*X(bits(0,1,1,1,1), Y)*/ \
    X(bits(1,0,0,0,0), Y) \
  /*X(bits(1,0,0,0,1), Y)*/ \
  /*X(bits(1,0,0,1,0), Y)*/ \
  /*X(bits(1,0,0,1,1), Y)*/ \
  /*X(bits(1,0,1,0,0), Y)*/ \
  /*X(bits(1,0,1,0,1), Y)*/ \
  /*X(bits(1,0,1,1,0), Y)*/ \
  /*X(bits(1,0,1,1,1), Y)*/ \
  /*X(bits(1,1,0,0,0), Y)*/ \
  /*X(bits(1,1,0,0,1), Y)*/ \
  /*X(bits(1,1,0,1,0), Y)*/ \
  /*X(bits(1,1,0,1,1), Y)*/ \
  /*X(bits(1,1,1,0,0), Y)*/ \
  /*X(bits(1,1,1,0,1), Y)*/ \
  /*X(bits(1,1,1,1,0), Y)*/ \
  /*X(bits(1,1,1,1,1), Y)*/

#define ALIAS_PGA_UNARY_CALL(F, A) ALIAS_PGA_UNARY_CALL_(F, ALIAS_PGA_BITS_TO_TAG(A))
#define ALIAS_PGA_UNARY_CALL_(F, A) ALIAS_PGA_UNARY_CALL__(F, A)
#define ALIAS_PGA_UNARY_CALL__(F, A) alias__pga__##F##_##A

#define ALIAS_PGA_IS_VALID_UNARY(F, A) ALIAS_PGA_IS_VALID_MULTIVECTOR(F(ALIAS_PGA_ONES_FROM_BITS(A)))

#define ALIAS_PGA_BINARY_CALL(F, A, B) ALIAS_PGA_BINARY_CALL_(F, ALIAS_PGA_BITS_TO_TAG(A), ALIAS_PGA_BITS_TO_TAG(B))
#define ALIAS_PGA_BINARY_CALL_(F, A, B) ALIAS_PGA_BINARY_CALL__(F, A, B)
#define ALIAS_PGA_BINARY_CALL__(F, A, B) alias__pga__##F##_##A##_##B

#define ALIAS_PGA_IS_VALID_BINARY(F, A, B) ALIAS_PGA_IS_VALID_MULTIVECTOR(F(ALIAS_PGA_ONES_FROM_BITS(A), ALIAS_PGA_ONES_FROM_BITS(B)))

// construct a c function from c-pp unary operator and bits
#define ALIAS_PGA_DEFINE_UNARY(op, OP) ALIAS_PGA_GEN_BITS_1(ALIAS_PGA_DEFINE_UNARY_, (op, OP))
#define ALIAS_PGA_DEFINE_UNARY_(A, op_OP) ALIAS_PGA_DEFINE_UNARY_1(A, ALIAS_PRIMITIVE_1st op_OP, ALIAS_PRIMITIVE_2nd op_OP)
#define ALIAS_PGA_DEFINE_UNARY_1(A, op, OP) \
  ALIAS_PGA_DEFINE_UNARY_2( \
    OP(ALIAS_PGA_ONES_FROM_BITS(A)), \
    A, ALIAS_PGA_BITS_TO_TAG(A), ALIAS_PGA_BITS_TO_MULTIGRADE(A), \
    op, OP \
  )
#define ALIAS_PGA_DEFINE_UNARY_2(MATH, A, A_TAG, A_TYPE, op, OP) ALIAS_IFF(ALIAS_PGA_IS_VALID_MULTIVECTOR(MATH))(ALIAS_PGA_DEFINE_UNARY_3(ALIAS_PGA_TO_TYPE(MATH), A, A_TAG, A_TYPE, op, OP),)
#define ALIAS_PGA_DEFINE_UNARY_3(RESULT_TYPE, A, A_TAG, A_TYPE, op, OP) ALIAS_PGA_DEFINE_UNARY_4(RESULT_TYPE, A, A_TAG, A_TYPE, op, OP)
#define ALIAS_PGA_DEFINE_UNARY_4(RESULT_TYPE, A, A_TAG, A_TYPE, op, OP) \
  static inline RESULT_TYPE alias__pga__##op##_##A_TAG(A_TYPE a) { \
    return ALIAS_PGA_TO_C(OP(ALIAS_PGA_IMPORT(A, a))); \
  }

// construct a c function from c-pp unary operator and combination bits
#define ALIAS_PGA_DEFINE_BINARY(op, OP) ALIAS_PGA_GEN_BITS_1(ALIAS_PGA_DEFINE_BINARY_LEFT, (op, OP))
#define ALIAS_PGA_DEFINE_BINARY_LEFT(A, op_OP) ALIAS_PGA_GEN_BITS_2(ALIAS_PGA_DEFINE_BINARY_RIGHT, (A, ALIAS_PRIMITIVE_1st op_OP, ALIAS_PRIMITIVE_2nd op_OP))
#define ALIAS_PGA_DEFINE_BINARY_RIGHT(B, A_op_OP) ALIAS_PGA_DEFINE_BINARY_1(ALIAS_PRIMITIVE_1st A_op_OP, B, ALIAS_PRIMITIVE_2nd A_op_OP, ALIAS_PRIMITIVE_3rd A_op_OP)
#define ALIAS_PGA_DEFINE_BINARY_1(A, B, op, OP) \
  ALIAS_PGA_DEFINE_BINARY_2( \
    OP(ALIAS_PGA_ONES_FROM_BITS(A), ALIAS_PGA_ONES_FROM_BITS(B)), \
    A, ALIAS_PGA_BITS_TO_TAG(A), ALIAS_PGA_BITS_TO_MULTIGRADE(A), \
    B, ALIAS_PGA_BITS_TO_TAG(B), ALIAS_PGA_BITS_TO_MULTIGRADE(B), \
    op, OP \
  )
#define ALIAS_PGA_DEFINE_BINARY_2(MATH, A, A_TAG, A_TYPE, B, B_TAG, B_TYPE, op, OP) ALIAS_IFF(ALIAS_PGA_IS_VALID_MULTIVECTOR(MATH))(ALIAS_PGA_DEFINE_BINARY_3(ALIAS_PGA_TO_TYPE(MATH), A, A_TAG, A_TYPE, B, B_TAG, B_TYPE, op, OP),)
#define ALIAS_PGA_DEFINE_BINARY_3(RESULT_TYPE, A, A_TAG, A_TYPE, B, B_TAG, B_TYPE, op, OP) ALIAS_PGA_DEFINE_BINARY_4(RESULT_TYPE, A, A_TAG, A_TYPE, B, B_TAG, B_TYPE, op, OP)
#define ALIAS_PGA_DEFINE_BINARY_4(RESULT_TYPE, A, A_TAG, A_TYPE, B, B_TAG, B_TYPE, op, OP) \
  static inline RESULT_TYPE alias__pga__##op##_##A_TAG##_##B_TAG(A_TYPE a, B_TYPE b) { \
    return ALIAS_PGA_TO_C(OP(ALIAS_PGA_IMPORT(A, a), ALIAS_PGA_IMPORT(B, b))); \
  }

ALIAS_PGA_DEFINE_UNARY(right_complement, ALIAS_PGA_RIGHT_COMPLEMENT)
ALIAS_PGA_DEFINE_UNARY(left_complement, ALIAS_PGA_LEFT_COMPLEMENT)
ALIAS_PGA_DEFINE_UNARY(double_complement, ALIAS_PGA_DOUBLE_COMPLEMENT)
ALIAS_PGA_DEFINE_UNARY(reverse, ALIAS_PGA_REVERSE)
ALIAS_PGA_DEFINE_UNARY(antireverse, ALIAS_PGA_ANTIREVERSE)

ALIAS_PGA_DEFINE_BINARY(add, ALIAS_PGA_ADD)
ALIAS_PGA_DEFINE_BINARY(subtract, ALIAS_PGA_SUBTRACT)
ALIAS_PGA_DEFINE_BINARY(exterior_product, ALIAS_PGA_EXTERIOR_PRODUCT)
ALIAS_PGA_DEFINE_BINARY(exterior_antiproduct, ALIAS_PGA_EXTERIOR_ANTIPRODUCT)
ALIAS_PGA_DEFINE_BINARY(geometric_product, ALIAS_PGA_GEOMETRIC_PRODUCT)
ALIAS_PGA_DEFINE_BINARY(geometric_antiproduct, ALIAS_PGA_GEOMETRIC_ANTIPRODUCT)

// = c on use
// alias_pga_right_complement
#define alias_pga_right_complement(A)    _Generic((A) ALIAS_PGA_GEN_BITS_1(alias_pga_right_complement_,))(A)
#define alias_pga_right_complement_(A,Y) , ALIAS_PGA_BITS_TO_MULTIGRADE(A): ALIAS_PGA_UNARY_CALL(right_complement, A)

// alias_pga_left_complement
#define alias_pga_left_complement(A)    _Generic((A) ALIAS_PGA_GEN_BITS_1(alias_pga_left_complement_,))(A)
#define alias_pga_left_complement_(A,Y) , ALIAS_PGA_BITS_TO_MULTIGRADE(A): ALIAS_PGA_UNARY_CALL(left_complement, A)

// alias_pga_double_complement
#define alias_pga_double_complement(A)    _Generic((A) ALIAS_PGA_GEN_BITS_1(alias_pga_double_complement_,))(A)
#define alias_pga_double_complement_(A,Y) , ALIAS_PGA_BITS_TO_MULTIGRADE(A): ALIAS_PGA_UNARY_CALL(double_complement, A)

// alias_pga_reverse
#define alias_pga_reverse(A)    _Generic((A) ALIAS_PGA_GEN_BITS_1(alias_pga_reverse_,))(A)
#define alias_pga_reverse_(A,Y) , ALIAS_PGA_BITS_TO_MULTIGRADE(A): ALIAS_PGA_UNARY_CALL(reverse, A)

// alias_pga_antireverse
#define alias_pga_antireverse(A)    _Generic((A) ALIAS_PGA_GEN_BITS_1(alias_pga_antireverse_,))(A)
#define alias_pga_antireverse_(A,Y) , ALIAS_PGA_BITS_TO_MULTIGRADE(A): ALIAS_PGA_UNARY_CALL(antireverse, A)

// alias_pga_add
#define alias_pga_add(A, B)       _Generic((A) ALIAS_PGA_GEN_BITS_1(alias_pga_add_left,B))(A, B)
#define alias_pga_add_left(A, B)  , ALIAS_PGA_BITS_TO_MULTIGRADE(A): _Generic(B ALIAS_PGA_GEN_BITS_2(alias_pga_add_right, A))
#define alias_pga_add_right(B, A) , ALIAS_PGA_BITS_TO_MULTIGRADE(B): ALIAS_PGA_BINARY_CALL(add, A, B)

// alias_pga_subtract
#define alias_pga_subtract(A, B)       _Generic((A) ALIAS_PGA_GEN_BITS_1(alias_pga_subtract_left,B))(A, B)
#define alias_pga_subtract_left(A, B)  , ALIAS_PGA_BITS_TO_MULTIGRADE(A): _Generic(B ALIAS_PGA_GEN_BITS_2(alias_pga_subtract_right, A))
#define alias_pga_subtract_right(B, A) , ALIAS_PGA_BITS_TO_MULTIGRADE(B): ALIAS_PGA_BINARY_CALL(subtract, A, B)

// alias_pga_exterior_product/wedge/join
#define alias_pga_exterior_product(A, B)       _Generic((A) ALIAS_PGA_GEN_BITS_1(alias_pga_exterior_product_left,B))(A, B)
#define alias_pga_exterior_product_left(A, B)  , ALIAS_PGA_BITS_TO_MULTIGRADE(A): _Generic(B ALIAS_PGA_GEN_BITS_2(alias_pga_exterior_product_right, A))
#define alias_pga_exterior_product_right(B, A) , ALIAS_PGA_BITS_TO_MULTIGRADE(B): ALIAS_PGA_BINARY_CALL(exterior_product, A, B)

#define alias_pga_wedge alias_pga_exterior_product
#define alias_pga_join alias_pga_exterior_product

// alias_pga_exterior_antiproduct/antiwedge/meet
#define alias_pga_exterior_antiproduct(A, B)       _Generic((A) ALIAS_PGA_GEN_BITS_1(alias_pga_exterior_antiproduct_left,B))(A, B)
#define alias_pga_exterior_antiproduct_left(A, B)  , ALIAS_PGA_BITS_TO_MULTIGRADE(A): _Generic(B ALIAS_PGA_GEN_BITS_2(alias_pga_exterior_antiproduct_right, A))
#define alias_pga_exterior_antiproduct_right(B, A) , ALIAS_PGA_BITS_TO_MULTIGRADE(B): ALIAS_PGA_BINARY_CALL(exterior_antiproduct, A, B)

#define alias_pga_antiwedge alias_pga_exterior_antiproduct
#define alias_pga_meet alias_pga_exterior_antiproduct

// alias_pga_geometric_product/wedge_dot
#define alias_pga_geometric_product(A, B)       _Generic((A) ALIAS_PGA_GEN_BITS_1(alias_pga_geometric_product_left,B))(A, B)
#define alias_pga_geometric_product_left(A, B)  , ALIAS_PGA_BITS_TO_MULTIGRADE(A): _Generic(B ALIAS_PGA_GEN_BITS_2(alias_pga_geometric_product_right, A))
#define alias_pga_geometric_product_right(B, A) , ALIAS_PGA_BITS_TO_MULTIGRADE(B): ALIAS_PGA_BINARY_CALL(geometric_product, A, B)

#define alias_pga_wedge_dot alias_pga_geometric_product

// alias_pga_geometric_antiproduct/antiwedge_dot
#define alias_pga_geometric_antiproduct(A, B)       _Generic((A) ALIAS_PGA_GEN_BITS_1(alias_pga_geometric_antiproduct_left,B))(A, B)
#define alias_pga_geometric_antiproduct_left(A, B)  , ALIAS_PGA_BITS_TO_MULTIGRADE(A): _Generic(B ALIAS_PGA_GEN_BITS_2(alias_pga_geometric_antiproduct_right, A))
#define alias_pga_geometric_antiproduct_right(B, A) , ALIAS_PGA_BITS_TO_MULTIGRADE(B): ALIAS_PGA_BINARY_CALL(geometric_antiproduct, A, B)

#define alias_pga_antiwedge_dot alias_pga_geometric_antiproduct

#endif

