#ifndef _ALIAS_CPP_H_
#define _ALIAS_CPP_H_

#define ALIAS_EVAL_2(...) __VA_ARGS__
#define ALIAS_EVAL_1(...) ALIAS_EVAL_2(ALIAS_EVAL_2(ALIAS_EVAL_2(ALIAS_EVAL_2(__VA_ARGS__))))
#define ALIAS_EVAL_0(...) ALIAS_EVAL_1(ALIAS_EVAL_1(ALIAS_EVAL_1(ALIAS_EVAL_1(__VA_ARGS__))))
#define ALIAS_EVAL ALIAS_EVAL_0

#define ALIAS_PRIMITIVE_CAT(X, ...) X ## __VA_ARGS__

#define ALIAS_CAT(X, ...) ALIAS_PRIMITIVE_CAT(X, __VA_ARGS__)

#define ALIAS_BNOT(X) ALIAS_CAT(ALIAS_BNOT_, X)
#define ALIAS_BNOT_0 1
#define ALIAS_BNOT_1 0

#define ALIAS_IFF(X) ALIAS_CAT(ALIAS__IFF_test_, X)
#define ALIAS__IFF_test_0(T, F) F
#define ALIAS__IFF_test_1(T, F) T

// create Some iff X is 1, or else None
#define ALIAS_Some_IFF(X) ALIAS_CAT(ALIAS_Some_IFF_test_, X)
#define ALIAS_Some_IFF_test_0(...) None()
#define ALIAS_Some_IFF_test_1(...) Some(__VA_ARGS__)

#define ALIAS__PROBE() ~, 1
#define ALIAS__IS_PROBE(...) ALIAS__IS_PROBE_(__VA_ARGS__, 0, 0)
#define ALIAS__IS_PROBE_(X, Y, ...) Y

// tell us if this is an option! can take any identifier or number-pp token
#define ALIAS_IS_OPTION(OPTION) ALIAS__IS_PROBE(ALIAS_CAT(ALIAS_IS_OPTION_, OPTION))
#define ALIAS_IS_OPTION_Some(...) ALIAS__PROBE()
#define ALIAS_IS_OPTION_None(...) ALIAS__PROBE()

// the Option's type None or Some
#define ALIAS_OPTION_TYPE(OPTION) ALIAS_CAT(ALIAS_OPTION_TYPE_, OPTION)
#define ALIAS_OPTION_TYPE_Some(...) Some
#define ALIAS_OPTION_TYPE_None(...) None

// same as ALIAS_OPTION_TYPE but returns 1/0
#define ALIAS_OPTION_IS_SOME(OPTION) ALIAS_CAT(ALIAS_OPTION_IS_SOME_, OPTION)
#define ALIAS_OPTION_IS_SOME_Some(...) 1
#define ALIAS_OPTION_IS_SOME_None(...) 0

#define ALIAS_OPTION_IS_NONE(OPTION) ALIAS_BNOT(ALIAS_OPTION_IS_SOME(OPTION))

// the Option's value as a parameter list.
// None always outputs ~ to cause syntax errors if the value is ever attempted to be emitted
#define ALIAS_OPTION_VALUE(OPTION) ALIAS_CAT(ALIAS_OPTION_VALUE_, OPTION)
#define ALIAS_OPTION_VALUE_Some(...) ( __VA_ARGS__ )
#define ALIAS_OPTION_VALUE_None(...) ~

// Simple map operation for option
#define ALIAS_OPTION_MAP(OPTION, F)      \
  ALIAS_IFF(                             \
    ALIAS_OPTION_IS_SOME(OPTION)         \
  )(                                     \
      Some(F ALIAS_OPTION_VALUE(OPTION)) \
    , None()                             \
  )

// unwrap an option, with a defualt value for None()
#define ALIAS_OPTION_UNWRAP(OPTION, DEFAULT) \
  ALIAS_IFF( \
    ALIAS_OPTION_IS_SOME(OPTION) \
  )( \
      ALIAS_EVAL ALIAS_OPTION_VALUE(OPTION) \
    , DEFAULT \
  )

// get the first argument, hopefully it catches a lot of things, returns None() or Some(X)
#define ALIAS_FIRST(...) ALIAS_FIRST_(~, ## __VA_ARGS__, ALIAS__PROBE)
#define ALIAS_FIRST_(X, Y, ...) ALIAS_Some_IFF(ALIAS_BNOT(ALIAS__IS_PROBE(Y())))(Y)

