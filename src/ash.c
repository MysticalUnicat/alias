// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <alias/ash.h>

#include <alias/log.h>

#define ALIAS_ASH_TRACE_INSTRUCTION 0

void alias_ash_Program_initialize(alias_ash_Program * p) {
  alias_memory_clear(p, sizeof(*p));
}

static inline void _free_word(alias_ash_Program * p, alias_MemoryCB * mcb) {
  if(p->words.length == 0) {
    return;
  }
  alias_ash_Word * word = alias_Vector_pop(&p->words);
  if(word->name != NULL) {
    extern size_t strlen(const char *);
    alias_free(mcb, (void *)word->name, strlen(word->name) + 1, alignof(*word->name));
  }
  alias_memory_clear(word, sizeof(*word));
}

void alias_ash_Program_free(alias_ash_Program * p, alias_MemoryCB * mcb) {
  (void)p;
  (void)mcb;
}

void alias_ash_Program_begin_library(alias_ash_Program * p, alias_MemoryCB * mcb) {
  alias_Vector_clear(&p->instructions);
  while(p->words.length) {
    _free_word(p, mcb);
  }
  alias_Vector_clear(&p->words);
  p->library_end_instruction = 0;
  p->library_end_word = 0;
}

void alias_ash_Program_end_library(alias_ash_Program * p) {
  p->library_end_instruction = p->instructions.length;
  p->library_end_word = p->words.length;
}

void alias_ash_Program_begin_shader(alias_ash_Program * p, alias_MemoryCB * mcb) {
  p->instructions.length = p->library_end_instruction;
  while(p->words.length > p->library_end_word) {
    _free_word(p, mcb);
  }
}

bool alias_ash_Program_end_shader(alias_ash_Program * p, alias_MemoryCB * mcb) {
  return alias_ash_Program_emit_op(p, mcb, alias_ash_Op_end);
}

bool alias_ash_Program_define_cfun(alias_ash_Program * p, alias_MemoryCB * mcb, const char * name, alias_ash_CFunction cfun) {
  extern size_t strlen(const char *);

  if(!alias_Vector_space_for(&p->words, mcb, 1)) {
    return false;
  }
  const char * name_clone = alias_memory_clone(mcb, name, strlen(name) + 1, alignof(*name));
  if(name_clone == NULL) {
    return false;
  }
  alias_ash_Word * word = alias_Vector_push(&p->words);
  word->name = name_clone;
  word->cfun = cfun;
  word->hidden = false;
  word->ip = 0;
  return true;
}

bool alias_ash_Program_begin_word(alias_ash_Program * p, alias_MemoryCB * mcb, const char * name) {
  extern size_t strlen(const char *);

  if(!alias_Vector_space_for(&p->words, mcb, 1)) {
    return false;
  }
  const char * name_clone = alias_memory_clone(mcb, name, strlen(name) + 1, alignof(*name));
  if(name_clone == NULL) {
    return false;
  }
  alias_ash_Word * word = alias_Vector_push(&p->words);
  word->name = name_clone;
  word->cfun = NULL;
  word->hidden = true;

  // if we are in shader mode, jump over new words
  if(p->library_end_word != 0) {
    word->hole = p->instructions.length;
    if( !alias_ash_Program_emit_i(p, mcb, 0)
     || !alias_ash_Program_emit_op(p, mcb, alias_ash_Op_jump)
    ) {
      --p->words.length;
      return false;
    }
  }

  word->ip = p->instructions.length;
  return true;
}

bool alias_ash_Program_end_word(alias_ash_Program * p, alias_MemoryCB * mcb) {
  alias_ash_Word * word = &p->words.data[p->words.length - 1];
  // TODO assert we are in a named word

  word->hidden = false;

  // return from this function
  if(!alias_ash_Program_emit_op(p, mcb, alias_ash_Op_ret)) {
    return false;
  }

  // if we are in shader mode, set jump target
  if(p->library_end_word != 0) {
    *(uint32_t *)&p->instructions.data[word->hole] = p->instructions.length;
  }

  return true;
}

