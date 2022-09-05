cmake_minimum_required(VERSION 3.18)
# - 3.1 for C_STANDARD

project(Alias-tabula
  VERSION 0.1.0
  DESCRIPTION "a warm comfortable blanket over standard library used by alias and tools to normalize C functionalty"
  HOMEPAGE_URL "https://github.com/MysticalUnicat/tabula"
  LANGUAGES C
)

add_library(tabula INTERFACE)
target_include_directories(tabula SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(tabula-format-conformance-test format_conformance_test.c)
target_link_libraries(tabula-format-conformance-test tabula)

add_test(NAME standard COMMAND tabula-format-conformance-test)
add_test(NAME arguments COMMAND tabula-format-conformance-test --arguments)
add_test(NAME flags COMMAND tabula-format-conformance-test --flags)

set_tests_properties(standard arguments flags PROPERTIES
  PASS_REGULAR_EXPRESSION "all OK"
  FAIL_REGULAR_EXPRESSION "failed"
)
