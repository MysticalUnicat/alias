#define TABULA_NO_REPLACEMENT_MACROS
#define TABULA_IMPLEMENTATION
#include <tabula.h>

unsigned int tests_run = 0;
unsigned int tests_failed = 0;

int comp_int(const void *a, const void *b, void *ud) { 
  int ai = *(const int *)a;
  int bi = *(const int *)b;
  return (ai > bi) - (ai < bi);
}

void all_quicksort_tests(void) {
#define TEST(...)                                                                                                                                              \
  do {                                                                                                                                                         \
    int items[] = {__VA_ARGS__};                                                                                                                               \
    printf("("); \
    for(int j = 0; j < sizeof(items) / sizeof(items[0]); j++) {                                                                                            \
      printf("%i ", items[j]);                                                                                                                             \
    }                                                                                                                                                      \
   printf(") -> (");                                                                                                                                          \
    tabula_qsort(items, sizeof(items[0]), (sizeof(items) / sizeof(items[0])), comp_int, NULL);                                                      \
    tests_run++;                                                                                                                                               \
    for(int j = 0; j < sizeof(items) / sizeof(items[0]); j++) {                                                                                            \
      printf("%i ", items[j]);                                                                                                                             \
    }                                                                                                                                                      \
    printf(")\n");                                                                                                                                          \
    for(int i = 1; i < sizeof(items) / sizeof(items[0]); i++) {                                                                                                \
      if(items[i - 1] > items[i]) {                                                                                                                            \
        tests_failed++;                                                                                                                                        \
        break;                                                                                                                                                 \
      }                                                                                                                                                        \
    }                                                                                                                                                          \
  } while(false)

  TEST(0);

  TEST(0, 1);
  TEST(1, 0);

  TEST(0, 1, 2);
  TEST(0, 2, 1);
  TEST(2, 0, 1);
  TEST(2, 1, 0);
  TEST(1, 2, 0);
  TEST(1, 0, 2);

  TEST(0, 1, 2, 3);
  TEST(0, 1, 3, 2);
  TEST(0, 3, 1, 2);
  TEST(3, 0, 1, 2);
  TEST(3, 0, 2, 1);
  TEST(3, 2, 0, 1);
  TEST(2, 3, 0, 1);
  TEST(2, 3, 1, 0);
  TEST(2, 1, 3, 0);
  TEST(1, 2, 3, 0);
  TEST(1, 2, 0, 3);
  TEST(1, 0, 2, 3);
}

int main(int argc, char *argv[]) {
  all_quicksort_tests();

  if(tests_failed) {
    printf("%u tests run, %u tests failed\n", tests_run, tests_failed);
    return 0;
  } else {
    printf("%u tests run, all OK\n", tests_run);
    return 1;
  }
}
