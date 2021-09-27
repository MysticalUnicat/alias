#ifndef _ALIAS_PGA_BITS_H_
#define _ALIAS_PGA_BITS_H_

#include <alias/cpp/boolean.h>

#define ALIAS_PGA_HAS_GRADES(A, B, C, D, E) ALIAS_CPP_OR(A, ALIAS_CPP_OR(B, ALIAS_CPP_OR(C, ALIAS_CPP_OR(D, E))))

#define ALIAS_PGA_HAS_NO_GRADES(A, B, C, D, E) ALIAS_CPP_BNOT(ALIAS_PGA_HAS_GRADES(A, B, C, D, E))

#define ALIAS_PGA_HAS_GRADE_0(A, B, C, D, E) A
#define ALIAS_PGA_HAS_GRADE_1(A, B, C, D, E) B
#define ALIAS_PGA_HAS_GRADE_2(A, B, C, D, E) C
#define ALIAS_PGA_HAS_GRADE_3(A, B, C, D, E) D
#define ALIAS_PGA_HAS_GRADE_4(A, B, C, D, E) E

#define ALIAS_PGA_EXPAND_BITS_1(RETURN, A,B,C,D,E, ...) RETURN(A, B, B, B, B, C, C, C, C, C, C, D, D, D, D, E, ## __VA_ARGS__)
#define ALIAS_PGA_EXPAND_BITS_2(RETURN, A,B,C,D,E, ...) RETURN(A, B, B, B, B, C, C, C, C, C, C, D, D, D, D, E, ## __VA_ARGS__)

#define ALIAS_PGA_GRADE(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) \
  RETURN( \
      ALIAS_CPP_IS_NONZERO(A) \
    , ALIAS_CPP_OR(ALIAS_CPP_IS_NONZERO(B), ALIAS_CPP_OR(ALIAS_CPP_IS_NONZERO(C), ALIAS_CPP_OR(ALIAS_CPP_IS_NONZERO(D), ALIAS_CPP_IS_NONZERO(E)))) \
    , ALIAS_CPP_OR(ALIAS_CPP_IS_NONZERO(F), ALIAS_CPP_OR(ALIAS_CPP_IS_NONZERO(G), ALIAS_CPP_OR(ALIAS_CPP_IS_NONZERO(H), ALIAS_CPP_OR(ALIAS_CPP_IS_NONZERO(I), ALIAS_CPP_OR(ALIAS_CPP_IS_NONZERO(J), ALIAS_CPP_IS_NONZERO(K)))))) \
    , ALIAS_CPP_OR(ALIAS_CPP_IS_NONZERO(L), ALIAS_CPP_OR(ALIAS_CPP_IS_NONZERO(M), ALIAS_CPP_OR(ALIAS_CPP_IS_NONZERO(N), ALIAS_CPP_IS_NONZERO(O)))) \
    , ALIAS_CPP_IS_NONZERO(P) \
    , ## __VA_ARGS__ \
    )

