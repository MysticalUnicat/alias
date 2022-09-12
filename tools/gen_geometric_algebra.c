// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#define _GNU_SOURCE
#define TABULA_IMPLEMENTATION
#include <tabula.h>

#include <getopt.h>

#define NL " \\\n"
//#define NL ""

#define MIN(A, B) ({ __auto_type a = A; __auto_type b = B; a < b ? a : b; })
#define MAX(A, B) ({ __auto_type a = A; __auto_type b = B; a > b ? a : b; })

char * Prefix = NULL;
char * PREFIX = NULL;
char * prefix = NULL;

int p = 0, n = 0, d = 0;
int first_basis;
int num_dimensions;
int num_grades;

enum Metric {
  One,
  Negative,
  Degenerate,
  Positive
};
const char * metric_name[] = { "one", "-1", "0", "+1" };
int metric_sign[] = { 1, -1, 0, 1 };

typedef struct {
  int basis;
  int sign;
} BasisRef;

int num_basis;
typedef struct {
  const char * name;
  int bits;
  int grade;
  enum Metric metric;
} Basis;
Basis * basis; // num_basis
int * basis_by_bits; // num_basis

int num_op_alias = 0;
struct {
  const char * from;
  const char * to;
  int binary;
} * op_alias = NULL;

void _add_op_alias(const char * from, const char * to, int binary) {
  op_alias = realloc(op_alias, sizeof(*op_alias) * (num_op_alias + 1));
  op_alias[num_op_alias].from = strdup(from);
  op_alias[num_op_alias].to = strdup(to);
  op_alias[num_op_alias].binary = binary;
  num_op_alias++;
}

int num_type_alias = 0;
struct {
  const char * name;
  const char * args;
  const char * elements;
} * type_alias = NULL;

void _add_type_alias(const char * name, const char * args, const char * elements) {
  type_alias = realloc(op_alias, sizeof(*type_alias) * (num_type_alias + 1));
  type_alias[num_type_alias].name = strdup(name);
  type_alias[num_type_alias].args = strdup(args);
  type_alias[num_type_alias].elements = strdup(elements);
  num_type_alias++;
}

int num_codes = 0;
struct {
  char code;
  uint32_t grades;
} * codes = NULL;

void _add_code(char code, uint32_t grades) {
  codes = realloc(codes, sizeof(*codes) * (num_codes + 1));
  codes[num_codes].code = code;
  codes[num_codes].grades = grades;
  num_codes++;
}

int _sort_basis(const void * ap, const void * bp, void * ud) {
  const Basis * a = (const Basis *)ap;
  const Basis * b = (const Basis *)bp;
  int len_diff = (int)strlen(a->name) - (int)strlen(b->name);
  return len_diff ? len_diff : strcmp(a->name, b->name);
}

BasisRef _mul_basis_ref(BasisRef a, BasisRef b) {
  if(a.basis == b.basis) {
    return (BasisRef) {
        .basis = One
      , .sign = a.sign * b.sign * metric_sign[basis[a.basis].metric]
    };
  }
  if(a.basis == 0 || b.basis == 0) {
    return (BasisRef) {
        .basis = a.basis | b.basis
      , .sign = a.sign * b.sign
    };
  }
  int ab = basis[a.basis].bits;
  int bb = basis[b.basis].bits;
  int sign = 1;
  char * nums;
  int length = asprintf(&nums, "%s%s", basis[a.basis].name + 1, basis[b.basis].name + 1);
  int modified = 1;
  while(modified) {
    modified = 0;
    for(int i = 1; i < length; i++) {
      if(nums[i - 1] == nums[i]) {
        i--;
        sign *= metric_sign[basis[(nums[i] - first_basis) + 1].metric];
        memmove(nums + i, nums + i + 2, length - i - 2 + 1);
        length -= 2;
        modified = 1;
      } else if(nums[i - 1] > nums[i]) {
        char t = nums[i - 1];
        nums[i - 1] = nums[i];
        nums[i] = t;
        sign *= -1;
        modified = 1;
      }
    }
  }
  return (BasisRef) {
      .basis = basis_by_bits[ab ^ bb]
    , .sign = sign
  };
}

BasisRef _dual(BasisRef a) {
  if(d) {
    BasisRef b = (BasisRef) { .basis = num_basis - 1 - a.basis, .sign = a.sign };
    b.sign = _mul_basis_ref(a, b).sign;
    return b;
  } else {
    return _mul_basis_ref(a, (BasisRef) { .basis = num_basis - 1, .sign = 1 });
  }
}

BasisRef * _cayley_table;  // num_basis*num_basis ; [a * num_basis + b] = c
BasisRef * _product_table; // num_basis*num_basis ; [c * num_basis + a] = b

void grades(char c) {
  for(int i = 0; i < num_grades; i++) {
    printf("%s%c%i", i ? "," : "", c, i);
  }
}

void values(char c) {
  for(int i = 0; i < num_basis; i++) {
    printf("%s%c%s", i ? "," : "", c, basis[i].name);
  }
}

