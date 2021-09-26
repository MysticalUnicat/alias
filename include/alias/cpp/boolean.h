#ifndef _ALIAS_CPP_BOOLEAN_H_
#define _ALIAS_CPP_BOOLEAN_H_

#include <alias/cpp/cat.h>
#include <alias/cpp/probe.h>

#define ALIAS_CPP_BOOLEAN_AND(X, Y) ALIAS_CPP_CAT3(ALIAS_CPP_BOOLEAN_AND_, X, Y)
#define ALIAS_CPP_BOOLEAN_AND_00 0
#define ALIAS_CPP_BOOLEAN_AND_10 0
#define ALIAS_CPP_BOOLEAN_AND_01 0
#define ALIAS_CPP_BOOLEAN_AND_11 1

#define ALIAS_CPP_BOOLEAN_OR(X, Y) ALIAS_CPP_CAT3(ALIAS_CPP_BOOLEAN_OR_, X, Y)
#define ALIAS_CPP_BOOLEAN_OR_00 0
#define ALIAS_CPP_BOOLEAN_OR_10 1
#define ALIAS_CPP_BOOLEAN_OR_01 1
#define ALIAS_CPP_BOOLEAN_OR_11 1

#define ALIAS_CPP_BOOLEAN_NOT(X) ALIAS_CPP_CAT(ALIAS_CPP_BOOLEAN_NOT_, X)
#define ALIAS_CPP_BOOLEAN_NOT_0 1
#define ALIAS_CPP_BOOLEAN_NOT_1 0

#define ALIAS_CPP_BOOLEAN_IMPLY(X, Y) ALIAS_CPP_CAT3(ALIAS_CPP_BOOLEAN_IMPLY_, X, Y)
#define ALIAS_CPP_BOOLEAN_IMPLY_00 1
#define ALIAS_CPP_BOOLEAN_IMPLY_10 0
#define ALIAS_CPP_BOOLEAN_IMPLY_01 1
#define ALIAS_CPP_BOOLEAN_IMPLY_11 1

#define ALIAS_CPP_BOOLEAN_XOR(X, Y) ALIAS_CPP_CAT3(ALIAS_CPP_BOOLEAN_XOR_, X, Y)
#define ALIAS_CPP_BOOLEAN_XOR_00 0
#define ALIAS_CPP_BOOLEAN_XOR_10 1
#define ALIAS_CPP_BOOLEAN_XOR_01 1
#define ALIAS_CPP_BOOLEAN_XOR_11 0

#define ALIAS_CPP_BOOLEAN_EQ(X, Y) ALIAS_CPP_CAT3(ALIAS_CPP_BOOLEAN_EQ_, X, Y)
#define ALIAS_CPP_BOOLEAN_EQ_00 1
#define ALIAS_CPP_BOOLEAN_EQ_10 0
#define ALIAS_CPP_BOOLEAN_EQ_01 0
#define ALIAS_CPP_BOOLEAN_EQ_11 1

#define ALIAS_CPP_BOOLEAN_CHOICE(X) ALIAS_CPP_CAT(ALIAS_CPP_BOOLEAN_CHOICE_, X)
#define ALIAS_CPP_BOOLEAN_CHOICE_0(...)              ALIAS_CPP_BOOLEAN_CHOICE_0_
#define ALIAS_CPP_BOOLEAN_CHOICE_0_(...) __VA_ARGS__
#define ALIAS_CPP_BOOLEAN_CHOICE_1(...)  __VA_ARGS__ ALIAS_CPP_BOOLEAN_CHOICE_1_
#define ALIAS_CPP_BOOLEAN_CHOICE_1_(...) 

#define ALIAS_CPP_ADD  ALIAS_CPP_BOOLEAN_AND
#define ALIAS_CPP_OR   ALIAS_CPP_BOOLEAN_OR
#define ALIAS_CPP_BNOT ALIAS_CPP_BOOLEAN_NOT

#define ALIAS_CPP_IFF(X) ALIAS_CPP_CAT(ALIAS_CPP_IFF_, X)
#define ALIAS_CPP_IFF_0(T, F) F
#define ALIAS_CPP_IFF_1(T, F) T

// test<x,y>( 1 )( 0 )
#define ALIAS_CPP_IF1 ALIAS_CPP_BOOLEAN_CHOICE 

// test<x,y>( 11 )( 10 )( 01 )( 00 )
#define ALIAS_CPP_IF2(X, Y) ALIAS_CPP_CAT4(ALIAS_CPP_IF2_, X, Y, _0)

#define ALIAS_CPP_IF2_11_0(...) __VA_ARGS__ ALIAS_CPP_IF2_11_1
#define ALIAS_CPP_IF2_11_1(...)             ALIAS_CPP_IF2_11_2
#define ALIAS_CPP_IF2_11_2(...)             ALIAS_CPP_IF2_11_3
#define ALIAS_CPP_IF2_11_3(...) 

#define ALIAS_CPP_IF2_10_0(...)             ALIAS_CPP_IF2_10_1
#define ALIAS_CPP_IF2_10_1(...) __VA_ARGS__ ALIAS_CPP_IF2_10_2
#define ALIAS_CPP_IF2_10_2(...)             ALIAS_CPP_IF2_10_3
#define ALIAS_CPP_IF2_10_3(...) 

