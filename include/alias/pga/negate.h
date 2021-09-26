#ifndef _ALIAS_PGA_NEGATE_H_
#define _ALIAS_PGA_NEGATE_H_

#include <alias/pga/real.h>
#include <alias/pga/unary.h>

#define ALIAS_PGA_UNARY_NEGATE(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) \
  RETURN( \
     ALIAS_PGA_RZ_NEGATE(A) /*   one */ \
   , ALIAS_PGA_RZ_NEGATE(B) /*    e0 */ \
   , ALIAS_PGA_RZ_NEGATE(C) /*    e1 */ \
   , ALIAS_PGA_RZ_NEGATE(D) /*    e2 */ \
   , ALIAS_PGA_RZ_NEGATE(E) /*    e3 */ \
   , ALIAS_PGA_RZ_NEGATE(F) /*   e01 */ \
   , ALIAS_PGA_RZ_NEGATE(G) /*   e02 */ \
   , ALIAS_PGA_RZ_NEGATE(H) /*   e03 */ \
   , ALIAS_PGA_RZ_NEGATE(I) /*   e12 */ \
   , ALIAS_PGA_RZ_NEGATE(J) /*   e31 */ \
   , ALIAS_PGA_RZ_NEGATE(K) /*   e23 */ \
   , ALIAS_PGA_RZ_NEGATE(L) /*  e021 */ \
   , ALIAS_PGA_RZ_NEGATE(M) /*  e013 */ \
   , ALIAS_PGA_RZ_NEGATE(N) /*  e032 */ \
   , ALIAS_PGA_RZ_NEGATE(O) /*  e123 */ \
   , ALIAS_PGA_RZ_NEGATE(P) /* e0123 */ \
   , ## __VA_ARGS__ \
   )

ALIAS_PGA_GENERATE_UNARY(ALIAS_PGA_UNARY_NEGATE, negate)

#define alias_pga_negate(A) ALIAS_PGA_USE_UNARY(ALIAS_PGA_UNARY_NEGATE, negate, A)

#endif

