#define TABULA_NO_REPLACEMENT_MACROS
#include "tabula.h"

unsigned int tests_run = 0;
unsigned int tests_failed = 0;

#define CAT(X, ...) CAT0(X, ##__VA_ARGS__)
#define CAT0(X, ...) CAT1(X, ##__VA_ARGS__)
#define CAT1(X, ...) X##__VA_ARGS__

#define STR(X, ...) STR0(X, ##__VA_ARGS__)
#define STR0(X, ...) STR1(X, ##__VA_ARGS__)
#define STR1(X, ...) #X #__VA_ARGS__

#define BITS_FLAGS 1
#define BITS_WIDTH 2
#define BITS_PRECISION 4
#define BITS_ARGUMENT 8
#define BITS_PLACEMENT 16

uint32_t require_bits = 0;
uint32_t require_mask = BITS_FLAGS | BITS_WIDTH | BITS_PRECISION | BITS_ARGUMENT | BITS_PLACEMENT;

void test_same(const char *name, const char *argument_string, const char *format, ...) {
  char t_buffer[1024];
  char s_buffer[1024];

  va_list ap_, ap;
  va_start(ap_, format);

  va_copy(ap, ap_);
  int t_result = tabula_vsprintf(t_buffer, 1024, format, ap);
  va_end(ap);

  va_copy(ap, ap_);
  int s_result = vsprintf(s_buffer, format, ap);
  va_end(ap);

  tests_run++;
  if(t_result != s_result || strcmp(t_buffer, s_buffer)) {
    printf("sprintf(\"%s\", %s);\n", format, argument_string);
    printf("    tabula %d \"%s\"\n", t_result, t_buffer);
    printf("  standard %d \"%s\"\n", s_result, s_buffer);
    tests_failed++;
    return;
  }

  t_buffer[0] = 'X';
  t_buffer[1] = '\0';
  s_buffer[0] = 'X';
  s_buffer[1] = '\0';
  int limit = s_result / 2;

  va_copy(ap, ap_);
  int t_result2 = tabula_vsnprintf(t_buffer, 1024, limit, format, ap);
  va_end(ap);

  va_copy(ap, ap_);
  int s_result2 = vsnprintf(s_buffer, limit, format, ap);
  va_end(ap);

  if(t_result2 != s_result2 || strcmp(t_buffer, s_buffer)) {
    printf("snprintf(%d, \"%s\", %s);\n", limit, format, argument_string);
    printf("    tabula %d \"%s\"\n", t_result2, t_buffer);
    printf("  standard %d \"%s\"\n", s_result2, s_buffer);
    tests_failed++;
  }
}

void test_pair(const char *name, const char *first_argument_string, const char *first_format, va_list first_ap, const char *second_argument_string, const char *second_format, va_list second_ap) {
  char t_buffer[1024];
  char s_buffer[1024];

  va_list ap;

  va_copy(ap, first_ap);
  int t_result = tabula_vsprintf(t_buffer, 1024, first_format, ap);
  va_end(ap);

  va_copy(ap, second_ap);
  int s_result = tabula_vsprintf(s_buffer, 1024, second_format, ap);
  va_end(ap);

  tests_run++;
  if(t_result != s_result || strcmp(t_buffer, s_buffer)) {
    printf("sprintf(\"%s\", %s) vs sprintf(\"%s\", %s);\n", first_format, first_argument_string, second_format, second_argument_string);
    printf("    tabula %d \"%s\"\n", t_result, t_buffer);
    printf("  standard %d \"%s\"\n", s_result, s_buffer);
    tests_failed++;
    return;
  }

  t_buffer[0] = 'X';
  t_buffer[1] = '\0';
  s_buffer[0] = 'X';
  s_buffer[1] = '\0';
  int limit = s_result / 2;

  va_copy(ap, first_ap);
  int t_result2 = tabula_vsnprintf(t_buffer, 1024, limit, first_format, ap);
  va_end(ap);

  va_copy(ap, second_ap);
  int s_result2 = tabula_vsnprintf(s_buffer, 1024, limit, second_format, ap);
  va_end(ap);

  if(t_result2 != s_result2 || strcmp(t_buffer, s_buffer)) {
  fail:
    printf("snprintf(\"%s\", %i, %s) vs snprintf(\"%s\", %i, %s);\n", first_format, limit, first_argument_string, second_format, limit, second_argument_string);
    printf("    tabula %d \"%s\"\n", t_result, t_buffer);
    printf("  standard %d \"%s\"\n", s_result, s_buffer);
    tests_failed++;
  }
}

