#ifndef _ALIAS_PGA_SUBTRACT_H_
#define _ALIAS_PGA_SUBTRACT_H_

#include <alias/pga/real.h>
#include <alias/pga/binary.h>

#define ALIAS_PGA_BINARY_SUBTRACT(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) \
  RETURN( \
     ALIAS_PGA_RZ_SUBTRACT(A, a) /*   one */ \
   , ALIAS_PGA_RZ_SUBTRACT(B, b) /*    e0 */ \
   , ALIAS_PGA_RZ_SUBTRACT(C, c) /*    e1 */ \
   , ALIAS_PGA_RZ_SUBTRACT(D, d) /*    e2 */ \
   , ALIAS_PGA_RZ_SUBTRACT(E, e) /*    e3 */ \
   , ALIAS_PGA_RZ_SUBTRACT(F, f) /*   e01 */ \
   , ALIAS_PGA_RZ_SUBTRACT(G, g) /*   e02 */ \
   , ALIAS_PGA_RZ_SUBTRACT(H, h) /*   e03 */ \
   , ALIAS_PGA_RZ_SUBTRACT(I, i) /*   e12 */ \
   , ALIAS_PGA_RZ_SUBTRACT(J, j) /*   e31 */ \
   , ALIAS_PGA_RZ_SUBTRACT(K, k) /*   e23 */ \
   , ALIAS_PGA_RZ_SUBTRACT(L, l) /*  e021 */ \
   , ALIAS_PGA_RZ_SUBTRACT(M, m) /*  e013 */ \
   , ALIAS_PGA_RZ_SUBTRACT(N, n) /*  e032 */ \
   , ALIAS_PGA_RZ_SUBTRACT(O, o) /*  e123 */ \
   , ALIAS_PGA_RZ_SUBTRACT(P, p) /* e0123 */ \
   , ## __VA_ARGS__ \
   )

ALIAS_PGA_GENERATE_BINARY_FUNCTIONS(ALIAS_PGA_BINARY_SUBTRACT, subtract)

#define alias_pga_subtract(A, B) ALIAS_PGA_USE_BINARY(ALIAS_PGA_BINARY_SUBTRACT, subtract, A, B)

#endif

