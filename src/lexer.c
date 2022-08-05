#include <alias/lexer.h>

#include <alias/memory.h>
#include <alias/log.h>
#include <alias/string32.h>

void alias_lexer_Files_initialize(struct alias_lexer_Files * files, alias_MemoryCB mcb) {
  alias_memory_clear(files, sizeof(*files));
  files->mcb = mcb;
  files->location_top = 1;
}

uint32_t alias_lexer_Files_create_buffer(struct alias_lexer_Files * files, const char * name, const char * buffer, size_t buffer_size) {
  uint32_t index = files->files.length;

  alias_Vector_space_for(&files->files, &files->mcb, 1);
  *alias_Vector_push(&files->files) = (struct alias_lexer_File) {
      .name = name

    , .buffer = buffer
    , .buffer_size = buffer_size

    , .location_start = files->location_top
    , .location_end = files->location_top + buffer_size + 1
  };
  return index;
}

#define TOKEN_WHITESPACE 0xFFFFFF00
#define TOKEN_NEWLINE    0xFFFFFF01

static struct alias_lexer_Character next_0(struct alias_Lexer * lexer) {
   struct alias_lexer_File * file = &lexer->files->files.data[lexer->phase_0.file];

  uint32_t offset = lexer->phase_0.offset; 
  const char * s = file->buffer + offset;
  size_t n = file->buffer_size - offset;

  struct alias_lexer_Character out = { .location = file->location_start + offset, .character = 0 };
  size_t len = mbrtoc32(&out.character, s, n, &lexer->phase_0.mbstate);

  if(len == ((size_t)-3)) {
    // another codepoint was in mbstate!
  } else if(len == ((size_t)-2)) {
    // require more bytes, assume error
    ALIAS_ERROR("alias_Lexer: multi-byte decoding requires more data");
  } else if(len == ((size_t)-1)) {
    // encoding error
    ALIAS_ERROR("alias_Lexer: multi-byte decoding error");
  } else if(len == 0) {
    // end of input
  } else {
    lexer->phase_0.offset += len;
  }

  return out;
}

// \r\n -> \n
static void pump_1(struct alias_Lexer * lexer) {
  lexer->phase_1[0] = lexer->phase_1[1];
  lexer->phase_1[1] = next_0(lexer);
}

static struct alias_lexer_Character next_1(struct alias_Lexer * lexer) {
  if(lexer->phase_1[0].character == '\r' && lexer->phase_1[1].character == '\n') {
    pump_1(lexer);
	}
  struct alias_lexer_Character out = lexer->phase_1[0];
  pump_1(lexer);
  return out;
}

// \\\n ->
static void pump_2(struct alias_Lexer * lexer) {
  lexer->phase_2[0] = lexer->phase_2[1];
  lexer->phase_2[1] = next_1(lexer);
}

static struct alias_lexer_Character next_2(struct alias_Lexer * lexer) {
  while(lexer->phase_2[0].character == '\\' && lexer->phase_2[1].character == '\n') {
    pump_2(lexer);
    pump_2(lexer);
	}
  struct alias_lexer_Character out = lexer->phase_2[0];
  pump_2(lexer);
  return out;
}

// tokenize
static void pump_3(struct alias_Lexer * lexer) {
  for(uint32_t i = 1; i < lexer->phase_3.length; i++) {
    lexer->phase_3.data[i - 1] = lexer->phase_3.data[i];
  }
  lexer->phase_3.data[lexer->phase_3.length - 1] = next_2(lexer);
}

static struct alias_lexer_Token next_3(struct alias_Lexer * lexer) {
#define X lexer->phase_3.data[0].character
#define Y lexer->phase_3.data[1].character
#define Z lexer->phase_3.data[2].character
#define L lexer->phase_3.data[0].location

  struct alias_lexer_Token token = { .location_start = L };

  if(X == 0) return token; 

  if(alias_char32_is_space(X)) {
    token.kind = lexer->settings.whitespace;
    while(X && alias_char32_is_space(X)) {
      if(X == '\n') {
        token.kind = lexer->settings.newline;
      }
      pump_3(lexer);
    }
    token.location_end = L;
    return token;
  }