bool alias_ash_Program_begin_quotation(alias_ash_Program * p, alias_MemoryCB * mcb) {
  if(!alias_Vector_space_for(&p->words, mcb, 1)) {
    return false;
  }
  alias_ash_Word * word = alias_Vector_push(&p->words);
  word->name = NULL;
  word->cfun = NULL;
  word->hidden = false;

  // jump over this anonymous word
  word->hole = p->instructions.length;
  if(!alias_ash_Program_emit_i(p, mcb, 0) || !alias_ash_Program_emit_op(p, mcb, alias_ash_Op_jump)) {
    --p->words.length;
    return false;
  }

  word->ip = p->instructions.length;
  return true;
}

bool alias_ash_Program_end_quotation(alias_ash_Program * p, alias_MemoryCB * mcb) {
  alias_ash_Word * word = alias_Vector_pop(&p->words);
  // TODO assert we are in an anonymous word

  // return from this anonymous function
  if(!alias_ash_Program_emit_op(p, mcb, alias_ash_Op_ret)) {
    return false;
  }

  // set jump target
  *(uint32_t *)&p->instructions.data[word->hole + 1] = p->instructions.length;

  // push it's address to the data stack
  if(!alias_ash_Program_emit_i(p, mcb, word->ip)) {
    return false;
  }

  return true;
}

bool alias_ash_Program_emit_call(alias_ash_Program * p, alias_MemoryCB * mcb, const char * name) {
  extern int strcmp(const char *, const char *);
  for(uint32_t i = 0; i < p->words.length; i++) {
    const alias_ash_Word * word = &p->words.data[p->words.length - i - 1];

    if(strcmp(word->name, name)) {
      continue;
    }

    if(word->hidden) {
      continue;
    }

    if(word->cfun == NULL) {
      return alias_ash_Program_emit_i(p, mcb, word->ip) &&
             alias_ash_Program_emit_op(p, mcb, alias_ash_Op_call);
    }

    if(!alias_ash_Program_emit_op(p, mcb, alias_ash_Op_cfun)) {
      return false;
    }

    if(!alias_Vector_space_for(&p->instructions, mcb, sizeof(word->cfun))) {
      return false;
    }
    *(void **)&p->instructions.data[p->instructions.length] = *(void **)&word->cfun;
    p->instructions.length += sizeof(word->cfun);
    return true;
  }

  ALIAS_ERROR("failed to find word %s", name);
  return false;
}

bool alias_ash_Program_emit_op(alias_ash_Program * p, alias_MemoryCB * mcb, alias_ash_Op op) {
  if(!alias_Vector_space_for(&p->instructions, mcb, 1)) {
    return false;
  }
  *alias_Vector_push(&p->instructions) = op;
  return true;
}

bool alias_ash_Program_emit_i(alias_ash_Program * p, alias_MemoryCB * mcb, uint32_t i) {
  if(!alias_Vector_space_for(&p->instructions, mcb, 1 + sizeof(i))) {
    return false;
  }
  *alias_Vector_push(&p->instructions) = alias_ash_Op_i;
  *(uint32_t *)&p->instructions.data[p->instructions.length] = i;
  p->instructions.length += sizeof(i);
  return true;
}

bool alias_ash_Program_emit_f(alias_ash_Program * p, alias_MemoryCB * mcb, float f) {
  union { float f; uint32_t i; } _;
  _.f = f;
  return alias_ash_Program_emit_i(p, mcb, _.i);
}

void alias_ash_initialize(alias_ash * ash, alias_ash_Program * program) {
  ash->cs_size = program->instructions.length;
  ash->cs = program->instructions.data;
  ash->ip = program->library_end_instruction;
  ash->dp = 0;
  ash->rp = 0;
}

