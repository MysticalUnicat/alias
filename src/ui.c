#include <alias/ui.h>
#include <alias/data_structure/vector.h>

#include <alias/cpp.h>

enum {
  op_invalid,

  op_pick_i, // n : a0..an -> a0..an a0
  op_roll_i, // n : a0..an -> a1..an a0
  op_drop,   // a ->
  op_rrot,   // a b c -> c a b
  op_tuck,   // a b -> b a b

  op_real, // real : -> real
  op_add,  // real real -> real
  op_sub,  // real real -> real
  op_mul,  // real real -> real
  op_div,  // real real -> real
  op_min,  // real real -> real
  op_max,  // real real -> real

  op_make_size,   // real real -> size
  op_unmake_size, // size -> real real
  op_size_min,    // size size -> size
  op_size_max,    // size size -> size

  op_make_constraint,   // size size -> constraint
  op_unmake_constraint, // constraint -> size size
};

struct program {
  alias_MemoryCB * mcb;
  alias_Vector(uint8_t) code;
};

static void _emit_u8(struct program * p, uint8_t byte) {
  alias_Vector_space_for(&p->code, p->mcb, 1);
  *alias_Vector_push(&p->code) = byte;
}

static void _emit_real(struct program * p, alias_R r) {
  union { alias_R r; uint8_t b[sizeof(r)]; } u;
  u.r = r;
  _emit_u8(p, op_real);
  for(uint32_t i = 0; i < sizeof(r); i++) {
    _emit_u8(p, u.b[i]);
  }
}

#define _emit(P, A) \
  _Generic(A, \
      alias_R: _emit_real \
    , default: _emit_u8 \
  )(P, A)

#define EMIT(P, ...) \
  do { \
    struct program * _EMIT_P = P; \
    ALIAS_MAP(_EMIT, __VA_ARGS__) \
  } while(0)
#define _EMIT(A) _emit(_EMIT_P, A);

#define op_dup            op_pick_i, 0
#define op_over           op_pick_i, 1
#define op_swap           op_roll_i, 1
#define op_rot            op_roll_i, 2

#define op_nip            op_swap, op_drop
#define op_size_x         op_unmake_size, op_drop
#define op_size_y         op_unmake_size, op_nip
#define op_constraint_min op_unmake_constraint, op_drop
#define op_constraint_max op_unmake_constraint, op_nip
#define op_fit            op_swap, op_unmake_constraint, op_rot, op_size_min, op_size_max

