#ifndef _ALIAS_ASH_H_
#define _ALIAS_ASH_H_

#include <alias/data_structure/vector.h>

#ifndef ALIAS_ASH_RSTACK_SIZE
#define ALIAS_ASH_RSTACK_SIZE 256
#endif

#ifndef ALIAS_ASH_DSTACK_SIZE
#define ALIAS_ASH_DSTACK_SIZE 256
#endif

// ASH Alias Script Holograph is used internally to unravel some complexity
// It is very FORTH influenced, as programs are designed to be be fast to generate and fast-enough to execute once and thrown away

// forward declaration
typedef struct alias_ash alias_ash;

typedef void (* alias_ash_CFunction)(alias_ash * ash);

typedef enum alias_ash_Op {
    alias_ash_Op_end

  // values on the stack are always 32-bit
  , alias_ash_Op_i      // (read 32-bit value) -- i

  // d-stack manipulation
  , alias_ash_Op_pick   // a0..an n -- a0..an a0
  , alias_ash_Op_roll   // a0..an n -- a1..an a0
  , alias_ash_Op_dup    // a        -- a a     (replacement: 0 pick)
  , alias_ash_Op_q_dup  // a        -- 0 | a a
  , alias_ash_Op_drop   // a        --
  , alias_ash_Op_swap   // a b      -- b a     (replacement: 1 roll)
  , alias_ash_Op_over   // a b      -- a b a   (replacement: 1 pick)
  , alias_ash_Op_rot    // a b c    -- b c a   (replacement: 2 roll)
  , alias_ash_Op_irot   // a b c    -- c a b   (replacement: rot rot)
  , alias_ash_Op_nip    // a b      -- b       (replacement: swap drop)
  , alias_ash_Op_tuck   // a b      -- b a b   (replacement: swap over)
  , alias_ash_Op_drop2  // a b      --         (replacement: drop drop)
  , alias_ash_Op_dup2   // a b      -- a b a b (replacement: over over)
  , alias_ash_Op_over2  // a b c d  -- a b c d a b
  , alias_ash_Op_swap2  // a b c d  -- c d a b

  // r-stack manipulation
  , alias_ash_Op_r_push // a    -- R: a
  , alias_ash_Op_r_pop  // R: a -- a
  , alias_ash_Op_r_at   // R: a -- a R: a

  // control flow
  , alias_ash_Op_jump   // a    -- IP=a
  , alias_ash_Op_jump_z // a b  -- IP=b if a==0
  , alias_ash_Op_call   // a    -- R: IP, IP=a
  , alias_ash_Op_ret    // R: a -- IP=a
  , alias_ash_Op_cfun   // reads a alias_ash_CFunction pointer from code and execute it

  // integer
  , alias_ash_Op_i_add  // a a -- a
  , alias_ash_Op_i_sub  // a a -- a
  , alias_ash_Op_i_neg  // a   -- a
  , alias_ash_Op_i_mul  // a a -- a
  , alias_ash_Op_i_div  // a a -- a
  , alias_ash_Op_i_min  // a a -- a
  , alias_ash_Op_i_max  // a a -- a

  // bit
  , alias_ash_Op_b_and  // a a -- a
  , alias_ash_Op_b_or   // a a -- a
  , alias_ash_Op_b_xor  // a a -- a

  // float
  , alias_ash_Op_f_add  // a a -- a
  , alias_ash_Op_f_sub  // a a -- a
  , alias_ash_Op_f_neg  // a   -- a
  , alias_ash_Op_f_mul  // a a -- a
  , alias_ash_Op_f_div  // a a -- a
  , alias_ash_Op_f_min  // a a -- a
  , alias_ash_Op_f_max  // a a -- a
  , alias_ash_Op_f_cmp  // a a -- a (-, 0, +)
} alias_ash_Op;

typedef struct alias_ash_Word {
  const char * name;
  alias_ash_CFunction cfun;
  bool hidden;
  uint32_t hole;
  uint32_t ip;
} alias_ash_Word;

// every program can come preloaded with a library, can get reset to that state and rerecorded if needed
typedef struct alias_ash_Program {
  alias_Vector(alias_ash_Word) words;
  alias_Vector(uint8_t) instructions;
  uint32_t library_end_word;
  uint32_t library_end_instruction;
} alias_ash_Program;