#define ALIAS__EMPTY()
#define ALIAS__DEFER_1(X) X ALIAS__EMPTY()
#define ALIAS__DEFER_2(X) X ALIAS__EMPTY ALIAS__EMPTY()()

#define ALIAS_MAP(F, ...) ALIAS_EVAL(ALIAS_MAP_(F, __VA_ARGS__))
#define ALIAS_MAP_(F, X, ...) \
  F(X) \
  ALIAS_IFF( \
    ALIAS_OPTION_IS_SOME(ALIAS_FIRST(__VA_ARGS__)) \
  )( \
      ALIAS__DEFER_2(ALIAS_MAP__)()(F, __VA_ARGS__) \
    , /* do nothing */ \
  )
#define ALIAS_MAP__() ALIAS_MAP_

#if 0
#define ALIAS__CONSUME_ARGUMENTS(...)

#define ALIAS__EMIT_ARGUMENTS(...) __VA_ARGS__
#define ALIAS__FIRST(X, ...) X
#define ALIAS__SECOND(X, Y, ...) Y

#define ALIAS__LIT_ZERO(...) 0
#define ALIAS__LIT_ONE(...)  1

#define ALIAS__EVAL_3(...) __VA_ARGS__
#define ALIAS__EVAL_2(...) ALIAS__EVAL_3(ALIAS__EVAL_3(ALIAS__EVAL_3(ALIAS__EVAL_3(__VA_ARGS__))))
#define ALIAS__EVAL_1(...) ALIAS__EVAL_2(ALIAS__EVAL_2(ALIAS__EVAL_2(ALIAS__EVAL_2(__VA_ARGS__))))
#define ALIAS__EVAL_0(...) ALIAS__EVAL_1(ALIAS__EVAL_1(ALIAS__EVAL_1(ALIAS__EVAL_1(__VA_ARGS__))))
#define ALIAS_EVAL ALIAS__EVAL_2

#define ALIAS__CAT_1(X, Y) X ## Y
#define ALIAS__CAT_0(X, Y) ALIAS__CAT_1(X, Y)
#define ALIAS_CAT(X, Y, ...) ALIAS__CAT_0(X, Y)

#define ALIAS__CAT3_1(A, B, C) A ## B ## C
#define ALIAS__CAT3_0(A, B, C) ALIAS__CAT3_1(A, B, C)
#define ALIAS_CAT3(A, B, C, ...) ALIAS__CAT3_0(A, B, C)

#define ALIAS__ARGSq(...) ALIAS_CAT3(ALIAS_, __VA_ARGS__, _LIT_ZERO)()

_Static_assert(ALIAS__ARGSq() == 0, "");
_Static_assert(ALIAS__ARGSq(.) == 1, "");
_Static_assert(ALIAS__ARGSq(,) == 1, "");

#define ALIAS__PROBE() ~, 1
#define ALIAS__IS_PROBE(...) ALIAS__SECOND(__VA_ARGS__, 0, 0)

#define ALIAS_NOT(X) ALIAS__IS_PROBE(ALIAS_CAT(ALIAS__NOT_, X))
#define ALIAS__NOT_0 ALIAS__PROBE()

#define ALIAS_BOOL(X) ALIAS_NOT(ALIAS_NOT(X))

_Static_assert(ALIAS_BOOL(0) == 0, "");
_Static_assert(ALIAS_BOOL(1) == 1, "");
_Static_assert(ALIAS_BOOL(_) == 1, "");
_Static_assert(ALIAS_BOOL(a) == 1, "");

#define ALIAS_AND(X, Y) ALIAS_NOT(ALIAS_CAT3( ALIAS__AND_test_, ALIAS_BOOL(X), ALIAS_BOOL(Y) ))
#define ALIAS__AND_test_11 0

#define ALIAS_OR(X, Y) ALIAS_NOT(ALIAS_CAT3( ALIAS__OR_test_, ALIAS_BOOL(X), ALIAS_BOOL(Y) ))
#define ALIAS__OR_test_11 0
#define ALIAS__OR_test_10 0
#define ALIAS__OR_test_01 0

#define ALIAS_HAS_ARGUMENTS(...) ALIAS_CAT(ALIAS__HAS_ARGUMENTS_test_, ALIAS__HAS_ARGUMENTS_simple(__VA_ARGS__))
#define ALIAS__HAS_ARGUMENTS_simple(...) ALIAS__HAS_ARGUMENTS_simple_ __VA_ARGS__ 
#define ALIAS__HAS_ARGUMENTS_simple() 1
#define ALIAS__HAS_ARGUMENTS_test_1 0

