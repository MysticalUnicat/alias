#ifndef _ALIAS_PGA_ADD_H_
#define _ALIAS_PGA_ADD_H_

#include <alias/pga/real.h>
#include <alias/pga/binary.h>

#define ALIAS_PGA_BINARY_ADD(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) \
  RETURN( \
     ALIAS_PGA_RZ_ADD(A, a) /*   one */ \
   , ALIAS_PGA_RZ_ADD(B, b) /*    e0 */ \
   , ALIAS_PGA_RZ_ADD(C, c) /*    e1 */ \
   , ALIAS_PGA_RZ_ADD(D, d) /*    e2 */ \
   , ALIAS_PGA_RZ_ADD(E, e) /*    e3 */ \
   , ALIAS_PGA_RZ_ADD(F, f) /*   e01 */ \
   , ALIAS_PGA_RZ_ADD(G, g) /*   e02 */ \
   , ALIAS_PGA_RZ_ADD(H, h) /*   e03 */ \
   , ALIAS_PGA_RZ_ADD(I, i) /*   e12 */ \
   , ALIAS_PGA_RZ_ADD(J, j) /*   e31 */ \
   , ALIAS_PGA_RZ_ADD(K, k) /*   e23 */ \
   , ALIAS_PGA_RZ_ADD(L, l) /*  e021 */ \
   , ALIAS_PGA_RZ_ADD(M, m) /*  e013 */ \
   , ALIAS_PGA_RZ_ADD(N, n) /*  e032 */ \
   , ALIAS_PGA_RZ_ADD(O, o) /*  e123 */ \
   , ALIAS_PGA_RZ_ADD(P, p) /* e0123 */ \
   , ## __VA_ARGS__ \
   )

ALIAS_PGA_GENERATE_BINARY_FUNCTIONS(ALIAS_PGA_BINARY_ADD, add)

#define alias_pga_add(A, B) ALIAS_PGA_USE_BINARY(ALIAS_PGA_BINARY_ADD, add, A, B)

#endif