const char * header =
  "#ifndef _%1$s_H_\n"
  "#define _%1$s_H_\n"
  "// %2$i positive dimension(s)\n"
  "// %3$i negative dimension(s)\n"
  "// %4$i deginerate dimension(s)\n"
  "// %5$i total dimension(s)\n"
  "// %6$i total grade(s)\n"
  "#define %1$s_EMPTY(...)\n"
  "#define %1$s_UNPACK(...) __VA_ARGS__\n"
  "#define %1$s_CAT(X, ...) %1$s_CAT0(X, ## __VA_ARGS__)\n"
  "#define %1$s_CAT0(X, ...) X ## __VA_ARGS__\n"
  "#define %1$s_CAT3(X, Y, ...) %1$s_CAT30(X, Y, ## __VA_ARGS__)\n"
  "#define %1$s_CAT30(X, Y, ...) X ## Y ## __VA_ARGS__\n"
  "#define %1$s_OR(X, Y) %1$s_CAT3(%1$s_OR_, X, Y)\n"
  "#define %1$s_OR_00 0\n"
  "#define %1$s_OR_01 1\n"
  "#define %1$s_OR_10 1\n"
  "#define %1$s_OR_11 1\n"
  "#define %1$s_IFF(X) %1$s_CAT(%1$s_IFF_, X)\n"
  "#define %1$s_IFF_0(T, F) F\n"
  "#define %1$s_IFF_1(T, F) T\n"
  "#define %1$s_IF2(X, Y) %1$s_CAT3(%1$s_IF2_, X, Y)\n"
  "#define %1$s_IF(X) %1$s_CAT(%1$s_IF_, X)\n"
  "#define %1$s_IF_0(...) %1$s_UNPACK\n"
  "#define %1$s_IF_1(...) __VA_ARGS__ %1$s_EMPTY\n"
  "#define %1$s_IF2(X, Y) %1$s_CAT3(%1$s_IF2_, X, Y)\n"
  "#define %1$s_IF2_00(...) %1$s_IF2_000\n"
  "#define %1$s_IF2_000(...) %1$s_IF2_001\n"
  "#define %1$s_IF2_001(...) %1$s_UNPACK\n"
  "#define %1$s_IF2_01(...) %1$s_IF2_010\n"
  "#define %1$s_IF2_010(...) %1$s_IF2_011\n"
  "#define %1$s_IF2_011(...) __VA_ARGS__ %1$s_EMPTY\n"
  "#define %1$s_IF2_10(...) %1$s_IF2_100\n"
  "#define %1$s_IF2_100(...) __VA_ARGS__ %1$s_IF2_101\n"
  "#define %1$s_IF2_101(...) %1$s_EMPTY\n"
  "#define %1$s_IF2_11(...) __VA_ARGS__ %1$s_IF2_110\n"
  "#define %1$s_IF2_110(...) %1$s_IF2_111\n"
  "#define %1$s_IF2_111(...) %1$s_EMPTY\n"
  "#define %1$s_PROBE(...) ~,1\n"
  "#define %1$s_IS_PROBE(...) %1$s_IS_PROBE0(__VA_ARGS__, 0, 0)\n"
  "#define %1$s_IS_PROBE0(X, Y, ...) Y\n"
  "#define %1$s_IS_ZERO(X) %1$s_IFF(%1$s_IS_PROBE(%1$s_PROBE X))(%1$s_IS_ZERO1, %1$s_IS_ZERO2)(X)\n"
  "#define %1$s_IS_ZERO1(X) 0\n"
  "#define %1$s_IS_ZERO2(X) %1$s_IS_PROBE(%1$s_CAT(%1$s_IS_ZERO3_, X)())\n"
  "#define %1$s_IS_ZERO3_0 %1$s_PROBE\n"
  "#define %1$s_IS_NONZERO(X) %1$s_IF(%1$s_IS_ZERO(X))(0)(1)\n"
  "#define %1$s_NEG(X) %1$s_IF(%1$s_IS_ZERO(X))( 0 )( (-X) )\n"
  "#define %1$s_ADD(X, Y) %1$s_IF2(%1$s_IS_ZERO(X), %1$s_IS_ZERO(Y))( 0 )(   Y  )( X )( X+Y )\n"
  "#define %1$s_SUB(X, Y) %1$s_IF2(%1$s_IS_ZERO(X), %1$s_IS_ZERO(Y))( 0 )( (-Y) )( X )( X-Y )\n"
  "#define %1$s_ADD_MUL(X, Y) %1$s_IF(%1$s_OR(%1$s_IS_ZERO(X), %1$s_IS_ZERO(Y)))( )( +(X*Y) )\n"
  "#define %1$s_SUB_MUL(X, Y) %1$s_IF(%1$s_OR(%1$s_IS_ZERO(X), %1$s_IS_ZERO(Y)))( )( -(X*Y) )\n"
  ;