#define ALIAS_CPP_IF2_01_0(...)             ALIAS_CPP_IF2_01_1
#define ALIAS_CPP_IF2_01_1(...)             ALIAS_CPP_IF2_01_2
#define ALIAS_CPP_IF2_01_2(...) __VA_ARGS__ ALIAS_CPP_IF2_01_3
#define ALIAS_CPP_IF2_01_3(...) 

#define ALIAS_CPP_IF2_00_0(...)             ALIAS_CPP_IF2_00_1
#define ALIAS_CPP_IF2_00_1(...)             ALIAS_CPP_IF2_00_2
#define ALIAS_CPP_IF2_00_2(...)             ALIAS_CPP_IF2_00_3
#define ALIAS_CPP_IF2_00_3(...) __VA_ARGS__ 

#define ALIAS_CPP_EQ(PREFIX, X, Y) ALIAS_CPP_IS_PROBE(ALIAS_CPP_CAT5(ALIAS_CPP_EQ__, PREFIX, X, _, Y)())

// simple template for how to use ALIAS_CPP_EQ
#define ALIAS_CPP_EQ__ALIAS0_0 ALIAS_CPP_PROBE

// used here
#define ALIAS_CPP_IS_ZERO(X) ALIAS_CPP_EQ(ALIAS, 0, X)

#define ALIAS_CPP_IS_NONZERO(X) ALIAS_CPP_BNOT(ALIAS_CPP_IS_ZERO(X))

#define ALIAS_CPP_IS_BEGIN_PAREN(X) ALIAS_CPP_IS_BEGIN_PAREN_(ALIAS_CPP_IS_BEGIN_PAREN_call X)
#define ALIAS_CPP_IS_BEGIN_PAREN_(X) ALIAS_CPP_IS_PROBE(X())
#define ALIAS_CPP_IS_BEGIN_PAREN_call(...) ALIAS_CPP_PROBE

_Static_assert(ALIAS_CPP_BOOLEAN_AND(0, 0) == 0, "");
_Static_assert(ALIAS_CPP_BOOLEAN_AND(0, 1) == 0, "");
_Static_assert(ALIAS_CPP_BOOLEAN_AND(1, 0) == 0, "");
_Static_assert(ALIAS_CPP_BOOLEAN_AND(1, 1) == 1, "");

_Static_assert(ALIAS_CPP_BOOLEAN_OR(0, 0) == 0, "");
_Static_assert(ALIAS_CPP_BOOLEAN_OR(0, 1) == 1, "");
_Static_assert(ALIAS_CPP_BOOLEAN_OR(1, 0) == 1, "");
_Static_assert(ALIAS_CPP_BOOLEAN_OR(1, 1) == 1, "");

_Static_assert(ALIAS_CPP_BOOLEAN_NOT(0) == 1, "");
_Static_assert(ALIAS_CPP_BOOLEAN_NOT(1) == 0, "");

_Static_assert(ALIAS_CPP_BOOLEAN_IMPLY(0, 0), "");
_Static_assert(ALIAS_CPP_BOOLEAN_IMPLY(0, 1) == 1, "");
_Static_assert(ALIAS_CPP_BOOLEAN_IMPLY(1, 0) == 0, "");
_Static_assert(ALIAS_CPP_BOOLEAN_IMPLY(1, 1) == 1, "");

_Static_assert(ALIAS_CPP_BOOLEAN_XOR(0, 0) == 0, "");
_Static_assert(ALIAS_CPP_BOOLEAN_XOR(0, 1) == 1, "");
_Static_assert(ALIAS_CPP_BOOLEAN_XOR(1, 0) == 1, "");
_Static_assert(ALIAS_CPP_BOOLEAN_XOR(1, 1) == 0, "");

_Static_assert(ALIAS_CPP_BOOLEAN_EQ(0, 0) == 1, "");
_Static_assert(ALIAS_CPP_BOOLEAN_EQ(0, 1) == 0, "");
_Static_assert(ALIAS_CPP_BOOLEAN_EQ(1, 0) == 0, "");
_Static_assert(ALIAS_CPP_BOOLEAN_EQ(1, 1) == 1, "");

_Static_assert(ALIAS_CPP_BOOLEAN_CHOICE(0)(2)(3) == 3, "");
_Static_assert(ALIAS_CPP_BOOLEAN_CHOICE(1)(2)(3) == 2, "");

_Static_assert(ALIAS_CPP_IF2(0, 0)(2)(3)(4)(5) == 5, "");
_Static_assert(ALIAS_CPP_IF2(0, 1)(2)(3)(4)(5) == 4, "");
_Static_assert(ALIAS_CPP_IF2(1, 0)(2)(3)(4)(5) == 3, "");
_Static_assert(ALIAS_CPP_IF2(1, 1)(2)(3)(4)(5) == 2, "");

_Static_assert(ALIAS_CPP_IS_ZERO(0) == 1, "");
_Static_assert(ALIAS_CPP_IS_ZERO(1) == 0, "");
_Static_assert(ALIAS_CPP_IS_ZERO(2) == 0, "");

_Static_assert(ALIAS_CPP_IS_NONZERO(0) == 0, "");
_Static_assert(ALIAS_CPP_IS_NONZERO(1) == 1, "");
_Static_assert(ALIAS_CPP_IS_NONZERO(2) == 1, "");

#endif

