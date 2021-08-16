#ifndef _ALIAS_UI_H_
#define _ALIAS_UI_H_

#include <stdarg.h>

#include <alias/memory.h>
#include <alias/color.h>

typedef struct alias_ui alias_ui;

typedef enum alias_ui_Result {
    alias_ui_Success,
    alias_ui_ErrorOutOfMemory
} alias_ui_Result;

typedef struct alias_ui_Size {
    alias_R x;
    alias_R y;
} alias_ui_Size;

typedef struct alias_ui_Constraint {
    alias_ui_Size min;
    alias_ui_Size max;
} alias_ui_Constraint;

typedef struct alias_ui_Input {
    alias_ui_Size screen_size;
} alias_ui_Input;

typedef struct alias_ui_Output {
    uint32_t things;
} alias_ui_Output;

alias_ui_Result alias_ui_initialize(alias_MemoryCB * mcb, alias_ui * * ui_ptr);
alias_ui_Result alias_ui_free(alias_ui * ui, alias_MemoryCB * mcb);

alias_ui_Result alias_ui_begin_frame(alias_ui * ui, alias_MemoryCB * mcb, const alias_ui_Input * input);
void alias_ui_center(alias_ui * ui);
void alias_ui_font_color(alias_ui * ui, alias_Color color);
void alias_ui_textv(alias_ui * ui, const char * format, va_list ap);
alias_ui_Result alias_ui_end_frame(alias_ui * ui, alias_MemoryCB * mcb, alias_ui_Output * output);

static inline alias_ui_Result alias_ui_text(alias_ui * ui, const char * format, ...) {
    va_list ap;
    va_start(ap, format);
    alias_ui_Result result = alias_ui_textv(ui, format, ap);
    va_end(ap);
    return result;
}

#if ALIAS_UI_IMPLEMENTATION
#include <alias/data_structure/vector.h>

enum {
    op_invalid,

    op_pick_i, // n : a0..an -> a0..an a0
    op_roll_i, // n : a0..an -> a1..an a0
    op_drop,   // a ->
    op_rrot,   // a b c -> c a b
    op_nip,    // a b -> b
    op_tuck,   // a b -> b a b

    op_real, // real : -> real

    op_add, // real real -> real
    op_sub, // real real -> real
    op_mul, // real real -> real
    op_div, // real real -> real
    op_min, // real real -> real
    op_max, // real real -> real
    
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

// a b -> b
static void _nip(struct program * p) {
    _emit(p, op_nip);
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

// size size -> size
static void _size_min(struct program * p) {
    // a b
    _unmake_size(p); // a bx by
    _rot(p);         // bx by a
    _unmake_size(p); // bx by ax ay
    _rot(p);         // bx ax ay by
    _min(p);         // bx ax Y
    _rrot(p);        // Y bx ax
    _min(p);         // Y X
    _swap(p);        // X Y
    _make_size(p);
}

// size size -> size
static void _size_max(struct program * p) {
    // a b
    _unmake_size(p); // a bx by
    _rot(p);         // bx by a
    _unmake_size(p); // bx by ax ay
    _rot(p);         // bx ax ay by
    _max(p);         // bx ax Y
    _rrot(p);        // Y bx ax
    _max(p);         // Y X
    _swap(p);        // X Y
    _make_size(p);
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

static void execute(uint32_t program_length, const uint8_t * program) {
    uint32_t ip = 0;

    while(ip < program_length) {
        uint8_t op = program[ip++];
        switch(op) {
        case op_invalid:
            break;
        case op_pick_i: // n : a0..an -> a0..an a0
            
            break;
        case op_roll_i: // n : a0..an -> a1..an a0
            break;
        case op_drop:   // a ->
            break;
        case op_rrot:   // a b c -> c a b
            break;
        case op_nip:    // a b -> b
            break;
        case op_tuck:   // a b -> b a b
            break;
        case op_real: // real : -> real
            break;
        case op_add: // real real -> real
            break;
        case op_sub: // real real -> real
            break;
        case op_mul: // real real -> real
            break;
        case op_div: // real real -> real
            break;
        case op_min: // real real -> real
            break;
        case op_max: // real real -> real
            break;
        case op_make_size:   // real real -> size
            break;
        case op_unmake_size: // size -> real real
            break;
        case op_size_min:    // size size -> size
            break;
        case op_size_max:    // size size -> size
            break;
        case op_make_constraint:   // size size -> constraint
            break;
        case op_unmake_constraint: // constraint -> size size
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
#endif
 
#endif
