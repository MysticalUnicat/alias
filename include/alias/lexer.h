// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_LEXER_H_
#define _ALIAS_LEXER_H_

#include <tabula.h>

#include <alias/data_structure/vector.h>
#include <alias/utils.h>
struct alias_lexer_Character {
  char32_t character;
  uint32_t location;
};

struct alias_lexer_Token {
  uint32_t kind;
  uint32_t location_start;
  uint32_t location_end;
};

struct alias_lexer_File {
  const char * name;

  const char * buffer;
  uint32_t   buffer_size;

  uint32_t location_start;
  uint32_t location_end;

  alias_Vector(uint32_t) newline_locations;
};

struct alias_lexer_Files {
  alias_MemoryCB mcb;
  alias_Vector(struct alias_lexer_File) files;
  uint32_t location_top;
};

void alias_lexer_Files_initialize(struct alias_lexer_Files * files, alias_MemoryCB mcb);
uint32_t alias_lexer_Files_create_buffer(struct alias_lexer_Files * files, const char * name, const char * buffer, size_t buffer_size);

struct alias_lexer_SetMatch {
  const char32_t * start;
  const char32_t * middle;
  const char32_t * end;
  uint32_t token;
};

struct alias_lexer_ExactMatch {
  const char32_t * exact;
  uint32_t token;
};

struct alias_lexer_Settings {
  alias_MemoryCB mcb;

  bool newline_splicing;

  uint32_t whitespace;
  uint32_t newline;
  uint32_t hash_line_comment;
  uint32_t c_line_comment;
  uint32_t c_block_comment;
  uint32_t c_character;
  uint32_t c_string;

  const char32_t * identifier_start;
  const char32_t * identifier_middle;
  uint32_t identifier;

  uint32_t                      num_keywords;
  struct alias_lexer_ExactMatch * keywords;

  uint32_t                      num_punctuation;
  struct alias_lexer_ExactMatch * punctuation;

  uint32_t num_remove_newline_before;
  uint32_t * remove_newline_before;

  uint32_t num_remove_newline_after;
  uint32_t * remove_newline_after;
  
  uint32_t num_remove;
  uint32_t * remove;
};

struct alias_Lexer {
  struct alias_lexer_Settings settings;
  struct alias_lexer_Files * files;

  // source character decoding
  struct {
    uint32_t file;
    mbstate_t mbstate;
    uint32_t offset;
  } phase_0;

  // newline source normalization
  struct alias_lexer_Character phase_1[2];  

  // newline splicing
  struct alias_lexer_Character phase_2[2];

  // tokenize
  alias_Vector(struct alias_lexer_Character) phase_3;
  
  // <some token> NEWLINE → <some token>
  // NEWLINE <some token> → <some token>
  struct alias_lexer_Token phase_4[2];

  // <some token> ->
  // <internal token> ->
  struct alias_lexer_Token phase_5[1];
};

void alias_Lexer_initialize(struct alias_Lexer * lexer, const struct alias_lexer_Settings * settings, struct alias_lexer_Files * files, uint32_t file);
struct alias_lexer_Token alias_Lexer_next_token(struct alias_Lexer * lexer);

#endif
