// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
// generated with alias_gen_geometric_algebra (author Sarah Burns <mystical.unicat@gmail.com>)
// options: -p 2 -d 1 --binary meet outer_product --binary join regressive_product --code m02
#ifndef _ALIAS_PGA2D_H_
#define _ALIAS_PGA2D_H_
// 2 positive dimension(s)
// 0 negative dimension(s)
// 1 deginerate dimension(s)
// 3 total dimension(s)
// 4 total grade(s)
#define ALIAS_PGA2D_EMPTY(...)
#define ALIAS_PGA2D_UNPACK(...) __VA_ARGS__
#define ALIAS_PGA2D_CAT(X, ...) ALIAS_PGA2D_CAT0(X, ## __VA_ARGS__)
#define ALIAS_PGA2D_CAT0(X, ...) X ## __VA_ARGS__
#define ALIAS_PGA2D_CAT3(X, Y, ...) ALIAS_PGA2D_CAT30(X, Y, ## __VA_ARGS__)
#define ALIAS_PGA2D_CAT30(X, Y, ...) X ## Y ## __VA_ARGS__
#define ALIAS_PGA2D_OR(X, Y) ALIAS_PGA2D_CAT3(ALIAS_PGA2D_OR_, X, Y)
#define ALIAS_PGA2D_OR_00 0
#define ALIAS_PGA2D_OR_01 1
#define ALIAS_PGA2D_OR_10 1
#define ALIAS_PGA2D_OR_11 1
#define ALIAS_PGA2D_IFF(X) ALIAS_PGA2D_CAT(ALIAS_PGA2D_IFF_, X)
#define ALIAS_PGA2D_IFF_0(T, F) F
#define ALIAS_PGA2D_IFF_1(T, F) T
#define ALIAS_PGA2D_IF2(X, Y) ALIAS_PGA2D_CAT3(ALIAS_PGA2D_IF2_, X, Y)
#define ALIAS_PGA2D_IF(X) ALIAS_PGA2D_CAT(ALIAS_PGA2D_IF_, X)
#define ALIAS_PGA2D_IF_0(...) ALIAS_PGA2D_UNPACK
#define ALIAS_PGA2D_IF_1(...) __VA_ARGS__ ALIAS_PGA2D_EMPTY
#define ALIAS_PGA2D_IF2(X, Y) ALIAS_PGA2D_CAT3(ALIAS_PGA2D_IF2_, X, Y)
#define ALIAS_PGA2D_IF2_00(...) ALIAS_PGA2D_IF2_000
#define ALIAS_PGA2D_IF2_000(...) ALIAS_PGA2D_IF2_001
#define ALIAS_PGA2D_IF2_001(...) ALIAS_PGA2D_UNPACK
#define ALIAS_PGA2D_IF2_01(...) ALIAS_PGA2D_IF2_010
#define ALIAS_PGA2D_IF2_010(...) ALIAS_PGA2D_IF2_011
#define ALIAS_PGA2D_IF2_011(...) __VA_ARGS__ ALIAS_PGA2D_EMPTY
#define ALIAS_PGA2D_IF2_10(...) ALIAS_PGA2D_IF2_100
#define ALIAS_PGA2D_IF2_100(...) __VA_ARGS__ ALIAS_PGA2D_IF2_101
#define ALIAS_PGA2D_IF2_101(...) ALIAS_PGA2D_EMPTY
#define ALIAS_PGA2D_IF2_11(...) __VA_ARGS__ ALIAS_PGA2D_IF2_110
#define ALIAS_PGA2D_IF2_110(...) ALIAS_PGA2D_IF2_111
#define ALIAS_PGA2D_IF2_111(...) ALIAS_PGA2D_EMPTY
#define ALIAS_PGA2D_PROBE(...) ~,1
#define ALIAS_PGA2D_IS_PROBE(...) ALIAS_PGA2D_IS_PROBE0(__VA_ARGS__, 0, 0)
#define ALIAS_PGA2D_IS_PROBE0(X, Y, ...) Y
#define ALIAS_PGA2D_IS_ZERO(X) ALIAS_PGA2D_IFF(ALIAS_PGA2D_IS_PROBE(ALIAS_PGA2D_PROBE X))(ALIAS_PGA2D_IS_ZERO1, ALIAS_PGA2D_IS_ZERO2)(X)
#define ALIAS_PGA2D_IS_ZERO1(X) 0
#define ALIAS_PGA2D_IS_ZERO2(X) ALIAS_PGA2D_IS_PROBE(ALIAS_PGA2D_CAT(ALIAS_PGA2D_IS_ZERO3_, X)())
#define ALIAS_PGA2D_IS_ZERO3_0 ALIAS_PGA2D_PROBE
#define ALIAS_PGA2D_IS_NONZERO(X) ALIAS_PGA2D_IF(ALIAS_PGA2D_IS_ZERO(X))(0)(1)
#define ALIAS_PGA2D_NEG(X) ALIAS_PGA2D_IF(ALIAS_PGA2D_IS_ZERO(X))( 0 )( (-X) )
#define ALIAS_PGA2D_ADD(X, Y) ALIAS_PGA2D_IF2(ALIAS_PGA2D_IS_ZERO(X), ALIAS_PGA2D_IS_ZERO(Y))( 0 )(   Y  )( X )( X+Y )
#define ALIAS_PGA2D_SUB(X, Y) ALIAS_PGA2D_IF2(ALIAS_PGA2D_IS_ZERO(X), ALIAS_PGA2D_IS_ZERO(Y))( 0 )( (-Y) )( X )( X-Y )
#define ALIAS_PGA2D_ADD_MUL(X, Y) ALIAS_PGA2D_IF(ALIAS_PGA2D_OR(ALIAS_PGA2D_IS_ZERO(X), ALIAS_PGA2D_IS_ZERO(Y)))( )( +(X*Y) )
#define ALIAS_PGA2D_SUB_MUL(X, Y) ALIAS_PGA2D_IF(ALIAS_PGA2D_OR(ALIAS_PGA2D_IS_ZERO(X), ALIAS_PGA2D_IS_ZERO(Y)))( )( -(X*Y) )
// cayley table:
// one    e0     e1     e2     e01    e02    e12    e012  
// e0     0      e01    e02    0      0      e012   0     
// e1     -e01   one    e12    -e0    -e012  e2     -e02  
// e2     -e02   -e12   one    e012   -e0    -e1    e01   
// e01    0      e0     e012   0      0      e02    0     
// e02    0      -e012  e0     0      0      -e01   0     
// e12    e012   -e2    e1     -e02   e01    -one   -e0   
// e012   0      -e02   e01    0      0      -e0    0     
typedef struct alias_pga2d_0000 { union { float _; }; } alias_pga2d_0000;
typedef struct alias_pga2d_1000 { union { float _; struct { float one; }; }; } alias_pga2d_1000, alias_pga2d_Scalar, alias_pga2d_AntiTrivector;
typedef struct alias_pga2d_0100 { union { float _; struct { float e0, e1, e2; }; }; } alias_pga2d_0100, alias_pga2d_Vector, alias_pga2d_AntiBivector;
typedef struct alias_pga2d_1100 { union { float _; struct { float one, e0, e1, e2; }; }; } alias_pga2d_1100;
typedef struct alias_pga2d_0010 { union { float _; struct { float e01, e02, e12; }; }; } alias_pga2d_0010, alias_pga2d_Bivector, alias_pga2d_AntiVector;
typedef struct alias_pga2d_1010 { union { float _; struct { float one, e01, e02, e12; }; }; } alias_pga2d_1010;
typedef struct alias_pga2d_0110 { union { float _; struct { float e0, e1, e2, e01, e02, e12; }; }; } alias_pga2d_0110;
typedef struct alias_pga2d_1110 { union { float _; struct { float one, e0, e1, e2, e01, e02, e12; }; }; } alias_pga2d_1110;
typedef struct alias_pga2d_0001 { union { float _; struct { float e012; }; }; } alias_pga2d_0001, alias_pga2d_Trivector, alias_pga2d_AntiScalar;
typedef struct alias_pga2d_1001 { union { float _; struct { float one, e012; }; }; } alias_pga2d_1001;
typedef struct alias_pga2d_0101 { union { float _; struct { float e0, e1, e2, e012; }; }; } alias_pga2d_0101;
typedef struct alias_pga2d_1101 { union { float _; struct { float one, e0, e1, e2, e012; }; }; } alias_pga2d_1101;
typedef struct alias_pga2d_0011 { union { float _; struct { float e01, e02, e12, e012; }; }; } alias_pga2d_0011;
typedef struct alias_pga2d_1011 { union { float _; struct { float one, e01, e02, e12, e012; }; }; } alias_pga2d_1011;
typedef struct alias_pga2d_0111 { union { float _; struct { float e0, e1, e2, e01, e02, e12, e012; }; }; } alias_pga2d_0111;
typedef struct alias_pga2d_1111 { union { float _; struct { float one, e0, e1, e2, e01, e02, e12, e012; }; }; } alias_pga2d_1111;
#define ALIAS_PGA2D_GRADE(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, ...) RETURN( \
    ALIAS_PGA2D_IS_NONZERO(Xone) \
  , ALIAS_PGA2D_OR(ALIAS_PGA2D_IS_NONZERO(Xe0), ALIAS_PGA2D_OR(ALIAS_PGA2D_IS_NONZERO(Xe1), ALIAS_PGA2D_IS_NONZERO(Xe2))) \
  , ALIAS_PGA2D_OR(ALIAS_PGA2D_IS_NONZERO(Xe01), ALIAS_PGA2D_OR(ALIAS_PGA2D_IS_NONZERO(Xe02), ALIAS_PGA2D_IS_NONZERO(Xe12))) \
  , ALIAS_PGA2D_IS_NONZERO(Xe012) \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_TYPE(X0,X1,X2,X3) ALIAS_PGA2D_TYPE_(X0,X1,X2,X3)
