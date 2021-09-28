#ifndef _ALIAS_PGA_BINARY_H_
#define _ALIAS_PGA_BINARY_H_

#include <alias/pga/bits.h>
#include <alias/pga/types.h>

// to elsewhere
#define ALIAS_PGA_EXPORT(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, A,B,C,D,E) \
  _first: 0 \
  ALIAS_CPP_IF1(A)(, one: a)() \
  ALIAS_CPP_IF1(B)(, e0: b)() \
  ALIAS_CPP_IF1(B)(, e1: c)() \
  ALIAS_CPP_IF1(B)(, e2: d)() \
  ALIAS_CPP_IF1(B)(, e3: e)() \
  ALIAS_CPP_IF1(C)(, e01: f)() \
  ALIAS_CPP_IF1(C)(, e02: g)() \
  ALIAS_CPP_IF1(C)(, e03: h)() \
  ALIAS_CPP_IF1(C)(, e12: i)() \
  ALIAS_CPP_IF1(C)(, e31: j)() \
  ALIAS_CPP_IF1(C)(, e23: k)() \
  ALIAS_CPP_IF1(D)(, e021: l)() \
  ALIAS_CPP_IF1(D)(, e013: m)() \
  ALIAS_CPP_IF1(D)(, e032: n)() \
  ALIAS_CPP_IF1(D)(, e123: o)() \
  ALIAS_CPP_IF1(E)(, e0123: p)() \

#define ALIAS_PGA_BINARY_IMPORT(RETURN, Xa,Xb,Xc,Xd,Xe, Ya,Yb,Yc,Yd,Ye, ...) \
  RETURN( \
      ALIAS_CPP_IF1(Xa)(x.one)(0) \
    , ALIAS_CPP_IF1(Xb)(x.e0)(0) \
    , ALIAS_CPP_IF1(Xb)(x.e1)(0) \
    , ALIAS_CPP_IF1(Xb)(x.e2)(0) \
    , ALIAS_CPP_IF1(Xb)(x.e3)(0) \
    , ALIAS_CPP_IF1(Xc)(x.e01)(0) \
    , ALIAS_CPP_IF1(Xc)(x.e02)(0) \
    , ALIAS_CPP_IF1(Xc)(x.e03)(0) \
    , ALIAS_CPP_IF1(Xc)(x.e12)(0) \
    , ALIAS_CPP_IF1(Xc)(x.e31)(0) \
    , ALIAS_CPP_IF1(Xc)(x.e23)(0) \
    , ALIAS_CPP_IF1(Xd)(x.e021)(0) \
    , ALIAS_CPP_IF1(Xd)(x.e013)(0) \
    , ALIAS_CPP_IF1(Xd)(x.e032)(0) \
    , ALIAS_CPP_IF1(Xd)(x.e123)(0) \
    , ALIAS_CPP_IF1(Xe)(x.e0123)(0) \
    , ALIAS_CPP_IF1(Ya)(y.one)(0) \
    , ALIAS_CPP_IF1(Yb)(y.e0)(0) \
    , ALIAS_CPP_IF1(Yb)(y.e1)(0) \
    , ALIAS_CPP_IF1(Yb)(y.e2)(0) \
    , ALIAS_CPP_IF1(Yb)(y.e3)(0) \
    , ALIAS_CPP_IF1(Yc)(y.e01)(0) \
    , ALIAS_CPP_IF1(Yc)(y.e02)(0) \
    , ALIAS_CPP_IF1(Yc)(y.e03)(0) \
    , ALIAS_CPP_IF1(Yc)(y.e12)(0) \
    , ALIAS_CPP_IF1(Yc)(y.e31)(0) \
    , ALIAS_CPP_IF1(Yc)(y.e23)(0) \
    , ALIAS_CPP_IF1(Yd)(y.e021)(0) \
    , ALIAS_CPP_IF1(Yd)(y.e013)(0) \
    , ALIAS_CPP_IF1(Yd)(y.e032)(0) \
    , ALIAS_CPP_IF1(Yd)(y.e123)(0) \
    , ALIAS_CPP_IF1(Ye)(y.e0123)(0) \
    , ## __VA_ARGS__ \
    )

#define ALIAS_PGA_BINARY_IMPORT_OP(RETURN, OP, Xa,Xb,Xc,Xd,Xe, Ya,Yb,Yc,Yd,Ye, ...) ALIAS_PGA_BINARY_IMPORT(ALIAS_PGA_BINARY_IMPORT_OP_1, Xa,Xb,Xc,Xd,Xe, Ya,Yb,Yc,Yd,Ye, RETURN,OP,##__VA_ARGS__)
#define ALIAS_PGA_BINARY_IMPORT_OP_1(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, RETURN,OP,...) OP(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ##__VA_ARGS__)

#define ALIAS_PGA_BINARY_NAME(op, A,B,C,D,E, a,b,c,d,e) alias_pga__##op##_##A##B##C##D##E##_##a##b##c##d##e

#define ALIAS_PGA_USE_BINARY(op, X, Y) _Generic((X) ALIAS_PGA_BITS_1(ALIAS_PGA_USE_BINARY_1, op, X))(X, Y)
#define ALIAS_PGA_USE_BINARY_1(A,B,C,D,E, op, X) , ALIAS_PGA_TYPENAME_FROM_BITS(A,B,C,D,E): _Generic((Y) ALIAS_PGA_BITS_2(ALIAS_PGA_USE_BINARY_2, A,B,C,D,E, op))
#define ALIAS_PGA_USE_BINARY_2(a,b,c,d,e, A,B,C,D,E, op) , ALIAS_PGA_TYPENAME_FROM_BITS(a,b,c,d,e): ALIAS_PGA_BINARY_NAME(op, A,B,C,D,E, a,b,c,d,e)

#define ALIAS_PGA_GENERATE_BINARY(OP, op, GEN) ALIAS_PGA_BITS_1(ALIAS_PGA_GENERATE_BINARY_1, GEN,OP,op)
#define ALIAS_PGA_GENERATE_BINARY_1(Xa,Xb,Xc,Xd,Xe, GEN,OP,op) ALIAS_PGA_BITS_2(ALIAS_PGA_GENERATE_BINARY_2, GEN,OP,op,Xa,Xb,Xc,Xd,Xe)
#define ALIAS_PGA_GENERATE_BINARY_2(Ya,Yb,Yc,Yd,Ye, GEN,OP,op,Xa,Xb,Xc,Xd,Xe) ALIAS_PGA_BINARY_IMPORT_OP(ALIAS_PGA_GENERATE_BINARY_3, OP, Xa,Xb,Xc,Xd,Xe, Ya,Yb,Yc,Yd,Ye, GEN,op,Xa,Xb,Xc,Xd,Xe,Ya,Yb,Yc,Yd,Ye)
#define ALIAS_PGA_GENERATE_BINARY_3(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, GEN,op,Xa,Xb,Xc,Xd,Xe,Ya,Yb,Yc,Yd,Ye) ALIAS_PGA_GRADE(ALIAS_PGA_GENERATE_BINARY_4, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, GEN,op,Xa,Xb,Xc,Xd,Xe,Ya,Yb,Yc,Yd,Ye,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define ALIAS_PGA_GENERATE_BINARY_4(Za,Zb,Zc,Zd,Ze, GEN,op,Xa,Xb,Xc,Xd,Xe,Ya,Yb,Yc,Yd,Ye,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) GEN(op, Xa,Xb,Xc,Xd,Xe, Ya,Yb,Yc,Yd,Ye, Za,Zb,Zc,Zd,Ze, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)

#endif