#define TEST_SAME(NAME, BITS, FORMAT, ...)                                                                             \
  void NAME##_test(void) { test_same(#NAME, #__VA_ARGS__, FORMAT, ##__VA_ARGS__); }

#define EXTRACT_SIDE_FORMAT_l(FORMAT, ...) FORMAT
#define EXTRACT_SIDE_FORMAT(SIDE) CAT(EXTRACT_SIDE_FORMAT_, SIDE)

#define EXTRACT_SIDE_ARGUMENT_STRING_l(FORMAT, ...) # __VA_ARGS__
#define EXTRACT_SIDE_ARGUMENT_STRING(SIDE) CAT(EXTRACT_SIDE_ARGUMENT_STRING_, SIDE)

#define EXTRACT_SIDE_ARGUMENTS_l(FORMAT, ...) __VA_ARGS__
#define EXTRACT_SIDE_ARGUMENTS(SIDE) CAT(EXTRACT_SIDE_ARGUMENTS_, SIDE)

#define TEST_PAIR(NAME, BITS, FIRST, SECOND)                                                                             \
  static void NAME##_test3(const char * first_format, va_list first_ap, const char * second_format, ... ) { \
    va_list second_ap; \
    va_start(second_ap, second_format); \
    test_pair(#NAME, EXTRACT_SIDE_ARGUMENT_STRING(FIRST), first_format, first_ap, EXTRACT_SIDE_ARGUMENT_STRING(SECOND), second_format, second_ap); \
    va_end(second_ap); \
  } \
  static void NAME##_test2(const char * format, ...) { \
    va_list ap; \
    va_start(ap, format); \
    NAME##_test3(format, ap, EXTRACT_SIDE_FORMAT(SECOND), EXTRACT_SIDE_ARGUMENTS(SECOND)); \
    va_end(ap); \
  } \
  static void NAME##_test(void) { \
    NAME##_test2(EXTRACT_SIDE_FORMAT(FIRST), EXTRACT_SIDE_ARGUMENTS(FIRST)); \
  }

TEST_PAIR(_plc__1, BITS_PLACEMENT, l("%2$s %1$s", "bar", "foo"), l("%s %s", "foo", "bar"))

#define TEST_RUN(NAME, BITS, FORMAT, ...)                                                                              \
  if((require_mask & (BITS)) == require_bits)                                                                          \
    NAME##_test();

char a_ = 'A', b_ = 'B', c_ = 'C';

