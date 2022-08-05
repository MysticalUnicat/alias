// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "local.h"

#include <alias/lexer.h>

#include <string.h>

#define C_KEYWORDS(X) \
	X(auto) \
	X(break) \
	X(case) \
	X(char) \
  X(const) \
  X(continue) \
  X(default) \
  X(do) \
  X(double) \
  X(else) \
  X(enum) \
  X(extern) \
  X(float) \
  X(for) \
  X(goto) \
  X(if) \
  X(inline) \
  X(int) \
  X(long) \
  X(register) \
  X(restrict) \
  X(return) \
  X(short) \
  X(signed) \
  X(sizeof) \
  X(static) \
  X(struct) \
  X(switch) \
  X(typedef) \
  X(union) \
  X(unsigned) \
  X(void) \
  X(volatile) \
  X(while) \
  X(_Alignas) \
  X(_Alignof) \
  X(_Atomic) \
  X(_Bool) \
  X(_Complex) \
  X(_Generic) \
  X(_Imaginary) \
  X(_Noreturn) \
  X(_Static_assert) \
  X(_Thread_local)

#define C_PUNCT(X) \
	X(U"["  , LeftSquareBracket) \
	X(U"]"  , RightSquareBracket) \
	X(U"("  , LeftParentheses) \
	X(U")"  , RightParentheses) \
	X(U"{"  , LeftCurlyBracket) \
	X(U"."  , Period) \
	X(U"->" , RightArrow) \
	X(U"++" , Increment) \
	X(U"--" , Decrement) \
	X(U"&"  , BinaryAnd) \
	X(U"*"  , Multiply) \
	X(U"+"  , Add) \
	X(U"-"  , Subtract) \
	X(U"~"  , BinaryNot) \
	X(U"!"  , LogicalNot) \
	X(U"/"  , Divide) \
	X(U"%"  , Modulo) \
	X(U"<<" , LeftShift) \
	X(U">>" , RightShift) \
	X(U"<"  , LessThan) \
	X(U">"  , GreaterThan) \
	X(U"<=" , LessThanEqualTo) \
	X(U">=" , GreaterThanEqualTo) \
	X(U"==" , EqualTo) \
	X(U"!=" , NotEqualTo) \
	X(U"^"  , BinaryXor) \
	X(U"|"  , BinaryOr) \
	X(U"&&" , LogicalAnd) \
	X(U"||" , LogicalOr) \
	X(U"?"  , QuestionMark) \
	X(U":"  , Colon) \
	X(U";"  , Semicolon) \
	X(U"...", ThreeDots) \
	X(U"="  , Assign) \
	X(U"*=" , MultiplyAssign) \
	X(U"/=" , DivideAssign) \
	X(U"%=" , ModuloAssign) \
	X(U"+=" , AddAssign) \
	X(U"-=" , SubtractAssign) \
	X(U"<<=", LeftShiftAssign) \
	X(U">>=", RightShiftAssign) \
	X(U"&=" , BinaryAndAssign) \
	X(U"^=" , BinaryXorAssign) \
	X(U"|=" , BinaryOrAssign) \
	X(U","  , Comma) \
	X(U"#"  , Hash) \
	X(U"##" , HashHash)

enum TokenC {
    TokenC_LineComment = 1
  , TokenC_BlockComment
  , TokenC_Character
  , TokenC_String
  , TokenC_Identifier

  #define KEYWORD(X) , TokenC_ ## X
  C_KEYWORDS(KEYWORD) 
  #undef KEYWORD

  #define PUNCT(X, Y) , TokenC_ ## Y
  C_PUNCT(PUNCT) 
  #undef PUNCT
};

TEST(lexer, "Alias Lexer - C") {
  #define KEYWORD(X) { U ## #X , TokenC_ ## X },
  struct alias_lexer_ExactMatch keywords[] = {
    C_KEYWORDS(KEYWORD) 
  };
  #undef KEYWORD

  #define PUNCT(X, Y) { X , TokenC_ ## Y },
  struct alias_lexer_ExactMatch punctuation[] = {
    C_PUNCT(PUNCT) 
  };
  #undef PUNCT

  const char * str = u8"identifier auto + += >>= >>> 'c' \"str\"";

  struct alias_lexer_Files files;
  alias_lexer_Files_initialize(&files, *alias_default_MemoryCB());

  uint32_t file = alias_lexer_Files_create_buffer(&files, "test", str, strlen(str));

  struct alias_lexer_Settings c_settings = {
      .mcb              = *alias_default_MemoryCB()

    , .newline_splicing = true
    , .c_line_comment   = TokenC_LineComment
    , .c_block_comment  = TokenC_BlockComment
    , .c_character      = TokenC_Character
    , .c_string         = TokenC_String

    , .identifier_start  = U"_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    , .identifier_middle = U"_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    , .identifier        = TokenC_Identifier

    , .num_keywords = sizeof(keywords)/sizeof(keywords[0])
    , .keywords     = keywords

    , .num_punctuation = sizeof(punctuation)/sizeof(punctuation[0])
    , .punctuation     = punctuation
  };

  struct alias_Lexer lexer;
  alias_Lexer_initialize(&lexer, &c_settings, &files, file);

  TEST_EQ(alias_Lexer_next_token(&lexer).kind, TokenC_Identifier,      "expected identifier");
  TEST_EQ(alias_Lexer_next_token(&lexer).kind, TokenC_auto,            "expected keyword auto");
  TEST_EQ(alias_Lexer_next_token(&lexer).kind, TokenC_Add,             "expected punctuation +");
  TEST_EQ(alias_Lexer_next_token(&lexer).kind, TokenC_AddAssign,       "expected punctuation +=");
  TEST_EQ(alias_Lexer_next_token(&lexer).kind, TokenC_LeftShiftAssign, "expected punctuation >>=");
  TEST_EQ(alias_Lexer_next_token(&lexer).kind, TokenC_LeftShift,       "expected punctuation >>");
  TEST_EQ(alias_Lexer_next_token(&lexer).kind, TokenC_GreaterThan,     "expected punctuation >");
}