#define ALIAS_PGA2D_TYPE_(X0,X1,X2,X3) alias_pga2d_ ## X0 ## X1 ## X2 ## X3
#define ALIAS_PGA2D_UNARY(OP, X) ALIAS_PGA2D_UNARY0(OP, ALIAS_PGA2D_UNPACK X)
#define ALIAS_PGA2D_UNARY0(...) ALIAS_PGA2D_UNARY1(__VA_ARGS__)
#define ALIAS_PGA2D_UNARY1(OP, X0,X1,X2,X3,X) ALIAS_PGA2D_UNARY2( \
    OP \
  , ALIAS_PGA2D_IF(X0)(_x.one)(0) \
  , ALIAS_PGA2D_IF(X1)(_x.e0)(0) \
  , ALIAS_PGA2D_IF(X1)(_x.e1)(0) \
  , ALIAS_PGA2D_IF(X1)(_x.e2)(0) \
  , ALIAS_PGA2D_IF(X2)(_x.e01)(0) \
  , ALIAS_PGA2D_IF(X2)(_x.e02)(0) \
  , ALIAS_PGA2D_IF(X2)(_x.e12)(0) \
  , ALIAS_PGA2D_IF(X3)(_x.e012)(0) \
  , X0,X1,X2,X3,X \
  )