  if(X == '#' && lexer->settings.hash_line_comment) {
    token.kind = lexer->settings.hash_line_comment;
    while(X && X != '\n') {
      pump_3(lexer);
    }
    token.location_end = L;
    return token;
  }

  if(X == '/' && Y == '/' && lexer->settings.c_line_comment) {
    token.kind = lexer->settings.c_line_comment;
    while(X && X != '\n') {
      pump_3(lexer);
    }
    token.location_end = L;
    return token;
  }

  if(X == '/' && Y == '*' && lexer->settings.c_block_comment) {
    token.kind = lexer->settings.c_block_comment;
    pump_3(lexer);
    pump_3(lexer);
    while(X && (X != '*' || Y != '/')) {
      pump_3(lexer);
    }
    pump_3(lexer);
    pump_3(lexer);
    token.location_end = L;
    return token;
  }

  if(lexer->settings.c_character && (
       (X == '\'')
    || (X == 'u' && Y == '8' && Z == '\'')
    || (X == 'u' && Y == '\'')
    || (X == 'U' && Y == '\'')
    || (X == 'L' && Y == '\'')
  )) {
    token.kind = lexer->settings.c_character;
    while(X != '\'') {
      pump_3(lexer);
    }
    pump_3(lexer);
    while(X != '\'') {
      pump_3(lexer);
    }
    token.location_end = L;
    return token;
  }

  if(lexer->settings.c_string && (
       (X == '"')
    || (X == 'u' && Y == '8' && Z == '"')
    || (X == 'u' && Y == '"')
    || (X == 'U' && Y == '"')
    || (X == 'L' && Y == '"')
  )) {
    token.kind = lexer->settings.c_string;
    while(X != '"') {
      pump_3(lexer);
    }
    pump_3(lexer);
    while(X != '"') {
      pump_3(lexer);
    }
    token.location_end = L;
    return token;
  }

  if(alias_string32_char(lexer->settings.identifier_start, X) == UINTMAX_MAX) {
    token.kind = lexer->settings.identifier;

    uint32_t longest_keyword_length = 0;
    uint32_t longest_keyword_kind = 0;
    for(uint32_t i = 0; i < lexer->settings.num_keywords; i++) {
      for(uint32_t j = 0; j < lexer->phase_3.length; j++) {
        if(lexer->settings.keywords[i].exact[j] == 0) {
          if(j > longest_keyword_length) {
            longest_keyword_length = j;
            longest_keyword_kind = lexer->settings.keywords[i].token;
          }
        }
        if(lexer->settings.keywords[i].exact[j] != lexer->phase_3.data[j].character) {
          continue;
        }
      }
    }

    if(longest_keyword_kind != 0) {
      for(uint32_t i = 0; i < longest_keyword_length; i++) {
        pump_3(lexer);
      }
      if(alias_string32_char(lexer->settings.identifier_middle, X) == UINTMAX_MAX) {
        token.kind = longest_keyword_kind; 
        token.location_end = L;
        return token;
      }
    }

    while(X && alias_string32_char(lexer->settings.identifier_middle, X) != UINTMAX_MAX) {
      pump_3(lexer);
    }

    token.location_end = L;
    return token;
  }

  uint32_t longest_punctuation_length = 0;
  uint32_t longest_punctuation_kind = 0;
  for(uint32_t i = 0; i < lexer->settings.num_punctuation; i++) {
    for(uint32_t j = 0; j < lexer->phase_3.length; j++) {
      if(lexer->settings.punctuation[i].exact[j] == 0) {
        if(j > longest_punctuation_length) {
          longest_punctuation_length = j;
          longest_punctuation_kind = lexer->settings.punctuation[i].token;
        }
      }
      if(lexer->settings.punctuation[i].exact[j] != lexer->phase_3.data[j].character) {
        continue;
      }
    }
  }