void generate(void) {
  first_basis = d ? '0' : '1';
  num_dimensions = p + n + d;
  num_grades = 1 + num_dimensions;
  num_basis = 1 << num_dimensions;

  printf(header, PREFIX, p, n, d, num_dimensions, num_grades);

  basis = calloc(num_basis, sizeof(*basis));
  basis_by_bits = calloc(num_basis, sizeof(*basis_by_bits));

  char * str_build = calloc(MAX(3, 1 + num_dimensions) + 1, sizeof(char));

  for(int i = 0; i < num_basis; i++) {
    char * name = str_build;
    *name++ = 'e';
    for(int j = 0; j < num_dimensions; j++) {
      if(i & (1 << j)) {
        *name++ = first_basis + j;
      }
    }
    *name++ = '\0';
    basis[i].name = strdup(i ? str_build : "one");
    basis[i].bits = i;
    basis[i].grade = __builtin_popcount(i);
  }
  qsort(basis + 1, num_basis - 1, sizeof(*basis), _sort_basis, NULL);
   free(str_build);

  for(int i = 0; i < num_basis; i++) {
    basis_by_bits[basis[i].bits] = i;

    if(basis[i].grade == 0) {
      basis[i].metric = One;
    } else if(basis[i].grade == 1) {
      basis[i].metric = i ? (i - 1 < d ? Degenerate : (i - 1 - d < p ? Positive : Negative)) : One;
    } else {
      int sign = -1;
      for(int j = 0; j < num_dimensions; j++) {
        if(!(basis[i].bits & (1 << j))) {
          continue;
        }
        int other = basis_by_bits[1 << j];
        if(basis[other].metric == Degenerate) {
          sign = 0;
          break;
        }
        if(basis[other].metric == Negative) {
          sign *= -1;
        }
      }
      basis[i].metric = Degenerate + sign;
    }
  }

  _cayley_table = calloc(num_basis*num_basis, sizeof(BasisRef));
  _product_table = calloc(num_basis*num_basis, sizeof(BasisRef));

  printf("// cayley table:\n");
  for(int i = 0; i < num_basis; i++) {
    BasisRef a = (BasisRef) { .basis = i, .sign = 1 };

    printf("//");
    for(int j = 0; j < num_basis; j++) {
      BasisRef b = (BasisRef) { .basis = j, .sign = 1 };
      BasisRef c = _mul_basis_ref(a, b);
      _cayley_table[a.basis * num_basis + b.basis] = c;
      _product_table[c.basis * num_basis + a.basis].basis = b.basis;
      _product_table[c.basis * num_basis + a.basis].sign = c.sign;

      if(c.sign == -1) {
        printf(" -%-5s", basis[c.basis].name);
      } else if(c.sign == 0) {
        printf(" 0     ");
      } else if(c.sign == 1) {
        printf(" %-6s", basis[c.basis].name);
      } else {
        printf("err");
      }
    }

    printf("\n");
  }

  str_build = calloc(num_grades + 1, sizeof(*str_build));
  for(int i = 0; i < 1 << num_grades; i++) {
    char * s = str_build;
    for(int j = 0; j < num_grades; j++) {
      *s++ = (i & (1 << j)) ? '1' : '0';
    }

    printf("typedef struct %s_%s {", prefix, str_build);
    printf(" union { ");
    printf("float _; ");
    if(i > 0) {
      int first = 1;
      printf("struct { float");
      for(int j = 0; j < num_basis; j++) {
        if(i & (1 << basis[j].grade)) {
          printf("%s %s", first ? "" : ",", basis[j].name);
          first = 0;
        }
      }
      printf("; }; ");
    }
    printf("}; } %s_%s", prefix, str_build);

    if(i == 1 << 0) {
      printf(", %s_Scalar", prefix);
    } else if(i == 1 << 1) {
      printf(", %s_Vector", prefix);
    } else if(i == 1 << 2) {
      printf(", %s_Bivector", prefix);
    } else if(i == 1 << 3) {
      printf(", %s_Trivector", prefix);
    }

    if(i == 1 << (num_grades - 1)) {
      printf(", %s_AntiScalar", prefix);
    } else if(i == 1 << (num_grades - 2)) {
      printf(", %s_AntiVector", prefix);
    } else if(i == 1 << (num_grades - 3)) {
      printf(", %s_AntiBivector", prefix);
    } else if(i == 1 << (num_grades - 4)) {
      printf(", %s_AntiTrivector", prefix);
    }

    printf(";\n");
  }
  free(str_build);

  printf("#define %s_GRADE(RETURN, ", PREFIX); values('X'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_grades; i++) {
    printf(i ? "  , " : "    ");
    int start = 0;
    while(basis[start].grade < i) start++;
    int end = start;
    while(end < num_basis && basis[end].grade < i + 1) end++;
    int count = end - start;
    for(int j = start; j < end; j++) {
      int e = j == end - 1;
      if(e) {
        printf("%s_IS_NONZERO(X%s)", PREFIX, basis[j].name);
      } else {
        printf("%s_OR(%s_IS_NONZERO(X%s), ", PREFIX, PREFIX, basis[j].name);
      }
    }
    printf("%.*s" NL, count - 1, ")))))))))))))))))))))");
  }
  printf("  , ## __VA_ARGS__)\n");

  printf("#define %s_TYPE(", PREFIX); grades('X'); printf(") %s_TYPE_(", PREFIX); grades('X'); printf(")\n");
  printf("#define %s_TYPE_(", PREFIX); grades('X'); printf(") %s_", prefix);
  for(int i = 0; i < num_grades; i++) {
    printf(" ## X%i", i);
  }
  printf("\n");

  // unary ====================================================================================================================================================
  printf("#define %s_UNARY(OP, X) %s_UNARY0(OP, %s_UNPACK X)\n", PREFIX, PREFIX, PREFIX);
  printf("#define %s_UNARY0(...) %s_UNARY1(__VA_ARGS__)\n", PREFIX, PREFIX);
  printf("#define %s_UNARY1(OP, ", PREFIX); grades('X'); printf(",X) %s_UNARY2(" NL, PREFIX);
  printf("    OP" NL);
  for(int i = 0; i < num_basis; i++) {
    printf("  , %s_IF(X%i)(_x.%s)(0)" NL, PREFIX, basis[i].grade, basis[i].name);
  }
  printf("  , "); grades('X'); printf(",X" NL);
  printf("  )\n");
  printf("#define %s_UNARY2(OP, ", PREFIX); values('X'); printf(","); grades('X'); printf(",X) OP(%s_UNARY3, ", PREFIX); values('X'); printf(", "); grades('X'); printf(",X)\n");
  printf("#define %s_UNARY3(", PREFIX); values('Z'); printf(","); grades('X'); printf(",X) %s_GRADE(%s_UNARY4, ", PREFIX, PREFIX); values('Z'); printf(", "); values('Z'); printf(","); grades('X'); printf(",X)\n");
  printf("#define %s_UNARY4(", PREFIX); grades('Z'); printf(","); values('Z'); printf(","); grades('X'); printf(",X) ("); grades('Z'); printf(", __extension__ ({" NL);
  printf("  %s_TYPE(", PREFIX); grades('X'); printf(") _x = X;" NL);
  printf("  (%s_TYPE(", PREFIX); grades('Z'); printf(")) {" NL);
  printf("    ._ = 0" NL);
  for(int i = 0; i < num_basis; i++) {
    printf("    %s_IF(Z%i)(, .%s = Z%s)()" NL, PREFIX, basis[i].grade, basis[i].name, basis[i].name);
  }
  printf("  };" NL);
  printf("}))\n");

  // grade_x
  for(int i = 0; i < num_grades; i++) {
    printf("#define %s_OP_GRADE_%i(RETURN, ", PREFIX, i); values('X'); printf(", ...) RETURN(" NL);
    for(int j = 0; j < num_basis; j++) {
      printf(j ? "  , " : "    ");
      if(basis[j].grade == i) {
        printf("X%s" NL, basis[j].name);
      } else {
        printf("0" NL);
      }
    }
    printf("  , ## __VA_ARGS__)\n");
  }

  // negate
  printf("#define %s_OP_NEGATE(RETURN, ", PREFIX); values('X'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    printf("%s%s_NEG(X%s)" NL, i ? "  , " : "    ", PREFIX, basis[i].name);
  }
  printf("  , ## __VA_ARGS__)\n");

  // dual
  printf("#define %s_OP_DUAL(RETURN, ", PREFIX); values('X'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    BasisRef dual = _dual((BasisRef) { .basis = i, .sign = 1 });
    printf(i ? "  , " : "    ");
    if(dual.sign == -1) {
      printf("%s_NEG(X%s)", PREFIX, basis[dual.basis].name);
    } else if(dual.sign == 1) {
      printf("X%s", basis[dual.basis].name);
    } else {
      printf("0");
    }
    printf(NL);
  }
  printf("  , ## __VA_ARGS__)\n");

  // undual
  printf("#define %s_OP_UNDUAL(RETURN, ", PREFIX); values('X'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    BasisRef dual = _dual((BasisRef) { .basis = i, .sign = 1 });
    BasisRef dual2 = _dual((BasisRef) { .basis = num_basis - i - 1, .sign = 1 });
    printf(i ? "  , " : "    ");
    if(dual2.sign == -1) {
      printf("%s_NEG(X%s)", PREFIX, basis[dual.basis].name);
    } else if(dual2.sign == 1) {
      printf("X%s", basis[dual.basis].name);
    } else {
      printf("0");
    }
    printf(NL);
  }
  printf("  , ## __VA_ARGS__)\n");

  // polar
  if(d) {
    printf("#define %s_OP_POLAR(RETURN, ", PREFIX); values('X'); printf(", ...) RETURN(" NL);
    for(int i = 0; i < num_basis; i++) {
      for(int j = 0; j < num_basis; j++) {
        BasisRef polar = _mul_basis_ref((BasisRef) { .basis = j, .sign = 1 }, (BasisRef) { .basis = num_basis - 1, .sign = 1 });
        if(polar.basis != i) {
          continue;
        }

        printf(i ? "  , " : "    ");
        if(polar.sign == -1) {
          printf("%s_NEG(X%s)", PREFIX, basis[polar.basis].name);
        } else if(polar.sign == 1) {
          printf("X%s", basis[polar.basis].name);
        } else {
          printf("0");
        }
      }

      printf(NL);
    }
    printf("  , ## __VA_ARGS__)\n");
  }

  // reverse
  printf("#define %s_OP_REVERSE(RETURN, ", PREFIX); values('X'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    if(basis[i].grade % 4 < 2) {
      printf("%sX%s" NL, i ? "  , " : "    ", basis[i].name);
    } else {
      printf("%s%s_NEG(X%s)" NL, i ? "  , " : "    ", PREFIX, basis[i].name);
    }
  }
  printf("  , ## __VA_ARGS__)\n");

  // involute
  printf("#define %s_OP_INVOLUTE(RETURN, ", PREFIX); values('X'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    if(basis[i].grade % 2 < 1) {
      printf("%sX%s" NL, i ? "  , " : "    ", basis[i].name);
    } else {
      printf("%s%s_NEG(X%s)" NL, i ? "  , " : "    ", PREFIX, basis[i].name);
    }
  }
  printf("  , ## __VA_ARGS__)\n");

  // conjugate
  printf("#define %s_OP_CONJUGATE(RETURN, ", PREFIX); values('X'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    if((basis[i].grade + 1) % 4 < 2) {
      printf("%sX%s" NL, i ? "  , " : "    ", basis[i].name);
    } else {
      printf("%s%s_NEG(X%s)" NL, i ? "  , " : "    ", PREFIX, basis[i].name);
    }
  }
  printf("  , ## __VA_ARGS__)\n");

  // binary
  printf("#define %s_BINARY(OP, X, Y) %s_BINARY0(OP, %s_UNPACK X, %s_UNPACK Y)\n", PREFIX, PREFIX, PREFIX, PREFIX);
  printf("#define %s_BINARY0(...) %s_BINARY1(__VA_ARGS__)\n", PREFIX, PREFIX);
  printf("#define %s_BINARY1(OP, ", PREFIX); grades('X'); printf(",X,"); grades('Y'); printf(",Y) %s_BINARY2(" NL, PREFIX);
  printf("    OP" NL);
  for(int i = 0; i < num_basis; i++) {
    printf("  , %s_IF(X%i)(_x.%s)(0)" NL, PREFIX, basis[i].grade, basis[i].name);
  }
  for(int i = 0; i < num_basis; i++) {
    printf("  , %s_IF(Y%i)(_y.%s)(0)" NL, PREFIX, basis[i].grade, basis[i].name);
  }
  printf("  , "); grades('X'); printf(",X" NL);
  printf("  , "); grades('Y'); printf(",Y" NL);
  printf("  )\n");
  printf("#define %s_BINARY2(OP, ", PREFIX); values('X'); printf(","); values('Y'); printf(","); grades('X'); printf(",X, "); grades('Y'); printf(",Y) OP(%s_BINARY3, ", PREFIX); values('X'); printf(","); values('Y'); printf(", "); grades('X'); printf(",X, "); grades('Y'); printf(",Y)\n");
  printf("#define %s_BINARY3(", PREFIX); values('Z'); printf(","); grades('X'); printf(",X, "); grades('Y'); printf(",Y) %s_GRADE(%s_BINARY4, ", PREFIX, PREFIX); values('Z'); printf(", "); values('Z'); printf(","); grades('X'); printf(",X, "); grades('Y'); printf(",Y)\n");
  printf("#define %s_BINARY4(", PREFIX); grades('Z'); printf(","); values('Z'); printf(","); grades('X'); printf(",X, "); grades('Y'); printf(",Y) ("); grades('Z'); printf(", __extension__ ({" NL);
  printf("  %s_TYPE(", PREFIX); grades('X'); printf(") _x = X;" NL);
  printf("  %s_TYPE(", PREFIX); grades('Y'); printf(") _y = Y;" NL);
  printf("  (%s_TYPE(", PREFIX); grades('Z'); printf(")) {" NL);
  printf("    ._ = 0" NL);
  for(int i = 0; i < num_basis; i++) {
    printf("    %s_IF(Z%i)(, .%s = Z%s)()" NL, PREFIX, basis[i].grade, basis[i].name, basis[i].name);
  }
  printf("  };" NL);
  printf("}))\n");

  // add
  printf("#define %s_OP_ADD(RETURN, ", PREFIX); values('X'); printf(", "); values('Y'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    printf("  %s%s_ADD(X%s, Y%s)" NL, i ? ", " : "  ", PREFIX, basis[i].name, basis[i].name);
  }
  printf("  , ## __VA_ARGS__)\n");

  // sub
  printf("#define %s_OP_SUBTRACT(RETURN, ", PREFIX); values('X'); printf(", "); values('Y'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    printf("  %s%s_SUB(X%s, Y%s)" NL, i ? ", " : "  ", PREFIX, basis[i].name, basis[i].name);
  }
  printf("  , ## __VA_ARGS__)\n");

  // geometric product
  printf("#define %s_OP_GEOMETRIC_PRODUCT(RETURN, ", PREFIX); values('X'); printf(", "); values('Y'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    printf("  %s0", i ? ", " : "  ");
    BasisRef c = (BasisRef) { i, 1 };
    for(int j = 0; j < num_basis; j++) {
      BasisRef a = (BasisRef) { j, 1 };
      BasisRef b = _product_table[c.basis * num_basis + a.basis];
      if(b.sign == -1) {
        printf(" %s_SUB_MUL(X%s,Y%s)", PREFIX, basis[a.basis].name, basis[b.basis].name);
      } else if(b.sign == 1) {
        printf(" %s_ADD_MUL(X%s,Y%s)", PREFIX, basis[a.basis].name, basis[b.basis].name);
      }
    }
    printf(NL);
  }
  printf("  , ## __VA_ARGS__)\n");

  // outer product
  printf("#define %s_OP_OUTER_PRODUCT(RETURN, ", PREFIX); values('X'); printf(", "); values('Y'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    printf("  %s0", i ? ", " : "  ");
    BasisRef c = (BasisRef) { i, 1 };
    for(int j = 0; j < num_basis; j++) {
      BasisRef a = (BasisRef) { j, 1 };
      BasisRef b = _product_table[c.basis * num_basis + a.basis];
      if(basis[a.basis].grade + basis[b.basis].grade != basis[c.basis].grade) {
        continue;
      }
      if(b.sign == -1) {
        printf(" %s_SUB_MUL(X%s,Y%s)", PREFIX, basis[a.basis].name, basis[b.basis].name);
      } else if(b.sign == 1) {
        printf(" %s_ADD_MUL(X%s,Y%s)", PREFIX, basis[a.basis].name, basis[b.basis].name);
      }
    }
    printf(NL);
  }
  printf("  , ## __VA_ARGS__)\n");

  // regressive product
  printf("#define %s_OP_REGRESSIVE_PRODUCT(RETURN, ", PREFIX); values('X'); printf(", "); values('Y'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    printf("  %s0", i ? ", " : "  ");

    // instead of the Product table use Cayley table and select based on output
    for(int j = 0; j < num_basis; j++) {
      BasisRef a = (BasisRef) { j, 1 }, ad = _dual(a);

      for(int k = 0; k < num_basis; k++) {
        BasisRef b = (BasisRef) { k, 1 }, bd = _dual(b);

        BasisRef c = _cayley_table[ad.basis * num_basis + bd.basis], cd = _dual(c);

        // limit output to dual basis
        if(cd.basis != i) {
          continue;
        }

        // and then non-dual grade selection of outer product
        if(basis[ad.basis].grade + basis[bd.basis].grade != basis[c.basis].grade) {
          continue;
        }

        int sign = ad.sign * bd.sign * c.sign * cd.sign;

        if(sign == -1) {
          printf(" %s_SUB_MUL(X%s,Y%s)", PREFIX, basis[a.basis].name, basis[b.basis].name);
        } else if(sign == 1) {
          printf(" %s_ADD_MUL(X%s,Y%s)", PREFIX, basis[a.basis].name, basis[b.basis].name);
        }
      }
    }
    printf(NL);
  }
  printf("  , ## __VA_ARGS__)\n");

  // commutator product
  printf("#define %s_OP_COMMUTATOR_PRODUCT(RETURN, ", PREFIX); values('X'); printf(", "); values('Y'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    printf("  %s0", i ? ", " : "  ");
    BasisRef c = (BasisRef) { i, 1 };

    // instead of the Product table use Cayley table and select based on output
    for(int j = 0; j < num_basis; j++) {
      BasisRef a = (BasisRef) { j, 1 };

      for(int k = 0; k < num_basis; k++) {
        BasisRef b = (BasisRef) { k, 1 };

        BasisRef ab = _cayley_table[a.basis * num_basis + b.basis];
        BasisRef ba = _cayley_table[b.basis * num_basis + a.basis];

        if(ab.basis == ba.basis && ab.sign == ba.sign) {
          continue;
        }

        if(ab.basis != c.basis) {
          continue;
        }

        if(ab.sign == -1) {
          printf(" %s_SUB_MUL(X%s,Y%s)", PREFIX, basis[a.basis].name, basis[b.basis].name);
        } else if(ab.sign == 1) {
          printf(" %s_ADD_MUL(X%s,Y%s)", PREFIX, basis[a.basis].name, basis[b.basis].name);
        }
      }
    }
    printf(NL);
  }
  printf("  , ## __VA_ARGS__)\n");

  // inner product
  printf("#define %s_OP_INNER_PRODUCT(RETURN, ", PREFIX); values('X'); printf(", "); values('Y'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    printf("  %s0", i ? ", " : "  ");
    BasisRef c = (BasisRef) { i, 1 };
    for(int j = 0; j < num_basis; j++) {
      BasisRef a = (BasisRef) { j, 1 };
      BasisRef b = _product_table[c.basis * num_basis + a.basis];
      if(abs(basis[b.basis].grade - basis[a.basis].grade) != basis[c.basis].grade) {
        continue;
      }
      if(b.sign == -1) {
        printf(" %s_SUB_MUL(X%s,Y%s)", PREFIX, basis[a.basis].name, basis[b.basis].name);
      } else if(b.sign == 1) {
        printf(" %s_ADD_MUL(X%s,Y%s)", PREFIX, basis[a.basis].name, basis[b.basis].name);
      }
    }
    printf(NL);
  }
  printf("  , ## __VA_ARGS__)\n");

  // left dot
  printf("#define %s_OP_LEFT_DOT_PRODUCT(RETURN, ", PREFIX); values('X'); printf(", "); values('Y'); printf(", ...) RETURN(" NL);
  for(int i = 0; i < num_basis; i++) {
    printf("  %s0", i ? ", " : "  ");
    BasisRef c = (BasisRef) { i, 1 };
    for(int j = 0; j < num_basis; j++) {
      BasisRef a = (BasisRef) { j, 1 };
      BasisRef b = _product_table[c.basis * num_basis + a.basis];
      if((basis[b.basis].grade - basis[a.basis].grade) != basis[c.basis].grade) {
        continue;
      }
      if(b.sign == -1) {
        printf(" %s_SUB_MUL(X%s,Y%s)", PREFIX, basis[a.basis].name, basis[b.basis].name);
      } else if(b.sign == 1) {
        printf(" %s_ADD_MUL(X%s,Y%s)", PREFIX, basis[a.basis].name, basis[b.basis].name);
      }
    }
    printf(NL);
  }
  printf("  , ## __VA_ARGS__)\n");

  // cpp interface
  // type coding
  char gcodes[] = "svbtq___";
  if(num_grades > 5) {
    gcodes[num_grades - 2] = 'V';
  }
  gcodes[num_grades - 1] = 'S';
  gcodes[num_grades] = 0;

  for(int i = 0; i < num_grades; i++) {
    _add_code(gcodes[i], 1 << i);
  }

  struct {
    const char * lower;
    const char * upper;
    int argument_count;
  } op[] = {
      { "negate",             "NEGATE",             1 }
    , { "dual",               "DUAL",               1 }
    , { "undual",             "UNDUAL",             1 }
    , { "polar",              "POLAR",              1 }
    , { "reverse",            "REVERSE",            1 }
    , { "involute",           "INVOLUTE",           1 }
    , { "conjugate",          "CONJUGATE",          1 }
    , { "add",                "ADD",                2 }
    , { "subtract",           "SUBTRACT",           2 }
    , { "geometric_product",  "GEOMETRIC_PRODUCT",  2 }
    , { "outer_product",      "OUTER_PRODUCT",      2 }
    , { "regressive_product", "REGRESSIVE_PRODUCT", 2 }
    , { "commutator_product", "COMMUTATOR_PRODUCT", 2 }
    , { "inner_product",      "INNER_PRODUCT",      2 }
    , { "left_dot_product",   "LEFT_DOT_PRODUCT",   2 }
  };

  if(d == 0) {
    op[2].lower = NULL;
    op[2].upper = NULL;
    op[2].argument_count = 0;
  }

  for(int i = 0; i < num_codes; i++) {
    printf("#define %s_%c(X) (", prefix, codes[i].code);
    for(int j = 0; j < num_grades; j++) {
      printf(codes[i].grades & (1 << j) ? "1," : "0,");
    }
    if(codes[i].grades == 1) {
      printf("_Generic((X), %s_Scalar: X, default: ((%s_Scalar){ .one = (float)X }))", prefix, prefix);
    } else {
      printf("X");
    }
    printf(")\n");
  }
  for(int i = 0; i < num_grades; i++) {
    printf("#define %s_grade_%i(X) %s_UNARY(%s_OP_GRADE_%i, X)\n", prefix, i, PREFIX, PREFIX, i);
  }

  for(unsigned int i = 0; i < (sizeof(op)/sizeof(op[0])); i++) {
    if(op[i].argument_count == 0) {
      continue;
    }

    if(op[i].argument_count == 1) {
      printf("#define %s_%s(X) %s_UNARY(%s_OP_%s, X)\n", prefix, op[i].lower, PREFIX, PREFIX, op[i].upper);
      for(int j = 0; j < num_codes; j++) {
        printf("#define %s_%s_%c(X) %s_%s(%s_%c(X))\n", prefix, op[i].lower, codes[j].code, prefix, op[i].lower, prefix, codes[j].code);
      }
    } else {
      printf("#define %s_%s(X, Y) %s_BINARY(%s_OP_%s, X, Y)\n", prefix, op[i].lower, PREFIX, PREFIX, op[i].upper);
      for(int j = 0; j < num_codes; j++) {
        for(int k = 0; k < num_codes; k++) {
          printf("#define %s_%s_%c%c(X, Y) %s_%s(%s_%c(X), %s_%c(Y))\n", prefix, op[i].lower, codes[j].code, codes[k].code, prefix, op[i].lower, prefix, codes[j].code, prefix, codes[k].code);
        }
      }
    }
  }

  for(unsigned int i = 0; i < num_op_alias; i++) {
    if(!op_alias[i].binary) {
      printf("#define %s_%s(X) %s_%s(X)\n", prefix, op_alias[i].from, prefix, op_alias[i].to);
      for(int j = 0; j < num_codes; j++) {
        printf("#define %s_%s_%c(X) %s_%s(%s_%c(X))\n", prefix, op_alias[i].from, codes[j].code, prefix, op_alias[i].from, prefix, codes[j].code);
      }
    } else {
      printf("#define %s_%s(X, Y) %s_%s(X, Y)\n", prefix, op_alias[i].from, prefix, op_alias[i].to);
      for(int j = 0; j < num_codes; j++) {
        for(int k = 0; k < num_codes; k++) {
          printf("#define %s_%s_%c%c(X, Y) %s_%s(%s_%c(X), %s_%c(Y))\n", prefix, op_alias[i].from, codes[j].code, codes[k].code, prefix, op_alias[i].from, prefix, codes[j].code, prefix, codes[k].code);
        }
      }
    }
  }

  printf("#endif // _%s_H_\n", PREFIX);
}

