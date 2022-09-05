cmake_minimum_required(VERSION 3.1)
# - 3.1 for C_STANDARD

project(Alias-gen
  VERSION 0.1.0
  DESCRIPTION "various systems to use for game development"
  HOMEPAGE_URL "https://github.com/MysticalUnicat/alias"
  LANGUAGES C
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tabula)
add_subdirectory(../tabula ${CMAKE_CURRENT_BINARY_DIR}/tabula)

add_executable(alias_gen_geometric_algebra gen_geometric_algebra.c)
target_link_libraries(alias_gen_geometric_algebra tabula)
