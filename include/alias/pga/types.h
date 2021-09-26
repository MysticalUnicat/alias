#ifndef _ALIAS_PGA_TYPES_H_
#define _ALIAS_PGA_TYPES_H_

#include <alias/cpp/cat.h>
#include <alias/cpp/boolean.h>

#include <alias/pga/bits.h>
#include <alias/pga/real.h>

#define ALIAS_PGA_TYPENAME_FROM_BITS(A, B, C, D, E) ALIAS_CPP_CAT6(alias_pga_Multigrade, A, B, C, D, E)

// elements are sorted so common combinations result in blocks of 4 floats?
#define ALIAS_PGA_GENERATE_MULTIGRADE_TYPE(A, B, C, D, E) \
  typedef struct ALIAS_PGA_TYPENAME_FROM_BITS(A, B, C, D, E) { \
    union { \
      alias_R _first; \
      ALIAS_CPP_IF1(ALIAS_PGA_HAS_GRADES(A, B, C, D, E))( \
        struct { \
          ALIAS_CPP_IF1(B)( alias_R e0, e1, e2, e3; )() \
          ALIAS_CPP_IF1(C)( alias_R e01, e02, e03; )() \
          ALIAS_CPP_IF1(A)( alias_R one; )() \
          ALIAS_CPP_IF1(C)( alias_R e12, e31, e23; )() \
          ALIAS_CPP_IF1(E)( alias_R e0123; )() \
          ALIAS_CPP_IF1(D)( alias_R e021, e013, e032, e123; )() \
        }; \
      )() \
    }; \
  } ALIAS_PGA_TYPENAME_FROM_BITS(A, B, C, D, E);

ALIAS_PGA_ALL_BITS(ALIAS_PGA_GENERATE_MULTIGRADE_TYPE)

typedef alias_pga_Multigrade01000 alias_pga_Plane;
typedef alias_pga_Multigrade00100 alias_pga_Line;
typedef alias_pga_Multigrade00010 alias_pga_Point;

#endif

