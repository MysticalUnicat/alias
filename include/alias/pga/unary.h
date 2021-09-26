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

#define ALIAS_PGA_UNARY_IMPORT(RETURN, X,Xa,Xb,Xc,Xd,Xe, ...) \
  RETURN( \
      ALIAS_CPP_IF1(Xa)(X.one)(0) \
    , ALIAS_CPP_IF1(Xb)(X.e0)(0) \
    , ALIAS_CPP_IF1(Xb)(X.e1)(0) \
    , ALIAS_CPP_IF1(Xb)(X.e2)(0) \
    , ALIAS_CPP_IF1(Xb)(X.e3)(0) \
    , ALIAS_CPP_IF1(Xc)(X.e01)(0) \
    , ALIAS_CPP_IF1(Xc)(X.e02)(0) \
    , ALIAS_CPP_IF1(Xc)(X.e03)(0) \
    , ALIAS_CPP_IF1(Xc)(X.e12)(0) \
    , ALIAS_CPP_IF1(Xc)(X.e31)(0) \
    , ALIAS_CPP_IF1(Xc)(X.e23)(0) \
    , ALIAS_CPP_IF1(Xd)(X.e021)(0) \
    , ALIAS_CPP_IF1(Xd)(X.e013)(0) \
    , ALIAS_CPP_IF1(Xd)(X.e032)(0) \
    , ALIAS_CPP_IF1(Xd)(X.e123)(0) \
    , ALIAS_CPP_IF1(Xe)(X.e0123)(0) \
    , ## __VA_ARGS__ \
    )

#define ALIAS_PGA_UNARY_IMPORT_OP(RETURN, OP, X,Xa,Xb,Xc,Xd,Xe, ...) ALIAS_PGA_UNARY_IMPORT(ALIAS_PGA_UNARY_IMPORT_OP_1, X,Xa,Xb,Xc,Xd,Xe, RETURN,OP,##__VA_ARGS__)
#define ALIAS_PGA_UNARY_IMPORT_OP_1(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, RETURN,OP,...) OP(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ##__VA_ARGS__)

#define ALIAS_PGA_UNARY_NAME(op, A,B,C,D,E) alias_pga__##op##_##A##B##C##D##E

#define ALIAS_PGA_UNARY_GENERATE_FUNCTION(OP,op, Xa,Xb,Xc,Xd,Xe) ALIAS_PGA_UNARY_IMPORT_OP(ALIAS_PGA_UNARY_GENERATE_FUNCTION_1, OP, x,Xa,Xb,Xc,Xd,Xe, op,Xa,Xb,Xc,Xd,Xe)
#define ALIAS_PGA_UNARY_GENERATE_FUNCTION_1(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, op,Xa,Xb,Xc,Xd,Xe) ALIAS_PGA_GRADE(ALIAS_PGA_UNARY_GENERATE_FUNCTION_2, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,op,Xa,Xb,Xc,Xd,Xe,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define ALIAS_PGA_UNARY_GENERATE_FUNCTION_2(Za,Zb,Zc,Zd,Ze, op,Xa,Xb,Xc,Xd,Xe,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) \
static inline ALIAS_PGA_TYPENAME_FROM_BITS(Za,Zb,Zc,Zd,Ze) ALIAS_PGA_UNARY_NAME(op,Xa,Xb,Xc,Xd,Xe)(ALIAS_PGA_TYPENAME_FROM_BITS(Xa,Xb,Xc,Xd,Xe) x) { \
  ALIAS_CPP_IF1(ALIAS_PGA_HAS_GRADES(Xa,Xb,Xc,Xd,Xe))()((void)x;) \
  return ( ALIAS_PGA_TYPENAME_FROM_BITS(Za,Zb,Zc,Zd,Ze) ) { \
    ALIAS_PGA_EXPORT(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, Za,Zb,Zc,Zd,Ze) \
  }; \
}

#define ALIAS_PGA_GENERATE_UNARY(OP, op) ALIAS_PGA_BITS_1(ALIAS_PGA_GENERATE_UNARY_1, OP,op)
#define ALIAS_PGA_GENERATE_UNARY_1(A,B,C,D,E, OP,op) ALIAS_PGA_UNARY_GENERATE_FUNCTION(OP,op, A,B,C,D,E)

#define ALIAS_PGA_USE_UNARY(op, X) _Generic((X) ALIAS_PGA_BITS_1(ALIAS_PGA_USE_UNARY_1, op))(X)
#define ALIAS_PGA_USE_UNARY_1(A,B,C,D,E, op) , ALIAS_PGA_TYPENAME_FROM_BITS(A,B,C,D,E): ALIAS_PGA_UNARY_NAME(op, A,B,C,D,E)

#endif