static void _execute(struct program * p) {
  alias_R  stack_data[1024];
  uint32_t dp = 0;
  
  uint16_t stack[256];
  uint32_t sp = 0;

  uint32_t ip = 0;

  while(ip < p->code.length) {
    union { alias_R r; uint8_t b[sizeof(alias_R)]; uint8_t i; } a;
    struct {
      uint8_t  size_log2;
      uint8_t  size;
      uint32_t index;
      union {
        alias_R             r;
        alias_ui_Size       s;
        alias_ui_Constraint c;
        alias_R             a[4];
      };
    } A, B, C;

    #define READ_U8() p->code.data[ip++]
    #define READ_R() do { \
      for(uint32_t i = 0; i < sizeof(alias_R); i++) { \
        a.b[i] = READ_U8(); \
      } \
    } while(0)

    #define LOAD(L, I) \
      do { \
        uint16_t _value = stack[I]; \
        L.size_log2 = _value >> 14; \
        L.size = 1 << L.size_log2; \
        L.index = _value & 0x3FFF; \
        for(uint32_t i = 0; i < L.size; i++) { \
          L.a[i] = stack_data[L.index + i]; \
        } \
      } while(0)

    #define SET_REAL(L, R) \
      do { \
        L.size = 1; \
        L.size_log2 = 0; \
        L.r = R; \
      } while(0)

    #define POP(L) \
      do { \
        LOAD(L, stack[sp - 1]); \
        dp -= L.size; \
        sp -= 1; \
      } while(0)

    #define PUSH(L) \
      do { \
        L.index = dp; \
        for(uint32_t i = 0; i < L.size; i++) { \
          stack_data[dp++] = L.a[i]; \
        } \
        stack[sp++] = L.size_log2 | L.index; \
      } while(0)

    uint8_t op = READ_U8();
    switch(op) {
    case op_invalid:
      break;
    case op_pick_i: // n : a0..an -> a0..an a0
      a.i = READ_U8();
      LOAD(A, sp - 1 - a.i);
      PUSH(A);
      break;
    case op_roll_i: // n : a0..an -> a1..an a0
      sp--;
      LOAD(A, sp - a.i);
      dp = A.index;
      for(uint32_t i = sp - a.i; i < sp; i++) {
        stack[i] = (stack[i + 1] & 0xB000) | dp;
        B.size_log2 = stack[i] >> 14;
        B.size = 1 << B.size_log2;
        for(uint32_t j = 0; j < B.size; j++) {
          stack_data[dp] = stack_data[dp + A.size];
          dp++;
        }
      }
      PUSH(A);
      break;
    case op_drop:   // a ->
      dp -= 1 << (stack[--sp] >> 14);
      break;
    case op_rrot:   // a b c -> c a b
      POP(C);
      POP(B);
      POP(A);
      PUSH(C);
      PUSH(A);
      PUSH(B);
      break;
    case op_tuck:   // a b -> b a b
      POP(B);
      POP(A);
      PUSH(B);
      PUSH(A);
      PUSH(B);
      break;
    case op_real: // real : -> real
      READ_R();
      SET_REAL(A, a.r);
      PUSH(A);
      break;
    case op_add: // real real -> real
      stack_data[dp - 2] += stack_data[dp - 1];
      dp--;
      sp--;
      break;
    case op_sub: // real real -> real
      stack_data[dp - 2] -= stack_data[dp - 1];
      dp--;
      sp--;
      break;
    case op_mul: // real real -> real
      stack_data[dp - 2] *= stack_data[dp - 1];
      dp--;
      sp--;
      break;
    case op_div: // real real -> real
      stack_data[dp - 2] /= stack_data[dp - 1];
      dp--;
      sp--;
      break;
    case op_min: // real real -> real
      stack_data[dp - 2] = alias_min(stack_data[dp - 2], stack_data[dp - 1]);
      dp--;
      sp--;
      break;
    case op_max: // real real -> real
      stack_data[dp - 2] = alias_max(stack_data[dp - 2], stack_data[dp - 1]);
      dp--;
      sp--;
      break;
    case op_make_size: // real real -> size
      sp--;
      stack[sp - 1] = (1 << 14) | (stack[sp - 1] & 0x3FFF);
      break;
    case op_unmake_size: // size -> real real
      stack[sp - 1] = (0 << 14) | (stack[sp - 1] & 0x3FFF);
      sp++;
      stack[sp - 1] = (0 << 14) | ((stack[sp - 2] & 0x3FFF) + 1);
      break;
    case op_size_min: // size size -> size
      stack_data[dp - 4] = alias_min(stack_data[dp - 4], stack_data[dp - 2]);
      stack_data[dp - 3] = alias_min(stack_data[dp - 3], stack_data[dp - 1]);
      dp -= 2;
      sp -= 1;
      break;
    case op_size_max: // size size -> size
      stack_data[dp - 4] = alias_max(stack_data[dp - 4], stack_data[dp - 2]);
      stack_data[dp - 3] = alias_max(stack_data[dp - 3], stack_data[dp - 1]);
      dp -= 2;
      sp -= 1;
      break;
    case op_make_constraint: // size size -> constraint
      sp--;
      stack[sp - 1] = (2 << 14) | (stack[sp - 1] & 0x3FFF);
      break;
    case op_unmake_constraint: // constraint -> size size
      stack[sp - 1] = (1 << 14) | (stack[sp - 1] & 0x3FFF);
      sp++;
      stack[sp - 1] = (1 << 14) | ((stack[sp - 2] & 0x3FFF) + 2);
      break;
    }
  }
}

// ====================================================================================================================
// structs
#define MAX_SCOPES 32

struct scope {
  alias_R     font_size;
  alias_Color font_color;

  alias_R flex;
  alias_R total_flex;
  
  void (* begin_child)(alias_ui *);
  void (* end_child)(alias_ui *);
  void (* end_scope)(alias_ui *);
};

struct alias_ui {
  struct program layout_program;

  struct scope * scope;
  struct scope scopes[MAX_SCOPES];
};

// ====================================================================================================================
// private functions
static inline void _begin_child(alias_ui * ui) {
  if(ui->scope->begin_child) {
    ui->scope->begin_child(ui);
  }
}