#define ALIAS_PGA2D_UNARY2(OP, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012,X0,X1,X2,X3,X) OP(ALIAS_PGA2D_UNARY3, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, X0,X1,X2,X3,X)
#define ALIAS_PGA2D_UNARY3(Zone,Ze0,Ze1,Ze2,Ze01,Ze02,Ze12,Ze012,X0,X1,X2,X3,X) ALIAS_PGA2D_GRADE(ALIAS_PGA2D_UNARY4, Zone,Ze0,Ze1,Ze2,Ze01,Ze02,Ze12,Ze012, Zone,Ze0,Ze1,Ze2,Ze01,Ze02,Ze12,Ze012,X0,X1,X2,X3,X)
#define ALIAS_PGA2D_UNARY4(Z0,Z1,Z2,Z3,Zone,Ze0,Ze1,Ze2,Ze01,Ze02,Ze12,Ze012,X0,X1,X2,X3,X) (Z0,Z1,Z2,Z3, __extension__ ({ \
  ALIAS_PGA2D_TYPE(X0,X1,X2,X3) _x = X; \
  (ALIAS_PGA2D_TYPE(Z0,Z1,Z2,Z3)) { \
    ._ = 0 \
    ALIAS_PGA2D_IF(Z0)(, .one = Zone)() \
    ALIAS_PGA2D_IF(Z1)(, .e0 = Ze0)() \
    ALIAS_PGA2D_IF(Z1)(, .e1 = Ze1)() \
    ALIAS_PGA2D_IF(Z1)(, .e2 = Ze2)() \
    ALIAS_PGA2D_IF(Z2)(, .e01 = Ze01)() \
    ALIAS_PGA2D_IF(Z2)(, .e02 = Ze02)() \
    ALIAS_PGA2D_IF(Z2)(, .e12 = Ze12)() \
    ALIAS_PGA2D_IF(Z3)(, .e012 = Ze012)() \
  }; \
}))
#define ALIAS_PGA2D_OP_GRADE_0(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, ...) RETURN( \
    Xone \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_GRADE_1(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, ...) RETURN( \
    0 \
  , Xe0 \
  , Xe1 \
  , Xe2 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_GRADE_2(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, ...) RETURN( \
    0 \
  , 0 \
  , 0 \
  , 0 \
  , Xe01 \
  , Xe02 \
  , Xe12 \
  , 0 \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_GRADE_3(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, ...) RETURN( \
    0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , Xe012 \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_NEGATE(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, ...) RETURN( \
    ALIAS_PGA2D_NEG(Xone) \
  , ALIAS_PGA2D_NEG(Xe0) \
  , ALIAS_PGA2D_NEG(Xe1) \
  , ALIAS_PGA2D_NEG(Xe2) \
  , ALIAS_PGA2D_NEG(Xe01) \
  , ALIAS_PGA2D_NEG(Xe02) \
  , ALIAS_PGA2D_NEG(Xe12) \
  , ALIAS_PGA2D_NEG(Xe012) \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_DUAL(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, ...) RETURN( \
    Xe012 \
  , Xe12 \
  , ALIAS_PGA2D_NEG(Xe02) \
  , Xe01 \
  , Xe2 \
  , ALIAS_PGA2D_NEG(Xe1) \
  , Xe0 \
  , Xone \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_POLAR(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, ...) RETURN( \
    0 \
  , ALIAS_PGA2D_NEG(Xe0) \
  , 0 \
  , 0 \
  , Xe01 \
  , ALIAS_PGA2D_NEG(Xe02) \
  , 0 \
  , Xe012 \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_REVERSE(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, ...) RETURN( \
    Xone \
  , Xe0 \
  , Xe1 \
  , Xe2 \
  , ALIAS_PGA2D_NEG(Xe01) \
  , ALIAS_PGA2D_NEG(Xe02) \
  , ALIAS_PGA2D_NEG(Xe12) \
  , ALIAS_PGA2D_NEG(Xe012) \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_INVOLUTE(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, ...) RETURN( \
    Xone \
  , ALIAS_PGA2D_NEG(Xe0) \
  , ALIAS_PGA2D_NEG(Xe1) \
  , ALIAS_PGA2D_NEG(Xe2) \
  , Xe01 \
  , Xe02 \
  , Xe12 \
  , ALIAS_PGA2D_NEG(Xe012) \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_CONJUGATE(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, ...) RETURN( \
    Xone \
  , ALIAS_PGA2D_NEG(Xe0) \
  , ALIAS_PGA2D_NEG(Xe1) \
  , ALIAS_PGA2D_NEG(Xe2) \
  , ALIAS_PGA2D_NEG(Xe01) \
  , ALIAS_PGA2D_NEG(Xe02) \
  , ALIAS_PGA2D_NEG(Xe12) \
  , Xe012 \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_BINARY(OP, X, Y) ALIAS_PGA2D_BINARY0(OP, ALIAS_PGA2D_UNPACK X, ALIAS_PGA2D_UNPACK Y)
#define ALIAS_PGA2D_BINARY0(...) ALIAS_PGA2D_BINARY1(__VA_ARGS__)
#define ALIAS_PGA2D_BINARY1(OP, X0,X1,X2,X3,X,Y0,Y1,Y2,Y3,Y) ALIAS_PGA2D_BINARY2( \
    OP \
  , ALIAS_PGA2D_IF(X0)(_x.one)(0) \
  , ALIAS_PGA2D_IF(X1)(_x.e0)(0) \
  , ALIAS_PGA2D_IF(X1)(_x.e1)(0) \
  , ALIAS_PGA2D_IF(X1)(_x.e2)(0) \
  , ALIAS_PGA2D_IF(X2)(_x.e01)(0) \
  , ALIAS_PGA2D_IF(X2)(_x.e02)(0) \
  , ALIAS_PGA2D_IF(X2)(_x.e12)(0) \
  , ALIAS_PGA2D_IF(X3)(_x.e012)(0) \
  , ALIAS_PGA2D_IF(Y0)(_y.one)(0) \
  , ALIAS_PGA2D_IF(Y1)(_y.e0)(0) \
  , ALIAS_PGA2D_IF(Y1)(_y.e1)(0) \
  , ALIAS_PGA2D_IF(Y1)(_y.e2)(0) \
  , ALIAS_PGA2D_IF(Y2)(_y.e01)(0) \
  , ALIAS_PGA2D_IF(Y2)(_y.e02)(0) \
  , ALIAS_PGA2D_IF(Y2)(_y.e12)(0) \
  , ALIAS_PGA2D_IF(Y3)(_y.e012)(0) \
  , X0,X1,X2,X3,X \
  , Y0,Y1,Y2,Y3,Y \
  )
#define ALIAS_PGA2D_BINARY2(OP, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012,Yone,Ye0,Ye1,Ye2,Ye01,Ye02,Ye12,Ye012,X0,X1,X2,X3,X, Y0,Y1,Y2,Y3,Y) OP(ALIAS_PGA2D_BINARY3, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012,Yone,Ye0,Ye1,Ye2,Ye01,Ye02,Ye12,Ye012, X0,X1,X2,X3,X, Y0,Y1,Y2,Y3,Y)
#define ALIAS_PGA2D_BINARY3(Zone,Ze0,Ze1,Ze2,Ze01,Ze02,Ze12,Ze012,X0,X1,X2,X3,X, Y0,Y1,Y2,Y3,Y) ALIAS_PGA2D_GRADE(ALIAS_PGA2D_BINARY4, Zone,Ze0,Ze1,Ze2,Ze01,Ze02,Ze12,Ze012, Zone,Ze0,Ze1,Ze2,Ze01,Ze02,Ze12,Ze012,X0,X1,X2,X3,X, Y0,Y1,Y2,Y3,Y)
#define ALIAS_PGA2D_BINARY4(Z0,Z1,Z2,Z3,Zone,Ze0,Ze1,Ze2,Ze01,Ze02,Ze12,Ze012,X0,X1,X2,X3,X, Y0,Y1,Y2,Y3,Y) (Z0,Z1,Z2,Z3, __extension__ ({ \
  ALIAS_PGA2D_TYPE(X0,X1,X2,X3) _x = X; \
  ALIAS_PGA2D_TYPE(Y0,Y1,Y2,Y3) _y = Y; \
  (ALIAS_PGA2D_TYPE(Z0,Z1,Z2,Z3)) { \
    ._ = 0 \
    ALIAS_PGA2D_IF(Z0)(, .one = Zone)() \
    ALIAS_PGA2D_IF(Z1)(, .e0 = Ze0)() \
    ALIAS_PGA2D_IF(Z1)(, .e1 = Ze1)() \
    ALIAS_PGA2D_IF(Z1)(, .e2 = Ze2)() \
    ALIAS_PGA2D_IF(Z2)(, .e01 = Ze01)() \
    ALIAS_PGA2D_IF(Z2)(, .e02 = Ze02)() \
    ALIAS_PGA2D_IF(Z2)(, .e12 = Ze12)() \
    ALIAS_PGA2D_IF(Z3)(, .e012 = Ze012)() \
  }; \
}))
#define ALIAS_PGA2D_OP_ADD(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, Yone,Ye0,Ye1,Ye2,Ye01,Ye02,Ye12,Ye012, ...) RETURN( \
    ALIAS_PGA2D_ADD(Xone, Yone) \
  , ALIAS_PGA2D_ADD(Xe0, Ye0) \
  , ALIAS_PGA2D_ADD(Xe1, Ye1) \
  , ALIAS_PGA2D_ADD(Xe2, Ye2) \
  , ALIAS_PGA2D_ADD(Xe01, Ye01) \
  , ALIAS_PGA2D_ADD(Xe02, Ye02) \
  , ALIAS_PGA2D_ADD(Xe12, Ye12) \
  , ALIAS_PGA2D_ADD(Xe012, Ye012) \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_SUBTRACT(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, Yone,Ye0,Ye1,Ye2,Ye01,Ye02,Ye12,Ye012, ...) RETURN( \
    ALIAS_PGA2D_SUB(Xone, Yone) \
  , ALIAS_PGA2D_SUB(Xe0, Ye0) \
  , ALIAS_PGA2D_SUB(Xe1, Ye1) \
  , ALIAS_PGA2D_SUB(Xe2, Ye2) \
  , ALIAS_PGA2D_SUB(Xe01, Ye01) \
  , ALIAS_PGA2D_SUB(Xe02, Ye02) \
  , ALIAS_PGA2D_SUB(Xe12, Ye12) \
  , ALIAS_PGA2D_SUB(Xe012, Ye012) \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_GEOMETRIC_PRODUCT(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, Yone,Ye0,Ye1,Ye2,Ye01,Ye02,Ye12,Ye012, ...) RETURN( \
    0 ALIAS_PGA2D_ADD_MUL(Xone,Yone) ALIAS_PGA2D_ADD_MUL(Xe1,Ye1) ALIAS_PGA2D_ADD_MUL(Xe2,Ye2) ALIAS_PGA2D_SUB_MUL(Xe12,Ye12) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye0) ALIAS_PGA2D_ADD_MUL(Xe0,Yone) ALIAS_PGA2D_SUB_MUL(Xe1,Ye01) ALIAS_PGA2D_SUB_MUL(Xe2,Ye02) ALIAS_PGA2D_ADD_MUL(Xe01,Ye1) ALIAS_PGA2D_ADD_MUL(Xe02,Ye2) ALIAS_PGA2D_SUB_MUL(Xe12,Ye012) ALIAS_PGA2D_SUB_MUL(Xe012,Ye12) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye1) ALIAS_PGA2D_ADD_MUL(Xe1,Yone) ALIAS_PGA2D_SUB_MUL(Xe2,Ye12) ALIAS_PGA2D_ADD_MUL(Xe12,Ye2) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye2) ALIAS_PGA2D_ADD_MUL(Xe1,Ye12) ALIAS_PGA2D_ADD_MUL(Xe2,Yone) ALIAS_PGA2D_SUB_MUL(Xe12,Ye1) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye01) ALIAS_PGA2D_ADD_MUL(Xe0,Ye1) ALIAS_PGA2D_SUB_MUL(Xe1,Ye0) ALIAS_PGA2D_ADD_MUL(Xe2,Ye012) ALIAS_PGA2D_ADD_MUL(Xe01,Yone) ALIAS_PGA2D_SUB_MUL(Xe02,Ye12) ALIAS_PGA2D_ADD_MUL(Xe12,Ye02) ALIAS_PGA2D_ADD_MUL(Xe012,Ye2) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye02) ALIAS_PGA2D_ADD_MUL(Xe0,Ye2) ALIAS_PGA2D_SUB_MUL(Xe1,Ye012) ALIAS_PGA2D_SUB_MUL(Xe2,Ye0) ALIAS_PGA2D_ADD_MUL(Xe01,Ye12) ALIAS_PGA2D_ADD_MUL(Xe02,Yone) ALIAS_PGA2D_SUB_MUL(Xe12,Ye01) ALIAS_PGA2D_SUB_MUL(Xe012,Ye1) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye12) ALIAS_PGA2D_ADD_MUL(Xe1,Ye2) ALIAS_PGA2D_SUB_MUL(Xe2,Ye1) ALIAS_PGA2D_ADD_MUL(Xe12,Yone) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye012) ALIAS_PGA2D_ADD_MUL(Xe0,Ye12) ALIAS_PGA2D_SUB_MUL(Xe1,Ye02) ALIAS_PGA2D_ADD_MUL(Xe2,Ye01) ALIAS_PGA2D_ADD_MUL(Xe01,Ye2) ALIAS_PGA2D_SUB_MUL(Xe02,Ye1) ALIAS_PGA2D_ADD_MUL(Xe12,Ye0) ALIAS_PGA2D_ADD_MUL(Xe012,Yone) \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_OUTER_PRODUCT(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, Yone,Ye0,Ye1,Ye2,Ye01,Ye02,Ye12,Ye012, ...) RETURN( \
    0 ALIAS_PGA2D_ADD_MUL(Xone,Yone) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye0) ALIAS_PGA2D_ADD_MUL(Xe0,Yone) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye1) ALIAS_PGA2D_ADD_MUL(Xe1,Yone) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye2) ALIAS_PGA2D_ADD_MUL(Xe2,Yone) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye01) ALIAS_PGA2D_ADD_MUL(Xe0,Ye1) ALIAS_PGA2D_SUB_MUL(Xe1,Ye0) ALIAS_PGA2D_ADD_MUL(Xe01,Yone) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye02) ALIAS_PGA2D_ADD_MUL(Xe0,Ye2) ALIAS_PGA2D_SUB_MUL(Xe2,Ye0) ALIAS_PGA2D_ADD_MUL(Xe02,Yone) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye12) ALIAS_PGA2D_ADD_MUL(Xe1,Ye2) ALIAS_PGA2D_SUB_MUL(Xe2,Ye1) ALIAS_PGA2D_ADD_MUL(Xe12,Yone) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye012) ALIAS_PGA2D_ADD_MUL(Xe0,Ye12) ALIAS_PGA2D_SUB_MUL(Xe1,Ye02) ALIAS_PGA2D_ADD_MUL(Xe2,Ye01) ALIAS_PGA2D_ADD_MUL(Xe01,Ye2) ALIAS_PGA2D_SUB_MUL(Xe02,Ye1) ALIAS_PGA2D_ADD_MUL(Xe12,Ye0) ALIAS_PGA2D_ADD_MUL(Xe012,Yone) \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_REGRESSIVE_PRODUCT(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, Yone,Ye0,Ye1,Ye2,Ye01,Ye02,Ye12,Ye012, ...) RETURN( \
    0 ALIAS_PGA2D_ADD_MUL(Xone,Ye012) ALIAS_PGA2D_ADD_MUL(Xe0,Ye12) ALIAS_PGA2D_SUB_MUL(Xe1,Ye02) ALIAS_PGA2D_ADD_MUL(Xe2,Ye01) ALIAS_PGA2D_ADD_MUL(Xe01,Ye2) ALIAS_PGA2D_SUB_MUL(Xe02,Ye1) ALIAS_PGA2D_ADD_MUL(Xe12,Ye0) ALIAS_PGA2D_ADD_MUL(Xe012,Yone) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xe0,Ye012) ALIAS_PGA2D_SUB_MUL(Xe01,Ye02) ALIAS_PGA2D_ADD_MUL(Xe02,Ye01) ALIAS_PGA2D_ADD_MUL(Xe012,Ye0) \
  , 0 ALIAS_PGA2D_SUB_MUL(Xe1,Ye012) ALIAS_PGA2D_ADD_MUL(Xe01,Ye12) ALIAS_PGA2D_SUB_MUL(Xe12,Ye01) ALIAS_PGA2D_SUB_MUL(Xe012,Ye1) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xe2,Ye012) ALIAS_PGA2D_SUB_MUL(Xe02,Ye12) ALIAS_PGA2D_ADD_MUL(Xe12,Ye02) ALIAS_PGA2D_ADD_MUL(Xe012,Ye2) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xe01,Ye012) ALIAS_PGA2D_ADD_MUL(Xe012,Ye01) \
  , 0 ALIAS_PGA2D_SUB_MUL(Xe02,Ye012) ALIAS_PGA2D_SUB_MUL(Xe012,Ye02) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xe12,Ye012) ALIAS_PGA2D_ADD_MUL(Xe012,Ye12) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xe012,Ye012) \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_COMMUTATOR_PRODUCT(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, Yone,Ye0,Ye1,Ye2,Ye01,Ye02,Ye12,Ye012, ...) RETURN( \
    0 \
  , 0 ALIAS_PGA2D_SUB_MUL(Xe1,Ye01) ALIAS_PGA2D_SUB_MUL(Xe2,Ye02) ALIAS_PGA2D_ADD_MUL(Xe01,Ye1) ALIAS_PGA2D_ADD_MUL(Xe02,Ye2) \
  , 0 ALIAS_PGA2D_SUB_MUL(Xe2,Ye12) ALIAS_PGA2D_ADD_MUL(Xe12,Ye2) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xe1,Ye12) ALIAS_PGA2D_SUB_MUL(Xe12,Ye1) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xe0,Ye1) ALIAS_PGA2D_SUB_MUL(Xe1,Ye0) ALIAS_PGA2D_SUB_MUL(Xe02,Ye12) ALIAS_PGA2D_ADD_MUL(Xe12,Ye02) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xe0,Ye2) ALIAS_PGA2D_SUB_MUL(Xe2,Ye0) ALIAS_PGA2D_ADD_MUL(Xe01,Ye12) ALIAS_PGA2D_SUB_MUL(Xe12,Ye01) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xe1,Ye2) ALIAS_PGA2D_SUB_MUL(Xe2,Ye1) \
  , 0 \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_INNER_PRODUCT(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, Yone,Ye0,Ye1,Ye2,Ye01,Ye02,Ye12,Ye012, ...) RETURN( \
    0 ALIAS_PGA2D_ADD_MUL(Xone,Yone) ALIAS_PGA2D_ADD_MUL(Xe1,Ye1) ALIAS_PGA2D_ADD_MUL(Xe2,Ye2) ALIAS_PGA2D_SUB_MUL(Xe12,Ye12) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye0) ALIAS_PGA2D_ADD_MUL(Xe0,Yone) ALIAS_PGA2D_SUB_MUL(Xe1,Ye01) ALIAS_PGA2D_SUB_MUL(Xe2,Ye02) ALIAS_PGA2D_ADD_MUL(Xe01,Ye1) ALIAS_PGA2D_ADD_MUL(Xe02,Ye2) ALIAS_PGA2D_SUB_MUL(Xe12,Ye012) ALIAS_PGA2D_SUB_MUL(Xe012,Ye12) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye1) ALIAS_PGA2D_ADD_MUL(Xe1,Yone) ALIAS_PGA2D_SUB_MUL(Xe2,Ye12) ALIAS_PGA2D_ADD_MUL(Xe12,Ye2) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye2) ALIAS_PGA2D_ADD_MUL(Xe1,Ye12) ALIAS_PGA2D_ADD_MUL(Xe2,Yone) ALIAS_PGA2D_SUB_MUL(Xe12,Ye1) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye01) ALIAS_PGA2D_ADD_MUL(Xe2,Ye012) ALIAS_PGA2D_ADD_MUL(Xe01,Yone) ALIAS_PGA2D_ADD_MUL(Xe012,Ye2) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye02) ALIAS_PGA2D_SUB_MUL(Xe1,Ye012) ALIAS_PGA2D_ADD_MUL(Xe02,Yone) ALIAS_PGA2D_SUB_MUL(Xe012,Ye1) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye12) ALIAS_PGA2D_ADD_MUL(Xe12,Yone) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye012) ALIAS_PGA2D_ADD_MUL(Xe012,Yone) \
  , ## __VA_ARGS__)
