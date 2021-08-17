#include <alias/ui.h>
#include <alias/data_structure/vector.h>

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

static void _emit(struct program * p, uint8_t byte) {
    alias_Vector_space_for(&p->code, p->mcb, 1);
    *alias_Vector_push(&p->code) = byte;
}

// individual ops
// n : a0..an -> a0..an a0
static void _pick_i(struct program * p, uint8_t index) {
    _emit(p, op_pick_i);
    _emit(p, index);
}

// n : a0..an -> a1..an a0
static void _roll_i(struct program * p, uint8_t index) {
    _emit(p, op_roll_i);
    _emit(p, index);
}

// a ->
static void _drop(struct program * p) {
    _emit(p, op_drop);
}

// a b c -> c a b
static void _rrot(struct program * p) {
    _emit(p, op_rrot);
}

// a b -> b a b
static void _tuck(struct program * p) {
    _emit(p, op_tuck);
}

// real : -> real
static void _real(struct program * p, alias_R r) {
    union { alias_R r; uint8_t b[sizeof(r)]; } u;
    u.r = r;
    _emit(p, op_real);
    for(uint32_t i = 0; i < sizeof(r); i++) {
        _emit(p, b[i]);
    }
}

// real real -> real
static void _add(struct program * p) {
    _emit(p, op_add);
}

// real real -> real
static void _sub(struct program * p) {
    _emit(p, op_sub);
}

// real real -> real
static void _mul(struct program * p) {
    _emit(p, op_mul);
}

// real real -> real
static void _div(struct program * p) {
    _emit(p, op_div);
}

// real real -> size
static void _make_size(struct program * p) {
    _emit(p, op_make_size);
}

// size -> real real
static void _unmake_size(struct program * p) {
    _emit(p, op_unmake_size);
}

// size size -> size
static void _size_min(struct program * p) {
    _emit(p, op_size_min);
}

// size size -> size
static void _size_max(struct program * p) {
    _emit(p, op_size_max);
}
// size size -> constraint
static void _make_constraint(struct program * p) {
    _emit(p, op_make_constraint);
}

// constraint -> size size
static void _unmake_constraint(struct program * p) {
    _emit(p, op_unmake_constraint);
}

// 'sugar'
// a -> a a
static void _dup(struct program * p) {
    _pick_i(p, 0);
}

// a b -> a b a
static void _over(struct program * p) {
    _pick_i(p, 1);
}

// a b -> b a
static void _swap(struct program * p) {
    _roll_i(p, 1);
}

// a b c -> b c a
static void _rot(struct program * p) {
    _roll_i(p, 2);
}

// a b -> b
static void _nip(struct program * p) {
    _swap(p);
    _emit(p, op_drop);
}

// real real : -> real
static void _size(struct program * p, alias_R width, alias_R height) {
    _real(p, width);
    _real(p, height);
    _emit(p, op_make_size);
}

// size -> real
static void _size_x(struct program * p) {
  _unmake_size(p);
  _drop(p);
}

// size -> real
static void _size_y(struct program * p) {
  _unmake_size(p);
  _nip(p);
}

// constraint -> size
static void _constraint_min(struct program * p) {
  _unmake_constraint(p);
  _drop(p);
}

// constraint -> size
static void _constraint_max(struct program * p) {
  _unmake_constraint(p);
  _nip(p);
}

// constraint size -> size
static void _fit(struct program * p) {
    // c s
    _swap(p);              // s c
    _unmake_constraint(p); // s ca cb
    _rot(p);               // ca cb s
    _size_min(p);
    _size_max(p);
}

static void _execute(struct program * p) {
    alias_R  stack_data[1024];
    uint32_t dp = 0;
    
    uint16_t stack[256];
    uint32_t sp = 0;

    uint32_t ip = 0;

    while(ip < program_length) {
        union { alias_R r; uint8_t b[sizeof(alias_R)]; uint8_t i; } a;
        struct {
          uint8_t  size_log2;
          uint8_t  size;
          uint32_t index;
          union {
            alias_R             r;
            alias_ui_Size       s;
            alias_ui_Constraint c;
            alias_R             a;
          };
        } A, B, C, P;

        #define READ_U8() program[ip++]
        #define READ_R() ({ \
          for(uint32_t i = 0; i < sizeof(alias_R); i++) { \
            a.b[i] = READ_U8(); \
          } \
          a.r; \
        })

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
            ai = sp - 1 - a.i;
            LOAD(A, ai);
            PUSH(A);
            break;
        case op_roll_i: // n : a0..an -> a1..an a0
            sp--;
            LOAD(A, sp - a.i);
            dp = A.index;
            for(uint32_t i = sp - a.i; i < sp; i++) {
              stack[i] = (stack[i + 1] & 0xB000) | dp;
              for(uint32_t j = 0; j < data_; j++) {
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
            SET_REAL(A, READ_R());
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
            data_stack[dp - 4] = alias_min(data_stack[dp - 4], data_stack[dp - 2]);
            data_stack[dp - 3] = alias_min(data_stack[dp - 3], data_stack[dp - 1]);
            dp -= 2;
            sp -= 1;
            break;
        case op_size_max: // size size -> size
            data_stack[dp - 4] = alias_max(data_stack[dp - 4], data_stack[dp - 2]);
            data_stack[dp - 3] = alias_max(data_stack[dp - 3], data_stack[dp - 1]);
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

alias_ui_Result alias_ui_initialize(alias_MemoryCB * mcb, alias_ui * * ui_ptr) {
}

alias_ui_Result alias_ui_free(alias_ui * ui, alias_MemoryCB * mcb) {
}

alias_ui_Result alias_ui_begin_frame(alias_ui * ui, alias_MemoryCB * mcb, const alias_ui_Input * input) {
}

void alias_ui_center(alias_ui * ui) {
}

void alias_ui_font_size(alias_ui * ui, alias_R size) {
}

void alias_ui_font_color(alias_ui * ui, alias_Color color) {
}

void alias_ui_textv(alias_ui * ui, const char * format, va_list ap) {
    struct program * lp = &ui->layout_program;

    alias_R width = 100;
    alias_R height = 80;

    // constraint -> size
    _size(lp, width, height);
    _fit(lp);
}

alias_ui_Result alias_ui_end_frame(alias_ui * ui, alias_MemoryCB * mcb, alias_ui_Output * output) {
}