#define ALIAS_PGA_BITS_1(X, ...) \
  /* X(0, 0, 0, 0, 0, ## __VA_ARGS__) */ \
  X(0, 0, 0, 0, 1, ## __VA_ARGS__) \
  X(0, 0, 0, 1, 0, ## __VA_ARGS__) \
  /* X(0, 0, 0, 1, 1, ## __VA_ARGS__) */ \
  X(0, 0, 1, 0, 0, ## __VA_ARGS__) \
  /* X(0, 0, 1, 0, 1, ## __VA_ARGS__) */ \
  /* X(0, 0, 1, 1, 0, ## __VA_ARGS__) */ \
  /* X(0, 0, 1, 1, 1, ## __VA_ARGS__) */ \
  X(0, 1, 0, 0, 0, ## __VA_ARGS__) \
  /* X(0, 1, 0, 0, 1, ## __VA_ARGS__) */ \
  /* X(0, 1, 0, 1, 0, ## __VA_ARGS__) */ \
  /* X(0, 1, 0, 1, 1, ## __VA_ARGS__) */ \
  /* X(0, 1, 1, 0, 0, ## __VA_ARGS__) */ \
  /* X(0, 1, 1, 0, 1, ## __VA_ARGS__) */ \
  /* X(0, 1, 1, 1, 0, ## __VA_ARGS__) */ \
  /* X(0, 1, 1, 1, 1, ## __VA_ARGS__) */ \
  X(1, 0, 0, 0, 0, ## __VA_ARGS__) \
  /* X(1, 0, 0, 0, 1, ## __VA_ARGS__) */ \
  /* X(1, 0, 0, 1, 0, ## __VA_ARGS__) */ \
  /* X(1, 0, 0, 1, 1, ## __VA_ARGS__) */ \
  /* X(1, 0, 1, 0, 0, ## __VA_ARGS__) */ \
  X(1, 0, 1, 0, 1, ## __VA_ARGS__) \
  /* X(1, 0, 1, 1, 0, ## __VA_ARGS__) */ \
  /* X(1, 0, 1, 1, 1, ## __VA_ARGS__) */ \
  /* X(1, 1, 0, 0, 0, ## __VA_ARGS__) */ \
  /* X(1, 1, 0, 0, 1, ## __VA_ARGS__) */ \
  /* X(1, 1, 0, 1, 0, ## __VA_ARGS__) */ \
  /* X(1, 1, 0, 1, 1, ## __VA_ARGS__) */ \
  /* X(1, 1, 1, 0, 0, ## __VA_ARGS__) */ \
  /* X(1, 1, 1, 0, 1, ## __VA_ARGS__) */ \
  /* X(1, 1, 1, 1, 0, ## __VA_ARGS__) */ \
  /* X(1, 1, 1, 1, 1, ## __VA_ARGS__) */

#define ALIAS_PGA_BITS_2(X, ...) \
  /* X(0, 0, 0, 0, 0, ## __VA_ARGS__) */ \
  X(0, 0, 0, 0, 1, ## __VA_ARGS__) \
  X(0, 0, 0, 1, 0, ## __VA_ARGS__) \
  /* X(0, 0, 0, 1, 1, ## __VA_ARGS__) */ \
  X(0, 0, 1, 0, 0, ## __VA_ARGS__) \
  /* X(0, 0, 1, 0, 1, ## __VA_ARGS__) */ \
  /* X(0, 0, 1, 1, 0, ## __VA_ARGS__) */ \
  /* X(0, 0, 1, 1, 1, ## __VA_ARGS__) */ \
  X(0, 1, 0, 0, 0, ## __VA_ARGS__) \
  /* X(0, 1, 0, 0, 1, ## __VA_ARGS__) */ \
  /* X(0, 1, 0, 1, 0, ## __VA_ARGS__) */ \
  /* X(0, 1, 0, 1, 1, ## __VA_ARGS__) */ \
  /* X(0, 1, 1, 0, 0, ## __VA_ARGS__) */ \
  /* X(0, 1, 1, 0, 1, ## __VA_ARGS__) */ \
  /* X(0, 1, 1, 1, 0, ## __VA_ARGS__) */ \
  /* X(0, 1, 1, 1, 1, ## __VA_ARGS__) */ \
  X(1, 0, 0, 0, 0, ## __VA_ARGS__) \
  /* X(1, 0, 0, 0, 1, ## __VA_ARGS__) */ \
  /* X(1, 0, 0, 1, 0, ## __VA_ARGS__) */ \
  /* X(1, 0, 0, 1, 1, ## __VA_ARGS__) */ \
  /* X(1, 0, 1, 0, 0, ## __VA_ARGS__) */ \
  X(1, 0, 1, 0, 1, ## __VA_ARGS__) \
  /* X(1, 0, 1, 1, 0, ## __VA_ARGS__) */ \
  /* X(1, 0, 1, 1, 1, ## __VA_ARGS__) */ \
  /* X(1, 1, 0, 0, 0, ## __VA_ARGS__) */ \
  /* X(1, 1, 0, 0, 1, ## __VA_ARGS__) */ \
  /* X(1, 1, 0, 1, 0, ## __VA_ARGS__) */ \
  /* X(1, 1, 0, 1, 1, ## __VA_ARGS__) */ \
  /* X(1, 1, 1, 0, 0, ## __VA_ARGS__) */ \
  /* X(1, 1, 1, 0, 1, ## __VA_ARGS__) */ \
  /* X(1, 1, 1, 1, 0, ## __VA_ARGS__) */ \
  /* X(1, 1, 1, 1, 1, ## __VA_ARGS__) */

#define ALIAS_PGA_ALL_BITS(X, ...) \
  X(0, 0, 0, 0, 0, ## __VA_ARGS__) \
  X(0, 0, 0, 0, 1, ## __VA_ARGS__) \
  X(0, 0, 0, 1, 0, ## __VA_ARGS__) \
  X(0, 0, 0, 1, 1, ## __VA_ARGS__) \
  X(0, 0, 1, 0, 0, ## __VA_ARGS__) \
  X(0, 0, 1, 0, 1, ## __VA_ARGS__) \
  X(0, 0, 1, 1, 0, ## __VA_ARGS__) \
  X(0, 0, 1, 1, 1, ## __VA_ARGS__) \
  X(0, 1, 0, 0, 0, ## __VA_ARGS__) \
  X(0, 1, 0, 0, 1, ## __VA_ARGS__) \
  X(0, 1, 0, 1, 0, ## __VA_ARGS__) \
  X(0, 1, 0, 1, 1, ## __VA_ARGS__) \
  X(0, 1, 1, 0, 0, ## __VA_ARGS__) \
  X(0, 1, 1, 0, 1, ## __VA_ARGS__) \
  X(0, 1, 1, 1, 0, ## __VA_ARGS__) \
  X(0, 1, 1, 1, 1, ## __VA_ARGS__) \
  X(1, 0, 0, 0, 0, ## __VA_ARGS__) \
  X(1, 0, 0, 0, 1, ## __VA_ARGS__) \
  X(1, 0, 0, 1, 0, ## __VA_ARGS__) \
  X(1, 0, 0, 1, 1, ## __VA_ARGS__) \
  X(1, 0, 1, 0, 0, ## __VA_ARGS__) \
  X(1, 0, 1, 0, 1, ## __VA_ARGS__) \
  X(1, 0, 1, 1, 0, ## __VA_ARGS__) \
  X(1, 0, 1, 1, 1, ## __VA_ARGS__) \
  X(1, 1, 0, 0, 0, ## __VA_ARGS__) \
  X(1, 1, 0, 0, 1, ## __VA_ARGS__) \
  X(1, 1, 0, 1, 0, ## __VA_ARGS__) \
  X(1, 1, 0, 1, 1, ## __VA_ARGS__) \
  X(1, 1, 1, 0, 0, ## __VA_ARGS__) \
  X(1, 1, 1, 0, 1, ## __VA_ARGS__) \
  X(1, 1, 1, 1, 0, ## __VA_ARGS__) \
  X(1, 1, 1, 1, 1, ## __VA_ARGS__)

#endif

