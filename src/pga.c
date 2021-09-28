#include <alias/pga.h>

#include <alias/cpp/defer_eval.h>

#include <alias/pga/operators.h>

#include <alias/pga/unary.h>
#include <alias/pga/binary.h>

#define base_unary_function(op, Xa,Xb,Xc,Xd,Xe, Za,Zb,Zc,Zd,Ze, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) \
ALIAS_CPP_IF1(ALIAS_PGA_HAS_GRADES(Za,Zb,Zc,Zd,Ze))( \
  @ ALIAS_PGA_TYPENAME_FROM_BITS(Za,Zb,Zc,Zd,Ze) ALIAS_PGA_UNARY_NAME(op,Xa,Xb,Xc,Xd,Xe)(ALIAS_PGA_TYPENAME_FROM_BITS(Xa,Xb,Xc,Xd,Xe) x) { \
    ALIAS_CPP_IF1(ALIAS_PGA_HAS_GRADES(Xa,Xb,Xc,Xd,Xe))()((void)x;) \
    return ( ALIAS_PGA_TYPENAME_FROM_BITS(Za,Zb,Zc,Zd,Ze) ) { \
      ALIAS_PGA_EXPORT(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, Za,Zb,Zc,Zd,Ze) \
    }; \
  } \
)()

#define base_binary_function(op, Xa,Xb,Xc,Xd,Xe, Ya,Yb,Yc,Yd,Ye, Za,Zb,Zc,Zd,Ze, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) \
ALIAS_CPP_IF1(ALIAS_PGA_HAS_GRADES(Za,Zb,Zc,Zd,Ze))( \
  @ ALIAS_PGA_TYPENAME_FROM_BITS(Za,Zb,Zc,Zd,Ze) ALIAS_PGA_BINARY_NAME(op,Xa,Xb,Xc,Xd,Xe,Ya,Yb,Yc,Yd,Ye)(ALIAS_PGA_TYPENAME_FROM_BITS(Xa,Xb,Xc,Xd,Xe) x, ALIAS_PGA_TYPENAME_FROM_BITS(Ya,Yb,Yc,Yd,Ye) y) { \
    ALIAS_CPP_IF1(ALIAS_PGA_HAS_GRADES(Xa,Xb,Xc,Xd,Xe))()((void)x;) \
    ALIAS_CPP_IF1(ALIAS_PGA_HAS_GRADES(Ya,Yb,Yc,Yd,Ye))()((void)y;) \
    return ( ALIAS_PGA_TYPENAME_FROM_BITS(Za,Zb,Zc,Zd,Ze) ) { \
      ALIAS_PGA_EXPORT(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, Za,Zb,Zc,Zd,Ze) \
    }; \
  } \
)()

ALIAS_CPP_EVAL( ALIAS_PGA_UNARY_OPERATORS(ALIAS_PGA_GENERATE_UNARY, base_unary_function) )

ALIAS_CPP_EVAL( ALIAS_PGA_BINARY_OPERATORS(ALIAS_PGA_GENERATE_BINARY, base_binary_function) )