const char * license =
  "// This Source Code Form is subject to the terms of the Mozilla Public\n"
  "// License, v. 2.0. If a copy of the MPL was not distributed with this\n"
  "// file, You can obtain one at http://mozilla.org/MPL/2.0/.\n"
  ;

int main(int argc, char * argv []) {
  struct option longopts[] = {
      { "positive", required_argument, NULL, 'p' }
    , { "negative", required_argument, NULL, 'n' }
    , { "degenerate", required_argument, NULL, 'd' }
    , { "prefix", required_argument, NULL, 0 }
    , { "unary", required_argument, NULL, 0 }
    , { "binary", required_argument, NULL, 0 }
    , { "code", required_argument, NULL, 0 }
    , { NULL, no_argument, NULL, 0 }
  };

  printf("%s", license);
  printf("// generated with alias_gen_geometric_algebra (author Sarah Burns <mystical.unicat@gmail.com>)\n");
  printf("// options:");
  for(int i = 1; i < argc; i++) {
    printf(" %s", argv[i]);
  }
  printf("\n");

  for(;;) {
    int longindex;
    int opt = getopt_long_only(argc, argv, "p:n:d:", longopts, &longindex);

    if(opt == -1) {
      break;
    }

    switch(opt) {
    case 0:
      switch(longindex) {
      case 3:
        Prefix = optarg;
        break;
      case 4:
        _add_op_alias(optarg, argv[optind], 0);
        optind++;
        break;
      case 5:
        _add_op_alias(optarg, argv[optind], 1);
        optind++;
        break;
      case 6:
        {
          uint32_t grades = 0, l = strlen(optarg);
          for(int i = 1; i < l; i++) {
            grades |= (1 << (optarg[i] - '0'));
          }
          _add_code(optarg[0], grades);
        }
      default:
        break;
      }
      break;
    case 'p':
      p = atoi(optarg);
      break;
    case 'n':
      n = atoi(optarg);
      break;
    case 'd':
      d = atoi(optarg);
      break;
    }
  }

  p = 2;
  d = 1;

  _add_op_alias("neg", "negate", 0);
  _add_op_alias("sub", "subtract", 1);
  _add_op_alias("mul", "geometric_product", 1);
  _add_op_alias("weg", "outer_product", 1);
  _add_op_alias("vee", "regressive_product", 1);
  _add_op_alias("dot", "inner_product", 1);

  if(Prefix == NULL) {
    struct { int p, n, d; const char * name; } names[] = {
        { 2, 0, 1, "ALIAS_PGA2D" }
      , { 3, 0, 1, "ALIAS_PGA3D" }
      , { 3, 1, 0, "ALIAS_CGA2D" }
      , { 4, 1, 0, "ALIAS_CGA3D" }
    };

    for(int i = 0; i < sizeof(names)/sizeof(names[0]); i++) {
      if(names[i].p == p && names[i].n == n && names[i].d == d) {
        Prefix = (char *)names[i].name;
        break;
      }
    }
  }

  if(Prefix == NULL) {
    int length = cprintf("ALIAS_GA%i_%i_%i", p, n, d);
    Prefix = calloc(length + 1, 1);
    sprintf(Prefix, length + 1, "ALIAS_GA%i_%i_%i", p, n, d);
  }

  int prefix_length = strlen(Prefix);
  PREFIX = calloc(prefix_length + 1, 1);
  prefix = calloc(prefix_length + 1, 1);

  for(int i = 0; Prefix[i]; i++) {
    PREFIX[i] = toupper(Prefix[i]);
    prefix[i] = tolower(Prefix[i]);
  }

  generate();
}


