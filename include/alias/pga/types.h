#ifndef _ALIAS_PGA_TYPES_H_
#define _ALIAS_PGA_TYPES_H_

#define ALIAS_PGA_SSE 0

#if ALIAS_PGA_SSE
#include <pmmintrin.h>
#endif

#include <alias/math.h>

#include <alias/cpp/cat.h>
#include <alias/cpp/boolean.h>

#include <alias/pga/bits.h>

#define ALIAS_PGA_TYPENAME_FROM_BITS(A, B, C, D, E) ALIAS_CPP_CAT6(alias_pga_Multigrade, A, B, C, D, E)

// elements are sorted so common combinations result in blocks of 4 floats
#if ALIAS_PGA_SSE

#define ALIAS_PGA_GENERATE_MULTIGRADE_TYPE(A, B, C, D, E) \
  typedef struct __attribute__((aligned(16))) ALIAS_PGA_TYPENAME_FROM_BITS(A, B, C, D, E) { \
    union { \
      alias_R _first; \
      ALIAS_CPP_IF1(ALIAS_PGA_HAS_GRADES(A, B, C, D, E))( \
        struct { \
          ALIAS_CPP_IF1(B)( __m128 e0_e1_e2_e3; )() \
          ALIAS_CPP_IF2(A, C)( __m128   one_e01_e02_e03; )( float   one; )( __m128   one_e01_e02_e03; )() \
          ALIAS_CPP_IF2(E, C)( __m128 e0123_e12_e31_e23; )( float e0123; )( __m128 e0123_e12_e31_e23; )() \
          ALIAS_CPP_IF1(D)( __m128 e021_e013_e032_e123; )() \
        }; \
      )() \
    }; \
  } ALIAS_PGA_TYPENAME_FROM_BITS(A, B, C, D, E);

#else

#define ALIAS_PGA_GENERATE_MULTIGRADE_TYPE(A, B, C, D, E) \
  typedef struct __attribute__((aligned(16))) ALIAS_PGA_TYPENAME_FROM_BITS(A, B, C, D, E) { \
    union { \
      alias_R _first; \
      struct ALIAS_PGA_TYPENAME_FROM_BITS(E, D, C, B, A) * _dual_type; \
      ALIAS_CPP_IF1(ALIAS_PGA_HAS_GRADES(A, B, C, D, E))( \
        struct { \
          ALIAS_CPP_IF1(B)( alias_R e0,e1,e2,e3; )() \
          ALIAS_CPP_IF1(A)( alias_R one; )() \
          ALIAS_CPP_IF1(C)( alias_R e01,e02,e03; )() \
          ALIAS_CPP_IF1(E)( alias_R e0123; )() \
          ALIAS_CPP_IF1(D)( alias_R e12,e31,e23; )() \
          ALIAS_CPP_IF1(D)( alias_R e021,e013,e032,e123; )() \
        }; \
      )() \
    }; \
  } ALIAS_PGA_TYPENAME_FROM_BITS(A, B, C, D, E);

#endif

ALIAS_PGA_ALL_BITS(ALIAS_PGA_GENERATE_MULTIGRADE_TYPE)

// gemetric algebra types
typedef alias_pga_Multigrade10000 alias_pga_Scalar;
typedef alias_pga_Multigrade01000 alias_pga_Vector;
typedef alias_pga_Multigrade00100 alias_pga_Bivector;
typedef alias_pga_Multigrade00010 alias_pga_Trivector;
typedef alias_pga_Multigrade00001 alias_pga_Antiscalar;

// geometric object types
typedef alias_pga_Multigrade01000 alias_pga_Plane;
typedef alias_pga_Multigrade00100 alias_pga_Line;
typedef alias_pga_Multigrade00010 alias_pga_Point, alias_pga_Direction;
typedef alias_pga_Multigrade10101 alias_pga_Rotor;

// computational type
typedef alias_pga_Multigrade11111 alias_pga_Multivector;

#endif

