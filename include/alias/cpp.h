#ifndef _ALIAS_CPP_H_
#define _ALIAS_CPP_H_

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
#define ALIAS_EVAL ALIAS__EVAL_0

#define ALIAS__CAT_1(X, Y) X ## Y
#define ALIAS__CAT_0(X, Y) ALIAS__CAT_1(X, Y)
#define ALIAS_CAT(X, Y) ALIAS__CAT_0(X, Y)

#define ALIAS__CAT3_1(A, B, C) A ## B ## C
#define ALIAS__CAT3_0(A, B, C) ALIAS__CAT3_1(A, B, C)
#define ALIAS_CAT3(A, B, C) ALIAS__CAT3_0(A, B, C)

#define ALIAS__PROBE() ~, 1
#define ALIAS__IS_PROBE(...) ALIAS__SECOND(__VA_ARGS__, 0, 0)

#define ALIAS_NOT(X) ALIAS__IS_PROBE(ALIAS_CAT(ALIAS__NOT_, X))
#define ALIAS__NOT_0 ALIAS__PROBE()

#define ALIAS_BOOL(X) ALIAS_NOT(ALIAS_NOT(X))

#define ALIAS_AND(X, Y) ALIAS_NOT(ALIAS_CAT3( ALIAS__AND_test_, ALIAS_BOOL(X), ALIAS_BOOL(Y) ))
#define ALIAS__AND_test_11 0

#define ALIAS_OR(X, Y) ALIAS_NOT(ALIAS_CAT3( ALIAS__OR_test_, ALIAS_BOOL(X), ALIAS_BOOL(Y) ))
#define ALIAS__OR_test_11 0
#define ALIAS__OR_test_10 0
#define ALIAS__OR_test_01 0

#define ALIAS_HAS_ARGUMENTS(...) ALIAS_BOOL(ALIAS_CAT3(ALIAS_, __VA_ARGS__, _LIT_ZERO)())

#define ALIAS_IF_ELSE(COND) ALIAS__IF_ELSE(ALIAS_BOOL(COND))
#define ALIAS__IF_ELSE(COND) ALIAS_CAT(ALIAS__IF_ELSE_, COND)
#define ALIAS__IF_ELSE_1(...) __VA_ARGS__ ALIAS__CONSUME_ARGUMENTS
#define ALIAS__IF_ELSE_0(...)             ALIAS__EMIT_ARGUMENTS

#define ALIAS__EMPTY()
#define ALIAS__DEFER_1(X) X ALIAS__EMPTY()
#define ALIAS__DEFER_2(X) X ALIAS__EMPTY ALIAS__EMPTY()()

#define ALIAS_MAP(F, ...) ALIAS_EVAL(ALIAS__MAP(F, ## __VA_ARGS__))
#define ALIAS__MAP(F, X, ...) \
  F(X) \
  ALIAS_IF_ELSE(ALIAS_HAS_ARGUMENTS(__VA_ARGS__))( \
    ALIAS__DEFER_2(ALIAS__MAP_)()()(F, __VA_ARGS__) \
  )()
#define ALIAS__MAP_() ALIAS__MAP

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
