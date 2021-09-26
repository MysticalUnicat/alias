#ifndef _ALIAS_CPP_OPTION_H_
#define _ALIAS_CPP_OPTION_H_

#include <alias/cpp/cat.h>

// create Some iff X is 1, or else None
#define ALIAS_CPP_Some_IFF(X) ALIAS_CPP_CAT(ALIAS_CPP_Some_IFF_test_, X)
#define ALIAS_CPP_Some_IFF_test_0(...) None()
#define ALIAS_CPP_Some_IFF_test_1(...) Some(__VA_ARGS__)

// tell us if this is an option! can take any identifier or number-pp token
#define ALIAS_CPP_IS_OPTION(OPTION) ALIAS_CPP_IS_PROBE(ALIAS_CPP_CAT(ALIAS_IS_OPTION_, OPTION))
#define ALIAS_CPP_IS_OPTION_Some(...) ALIAS_CPP_PROBE()
#define ALIAS_CPP_IS_OPTION_None(...) ALIAS_CPP_PROBE()

// the Option's type None or Some
#define ALIAS_CPP_OPTION_TYPE(OPTION) ALIAS_CPP_CAT(ALIAS_CPP_OPTION_TYPE_, OPTION)
#define ALIAS_CPP_OPTION_TYPE_Some(...) Some
#define ALIAS_CPP_OPTION_TYPE_None(...) None

// same as ALIAS_OPTION_TYPE but returns 1/0
#define ALIAS_CPP_OPTION_IS_SOME(OPTION) ALIAS_CPP_CAT(ALIAS_CPP_OPTION_IS_SOME_, OPTION)
#define ALIAS_CPP_OPTION_IS_SOME_Some(...) 1
#define ALIAS_CPP_OPTION_IS_SOME_None(...) 0

#define ALIAS_CPP_OPTION_IS_NONE(OPTION) ALIAS_CPP_BNOT(ALIAS_CPP_OPTION_IS_SOME(OPTION))

// the Option's value as a parameter list.
// None always outputs ~ to cause syntax errors if the value is ever attempted to be emitted
#define ALIAS_CPP_OPTION_VALUE(OPTION) ALIAS_CPP_CAT(ALIAS_CPP_OPTION_VALUE_, OPTION)
#define ALIAS_CPP_OPTION_VALUE_Some(...) ( __VA_ARGS__ )
#define ALIAS_CPP_OPTION_VALUE_None(...) ~

// Simple map operation for option
#define ALIAS_CPP_OPTION_MAP(OPTION, F)      \
  ALIAS_CPP_IFF(                             \
    ALIAS_CPP_OPTION_IS_SOME(OPTION)         \
  )(                                     \
      Some(F ALIAS_CPP_OPTION_VALUE(OPTION)) \
    , None()                             \
  )

// unwrap an option, with a defualt value for None()
#define ALIAS_CPP_OPTION_UNWRAP(OPTION, DEFAULT) \
  ALIAS_CPP_IFF( \
    ALIAS_CPP_OPTION_IS_SOME(OPTION) \
  )( \
      ALIAS_CPP_EVAL ALIAS_CPP_OPTION_VALUE(OPTION) \
    , DEFAULT \
  )

#endif
