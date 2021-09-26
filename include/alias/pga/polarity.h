#ifndef _ALIAS_PGA_POLARITY_H_
#define _ALIAS_PGA_POLARITY_H_

#include <alias/pga/real.h>
#include <alias/pga/unary.h>

#define ALIAS_PGA_UNARY_POLARITY(RETURN, one,e0,e1,e2,e3,e01,e02,e03,e12,e31,e23,e021,e013,e032,e123,e0123, ...) \
  RETURN( \
     0 \
   , e123 \
   , 0 \
   , 0 \
   , 0 \
   , ALIAS_PGA_RZ_NEGATE(e23) \
   , ALIAS_PGA_RZ_NEGATE(e31) \
   , ALIAS_PGA_RZ_NEGATE(e12) \
   , 0 \
   , 0 \
   , 0 \
   , e3 \
   , e2 \
   , e1 \
   , 0 \
   , one \
   , ## __VA_ARGS__ \
   )

ALIAS_PGA_GENERATE_UNARY(ALIAS_PGA_UNARY_POLARITY, polarity)

#define alias_pga_polarity(A) ALIAS_PGA_USE_UNARY(ALIAS_PGA_UNARY_POLARITY, polarity, A)

#endif