static inline void _end_child(alias_ui * ui) {
  if(ui->scope->end_child) {
    ui->scope->end_child(ui);
  }
}

static inline void _begin_scope(alias_ui * ui, void (* begin_child)(alias_ui *), void (* end_child)(alias_ui *), void (* end_scope)(alias_ui *)) {
  ui->scope++;
  ui->scope->font_size = (ui->scope - 1)->font_size;
  ui->scope->font_color = (ui->scope - 1)->font_color;
  ui->scope->flex = alias_R_ZERO;
  ui->scope->total_flex = alias_R_ZERO;
  ui->scope->begin_child = begin_child;
  ui->scope->end_child = end_child;
  ui->scope->end_scope = end_scope;
}

static inline void _end_scope(alias_ui * ui) {
  ui->scope--;
  if((ui->scope + 1)->end_scope) {
    (ui->scope + 1)->end_scope(ui);
  }
}

// ====================================================================================================================
// lifetime
alias_ui_Result alias_ui_initialize(alias_MemoryCB * mcb, alias_ui * * ui_ptr) {
  (void)mcb;
  (void)ui_ptr;

  return alias_ui_Success;
}

alias_ui_Result alias_ui_free(alias_ui * ui, alias_MemoryCB * mcb) {
  (void)ui;
  (void)mcb;

  return alias_ui_Success;
}

// ====================================================================================================================
// frame (begin)
alias_ui_Result alias_ui_begin_frame(alias_ui * ui, alias_MemoryCB * mcb, const alias_ui_Input * input) {
  struct program * lp = &ui->layout_program;
  lp->mcb = mcb;
  alias_Vector_clear(&lp->code);

  // -> constraint
  EMIT(lp,
    input->screen_size.width, input->screen_size.height, op_make_size,
    op_dup,
    op_make_constraint
  );

  return alias_ui_Success;
}

// ====================================================================================================================
// center
// state: constraint-max
static inline void _center_end_child(alias_ui * ui) {
  struct program * lp = &ui->layout_program;
  
  // a:size(max constraint)
  // b:size -> size
  EMIT(lp,
    op_over,
    op_size_min,
    op_drop // TODO: store size of child
  );

  _end_scope(ui);
  _end_child(ui);
}

void alias_ui_center(alias_ui * ui) {
  struct program * lp = &ui->layout_program;

  _begin_child(ui);
  _begin_scope(ui, NULL, _center_end_child, NULL);

  // save max constraint
  // constraint -> size
  EMIT(lp, op_constraint_max);
}

// ====================================================================================================================
// vertical
// state: constraint-max y-offset align
static inline void _vertical_begin_child(alias_ui * ui) {
  // state -> state constraint constraint
  struct program * lp = &ui->layout_program;
  EMIT(lp, op_dup);
}

static inline void _vertical_end_child(alias_ui * ui) {
  struct program * lp = &ui->layout_program;
  (void)lp;
}

static inline void _vertical_end_scope(alias_ui * ui) {
  _end_child(ui);

  // state -> size
  struct program * lp = &ui->layout_program;
  (void)lp;
}

void alias_ui_vertical(alias_ui * ui) {
  _begin_child(ui);
  _begin_scope(ui, _vertical_begin_child, _vertical_end_child, _vertical_end_scope);

  // constraint -> constraint
  struct program * lp = &ui->layout_program;
  (void)lp;
}

// ====================================================================================================================
// font
void alias_ui_font_size(alias_ui * ui, alias_R size) {
  ui->scope->font_size = size;
}

void alias_ui_font_color(alias_ui * ui, alias_Color color) {
  ui->scope->font_color = color;
}

// ====================================================================================================================
// text
void alias_ui_textv(alias_ui * ui, const char * format, va_list ap) {
  (void)format;
  (void)ap;

  _begin_child(ui);

  alias_R width = 100;
  alias_R height = 80;

  // constraint -> size
  struct program * lp = &ui->layout_program;
  EMIT(lp, width, height, op_make_size, op_fit);

  _end_child(ui);
}

// ====================================================================================================================
// frame (end)
alias_ui_Result alias_ui_end_frame(alias_ui * ui, alias_MemoryCB * mcb, alias_ui_Output * output) {
  (void)mcb;
  (void)output;

  _execute(&ui->layout_program);
  
  return alias_ui_Success;
}

