cmake_minimum_required(VERSION 3.18)
# - 3.1 for C_STANDARD

project(Alias-tabula
  VERSION 0.1.0
  DESCRIPTION "a warm comfortable blanket over standard library used by alias and tools to normalize C functionalty"
  HOMEPAGE_URL "https://github.com/MysticalUnicat/tabula"
  LANGUAGES C
)

include(CTest)

set(FILES atoi format)

set(C_FILES ${FILES})
list(TRANSFORM C_FILES APPEND ".c")

set(H_FILES ${FILES})
list(TRANSFORM H_FILES APPEND ".h")

set(FILES header.h ${H_FILES} middle.h ${C_FILES} footer.h)
list(TRANSFORM FILES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/src/")
message(${FILES})

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/tabula.h
  COMMAND ${CMAKE_COMMAND} -E cat -- ${FILES} > ${CMAKE_CURRENT_SOURCE_DIR}/include/tabula.h
  DEPENDS ${FILES}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(tabula INTERFACE)
target_sources(tabula INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/tabula.h)
target_include_directories(tabula SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(tabula-format-conformance-test test/format_conformance_test.c)
target_link_libraries(tabula-format-conformance-test tabula)

add_test(NAME standard COMMAND tabula-format-conformance-test)
add_test(NAME arguments COMMAND tabula-format-conformance-test --arguments)
add_test(NAME flags COMMAND tabula-format-conformance-test --flags)

set_tests_properties(standard arguments flags PROPERTIES
  PASS_REGULAR_EXPRESSION "all OK"
  FAIL_REGULAR_EXPRESSION "failed"
)