#define STANDARD_TESTS(NAME, X)                                                                                        \
  /*X(NAME##_std_1_, 0, "%%")*/                                                                                        \
  X(NAME##_std_2_, 0, "%d%d", 1234, 5678)                                                                              \
  X(NAME##_std_3_, 0, "%d%s", 1234, "test")                                                                            \
  X(NAME##_std_4_, 0, "%s%d", "test", 1234)                                                                            \
  X(NAME##_std_5_, 0, "%s%s", "test", "more")                                                                          \
  X(NAME##_std_6_, 0, "%.2s%.2s", "test", "more")                                                                      \
  X(NAME##_std_7_, 0, "%4.02d", 3)                                                                                     \
  X(NAME##_std_8_, 0, "%4.02s", "test")                                                                                \
  X(NAME##_std_9_, 0, "%c%c%c", a_, b_, c_)                                                                            \
  X(NAME##_std10_, 0, "%d%d%d", a_, b_, c_)                                                                            \
  X(NAME##_std11_, 0, "%d%%%d", 1234, 5678)                                                                            \
  X(NAME##_std12_, 0, "%d%%%s", 1234, "test")                                                                          \
  X(NAME##_std13_, 0, "%s%%%d", "test", 1234)                                                                          \
  X(NAME##_std14_, 0, "%s%%%s", "test", "more")                                                                        \
  X(NAME##_std15_, 0, "%.2s%%%.2s", "test", "more")                                                                    \
  X(NAME##_std16_, 0, "a%4.02dc", 3)                                                                                   \
  X(NAME##_std17_, 0, "d%4.02sf", "test")

#define NUMBER_FLAGS(NAME, BITS, X, ...)                                                                               \
  X(NAME##_flg_1_, BITS, "", ##__VA_ARGS__)                                                                            \
  X(NAME##_flg_2_, BITS | BITS_FLAGS, "-", ##__VA_ARGS__)                                                              \
  X(NAME##_flg_3_, BITS | BITS_FLAGS, "0", ##__VA_ARGS__)                                                              \
  X(NAME##_flg_4_, BITS | BITS_FLAGS, "+", ##__VA_ARGS__)                                                              \
  X(NAME##_flg_5_, BITS | BITS_FLAGS, " ", ##__VA_ARGS__)                                                              \
  X(NAME##_flg_6_, BITS | BITS_FLAGS, "#", ##__VA_ARGS__)                                                              \
  X(NAME##_flg_7_, BITS | BITS_FLAGS, "-0", ##__VA_ARGS__)                                                             \
  X(NAME##_flg_8_, BITS | BITS_FLAGS, "-+", ##__VA_ARGS__)                                                             \
  X(NAME##_flg_9_, BITS | BITS_FLAGS, "- ", ##__VA_ARGS__)                                                             \
  X(NAME##_flg10_, BITS | BITS_FLAGS, "-#", ##__VA_ARGS__)                                                             \
  X(NAME##_flg11_, BITS | BITS_FLAGS, "0+", ##__VA_ARGS__)                                                             \
  X(NAME##_flg12_, BITS | BITS_FLAGS, "0 ", ##__VA_ARGS__)                                                             \
  X(NAME##_flg13_, BITS | BITS_FLAGS, "0#", ##__VA_ARGS__)                                                             \
  X(NAME##_flg14_, BITS | BITS_FLAGS, "+ ", ##__VA_ARGS__)                                                             \
  X(NAME##_flg15_, BITS | BITS_FLAGS, " #", ##__VA_ARGS__)                                                             \
  X(NAME##_flg16_, BITS | BITS_FLAGS, "-0+", ##__VA_ARGS__)                                                            \
  X(NAME##_flg17_, BITS | BITS_FLAGS, "-0 ", ##__VA_ARGS__)                                                            \
  X(NAME##_flg18_, BITS | BITS_FLAGS, "-0#", ##__VA_ARGS__)                                                            \
  X(NAME##_flg19_, BITS | BITS_FLAGS, "-+ ", ##__VA_ARGS__)                                                            \
  X(NAME##_flg20_, BITS | BITS_FLAGS, "- #", ##__VA_ARGS__)                                                            \
  X(NAME##_flg21_, BITS | BITS_FLAGS, "0+ ", ##__VA_ARGS__)                                                            \
  X(NAME##_flg22_, BITS | BITS_FLAGS, "0+#", ##__VA_ARGS__)                                                            \
  X(NAME##_flg23_, BITS | BITS_FLAGS, "+ #", ##__VA_ARGS__)                                                            \
  X(NAME##_flg24_, BITS | BITS_FLAGS, "-0+ ", ##__VA_ARGS__)                                                           \
  X(NAME##_flg25_, BITS | BITS_FLAGS, "-0+#", ##__VA_ARGS__)                                                           \
  X(NAME##_flg26_, BITS | BITS_FLAGS, "-+ #", ##__VA_ARGS__)                                                           \
  X(NAME##_flg27_, BITS | BITS_FLAGS, "0+ #", ##__VA_ARGS__)                                                           \
  X(NAME##_flg28_, BITS | BITS_FLAGS, "-0+ #", ##__VA_ARGS__)                                                          \
  X(NAME##_flg29_, BITS | BITS_FLAGS, "--", ##__VA_ARGS__)                                                             \
  X(NAME##_flg30_, BITS | BITS_FLAGS, "00", ##__VA_ARGS__)                                                             \
  X(NAME##_flg31_, BITS | BITS_FLAGS, "++", ##__VA_ARGS__)                                                             \
  X(NAME##_flg32_, BITS | BITS_FLAGS, "  ", ##__VA_ARGS__)                                                             \
  X(NAME##_flg33_, BITS | BITS_FLAGS, "##", ##__VA_ARGS__)                                                             \
  X(NAME##_flg34_, BITS | BITS_FLAGS, "-00", ##__VA_ARGS__)                                                            \
  X(NAME##_flg35_, BITS | BITS_FLAGS, "-++", ##__VA_ARGS__)                                                            \
  X(NAME##_flg36_, BITS | BITS_FLAGS, "- - ", ##__VA_ARGS__)                                                           \
  X(NAME##_flg37_, BITS | BITS_FLAGS, "0  -#", ##__VA_ARGS__)                                                          \
  X(NAME##_flg38_, BITS | BITS_FLAGS, "--+# ", ##__VA_ARGS__)                                                          \
  X(NAME##_flg39_, BITS | BITS_FLAGS, "--0", ##__VA_ARGS__)

#define CHARACTER_FLAGS(NAME, BITS, X, ...)                                                                            \
  X(NAME##_flg_1_, BITS, "", ##__VA_ARGS__)                                                                            \
  X(NAME##_flg_2_, BITS | BITS_FLAGS, "-", ##__VA_ARGS__)                                                              \
  X(NAME##_flg_4_, BITS | BITS_FLAGS, "+", ##__VA_ARGS__)                                                              \
  X(NAME##_flg_5_, BITS | BITS_FLAGS, " ", ##__VA_ARGS__)                                                              \
  X(NAME##_flg_6_, BITS | BITS_FLAGS, "#", ##__VA_ARGS__)                                                              \
  X(NAME##_flg_8_, BITS | BITS_FLAGS, "-+", ##__VA_ARGS__)                                                             \
  X(NAME##_flg_9_, BITS | BITS_FLAGS, "- ", ##__VA_ARGS__)                                                             \
  X(NAME##_flg10_, BITS | BITS_FLAGS, "-#", ##__VA_ARGS__)                                                             \
  X(NAME##_flg14_, BITS | BITS_FLAGS, "+ ", ##__VA_ARGS__)                                                             \
  X(NAME##_flg15_, BITS | BITS_FLAGS, " #", ##__VA_ARGS__)                                                             \
  X(NAME##_flg19_, BITS | BITS_FLAGS, "-+ ", ##__VA_ARGS__)                                                            \
  X(NAME##_flg20_, BITS | BITS_FLAGS, "- #", ##__VA_ARGS__)                                                            \
  X(NAME##_flg23_, BITS | BITS_FLAGS, "+ #", ##__VA_ARGS__)                                                            \
  X(NAME##_flg26_, BITS | BITS_FLAGS, "-+ #", ##__VA_ARGS__)                                                           \
  X(NAME##_flg29_, BITS | BITS_FLAGS, "--", ##__VA_ARGS__)                                                             \
  X(NAME##_flg31_, BITS | BITS_FLAGS, "++", ##__VA_ARGS__)                                                             \
  X(NAME##_flg32_, BITS | BITS_FLAGS, "  ", ##__VA_ARGS__)                                                             \
  X(NAME##_flg33_, BITS | BITS_FLAGS, "##", ##__VA_ARGS__)                                                             \
  X(NAME##_flg35_, BITS | BITS_FLAGS, "-++", ##__VA_ARGS__)                                                            \
  X(NAME##_flg36_, BITS | BITS_FLAGS, "- - ", ##__VA_ARGS__)                                                           \
  X(NAME##_flg38_, BITS | BITS_FLAGS, "--+# ", ##__VA_ARGS__)

#define ARGUMENT_TEST_INTEGER(NAME, BITS, FLAGS, LENGTH, TYPE, ARG, X) X(NAME, BITS, "%" FLAGS #LENGTH #TYPE, ARG)
#define ARGUMENT_TEST_STRING(NAME, BITS, FLAGS, LENGTH, TYPE, ARG, X)  X(NAME, BITS, "%" FLAGS #LENGTH #TYPE, ARG)
#define ARGUMENT_TEST_POINTER(NAME, BITS, FLAGS, LENGTH, TYPE, ARG, X) X(NAME, BITS, "%" FLAGS #LENGTH #TYPE, ARG)

#define ARGUMENT_TEST_d(NAME, LENGTH, TYPE, ARG, X) ARGUMENT_TEST_i(NAME, LENGTH, TYPE, ARG, X)
#define ARGUMENT_TEST_u(NAME, LENGTH, TYPE, ARG, X) ARGUMENT_TEST_i(NAME, LENGTH, TYPE, ARG, X)
#define ARGUMENT_TEST_x(NAME, LENGTH, TYPE, ARG, X) ARGUMENT_TEST_i(NAME, LENGTH, TYPE, ARG, X)
#define ARGUMENT_TEST_X(NAME, LENGTH, TYPE, ARG, X) ARGUMENT_TEST_i(NAME, LENGTH, TYPE, ARG, X)
#define ARGUMENT_TEST_o(NAME, LENGTH, TYPE, ARG, X) ARGUMENT_TEST_i(NAME, LENGTH, TYPE, ARG, X)
#define ARGUMENT_TEST_i(NAME, LENGTH, TYPE, ARG, X) /* no restriction */                                               \
  NUMBER_FLAGS(NAME, BITS_ARGUMENT, ARGUMENT_TEST_INTEGER, LENGTH, TYPE, ARG, X)

#define ARGUMENT_TEST_s(NAME, LENGTH, TYPE, ARG,                                                                       \
                        X) /* no 0 flags, no dynamic precision */                   \
  CHARACTER_FLAGS(NAME, BITS_ARGUMENT, ARGUMENT_TEST_STRING, LENGTH, TYPE, ARG, X)

#define ARGUMENT_TEST_c(NAME, LENGTH, TYPE, ARG, X) /* no 0 flags */                                                   \
  CHARACTER_FLAGS(NAME, BITS_ARGUMENT, ARGUMENT_TEST_STRING, LENGTH, TYPE, ARG, X)

#define ARGUMENT_TEST_p(NAME, LENGTH, TYPE, ARG, X) /* no dynamic precision */ \
  NUMBER_FLAGS(NAME, BITS_ARGUMENT, ARGUMENT_TEST_POINTER, LENGTH, TYPE, ARG, X)

#define ARGUMENT_TEST_e(NAME, LENGTH, TYPE, ARG, X) ARGUMENT_TEST_f(NAME, LENGTH, TYPE, ARG, X)
#define ARGUMENT_TEST_g(NAME, LENGTH, TYPE, ARG, X) ARGUMENT_TEST_f(NAME, LENGTH, TYPE, ARG, X)
#define ARGUMENT_TEST_a(NAME, LENGTH, TYPE, ARG, X) ARGUMENT_TEST_f(NAME, LENGTH, TYPE, ARG, X)
#define ARGUMENT_TEST_E(NAME, LENGTH, TYPE, ARG, X) ARGUMENT_TEST_f(NAME, LENGTH, TYPE, ARG, X)
#define ARGUMENT_TEST_F(NAME, LENGTH, TYPE, ARG, X) ARGUMENT_TEST_f(NAME, LENGTH, TYPE, ARG, X)
#define ARGUMENT_TEST_G(NAME, LENGTH, TYPE, ARG, X) ARGUMENT_TEST_f(NAME, LENGTH, TYPE, ARG, X)
#define ARGUMENT_TEST_A(NAME, LENGTH, TYPE, ARG, X) ARGUMENT_TEST_f(NAME, LENGTH, TYPE, ARG, X)
#define ARGUMENT_TEST_f(NAME, LENGTH, TYPE, ARG, X) /* no precision over 16 */

#define ARGUMENT_TEST(NAME, LENGTH, TYPE, ARG, X) CAT(ARGUMENT_TEST_, TYPE)(NAME, LENGTH, TYPE, ARG, X)

#define ARGUMENT_TESTS(NAME, XX)                                                                                       \
  ARGUMENT_TEST(NAME##_arg000_, , s, NULL, XX)                                                                         \
  ARGUMENT_TEST(NAME##_arg001_, , s, "", XX)                                                                           \
  ARGUMENT_TEST(NAME##_arg002_, , s, "sarah", XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg003_, , s, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", XX)                       \
  ARGUMENT_TEST(NAME##_arg004_, , c, '\0', XX)                                                                         \
  ARGUMENT_TEST(NAME##_arg005_, , c, 'A', XX)                                                                          \
  ARGUMENT_TEST(NAME##_arg006_, , c, 228 - 256, XX)                                                                    \
  ARGUMENT_TEST(NAME##_arg007_, , p, NULL, XX)                                                                         \
  ARGUMENT_TEST(NAME##_arg008_, , p, 0x12345678, XX)                                                                   \
  ARGUMENT_TEST(NAME##_arg009_, , p, 0xE2345678, XX)                                                                   \
  ARGUMENT_TEST(NAME##_arg010_, , p, 0x1234567812345678ll, XX)                                                         \
  ARGUMENT_TEST(NAME##_arg011_, , p, 0xE234567812345678ll, XX)                                                         \
  ARGUMENT_TEST(NAME##_arg012_, , d, 0, XX)                                                                            \
  ARGUMENT_TEST(NAME##_arg013_, , d, 3, XX)                                                                            \
  ARGUMENT_TEST(NAME##_arg014_, , d, -600000, XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg015_, , d, 600000, XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg016_, , u, 0, XX)                                                                            \
  ARGUMENT_TEST(NAME##_arg017_, , u, -600000, XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg018_, , u, 600000, XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg019_, l, d, 0, XX)                                                                           \
  ARGUMENT_TEST(NAME##_arg020_, l, d, -600000, XX)                                                                     \
  ARGUMENT_TEST(NAME##_arg021_, l, d, 600000, XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg022_, l, u, 0, XX)                                                                           \
  ARGUMENT_TEST(NAME##_arg023_, l, u, -600000, XX)                                                                     \
  ARGUMENT_TEST(NAME##_arg024_, l, u, 600000, XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg025_, ll, d, 0, XX)                                                                          \
  ARGUMENT_TEST(NAME##_arg026_, ll, d, -60000000000000ll, XX)                                                          \
  ARGUMENT_TEST(NAME##_arg027_, ll, d, 60000000000000ll, XX)                                                           \
  ARGUMENT_TEST(NAME##_arg028_, ll, u, 0, XX)                                                                          \
  ARGUMENT_TEST(NAME##_arg029_, ll, u, -60000000000000ll, XX)                                                          \
  ARGUMENT_TEST(NAME##_arg030_, ll, u, 60000000000000ll, XX)                                                           \
  ARGUMENT_TEST(NAME##_arg031_, , x, 600000, XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg032_, , X, 600000, XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg033_, , o, 600000, XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg034_, , x, -600000, XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg035_, , X, -600000, XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg036_, , o, -600000, XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg037_, , x, 0, XX)                                                                            \
  ARGUMENT_TEST(NAME##_arg038_, , X, 0, XX)                                                                            \
  ARGUMENT_TEST(NAME##_arg039_, , o, 0, XX)                                                                            \
  ARGUMENT_TEST(NAME##_arg040_, , d, 0x80000000u, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg041_, , i, 0x80000000u, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg042_, , u, 0x80000000u, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg043_, , x, 0x80000000u, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg044_, , X, 0x80000000u, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg045_, , o, 0x80000000u, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg046_, , d, 0xFFFFFFFFu, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg047_, , i, 0xFFFFFFFFu, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg048_, , u, 0xFFFFFFFFu, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg049_, , x, 0xFFFFFFFFu, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg050_, , X, 0xFFFFFFFFu, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg051_, , o, 0xFFFFFFFFu, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg052_, , d, 0x7FFFFFFFu, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg053_, , i, 0x7FFFFFFFu, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg054_, , u, 0x7FFFFFFFu, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg055_, , x, 0x7FFFFFFFu, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg056_, , X, 0x7FFFFFFFu, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg057_, , o, 0x7FFFFFFFu, XX)                                                                  \
  ARGUMENT_TEST(NAME##_arg058_, ll, d, 0x8000000000000000ull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg059_, ll, i, 0x8000000000000000ull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg060_, ll, u, 0x8000000000000000ull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg061_, ll, x, 0x8000000000000000ull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg062_, ll, X, 0x8000000000000000ull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg063_, ll, o, 0x8000000000000000ull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg064_, ll, d, 0xFFFFFFFFFFFFFFFFull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg065_, ll, i, 0xFFFFFFFFFFFFFFFFull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg066_, ll, u, 0xFFFFFFFFFFFFFFFFull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg067_, ll, x, 0xFFFFFFFFFFFFFFFFull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg068_, ll, X, 0xFFFFFFFFFFFFFFFFull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg069_, ll, o, 0xFFFFFFFFFFFFFFFFull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg070_, ll, d, 0x7FFFFFFFFFFFFFFFull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg071_, ll, i, 0x7FFFFFFFFFFFFFFFull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg072_, ll, u, 0x7FFFFFFFFFFFFFFFull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg073_, ll, x, 0x7FFFFFFFFFFFFFFFull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg074_, ll, X, 0x7FFFFFFFFFFFFFFFull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg075_, ll, o, 0x7FFFFFFFFFFFFFFFull, XX)                                                      \
  ARGUMENT_TEST(NAME##_arg076_, h, d, 0, XX)                                                                           \
  ARGUMENT_TEST(NAME##_arg077_, h, d, 20000, XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg078_, h, d, -20000, XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg079_, h, d, -600000, XX)                                                                     \
  ARGUMENT_TEST(NAME##_arg080_, h, d, 600000, XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg081_, h, u, 0, XX)                                                                           \
  ARGUMENT_TEST(NAME##_arg082_, h, u, 20000, XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg083_, h, u, -20000, XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg084_, h, u, -600000, XX)                                                                     \
  ARGUMENT_TEST(NAME##_arg085_, h, u, 600000, XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg086_, hh, d, 0, XX)                                                                          \
  ARGUMENT_TEST(NAME##_arg087_, hh, d, 100, XX)                                                                        \
  ARGUMENT_TEST(NAME##_arg088_, hh, d, -100, XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg089_, hh, d, -600000, XX)                                                                    \
  ARGUMENT_TEST(NAME##_arg090_, hh, d, 600000, XX)                                                                     \
  ARGUMENT_TEST(NAME##_arg091_, hh, u, 0, XX)                                                                          \
  ARGUMENT_TEST(NAME##_arg092_, hh, u, 100, XX)                                                                        \
  ARGUMENT_TEST(NAME##_arg093_, hh, u, -100, XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg094_, hh, u, -600000, XX)                                                                    \
  ARGUMENT_TEST(NAME##_arg095_, hh, u, 600000, XX)                                                                     \
  ARGUMENT_TEST(NAME##_arg096_, , e, 10000., XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg097_, , e, 0.000123456789, XX)                                                               \
  ARGUMENT_TEST(NAME##_arg098_, , e, 1.23456789, XX)                                                                   \
  ARGUMENT_TEST(NAME##_arg099_, , e, 123456.789, XX)                                                                   \
  ARGUMENT_TEST(NAME##_arg100_, , e, 1.5e42, XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg101_, , e, 1.5e-42, XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg102_, , e, 9.9999, XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg103_, , e, 0., XX)                                                                           \
  ARGUMENT_TEST(NAME##_arg104_, , e, 1. / 0., XX)                                                                      \
  ARGUMENT_TEST(NAME##_arg105_, , f, 10000., XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg106_, , f, 0.000123456789, XX)                                                               \
  ARGUMENT_TEST(NAME##_arg107_, , f, 1.23456789, XX)                                                                   \
  ARGUMENT_TEST(NAME##_arg108_, , f, 123456.789, XX)                                                                   \
  ARGUMENT_TEST(NAME##_arg109_, , f, 1.5e6, XX)                                                                        \
  ARGUMENT_TEST(NAME##_arg110_, , f, 1.5e-6, XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg111_, , f, 9.9999, XX)                                                                       \
  ARGUMENT_TEST(NAME##_arg112_, , f, 0., XX)                                                                           \
  ARGUMENT_TEST(NAME##_arg113_, , f, 1. / 0., XX)

#define ALL_TESTS(X)                                                                                                   \
  STANDARD_TESTS(, X)                                                                                                  \
  ARGUMENT_TESTS(, X)

STANDARD_TESTS(, TEST_SAME)
ARGUMENT_TESTS(, TEST_SAME)

int main(int argc, char *argv[]) {
  tabula_format_set_ptrnull_from_system();
  tabula_format_set_strnull_from_system();

  for(uint32_t i = 1; i < argc; i++) {
    if(!strcmp(argv[i], "--arguments")) {
      require_bits |= BITS_ARGUMENT;
    }

    if(!strcmp(argv[i], "--flags")) {
      require_bits |= BITS_FLAGS;
      require_bits |= BITS_ARGUMENT;
    }
  }

  printf("%i %i\n", require_mask, require_bits);

  ALL_TESTS(TEST_RUN)

  _plc__1_test();

  if(tests_failed) {
    printf("%u tests run, %u tests failed\n", tests_run, tests_failed);
    return 0;
  } else {
    printf("%u tests run, all OK\n", tests_run);
    return 1;
  }
}
