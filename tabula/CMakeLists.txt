cmake_minimum_required(VERSION 3.1)
# - 3.1 for C_STANDARD

project(Alias-tabula
  VERSION 0.1.0
  DESCRIPTION "a warm comfortable blanket over standard library used by alias and tools to normalize C functionalty"
  HOMEPAGE_URL "https://github.com/MysticalUnicat/tabula"
  LANGUAGES C
)

add_library(tabula INTERFACE)
target_include_directories(tabula SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(tabula-test test.c)
target_link_libraries(tabula-test tabula)

add_test(NAME format COMMAND tabula-test --format)
add_test(NAME quicksort COMMAND tabula-test --quicksort)

set_tests_properties(format quicksort PROPERTIES
  PASS_REGULAR_EXPRESSION "all OK"
  FAIL_REGULAR_EXPRESSION "failed"
)
