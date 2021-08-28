#ifndef _ALIAS_CPP_H_
#define _ALIAS_CPP_H_

#define ALIAS_EVAL_2(...) __VA_ARGS__
#define ALIAS_EVAL_1(...) ALIAS_EVAL_2(ALIAS_EVAL_2(ALIAS_EVAL_2(ALIAS_EVAL_2(__VA_ARGS__))))
#define ALIAS_EVAL_0(...) ALIAS_EVAL_1(ALIAS_EVAL_1(ALIAS_EVAL_1(ALIAS_EVAL_1(__VA_ARGS__))))
#define ALIAS_EVAL ALIAS_EVAL_0

#define ALIAS_ALL(...) __VA_ARGS__
#define ALIAS_NONE(...)

#define ALIAS_PRIMITIVE_CAT(X, ...) X ## __VA_ARGS__

#define ALIAS_CAT(X, ...) ALIAS_PRIMITIVE_CAT(X, __VA_ARGS__)
#define ALIAS_CAT_ID() ALIAS_CAT

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

#define ALIAS__PROBE(...) ~, 1
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

#define ALIAS_IS_BEGIN_PAREN(X) ALIAS__IS_BEGIN_PAREN_(ALIAS__IS_BEGIN_PAREN_test_ X)
#define ALIAS__IS_BEGIN_PAREN_(X) ALIAS__IS_PROBE(X())
#define ALIAS__IS_BEGIN_PAREN_test_(...) ALIAS__PROBE

#define ALIAS__EMPTY()
#define ALIAS__DEFER_1(X) X ALIAS__EMPTY()
#define ALIAS__DEFER_2(X) X ALIAS__EMPTY ALIAS__EMPTY()()
#define ALIAS__DEFER_3(X) X ALIAS__EMPTY ALIAS__EMPTY ALIAS__EMPTY()()()

#define ALIAS_MAP(F, X, ...) \
  F(X) \
  ALIAS_IFF( \
    ALIAS_OPTION_IS_SOME(ALIAS_FIRST(__VA_ARGS__)) \
  )( \
      ALIAS__DEFER_2(ALIAS_MAP_ID)()(F, __VA_ARGS__) \
    , /* do nothing */ \
  )
#define ALIAS_MAP_ID() ALIAS_MAP

#endif