bool alias_ash_step(alias_ash * ash) {
  if(ash->ip >= ash->cs_size) {
    return false;
  }

  uint32_t * ds = ash->ds;
  float * fs = (float *)ds;
  uint32_t * rs = ash->rs;

  #define D(O) ds[ash->dp - (O) - 1]
  #define F(O) fs[ash->dp - (O) - 1]
  #define R(O) rs[ash->rp - (O) - 1]

  #define dPUSH(V) do { ds[ash->dp] = V; ++ash->dp; } while(0)
  #define dPOP(V) do { --ash->dp; V = ds[ash->dp]; } while(0)

  #define rPUSH(V) do { rs[ash->rp] = V; ++ash->rp; } while(0)
  #define rPOP(V) do { --ash->rp; V = rs[ash->rp]; } while(0)

  alias_ash_Op op;
  uint32_t a, b;
  float A, B;
  alias_ash_CFunction cfun;

  op = ash->cs[ash->ip++];

  #if ALIAS_ASH_TRACE_INSTRUCTION
  struct {
    char * name;
    int d_pre;
    int d_post;
    int r_pre;
    int r_post;
  } opinfo[] = {
      [alias_ash_Op_end]    = { "end", 0, 0, 0, 0 }
    , [alias_ash_Op_i]      = { "i", 0, 1, 0, 0 }
    , [alias_ash_Op_pick]   = { "pick", 2, 1, 0, 0 }
    , [alias_ash_Op_roll]   = { "roll", 0, 1, 0, 0 }
    , [alias_ash_Op_dup]    = { "dup", 0, 1, 0, 0 }
    , [alias_ash_Op_q_dup]  = { "q_dup", 0, 1, 0, 0 }
    , [alias_ash_Op_drop]   = { "drop", 1, 0, 0, 0 }
    , [alias_ash_Op_swap]   = { "swap", 2, 2, 0, 0 }
    , [alias_ash_Op_over]   = { "over", 2, 3, 0, 0 }
    , [alias_ash_Op_rot]    = { "rot", 3, 3, 0, 0 }
    , [alias_ash_Op_irot]   = { "irot", 3, 3, 0, 0 }
    , [alias_ash_Op_nip]    = { "nip", 2, 1, 0, 0 }
    , [alias_ash_Op_tuck]   = { "tuck", 2, 3, 0, 0 }
    , [alias_ash_Op_drop2]  = { "drop2", 2, 0, 0, 0 }
    , [alias_ash_Op_dup2]   = { "dup2", 2, 4, 0, 0 }
    , [alias_ash_Op_over2]  = { "over2", 4, 6, 0, 0 }
    , [alias_ash_Op_swap2]  = { "swap2", 2, 2, 0, 0 }
    , [alias_ash_Op_r_push] = { "r_push", 1, 0, 0, 1 }
    , [alias_ash_Op_r_pop]  = { "r_pop", 0, 1, 1, 0 }
    , [alias_ash_Op_r_at]   = { "r_at", 0, 1, 0, 0 }
    , [alias_ash_Op_jump]   = { "jump", 0, 0, 0, 0 }
    , [alias_ash_Op_jump_z] = { "jump_z", 0, 0, 0, 0 }
    , [alias_ash_Op_call]   = { "call", 1, 0, 0, 1 }
    , [alias_ash_Op_ret]    = { "ret", 0, 0, 1, 0 }
    , [alias_ash_Op_cfun]   = { "cfun", 0, 0, 0, 0 }
    , [alias_ash_Op_i_add]  = { "i_add", 2, 1, 0, 0 }
    , [alias_ash_Op_i_sub]  = { "i_sub", 2, 1, 0, 0 }
    , [alias_ash_Op_i_neg]  = { "i_neg", 1, 1, 0, 0 }
    , [alias_ash_Op_i_mul]  = { "i_mul", 2, 1, 0, 0 }
    , [alias_ash_Op_i_div]  = { "i_div", 2, 1, 0, 0 }
    , [alias_ash_Op_i_min]  = { "i_min", 2, 1, 0, 0 }
    , [alias_ash_Op_i_max]  = { "i_max", 2, 1, 0, 0 }
    , [alias_ash_Op_b_and]  = { "b_and", 2, 1, 0, 0 }
    , [alias_ash_Op_b_or]   = { "b_or", 2, 1, 0, 0 }
    , [alias_ash_Op_b_xor]  = { "b_xor", 2, 1, 0, 0 }
    , [alias_ash_Op_f_add]  = { "f_add", 2, 1, 0, 0 }
    , [alias_ash_Op_f_sub]  = { "f_sub", 2, 1, 0, 0 }
    , [alias_ash_Op_f_neg]  = { "f_neg", 1, 1, 0, 0 }
    , [alias_ash_Op_f_mul]  = { "f_mul", 2, 1, 0, 0 }
    , [alias_ash_Op_f_div]  = { "f_div", 2, 1, 0, 0 }
    , [alias_ash_Op_f_min]  = { "f_min", 2, 1, 0, 0 }
    , [alias_ash_Op_f_max]  = { "f_max", 2, 1, 0, 0 }
    , [alias_ash_Op_f_cmp]  = { "f_cmp", 2, 1, 0, 0 }
  };
  int d_pre = opinfo[op].d_pre, d_post = opinfo[op].d_post, r_pre = opinfo[op].r_pre, r_post = opinfo[op].r_post;
  int printf(const char *, ...);
  if(op == alias_ash_Op_i) {
    printf("% 4i i(%i)", ash->ip - 1, *(uint32_t *)&ash->cs[ash->ip]);
  } else if(op == alias_ash_Op_cfun) {
    void * cfun = *(void **)&ash->cs[ash->ip];
    printf("% 4i cfun(%p)", ash->ip - 1, cfun);
  } else if(op <= sizeof(opinfo)/sizeof(opinfo[0])) {
    printf("% 4i %s", ash->ip - 1, opinfo[op].name);
  } else {
    printf("% 4i unknown opcode %i", ash->ip - 1, op);
  }

  if(op == alias_ash_Op_pick || op == alias_ash_Op_roll) {
    d_pre += D(0);
    d_post += D(0);
  }

  for(int i = 0; i < d_pre; i++) {
    printf(" %g", fs[ash->dp - d_pre + i]);
  }
  if(r_pre) {
    printf(" r:");
  }
  for(int i = 0; i < r_pre; i++) {
    printf(" %i", rs[ash->rp - r_pre + i]);
  }
  printf(" --");
  #endif

  switch(op) {
  case alias_ash_Op_end:    /*          -- IP=end       */ ash->ip = ash->cs_size;                                                                                            break;
  case alias_ash_Op_i:      /*          -- a            */ a = *(uint32_t *)&ash->cs[ash->ip]; ash->ip += sizeof(uint32_t); dPUSH(a);                                         break;
  case alias_ash_Op_pick:   /* a0..an n -- a0..an a0    */ dPOP(a); b = D(a); dPUSH(b);                                                                                       break;
  case alias_ash_Op_roll:   /* a0..an n -- a1..an a0    */ dPOP(a); b = D(a); alias_memory_move(&D(a), ALIAS_ASH_DSTACK_SIZE - a, &D(a + 1), sizeof(uint32_t) * a); D(0) = b; break;
  case alias_ash_Op_dup:    /*        a -- a a          */ dPUSH(D(0));                                                                                                       break;
  case alias_ash_Op_q_dup:  /*        a -- 0 | a a      */ if(D(0) != 0) { dPUSH(D(0)); }                                                                                     break;
  case alias_ash_Op_drop:   /*        a --              */ --ash->dp;                                                                                                         break;
  case alias_ash_Op_swap:   /*      a b -- b a          */ a = D(0); D(0) = D(1); D(1) = a;                                                                                   break;
  case alias_ash_Op_over:   /*      a b -- a b a        */ dPUSH(D(1));                                                                                                       break;
  case alias_ash_Op_rot:    /*    a b c -- b c a        */ a = D(2); D(2) = D(1); D(1) = D(0); D(0) = a;                                                                      break;
  case alias_ash_Op_irot:   /*    a b c -- c a b        */ a = D(2); D(2) = D(0); D(0) = D(1); D(1) = a;                                                                      break;
  case alias_ash_Op_nip:    /*      a b -- b            */ D(1) = D(0); --ash->dp;                                                                                            break;
  case alias_ash_Op_tuck:   /*      a b -- b a b        */ a = D(1); b = D(0); D(1) = b; D(0) = a; dPUSH(b);                                                                  break;
  case alias_ash_Op_drop2:  /* a b      --              */ ash->dp -= 2;                                                                                                      break;
  case alias_ash_Op_dup2:   /* a b      -- a b a b      */ dPUSH(D(1)); dPUSH(D(1));                                                                                          break;
  case alias_ash_Op_over2:  /* a b c d  -- a b c d a b  */ dPUSH(D(3)); dPUSH(D(3));                                                                                          break;
  case alias_ash_Op_swap2:  /* a b c d  -- c d a b      */ a = D(1); b = D(0); D(0) = D(2); D(1) = D(3); D(3) = a; D(2) = b;                                                  break;
  case alias_ash_Op_r_push: /*        a -- R: a         */ dPOP(a); rPUSH(a);                                                                                                 break;
  case alias_ash_Op_r_pop:  /*     R: a -- a            */ rPOP(a); dPUSH(a);                                                                                                 break;
  case alias_ash_Op_r_at:   /*     R: a -- a R: a       */ dPUSH(R(0));                                                                                                       break;
  case alias_ash_Op_jump:   /*        a -- IP=a         */ dPOP(a); ash->ip = a;                                                                                              break;
  case alias_ash_Op_jump_z: /*      a b -- IP=b if a==0 */ dPOP(b); dPOP(a); if(a == 0) { ash->ip = b; }                                                                      break;
  case alias_ash_Op_call:   /*        a -- R: IP, IP=a  */ dPOP(a); rPUSH(ash->ip); ash->ip = a;                                                                              break;
  case alias_ash_Op_ret:    /*     R: a -- IP=a         */ rPOP(a); ash->ip = a;                                                                                              break;
  case alias_ash_Op_cfun:   /*        ? -- ?            */ *(void **)&cfun = *(void **)&ash->cs[ash->ip]; ash->ip += sizeof(void *); cfun(ash);                               break;
  case alias_ash_Op_i_add:  /*      a b -- (a + b)      */ D(1) += D(0); --ash->dp;                                                                                           break;
  case alias_ash_Op_i_sub:  /*      a b -- (a - b)      */ D(1) -= D(0); --ash->dp;                                                                                           break;
  case alias_ash_Op_i_neg:  /*        a -- (-a)         */ D(0) = -D(0);                                                                                                      break;
  case alias_ash_Op_i_mul:  /*      a b -- (a * b)      */ D(1) *= D(0); --ash->dp;                                                                                           break;
  case alias_ash_Op_i_div:  /*      a b -- (a / b)      */ D(1) /= D(0); --ash->dp;                                                                                           break;
  case alias_ash_Op_i_min:  /*      a b -- min(a, b)    */ a = D(1); b = D(0); D(1) = a < b ? a : b; --ash->dp;                                                               break;
  case alias_ash_Op_i_max:  /*      a b -- max(a, b)    */ a = D(1); b = D(0); D(1) = a > b ? a : b; --ash->dp;                                                               break;
  case alias_ash_Op_b_and:  /*      a b -- (a & b)      */ D(1) &= D(0); --ash->dp;                                                                                           break;
  case alias_ash_Op_b_or:   /*      a b -- (a | b)      */ D(1) |= D(0); --ash->dp;                                                                                           break;
  case alias_ash_Op_b_xor:  /*      a b -- (a ^ b)      */ D(1) ^= D(0); --ash->dp;                                                                                           break;
  case alias_ash_Op_f_add:  /*      a b -- (a + b)      */ F(1) += F(0); --ash->dp;                                                                                           break;
  case alias_ash_Op_f_sub:  /*      a b -- (a - b)      */ F(1) -= F(0); --ash->dp;                                                                                           break;
  case alias_ash_Op_f_neg:  /*        a -- (-a)         */ F(0) = -F(0);                                                                                                      break;
  case alias_ash_Op_f_mul:  /*      a b -- (a * b)      */ F(1) *= F(0); --ash->dp;                                                                                           break;
  case alias_ash_Op_f_div:  /*      a b -- (a / b)      */ F(1) /= F(0); --ash->dp;                                                                                           break;
  case alias_ash_Op_f_min:  /*      a b -- min(a, b)    */ A = F(1); B = F(0); F(1) = A < B ? A : B; --ash->dp;                                                               break;
  case alias_ash_Op_f_max:  /*      a b -- max(a, b)    */ A = F(1); B = F(0); F(1) = A > B ? A : B; --ash->dp;                                                               break;
  case alias_ash_Op_f_cmp:  /*      a b -- (-,0,+)      */ F(1) = F(1) - F(0); --ash->dp;                                                                                     break;
  }

  #if ALIAS_ASH_TRACE_INSTRUCTION
  for(int i = 0; i < d_post; i++) {
    printf(" %g", fs[ash->dp - d_post + i]);
  }
  if(r_post) {
    printf(" r:");
  }
  for(int i = 0; i < r_post; i++) {
    printf(" %i", rs[ash->rp - r_post + i]);
  }
  printf("\n");
  #endif

  #undef D
  #undef F
  #undef R
  #undef dPUSH
  #undef dPOP
  #undef rPUSH
  #undef rPOP

  return ash->ip <= ash->cs_size;
}