#define ALIAS_PGA2D_OP_LEFT_DOT_PRODUCT(RETURN, Xone,Xe0,Xe1,Xe2,Xe01,Xe02,Xe12,Xe012, Yone,Ye0,Ye1,Ye2,Ye01,Ye02,Ye12,Ye012, ...) RETURN( \
    0 ALIAS_PGA2D_ADD_MUL(Xone,Yone) ALIAS_PGA2D_ADD_MUL(Xe1,Ye1) ALIAS_PGA2D_ADD_MUL(Xe2,Ye2) ALIAS_PGA2D_SUB_MUL(Xe12,Ye12) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye0) ALIAS_PGA2D_SUB_MUL(Xe1,Ye01) ALIAS_PGA2D_SUB_MUL(Xe2,Ye02) ALIAS_PGA2D_SUB_MUL(Xe12,Ye012) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye1) ALIAS_PGA2D_SUB_MUL(Xe2,Ye12) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye2) ALIAS_PGA2D_ADD_MUL(Xe1,Ye12) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye01) ALIAS_PGA2D_ADD_MUL(Xe2,Ye012) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye02) ALIAS_PGA2D_SUB_MUL(Xe1,Ye012) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye12) \
  , 0 ALIAS_PGA2D_ADD_MUL(Xone,Ye012) \
  , ## __VA_ARGS__)