void alias_ash_Program_initialize(alias_ash_Program * p);
void alias_ash_Program_free(alias_ash_Program * p, alias_MemoryCB * mcb);

void alias_ash_Program_begin_library(alias_ash_Program * p, alias_MemoryCB * mcb);
void alias_ash_Program_end_library(alias_ash_Program * p);

void alias_ash_Program_begin_shader(alias_ash_Program * p, alias_MemoryCB * mcb);
bool alias_ash_Program_end_shader(alias_ash_Program * p, alias_MemoryCB * mcb);

bool alias_ash_Program_define_cfun(alias_ash_Program * p, alias_MemoryCB * mcb, const char * name, alias_ash_CFunction cfun);

bool alias_ash_Program_begin_word(alias_ash_Program * p, alias_MemoryCB * mcb, const char * name);
bool alias_ash_Program_end_word(alias_ash_Program * p, alias_MemoryCB * mcb);

bool alias_ash_Program_begin_quotation(alias_ash_Program * p, alias_MemoryCB * mcb);
bool alias_ash_Program_end_quotation(alias_ash_Program * p, alias_MemoryCB * mcb);

bool alias_ash_Program_emit_call(alias_ash_Program * p, alias_MemoryCB * mcb, const char * name);
bool alias_ash_Program_emit_op(alias_ash_Program * p, alias_MemoryCB * mcb, alias_ash_Op op);
bool alias_ash_Program_emit_i(alias_ash_Program * p, alias_MemoryCB * mcb, uint32_t i);
bool alias_ash_Program_emit_f(alias_ash_Program * p, alias_MemoryCB * mcb, float f);

struct alias_ash {
  const uint8_t * cs;
  uint32_t cs_size;
  uint32_t ip;

  uint32_t rs[ALIAS_ASH_RSTACK_SIZE];
  uint32_t rp;

  uint32_t ds[ALIAS_ASH_DSTACK_SIZE];
  uint32_t dp;

  void * user_data;
};

static inline void alias_ash_push(alias_ash * ash, uint32_t i) {
  ash->ds[ash->dp++] = i;
}

static inline void alias_ash_push_R(alias_ash * ash, float f) {
  ash->ds[ash->dp++] = *(uint32_t *)&f;
}

static inline uint32_t alias_ash_pop(alias_ash * ash) {
  return ash->ds[--ash->dp];
}

static inline float alias_ash_pop_R(alias_ash * ash) {
  return *(float *)&ash->ds[--ash->dp];
}

static inline void alias_ash_push_r(alias_ash * ash, uint32_t i) {
  ash->rs[ash->rp++] = i;
}

static inline uint32_t alias_ash_pop_r(alias_ash * ash) {
  return ash->rs[--ash->rp];
}

void alias_ash_initialize(alias_ash * ash, alias_ash_Program * program);

bool alias_ash_step(alias_ash * ash);

#if defined(_ALIAS_CPP_H_)
#define ALIAS_ASH_IS_OP(X) ALIAS_CPP_IS_PROBE(ALIAS_CPP_CAT(ALIAS_ASH_IS_OP_, X)())
#define ALIAS_ASH_IS_OP_pick   ALIAS_CPP_PROBE 
#define ALIAS_ASH_IS_OP_roll   ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_dup    ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_q_dup  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_drop   ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_swap   ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_over   ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_rot    ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_irot   ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_nip    ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_tuck   ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_drop2  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_dup2   ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_over2  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_swap2  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_r_push ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_r_pop  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_r_at   ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_jump   ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_jump_z ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_call   ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_ret    ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_cfun   ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_i_add  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_i_sub  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_i_neg  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_i_mul  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_i_div  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_i_min  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_i_max  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_b_and  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_b_or   ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_b_xor  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_f_add  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_f_sub  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_f_neg  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_f_mul  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_f_div  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_f_min  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_f_max  ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_OP_f_cmp  ALIAS_CPP_PROBE

#define ALIAS_ASH_IS_SPECIAL(X) ALIAS_CPP_IS_PROBE(ALIAS_CPP_CAT(ALIAS_ASH_IS_SPECIAL_, X)())
#define ALIAS_ASH_IS_SPECIAL_fn(...) ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_SPECIAL_i(...) ALIAS_CPP_PROBE
#define ALIAS_ASH_IS_SPECIAL_f(...) ALIAS_CPP_PROBE