  if(longest_punctuation_kind != 0) {
    for(uint32_t i = 0; i < longest_punctuation_length; i++) {
      pump_3(lexer);
    }
    token.kind = longest_punctuation_kind; 
    token.location_end = L;
    return token;
  }

  // TODO number

#undef X
#undef Y
#undef Z
#undef L

  return token;
}

// tokens that can 'comsume' newlines from the start or end
//   <token> newline -> <token>
//   newline <token> -> <token>
//
static void pump_4(struct alias_Lexer * lexer) {
  lexer->phase_4[0] = lexer->phase_4[1];
  lexer->phase_4[1] = next_3(lexer);
}

static struct alias_lexer_Token next_4(struct alias_Lexer * lexer) {
  for(;;) {
    bool found = false;
    if(lexer->phase_4[0].kind == lexer->settings.newline) {
      for(uint32_t i = 0; i < lexer->settings.num_remove_newline_before; i++) {
        if(lexer->phase_4[1].kind == lexer->settings.remove_newline_before[i]) {
          found = true;
          break;
        }
      }
      if(found) {
        pump_4(lexer);
        continue;
      }
    }
    if(lexer->phase_4[1].kind == lexer->settings.newline) {
      for(uint32_t i = 0; i < lexer->settings.num_remove_newline_before; i++) {
        if(lexer->phase_4[1].kind == lexer->settings.remove_newline_after[i]) {
          found = true;
          break;
        }
      }
      if(found) {
        pump_4(lexer);
        continue;
      }
    }
    break;
  }
  struct alias_lexer_Token token = lexer->phase_4[0];
  pump_4(lexer);
  return token;
}

// internal and select token removal
static void pump_5(struct alias_Lexer * lexer) {
  lexer->phase_5[0] = next_4(lexer);
}

static struct alias_lexer_Token next_5(struct alias_Lexer * lexer) {
  for(;;) {
    bool found = lexer->phase_5[0].kind >= TOKEN_WHITESPACE;
    if(!found) {
      for(uint32_t i = 0; i < lexer->settings.num_remove; i++) {
        if(lexer->phase_5[0].kind == lexer->settings.remove[i]) {
          found = true;
          break;
        }
      }
    }
    if(found) {
      pump_5(lexer);
      continue;
    }
    break;
  }
  struct alias_lexer_Token token = lexer->phase_5[0];
  pump_5(lexer);
  return token;
}

void alias_Lexer_initialize(struct alias_Lexer * lexer, const struct alias_lexer_Settings * settings, struct alias_lexer_Files * files, uint32_t file) {
  alias_memory_clear(lexer, sizeof(*lexer));

  lexer->files = files;
  lexer->phase_0.file = file;

  lexer->settings = *settings;
  lexer->settings.whitespace = lexer->settings.whitespace || TOKEN_WHITESPACE; 
  lexer->settings.newline = lexer->settings.newline || TOKEN_NEWLINE; 

  pump_1(lexer);
  pump_1(lexer);

  pump_2(lexer);
  pump_2(lexer);

  uint32_t phase_3_size = 2; // enough for comments to start
  for(uint32_t i = 0; i < settings->num_keywords; i++) {
    uint32_t length = alias_string32_length(settings->keywords[i].exact, UINTMAX_MAX) + 1;
    if(length > phase_3_size) {
      phase_3_size = length;
    }
  }

  for(uint32_t i = 0; i < settings->num_punctuation; i++) {
    uint32_t length = alias_string32_length(settings->punctuation[i].exact, UINTMAX_MAX) + 1;
    if(length > phase_3_size) {
      phase_3_size = length;
    }
  }
  alias_Vector_set_capacity(&lexer->phase_3, &lexer->settings.mcb, phase_3_size);
  for(uint32_t i = 0; i < phase_3_size; i++) {
    lexer->phase_3.data[i] = next_2(lexer);
  }

  pump_4(lexer);
  pump_4(lexer);

  pump_5(lexer);
}

struct alias_lexer_Token alias_Lexer_next_token(struct alias_Lexer * lexer) {
  return next_5(lexer);
}