_Static_assert(ALIAS_HAS_ARGUMENTS() == 0, "");
_Static_assert(ALIAS_HAS_ARGUMENTS(0) == 1, "");
_Static_assert(ALIAS_HAS_ARGUMENTS(0, 1) == 1, "");
_Static_assert(ALIAS_HAS_ARGUMENTS(1) == 1, "");
_Static_assert(ALIAS_HAS_ARGUMENTS(,) == 1, "");

#define ALIAS_IF_ELSE(COND) ALIAS__IF_ELSE(ALIAS_BOOL(COND))
#define ALIAS__IF_ELSE(COND) ALIAS_CAT(ALIAS__IF_ELSE_, COND)
#define ALIAS__IF_ELSE_1(...) __VA_ARGS__ ALIAS__CONSUME_ARGUMENTS
#define ALIAS__IF_ELSE_0(...)             ALIAS__EMIT_ARGUMENTS

_Static_assert(ALIAS_IF_ELSE(0)(10)(11) == 11, "");
_Static_assert(ALIAS_IF_ELSE(0)(11)(10) == 10, "");
_Static_assert(ALIAS_IF_ELSE(1)(10)(11) == 10, "");
_Static_assert(ALIAS_IF_ELSE(1)(11)(10) == 11, "");

#define ALIAS__EMPTY()
#define ALIAS__DEFER_1(X) X ALIAS__EMPTY()
#define ALIAS__DEFER_2(X) X ALIAS__EMPTY ALIAS__EMPTY()()

#define ALIAS_MAP(F, ...) ALIAS_EVAL(ALIAS__MAP(F, ## __VA_ARGS__))
#define ALIAS__MAP(F, X, ...) \
  F(X) \
  ALIAS_IF_ELSE(ALIAS_HAS_ARGUMENTS(__VA_ARGS__))( \
    ALIAS__DEFER_2(ALIAS__MAP_)()(F, __VA_ARGS__) \
  )()
#define ALIAS__MAP_() ALIAS__MAP

_Static_assert(0 ALIAS_MAP(_ALAIS__MAP_TEST_1, 1, 2, 3) == 6, "");
#define _ALIAS__MAP_TEST_1(X) +X

#define ALIAS_MAP_A(F, A, ...) ALIAS_EVAL(ALIAS__MAP_A(F, A, ## __VA_ARGS__))
#define ALIAS__MAP_A(F, A, X, ...) \
  F(A, X) \
  ALIAS_IF_ELSE(ALIAS_HAS_ARGUMENTS(__VA_ARGS__))( \
    ALIAS__DEFER_2(ALIAS__MAP_A_)()()(F, A, __VA_ARGS__) \
  )()
#define ALIAS__MAP_A_() ALIAS__MAP_A

#define ALIAS_MAP_P(F, ...) ALIAS_EVAL(ALIAS__MAP_P(F, ## __VA_ARGS__))
#define ALIAS__MAP_P(F, X, ...) \
  F X \
  ALIAS_IF_ELSE(ALIAS_HAS_ARGUMENTS(__VA_ARGS__))( \
    ALIAS__DEFER_2(ALIAS__MAP_P_)()()(F, __VA_ARGS__) \
  )()
#define ALIAS__MAP_P_() ALIAS__MAP_P

#define ALIAS_MAP_C(F, ...) ALIAS_EVAL(ALIAS__MAP_C(F, ## __VA_ARGS__))
#define ALIAS__MAP_C(F, X, ...) \
  ALIAS_CAT(F, X) \
  ALIAS_IF_ELSE(ALIAS_HAS_ARGUMENTS(__VA_ARGS__))( \
    ALIAS__DEFER_2(ALIAS__MAP_C_)()()(F, __VA_ARGS__) \
  )()
#define ALIAS__MAP_C_() ALIAS__MAP_C

#if defined(ALIAS_USE_ALL) || defined(ALAIS_USE_CPP)
#define CAT ALIAS_CAT
#define EVAL ALIAS_EVAL
#define MAP ALIAS_MAP
#define NOT ALIAS_NOT
#define BOOL ALIAS_BOOL
#define MAP ALIAS_MAP
#endif

#endif

#endif