#define ALIAS_ASH_EMIT(P, M, ...) \
  do { \
    alias_ash_Program * ALIAS_ASH_EMIT_P = (P); \
    alias_MemoryCB * ALIAS_ASH_EMIT_M = (M); \
    (void)(true ALIAS_CPP_EVAL(ALIAS_ASH_EMIT_map(__VA_ARGS__))); \
  } while(0)

#define ALIAS_ASH_EMIT_map_id() ALIAS_ASH_EMIT_map
#define ALIAS_ASH_EMIT_map(...) ALIAS_CPP_MAP(ALIAS_ASH_EMIT_item, __VA_ARGS__)

#define ALIAS_ASH_EMIT_item(X) ALIAS_ASH_EMIT_maybe_quotation(X)

#define ALIAS_ASH_EMIT_maybe_quotation(X) \
  ALIAS_CPP_IFF(ALIAS_CPP_IS_BEGIN_PAREN(X))(ALIAS_ASH_EMIT_quotation_id, ALIAS_ASH_EMIT_maybe_op_id)()(X)

#define ALIAS_ASH_EMIT_quotation_id() ALIAS_ASH_EMIT_quotation
#define ALIAS_ASH_EMIT_quotation(X) \
  && alias_ash_Program_begin_quotation(ALIAS_ASH_EMIT_P, ALIAS_ASH_EMIT_M) \
  ALIAS_CPP_DEFER_2(ALIAS_ASH_EMIT_map_id)()X \
  && alias_ash_Program_end_quotation(ALIAS_ASH_EMIT_P, ALIAS_ASH_EMIT_M)

#define ALIAS_ASH_EMIT_maybe_op_id() ALIAS_ASH_EMIT_maybe_op
#define ALIAS_ASH_EMIT_maybe_op(X) \
  ALIAS_CPP_IFF(ALIAS_ASH_IS_OP(X))(ALIAS_ASH_EMIT_op_id, ALIAS_ASH_EMIT_maybe_special_id)()(X)

#define ALIAS_ASH_EMIT_op_id() ALIAS_ASH_EMIT_op
#define ALIAS_ASH_EMIT_op(X) && alias_ash_Program_emit_op(ALIAS_ASH_EMIT_P, ALIAS_ASH_EMIT_M, alias_ash_Op_ ## X)

#define ALIAS_ASH_EMIT_maybe_special_id() ALIAS_ASH_EMIT_maybe_special
#define ALIAS_ASH_EMIT_maybe_special(X) \
  ALIAS_CPP_IFF(ALIAS_ASH_IS_SPECIAL(X))(ALIAS_ASH_EMIT_special_id, ALIAS_ASH_EMIT_call_id)()(X)

#define ALIAS_ASH_EMIT_special_id() ALIAS_ASH_EMIT_special
#define ALIAS_ASH_EMIT_special(X) ALIAS_CPP_CAT(ALIAS_ASH_EMIT_special_, X)
#define ALIAS_ASH_EMIT_special_fn(NAME, ...) \
  && alias_ash_Program_begin_word(ALIAS_ASH_EMIT_P, ALIAS_ASH_EMIT_M, #NAME) \
  ALIAS_CPP_DEFER_2(ALIAS_ASH_EMIT_map_id)()(__VA_ARGS__) \
  && alias_ash_Program_end_word(ALIAS_ASH_EMIT_P, ALIAS_ASH_EMIT_M)
#define ALIAS_ASH_EMIT_special_i(X) && alias_ash_Program_emit_i(ALIAS_ASH_EMIT_P, ALIAS_ASH_EMIT_M, X)
#define ALIAS_ASH_EMIT_special_f(X) && alias_ash_Program_emit_f(ALIAS_ASH_EMIT_P, ALIAS_ASH_EMIT_M, X)

#define ALIAS_ASH_EMIT_call_id() ALIAS_ASH_EMIT_call
#define ALIAS_ASH_EMIT_call(X) && alias_ash_Program_emit_call(ALIAS_ASH_EMIT_P, ALIAS_ASH_EMIT_M, #X)
#endif

#endif
