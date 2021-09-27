#ifndef _ALIAS_PGA_DUAL_H_
#define _ALIAS_PGA_DUAL_H_

#include <alias/pga/unary.h>

#define ALIAS_PGA_UNARY_DUAL(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) \
  RETURN( \
     P /*   one */ \
   , O /*    e0 */ \
   , N /*    e1 */ \
   , M /*    e2 */ \
   , L /*    e3 */ \
   , K /*   e01 */ \
   , J /*   e02 */ \
   , I /*   e03 */ \
   , H /*   e12 */ \
   , G /*   e31 */ \
   , F /*   e23 */ \
   , E /*  e021 */ \
   , D /*  e013 */ \
   , C /*  e032 */ \
   , B /*  e123 */ \
   , A /* e0123 */ \
   , ## __VA_ARGS__ \
   )

#endif

