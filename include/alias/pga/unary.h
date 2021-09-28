#ifndef _ALIAS_PGA_UNARY_H_
#define _ALIAS_PGA_UNARY_H_

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

#define ALIAS_PGA_UNARY_IMPORT(RETURN, Xa,Xb,Xc,Xd,Xe, ...) \
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
    , ## __VA_ARGS__ \
    )

#define ALIAS_PGA_UNARY_IMPORT_OP(RETURN, OP, Xa,Xb,Xc,Xd,Xe, ...) ALIAS_PGA_UNARY_IMPORT(ALIAS_PGA_UNARY_IMPORT_OP_1, Xa,Xb,Xc,Xd,Xe, RETURN,OP,##__VA_ARGS__)
#define ALIAS_PGA_UNARY_IMPORT_OP_1(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, RETURN,OP,...) OP(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ##__VA_ARGS__)

#define ALIAS_PGA_UNARY_NAME(op, A,B,C,D,E) alias_pga__##op##_##A##B##C##D##E

#define ALIAS_PGA_GENERATE_UNARY(OP, op, GEN) ALIAS_PGA_BITS_1(ALIAS_PGA_GENERATE_UNARY_1, GEN,OP,op)
#define ALIAS_PGA_GENERATE_UNARY_1(Xa,Xb,Xc,Xd,Xe, GEN,OP,op) ALIAS_PGA_UNARY_IMPORT_OP(ALIAS_PGA_GENERATE_UNARY_2, OP, Xa,Xb,Xc,Xd,Xe, GEN,op,Xa,Xb,Xc,Xd,Xe)
#define ALIAS_PGA_GENERATE_UNARY_2(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, GEN,op,Xa,Xb,Xc,Xd,Xe) ALIAS_PGA_GRADE(ALIAS_PGA_GENERATE_UNARY_3, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, GEN,op,Xa,Xb,Xc,Xd,Xe,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define ALIAS_PGA_GENERATE_UNARY_3(Za,Zb,Zc,Zd,Ze, GEN,op,Xa,Xb,Xc,Xd,Xe,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) GEN(op, Xa,Xb,Xc,Xd,Xe, Za,Zb,Zc,Zd,Ze, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)

#endif