#define alias_pga2d_m(X) (1,0,1,0,X)
#define alias_pga2d_s(X) (1,0,0,0,_Generic((X), alias_pga2d_Scalar: X, default: ((alias_pga2d_Scalar){ .one = (float)X })))
#define alias_pga2d_v(X) (0,1,0,0,X)
#define alias_pga2d_b(X) (0,0,1,0,X)
#define alias_pga2d_S(X) (0,0,0,1,X)
#define alias_pga2d_grade_0(X) ALIAS_PGA2D_UNARY(ALIAS_PGA2D_OP_GRADE_0, X)
#define alias_pga2d_grade_1(X) ALIAS_PGA2D_UNARY(ALIAS_PGA2D_OP_GRADE_1, X)
#define alias_pga2d_grade_2(X) ALIAS_PGA2D_UNARY(ALIAS_PGA2D_OP_GRADE_2, X)
#define alias_pga2d_grade_3(X) ALIAS_PGA2D_UNARY(ALIAS_PGA2D_OP_GRADE_3, X)
#define alias_pga2d_negate(X) ALIAS_PGA2D_UNARY(ALIAS_PGA2D_OP_NEGATE, X)
#define alias_pga2d_negate_m(X) alias_pga2d_negate(alias_pga2d_m(X))
#define alias_pga2d_negate_s(X) alias_pga2d_negate(alias_pga2d_s(X))
#define alias_pga2d_negate_v(X) alias_pga2d_negate(alias_pga2d_v(X))
#define alias_pga2d_negate_b(X) alias_pga2d_negate(alias_pga2d_b(X))
#define alias_pga2d_negate_S(X) alias_pga2d_negate(alias_pga2d_S(X))
#define alias_pga2d_dual(X) ALIAS_PGA2D_UNARY(ALIAS_PGA2D_OP_DUAL, X)
#define alias_pga2d_dual_m(X) alias_pga2d_dual(alias_pga2d_m(X))
#define alias_pga2d_dual_s(X) alias_pga2d_dual(alias_pga2d_s(X))
#define alias_pga2d_dual_v(X) alias_pga2d_dual(alias_pga2d_v(X))
#define alias_pga2d_dual_b(X) alias_pga2d_dual(alias_pga2d_b(X))
#define alias_pga2d_dual_S(X) alias_pga2d_dual(alias_pga2d_S(X))
#define alias_pga2d_polar(X) ALIAS_PGA2D_UNARY(ALIAS_PGA2D_OP_POLAR, X)
#define alias_pga2d_polar_m(X) alias_pga2d_polar(alias_pga2d_m(X))
#define alias_pga2d_polar_s(X) alias_pga2d_polar(alias_pga2d_s(X))
#define alias_pga2d_polar_v(X) alias_pga2d_polar(alias_pga2d_v(X))
#define alias_pga2d_polar_b(X) alias_pga2d_polar(alias_pga2d_b(X))
#define alias_pga2d_polar_S(X) alias_pga2d_polar(alias_pga2d_S(X))
#define alias_pga2d_reverse(X) ALIAS_PGA2D_UNARY(ALIAS_PGA2D_OP_REVERSE, X)
#define alias_pga2d_reverse_m(X) alias_pga2d_reverse(alias_pga2d_m(X))
#define alias_pga2d_reverse_s(X) alias_pga2d_reverse(alias_pga2d_s(X))
#define alias_pga2d_reverse_v(X) alias_pga2d_reverse(alias_pga2d_v(X))
#define alias_pga2d_reverse_b(X) alias_pga2d_reverse(alias_pga2d_b(X))
#define alias_pga2d_reverse_S(X) alias_pga2d_reverse(alias_pga2d_S(X))
#define alias_pga2d_involute(X) ALIAS_PGA2D_UNARY(ALIAS_PGA2D_OP_INVOLUTE, X)
#define alias_pga2d_involute_m(X) alias_pga2d_involute(alias_pga2d_m(X))
#define alias_pga2d_involute_s(X) alias_pga2d_involute(alias_pga2d_s(X))
#define alias_pga2d_involute_v(X) alias_pga2d_involute(alias_pga2d_v(X))
#define alias_pga2d_involute_b(X) alias_pga2d_involute(alias_pga2d_b(X))
#define alias_pga2d_involute_S(X) alias_pga2d_involute(alias_pga2d_S(X))
#define alias_pga2d_conjugate(X) ALIAS_PGA2D_UNARY(ALIAS_PGA2D_OP_CONJUGATE, X)
#define alias_pga2d_conjugate_m(X) alias_pga2d_conjugate(alias_pga2d_m(X))
#define alias_pga2d_conjugate_s(X) alias_pga2d_conjugate(alias_pga2d_s(X))
#define alias_pga2d_conjugate_v(X) alias_pga2d_conjugate(alias_pga2d_v(X))
#define alias_pga2d_conjugate_b(X) alias_pga2d_conjugate(alias_pga2d_b(X))
#define alias_pga2d_conjugate_S(X) alias_pga2d_conjugate(alias_pga2d_S(X))
#define alias_pga2d_add(X, Y) ALIAS_PGA2D_BINARY(ALIAS_PGA2D_OP_ADD, X, Y)
#define alias_pga2d_add_mm(X, Y) alias_pga2d_add(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_add_ms(X, Y) alias_pga2d_add(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_add_mv(X, Y) alias_pga2d_add(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_add_mb(X, Y) alias_pga2d_add(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_add_mS(X, Y) alias_pga2d_add(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_add_sm(X, Y) alias_pga2d_add(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_add_ss(X, Y) alias_pga2d_add(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_add_sv(X, Y) alias_pga2d_add(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_add_sb(X, Y) alias_pga2d_add(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_add_sS(X, Y) alias_pga2d_add(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_add_vm(X, Y) alias_pga2d_add(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_add_vs(X, Y) alias_pga2d_add(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_add_vv(X, Y) alias_pga2d_add(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_add_vb(X, Y) alias_pga2d_add(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_add_vS(X, Y) alias_pga2d_add(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_add_bm(X, Y) alias_pga2d_add(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_add_bs(X, Y) alias_pga2d_add(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_add_bv(X, Y) alias_pga2d_add(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_add_bb(X, Y) alias_pga2d_add(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_add_bS(X, Y) alias_pga2d_add(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_add_Sm(X, Y) alias_pga2d_add(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_add_Ss(X, Y) alias_pga2d_add(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_add_Sv(X, Y) alias_pga2d_add(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_add_Sb(X, Y) alias_pga2d_add(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_add_SS(X, Y) alias_pga2d_add(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_subtract(X, Y) ALIAS_PGA2D_BINARY(ALIAS_PGA2D_OP_SUBTRACT, X, Y)
#define alias_pga2d_subtract_mm(X, Y) alias_pga2d_subtract(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_subtract_ms(X, Y) alias_pga2d_subtract(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_subtract_mv(X, Y) alias_pga2d_subtract(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_subtract_mb(X, Y) alias_pga2d_subtract(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_subtract_mS(X, Y) alias_pga2d_subtract(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_subtract_sm(X, Y) alias_pga2d_subtract(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_subtract_ss(X, Y) alias_pga2d_subtract(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_subtract_sv(X, Y) alias_pga2d_subtract(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_subtract_sb(X, Y) alias_pga2d_subtract(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_subtract_sS(X, Y) alias_pga2d_subtract(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_subtract_vm(X, Y) alias_pga2d_subtract(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_subtract_vs(X, Y) alias_pga2d_subtract(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_subtract_vv(X, Y) alias_pga2d_subtract(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_subtract_vb(X, Y) alias_pga2d_subtract(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_subtract_vS(X, Y) alias_pga2d_subtract(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_subtract_bm(X, Y) alias_pga2d_subtract(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_subtract_bs(X, Y) alias_pga2d_subtract(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_subtract_bv(X, Y) alias_pga2d_subtract(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_subtract_bb(X, Y) alias_pga2d_subtract(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_subtract_bS(X, Y) alias_pga2d_subtract(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_subtract_Sm(X, Y) alias_pga2d_subtract(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_subtract_Ss(X, Y) alias_pga2d_subtract(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_subtract_Sv(X, Y) alias_pga2d_subtract(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_subtract_Sb(X, Y) alias_pga2d_subtract(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_subtract_SS(X, Y) alias_pga2d_subtract(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_geometric_product(X, Y) ALIAS_PGA2D_BINARY(ALIAS_PGA2D_OP_GEOMETRIC_PRODUCT, X, Y)
#define alias_pga2d_geometric_product_mm(X, Y) alias_pga2d_geometric_product(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_geometric_product_ms(X, Y) alias_pga2d_geometric_product(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_geometric_product_mv(X, Y) alias_pga2d_geometric_product(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_geometric_product_mb(X, Y) alias_pga2d_geometric_product(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_geometric_product_mS(X, Y) alias_pga2d_geometric_product(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_geometric_product_sm(X, Y) alias_pga2d_geometric_product(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_geometric_product_ss(X, Y) alias_pga2d_geometric_product(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_geometric_product_sv(X, Y) alias_pga2d_geometric_product(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_geometric_product_sb(X, Y) alias_pga2d_geometric_product(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_geometric_product_sS(X, Y) alias_pga2d_geometric_product(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_geometric_product_vm(X, Y) alias_pga2d_geometric_product(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_geometric_product_vs(X, Y) alias_pga2d_geometric_product(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_geometric_product_vv(X, Y) alias_pga2d_geometric_product(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_geometric_product_vb(X, Y) alias_pga2d_geometric_product(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_geometric_product_vS(X, Y) alias_pga2d_geometric_product(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_geometric_product_bm(X, Y) alias_pga2d_geometric_product(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_geometric_product_bs(X, Y) alias_pga2d_geometric_product(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_geometric_product_bv(X, Y) alias_pga2d_geometric_product(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_geometric_product_bb(X, Y) alias_pga2d_geometric_product(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_geometric_product_bS(X, Y) alias_pga2d_geometric_product(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_geometric_product_Sm(X, Y) alias_pga2d_geometric_product(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_geometric_product_Ss(X, Y) alias_pga2d_geometric_product(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_geometric_product_Sv(X, Y) alias_pga2d_geometric_product(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_geometric_product_Sb(X, Y) alias_pga2d_geometric_product(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_geometric_product_SS(X, Y) alias_pga2d_geometric_product(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_outer_product(X, Y) ALIAS_PGA2D_BINARY(ALIAS_PGA2D_OP_OUTER_PRODUCT, X, Y)
#define alias_pga2d_outer_product_mm(X, Y) alias_pga2d_outer_product(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_outer_product_ms(X, Y) alias_pga2d_outer_product(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_outer_product_mv(X, Y) alias_pga2d_outer_product(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_outer_product_mb(X, Y) alias_pga2d_outer_product(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_outer_product_mS(X, Y) alias_pga2d_outer_product(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_outer_product_sm(X, Y) alias_pga2d_outer_product(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_outer_product_ss(X, Y) alias_pga2d_outer_product(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_outer_product_sv(X, Y) alias_pga2d_outer_product(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_outer_product_sb(X, Y) alias_pga2d_outer_product(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_outer_product_sS(X, Y) alias_pga2d_outer_product(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_outer_product_vm(X, Y) alias_pga2d_outer_product(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_outer_product_vs(X, Y) alias_pga2d_outer_product(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_outer_product_vv(X, Y) alias_pga2d_outer_product(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_outer_product_vb(X, Y) alias_pga2d_outer_product(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_outer_product_vS(X, Y) alias_pga2d_outer_product(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_outer_product_bm(X, Y) alias_pga2d_outer_product(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_outer_product_bs(X, Y) alias_pga2d_outer_product(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_outer_product_bv(X, Y) alias_pga2d_outer_product(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_outer_product_bb(X, Y) alias_pga2d_outer_product(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_outer_product_bS(X, Y) alias_pga2d_outer_product(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_outer_product_Sm(X, Y) alias_pga2d_outer_product(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_outer_product_Ss(X, Y) alias_pga2d_outer_product(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_outer_product_Sv(X, Y) alias_pga2d_outer_product(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_outer_product_Sb(X, Y) alias_pga2d_outer_product(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_outer_product_SS(X, Y) alias_pga2d_outer_product(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_regressive_product(X, Y) ALIAS_PGA2D_BINARY(ALIAS_PGA2D_OP_REGRESSIVE_PRODUCT, X, Y)
#define alias_pga2d_regressive_product_mm(X, Y) alias_pga2d_regressive_product(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_regressive_product_ms(X, Y) alias_pga2d_regressive_product(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_regressive_product_mv(X, Y) alias_pga2d_regressive_product(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_regressive_product_mb(X, Y) alias_pga2d_regressive_product(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_regressive_product_mS(X, Y) alias_pga2d_regressive_product(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_regressive_product_sm(X, Y) alias_pga2d_regressive_product(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_regressive_product_ss(X, Y) alias_pga2d_regressive_product(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_regressive_product_sv(X, Y) alias_pga2d_regressive_product(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_regressive_product_sb(X, Y) alias_pga2d_regressive_product(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_regressive_product_sS(X, Y) alias_pga2d_regressive_product(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_regressive_product_vm(X, Y) alias_pga2d_regressive_product(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_regressive_product_vs(X, Y) alias_pga2d_regressive_product(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_regressive_product_vv(X, Y) alias_pga2d_regressive_product(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_regressive_product_vb(X, Y) alias_pga2d_regressive_product(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_regressive_product_vS(X, Y) alias_pga2d_regressive_product(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_regressive_product_bm(X, Y) alias_pga2d_regressive_product(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_regressive_product_bs(X, Y) alias_pga2d_regressive_product(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_regressive_product_bv(X, Y) alias_pga2d_regressive_product(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_regressive_product_bb(X, Y) alias_pga2d_regressive_product(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_regressive_product_bS(X, Y) alias_pga2d_regressive_product(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_regressive_product_Sm(X, Y) alias_pga2d_regressive_product(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_regressive_product_Ss(X, Y) alias_pga2d_regressive_product(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_regressive_product_Sv(X, Y) alias_pga2d_regressive_product(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_regressive_product_Sb(X, Y) alias_pga2d_regressive_product(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_regressive_product_SS(X, Y) alias_pga2d_regressive_product(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_commutator_product(X, Y) ALIAS_PGA2D_BINARY(ALIAS_PGA2D_OP_COMMUTATOR_PRODUCT, X, Y)
#define alias_pga2d_commutator_product_mm(X, Y) alias_pga2d_commutator_product(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_commutator_product_ms(X, Y) alias_pga2d_commutator_product(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_commutator_product_mv(X, Y) alias_pga2d_commutator_product(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_commutator_product_mb(X, Y) alias_pga2d_commutator_product(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_commutator_product_mS(X, Y) alias_pga2d_commutator_product(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_commutator_product_sm(X, Y) alias_pga2d_commutator_product(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_commutator_product_ss(X, Y) alias_pga2d_commutator_product(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_commutator_product_sv(X, Y) alias_pga2d_commutator_product(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_commutator_product_sb(X, Y) alias_pga2d_commutator_product(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_commutator_product_sS(X, Y) alias_pga2d_commutator_product(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_commutator_product_vm(X, Y) alias_pga2d_commutator_product(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_commutator_product_vs(X, Y) alias_pga2d_commutator_product(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_commutator_product_vv(X, Y) alias_pga2d_commutator_product(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_commutator_product_vb(X, Y) alias_pga2d_commutator_product(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_commutator_product_vS(X, Y) alias_pga2d_commutator_product(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_commutator_product_bm(X, Y) alias_pga2d_commutator_product(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_commutator_product_bs(X, Y) alias_pga2d_commutator_product(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_commutator_product_bv(X, Y) alias_pga2d_commutator_product(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_commutator_product_bb(X, Y) alias_pga2d_commutator_product(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_commutator_product_bS(X, Y) alias_pga2d_commutator_product(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_commutator_product_Sm(X, Y) alias_pga2d_commutator_product(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_commutator_product_Ss(X, Y) alias_pga2d_commutator_product(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_commutator_product_Sv(X, Y) alias_pga2d_commutator_product(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_commutator_product_Sb(X, Y) alias_pga2d_commutator_product(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_commutator_product_SS(X, Y) alias_pga2d_commutator_product(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_inner_product(X, Y) ALIAS_PGA2D_BINARY(ALIAS_PGA2D_OP_INNER_PRODUCT, X, Y)
#define alias_pga2d_inner_product_mm(X, Y) alias_pga2d_inner_product(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_inner_product_ms(X, Y) alias_pga2d_inner_product(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_inner_product_mv(X, Y) alias_pga2d_inner_product(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_inner_product_mb(X, Y) alias_pga2d_inner_product(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_inner_product_mS(X, Y) alias_pga2d_inner_product(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_inner_product_sm(X, Y) alias_pga2d_inner_product(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_inner_product_ss(X, Y) alias_pga2d_inner_product(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_inner_product_sv(X, Y) alias_pga2d_inner_product(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_inner_product_sb(X, Y) alias_pga2d_inner_product(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_inner_product_sS(X, Y) alias_pga2d_inner_product(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_inner_product_vm(X, Y) alias_pga2d_inner_product(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_inner_product_vs(X, Y) alias_pga2d_inner_product(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_inner_product_vv(X, Y) alias_pga2d_inner_product(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_inner_product_vb(X, Y) alias_pga2d_inner_product(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_inner_product_vS(X, Y) alias_pga2d_inner_product(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_inner_product_bm(X, Y) alias_pga2d_inner_product(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_inner_product_bs(X, Y) alias_pga2d_inner_product(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_inner_product_bv(X, Y) alias_pga2d_inner_product(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_inner_product_bb(X, Y) alias_pga2d_inner_product(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_inner_product_bS(X, Y) alias_pga2d_inner_product(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_inner_product_Sm(X, Y) alias_pga2d_inner_product(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_inner_product_Ss(X, Y) alias_pga2d_inner_product(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_inner_product_Sv(X, Y) alias_pga2d_inner_product(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_inner_product_Sb(X, Y) alias_pga2d_inner_product(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_inner_product_SS(X, Y) alias_pga2d_inner_product(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_left_dot_product(X, Y) ALIAS_PGA2D_BINARY(ALIAS_PGA2D_OP_LEFT_DOT_PRODUCT, X, Y)
#define alias_pga2d_left_dot_product_mm(X, Y) alias_pga2d_left_dot_product(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_left_dot_product_ms(X, Y) alias_pga2d_left_dot_product(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_left_dot_product_mv(X, Y) alias_pga2d_left_dot_product(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_left_dot_product_mb(X, Y) alias_pga2d_left_dot_product(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_left_dot_product_mS(X, Y) alias_pga2d_left_dot_product(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_left_dot_product_sm(X, Y) alias_pga2d_left_dot_product(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_left_dot_product_ss(X, Y) alias_pga2d_left_dot_product(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_left_dot_product_sv(X, Y) alias_pga2d_left_dot_product(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_left_dot_product_sb(X, Y) alias_pga2d_left_dot_product(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_left_dot_product_sS(X, Y) alias_pga2d_left_dot_product(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_left_dot_product_vm(X, Y) alias_pga2d_left_dot_product(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_left_dot_product_vs(X, Y) alias_pga2d_left_dot_product(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_left_dot_product_vv(X, Y) alias_pga2d_left_dot_product(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_left_dot_product_vb(X, Y) alias_pga2d_left_dot_product(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_left_dot_product_vS(X, Y) alias_pga2d_left_dot_product(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_left_dot_product_bm(X, Y) alias_pga2d_left_dot_product(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_left_dot_product_bs(X, Y) alias_pga2d_left_dot_product(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_left_dot_product_bv(X, Y) alias_pga2d_left_dot_product(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_left_dot_product_bb(X, Y) alias_pga2d_left_dot_product(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_left_dot_product_bS(X, Y) alias_pga2d_left_dot_product(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_left_dot_product_Sm(X, Y) alias_pga2d_left_dot_product(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_left_dot_product_Ss(X, Y) alias_pga2d_left_dot_product(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_left_dot_product_Sv(X, Y) alias_pga2d_left_dot_product(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_left_dot_product_Sb(X, Y) alias_pga2d_left_dot_product(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_left_dot_product_SS(X, Y) alias_pga2d_left_dot_product(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_meet(X, Y) alias_pga2d_outer_product(X, Y)
#define alias_pga2d_meet_mm(X, Y) alias_pga2d_meet(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_meet_ms(X, Y) alias_pga2d_meet(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_meet_mv(X, Y) alias_pga2d_meet(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_meet_mb(X, Y) alias_pga2d_meet(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_meet_mS(X, Y) alias_pga2d_meet(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_meet_sm(X, Y) alias_pga2d_meet(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_meet_ss(X, Y) alias_pga2d_meet(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_meet_sv(X, Y) alias_pga2d_meet(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_meet_sb(X, Y) alias_pga2d_meet(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_meet_sS(X, Y) alias_pga2d_meet(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_meet_vm(X, Y) alias_pga2d_meet(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_meet_vs(X, Y) alias_pga2d_meet(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_meet_vv(X, Y) alias_pga2d_meet(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_meet_vb(X, Y) alias_pga2d_meet(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_meet_vS(X, Y) alias_pga2d_meet(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_meet_bm(X, Y) alias_pga2d_meet(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_meet_bs(X, Y) alias_pga2d_meet(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_meet_bv(X, Y) alias_pga2d_meet(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_meet_bb(X, Y) alias_pga2d_meet(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_meet_bS(X, Y) alias_pga2d_meet(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_meet_Sm(X, Y) alias_pga2d_meet(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_meet_Ss(X, Y) alias_pga2d_meet(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_meet_Sv(X, Y) alias_pga2d_meet(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_meet_Sb(X, Y) alias_pga2d_meet(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_meet_SS(X, Y) alias_pga2d_meet(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_join(X, Y) alias_pga2d_regressive_product(X, Y)
#define alias_pga2d_join_mm(X, Y) alias_pga2d_join(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_join_ms(X, Y) alias_pga2d_join(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_join_mv(X, Y) alias_pga2d_join(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_join_mb(X, Y) alias_pga2d_join(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_join_mS(X, Y) alias_pga2d_join(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_join_sm(X, Y) alias_pga2d_join(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_join_ss(X, Y) alias_pga2d_join(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_join_sv(X, Y) alias_pga2d_join(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_join_sb(X, Y) alias_pga2d_join(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_join_sS(X, Y) alias_pga2d_join(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_join_vm(X, Y) alias_pga2d_join(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_join_vs(X, Y) alias_pga2d_join(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_join_vv(X, Y) alias_pga2d_join(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_join_vb(X, Y) alias_pga2d_join(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_join_vS(X, Y) alias_pga2d_join(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_join_bm(X, Y) alias_pga2d_join(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_join_bs(X, Y) alias_pga2d_join(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_join_bv(X, Y) alias_pga2d_join(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_join_bb(X, Y) alias_pga2d_join(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_join_bS(X, Y) alias_pga2d_join(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_join_Sm(X, Y) alias_pga2d_join(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_join_Ss(X, Y) alias_pga2d_join(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_join_Sv(X, Y) alias_pga2d_join(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_join_Sb(X, Y) alias_pga2d_join(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_join_SS(X, Y) alias_pga2d_join(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_neg(X) alias_pga2d_negate(X)
#define alias_pga2d_neg_m(X) alias_pga2d_neg(alias_pga2d_m(X))
#define alias_pga2d_neg_s(X) alias_pga2d_neg(alias_pga2d_s(X))
#define alias_pga2d_neg_v(X) alias_pga2d_neg(alias_pga2d_v(X))
#define alias_pga2d_neg_b(X) alias_pga2d_neg(alias_pga2d_b(X))
#define alias_pga2d_neg_S(X) alias_pga2d_neg(alias_pga2d_S(X))
#define alias_pga2d_sub(X, Y) alias_pga2d_subtract(X, Y)
#define alias_pga2d_sub_mm(X, Y) alias_pga2d_sub(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_sub_ms(X, Y) alias_pga2d_sub(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_sub_mv(X, Y) alias_pga2d_sub(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_sub_mb(X, Y) alias_pga2d_sub(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_sub_mS(X, Y) alias_pga2d_sub(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_sub_sm(X, Y) alias_pga2d_sub(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_sub_ss(X, Y) alias_pga2d_sub(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_sub_sv(X, Y) alias_pga2d_sub(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_sub_sb(X, Y) alias_pga2d_sub(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_sub_sS(X, Y) alias_pga2d_sub(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_sub_vm(X, Y) alias_pga2d_sub(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_sub_vs(X, Y) alias_pga2d_sub(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_sub_vv(X, Y) alias_pga2d_sub(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_sub_vb(X, Y) alias_pga2d_sub(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_sub_vS(X, Y) alias_pga2d_sub(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_sub_bm(X, Y) alias_pga2d_sub(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_sub_bs(X, Y) alias_pga2d_sub(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_sub_bv(X, Y) alias_pga2d_sub(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_sub_bb(X, Y) alias_pga2d_sub(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_sub_bS(X, Y) alias_pga2d_sub(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_sub_Sm(X, Y) alias_pga2d_sub(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_sub_Ss(X, Y) alias_pga2d_sub(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_sub_Sv(X, Y) alias_pga2d_sub(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_sub_Sb(X, Y) alias_pga2d_sub(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_sub_SS(X, Y) alias_pga2d_sub(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_mul(X, Y) alias_pga2d_geometric_product(X, Y)
#define alias_pga2d_mul_mm(X, Y) alias_pga2d_mul(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_mul_ms(X, Y) alias_pga2d_mul(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_mul_mv(X, Y) alias_pga2d_mul(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_mul_mb(X, Y) alias_pga2d_mul(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_mul_mS(X, Y) alias_pga2d_mul(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_mul_sm(X, Y) alias_pga2d_mul(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_mul_ss(X, Y) alias_pga2d_mul(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_mul_sv(X, Y) alias_pga2d_mul(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_mul_sb(X, Y) alias_pga2d_mul(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_mul_sS(X, Y) alias_pga2d_mul(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_mul_vm(X, Y) alias_pga2d_mul(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_mul_vs(X, Y) alias_pga2d_mul(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_mul_vv(X, Y) alias_pga2d_mul(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_mul_vb(X, Y) alias_pga2d_mul(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_mul_vS(X, Y) alias_pga2d_mul(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_mul_bm(X, Y) alias_pga2d_mul(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_mul_bs(X, Y) alias_pga2d_mul(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_mul_bv(X, Y) alias_pga2d_mul(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_mul_bb(X, Y) alias_pga2d_mul(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_mul_bS(X, Y) alias_pga2d_mul(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_mul_Sm(X, Y) alias_pga2d_mul(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_mul_Ss(X, Y) alias_pga2d_mul(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_mul_Sv(X, Y) alias_pga2d_mul(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_mul_Sb(X, Y) alias_pga2d_mul(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_mul_SS(X, Y) alias_pga2d_mul(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_weg(X, Y) alias_pga2d_outer_product(X, Y)
#define alias_pga2d_weg_mm(X, Y) alias_pga2d_weg(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_weg_ms(X, Y) alias_pga2d_weg(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_weg_mv(X, Y) alias_pga2d_weg(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_weg_mb(X, Y) alias_pga2d_weg(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_weg_mS(X, Y) alias_pga2d_weg(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_weg_sm(X, Y) alias_pga2d_weg(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_weg_ss(X, Y) alias_pga2d_weg(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_weg_sv(X, Y) alias_pga2d_weg(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_weg_sb(X, Y) alias_pga2d_weg(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_weg_sS(X, Y) alias_pga2d_weg(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_weg_vm(X, Y) alias_pga2d_weg(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_weg_vs(X, Y) alias_pga2d_weg(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_weg_vv(X, Y) alias_pga2d_weg(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_weg_vb(X, Y) alias_pga2d_weg(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_weg_vS(X, Y) alias_pga2d_weg(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_weg_bm(X, Y) alias_pga2d_weg(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_weg_bs(X, Y) alias_pga2d_weg(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_weg_bv(X, Y) alias_pga2d_weg(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_weg_bb(X, Y) alias_pga2d_weg(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_weg_bS(X, Y) alias_pga2d_weg(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_weg_Sm(X, Y) alias_pga2d_weg(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_weg_Ss(X, Y) alias_pga2d_weg(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_weg_Sv(X, Y) alias_pga2d_weg(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_weg_Sb(X, Y) alias_pga2d_weg(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_weg_SS(X, Y) alias_pga2d_weg(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_vee(X, Y) alias_pga2d_regressive_product(X, Y)
#define alias_pga2d_vee_mm(X, Y) alias_pga2d_vee(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_vee_ms(X, Y) alias_pga2d_vee(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_vee_mv(X, Y) alias_pga2d_vee(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_vee_mb(X, Y) alias_pga2d_vee(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_vee_mS(X, Y) alias_pga2d_vee(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_vee_sm(X, Y) alias_pga2d_vee(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_vee_ss(X, Y) alias_pga2d_vee(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_vee_sv(X, Y) alias_pga2d_vee(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_vee_sb(X, Y) alias_pga2d_vee(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_vee_sS(X, Y) alias_pga2d_vee(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_vee_vm(X, Y) alias_pga2d_vee(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_vee_vs(X, Y) alias_pga2d_vee(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_vee_vv(X, Y) alias_pga2d_vee(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_vee_vb(X, Y) alias_pga2d_vee(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_vee_vS(X, Y) alias_pga2d_vee(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_vee_bm(X, Y) alias_pga2d_vee(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_vee_bs(X, Y) alias_pga2d_vee(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_vee_bv(X, Y) alias_pga2d_vee(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_vee_bb(X, Y) alias_pga2d_vee(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_vee_bS(X, Y) alias_pga2d_vee(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_vee_Sm(X, Y) alias_pga2d_vee(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_vee_Ss(X, Y) alias_pga2d_vee(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_vee_Sv(X, Y) alias_pga2d_vee(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_vee_Sb(X, Y) alias_pga2d_vee(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_vee_SS(X, Y) alias_pga2d_vee(alias_pga2d_S(X), alias_pga2d_S(Y))
#define alias_pga2d_dot(X, Y) alias_pga2d_inner_product(X, Y)
#define alias_pga2d_dot_mm(X, Y) alias_pga2d_dot(alias_pga2d_m(X), alias_pga2d_m(Y))
#define alias_pga2d_dot_ms(X, Y) alias_pga2d_dot(alias_pga2d_m(X), alias_pga2d_s(Y))
#define alias_pga2d_dot_mv(X, Y) alias_pga2d_dot(alias_pga2d_m(X), alias_pga2d_v(Y))
#define alias_pga2d_dot_mb(X, Y) alias_pga2d_dot(alias_pga2d_m(X), alias_pga2d_b(Y))
#define alias_pga2d_dot_mS(X, Y) alias_pga2d_dot(alias_pga2d_m(X), alias_pga2d_S(Y))
#define alias_pga2d_dot_sm(X, Y) alias_pga2d_dot(alias_pga2d_s(X), alias_pga2d_m(Y))
#define alias_pga2d_dot_ss(X, Y) alias_pga2d_dot(alias_pga2d_s(X), alias_pga2d_s(Y))
#define alias_pga2d_dot_sv(X, Y) alias_pga2d_dot(alias_pga2d_s(X), alias_pga2d_v(Y))
#define alias_pga2d_dot_sb(X, Y) alias_pga2d_dot(alias_pga2d_s(X), alias_pga2d_b(Y))
#define alias_pga2d_dot_sS(X, Y) alias_pga2d_dot(alias_pga2d_s(X), alias_pga2d_S(Y))
#define alias_pga2d_dot_vm(X, Y) alias_pga2d_dot(alias_pga2d_v(X), alias_pga2d_m(Y))
#define alias_pga2d_dot_vs(X, Y) alias_pga2d_dot(alias_pga2d_v(X), alias_pga2d_s(Y))
#define alias_pga2d_dot_vv(X, Y) alias_pga2d_dot(alias_pga2d_v(X), alias_pga2d_v(Y))
#define alias_pga2d_dot_vb(X, Y) alias_pga2d_dot(alias_pga2d_v(X), alias_pga2d_b(Y))
#define alias_pga2d_dot_vS(X, Y) alias_pga2d_dot(alias_pga2d_v(X), alias_pga2d_S(Y))
#define alias_pga2d_dot_bm(X, Y) alias_pga2d_dot(alias_pga2d_b(X), alias_pga2d_m(Y))
#define alias_pga2d_dot_bs(X, Y) alias_pga2d_dot(alias_pga2d_b(X), alias_pga2d_s(Y))
#define alias_pga2d_dot_bv(X, Y) alias_pga2d_dot(alias_pga2d_b(X), alias_pga2d_v(Y))
#define alias_pga2d_dot_bb(X, Y) alias_pga2d_dot(alias_pga2d_b(X), alias_pga2d_b(Y))
#define alias_pga2d_dot_bS(X, Y) alias_pga2d_dot(alias_pga2d_b(X), alias_pga2d_S(Y))
#define alias_pga2d_dot_Sm(X, Y) alias_pga2d_dot(alias_pga2d_S(X), alias_pga2d_m(Y))
#define alias_pga2d_dot_Ss(X, Y) alias_pga2d_dot(alias_pga2d_S(X), alias_pga2d_s(Y))
#define alias_pga2d_dot_Sv(X, Y) alias_pga2d_dot(alias_pga2d_S(X), alias_pga2d_v(Y))
#define alias_pga2d_dot_Sb(X, Y) alias_pga2d_dot(alias_pga2d_S(X), alias_pga2d_b(Y))
#define alias_pga2d_dot_SS(X, Y) alias_pga2d_dot(alias_pga2d_S(X), alias_pga2d_S(Y))
#endif // _ALIAS_PGA2D_H_
