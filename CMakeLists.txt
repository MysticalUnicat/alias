cmake_minimum_required(VERSION 3.1)
# - 3.1 for C_STANDARD

project(Alias
  VERSION 0.1.0
  DESCRIPTION "various systems to use for game development"
  HOMEPAGE_URL "https://github.com/MysticalUnicat/alias"
  LANGUAGES C
)

include(ExternalProject)

option(ALIAS_BUILD_DOCS "Build documents if Doxygen is found" OFF)
option(ALIAS_BUILD_TESTS "Build tests for Alias" OFF)
option(ALIAS_BUILD_EXAMPLES "Build examples for Alias" OFF)
option(ALIAS_COVERAGE "Build tests and generate reports for coverage" OFF)
option(ALIAS_PROFILING "enable profiling output" OFF)

#add_subdirectory(ext/glfw)

add_library(alias-config INTERFACE)

if(ALIAS_COVERAGE AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(alias-config INTERFACE -O0 -g --coverage)
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(alias-config INTERFACE --coverage)
  endif()
endif()

if(ALIAS_PROFILING AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(alias-config INTERFACE -pg)
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(alias-config INTERFACE -pg)
  endif()
endif()

#add_executable(alias_gen_geometric_algebra gen/geometric_algebra.c)
ExternalProject_add(
  alias-tools
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tools"
  BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/alias-tools"
  STEP_TARGETS build
  INSTALL_COMMAND cmake -E echo "skipping tool install"
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/alias)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/alias/pga2d.h
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/alias-tools/alias_gen_geometric_algebra -p 2 -d 1 > ${CMAKE_CURRENT_BINARY_DIR}/include/alias/pga2d.h --binary meet outer_product --binary join regressive_product --code m02
  DEPENDS alias-tools-build
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/alias/pga3d.h
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/alias-tools/alias_gen_geometric_algebra -p 3 -d 1 > ${CMAKE_CURRENT_BINARY_DIR}/include/alias/pga3d.h --binary meet outer_product --binary join regressive_product --code m024
  DEPENDS alias-tools-build
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/alias/cga2d.h
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/alias-tools/alias_gen_geometric_algebra -p 3 -n 1 > ${CMAKE_CURRENT_BINARY_DIR}/include/alias/cga2d.h --binary meet outer_product --binary join regressive_product
  DEPENDS alias-tools-build
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/alias/cga3d.h
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/alias-tools/alias_gen_geometric_algebra -p 4 -n 1 > ${CMAKE_CURRENT_BINARY_DIR}/include/alias/cga3d.h --binary meet outer_product --binary join regressive_product
  DEPENDS alias-tools-build
)

add_library(alias STATIC
  src/ecs_archetype.c
  src/ecs_component.c
  src/ecs_entity.c
  src/ecs_instance.c
  src/ecs_layer.c
  src/ecs_memory.c
  src/ecs_query.c

  src/log.c

  src/geometry_bvh.c

  src/transform.c
  src/physics.c
  src/physics_bvh_2d.c
  src/color.c
  src/memory.c
  src/random.c
	src/string32.c

  src/lexer.c
  src/ash.c

  src/ui.c

  src/ff_qoi.c

  ${CMAKE_CURRENT_BINARY_DIR}/include/alias/pga2d.h
  ${CMAKE_CURRENT_BINARY_DIR}/include/alias/pga3d.h
  ${CMAKE_CURRENT_BINARY_DIR}/include/alias/cga2d.h
  ${CMAKE_CURRENT_BINARY_DIR}/include/alias/cga3d.h
)

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  set(ALLOW_WARNINGS -Wno-gnu-zero-variadic-macro-arguments -Wno-gnu-alignof-expression -Wno-initializer-overrides -Wno-unused-value)
else()
  set(ALLOW_WARNINGS -Wno-error=unused-value -Wno-unused-value)
endif()

set_property(TARGET alias PROPERTY C_STANDARD 11)
target_compile_options(alias PRIVATE -pedantic -Wall -Wextra -Werror -std=gnu11 ${ALLOW_WARNINGS})
target_include_directories(alias
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}/include
  PRIVATE ext/shishua
)
target_link_libraries(alias PUBLIC alias-config)

if(ALIAS_BUILD_TESTS)
  set(TEST_SOURCES test/main.c)

  enable_testing()
  macro(alias_test NAME)
    add_test(NAME ${NAME} COMMAND alias-test --test "${NAME}")
    list(APPEND TEST_SOURCES "test/${NAME}.c")
  endmacro()

  alias_test(data_structure_soa)
  alias_test(data_structure_paged_soa)

  alias_test(geometry_aabb)
  alias_test(geometry_bvh)

  alias_test(ecs_create_instance)
  alias_test(ecs_create_layer)
  alias_test(ecs_create_component)
  alias_test(ecs_component_set)
  alias_test(ecs_internal_sort)
  alias_test(ecs_internal_bsearch)
  alias_test(ecs_internal_archetype)
  alias_test(ecs_spawn)
  alias_test(ecs_query)
  alias_test(ecs_add_component)
  alias_test(ecs_remove_component)

  alias_test(ash)

  alias_test(ui)

  alias_test(lexer)

  list(REVERSE TEST_SOURCES)

  add_executable(alias-test ${TEST_SOURCES})
  target_link_libraries(alias-test alias)
endif()

if(ALIAS_BUILD_DOCS)
  find_package(Doxygen)

  if(DOXYGEN_FOUND)
    set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
    set(DOXYGEN_GENERATE_MAN YES)
    set(DOXYGEN_QUIET YES)

    doxygen_add_docs(alias-docs
      include/alias/ecs.h
      ALL
    )
  endif()
endif()

if(ALIAS_BUILD_EXAMPLES)
  add_executable(alias-example-breakout example/breakout.c)
  target_link_libraries(alias-example-breakout alias)
endif()

