#include "local.h"

#include <alias/geometry/aabb.h>

TEST(geometry_aabb, "AABB 2d tests") {
  alias_AABB2D a = { { 0, 0 }, { 10, 10 } };
  alias_AABB2D b = { { 5, 5 }, { 7, 7 } };
  alias_AABB2D c = { { 1, 11 }, { 2, 12 } };
  alias_AABB2D d = { { -1, -1 }, { 1, 1 } };
  
  TEST_EQ(alias_R_fuzzy_eq(alias_AABB2D_surface_area(a), 40), true, "SA(a) != 40");
  TEST_EQ(alias_R_fuzzy_eq(alias_AABB2D_surface_area(b), 8), true, "SA(b) != 8");
  TEST_EQ(alias_R_fuzzy_eq(alias_AABB2D_surface_area(c), 4), true, "SA(c) != 4");

  TEST_EQ(alias_AABB2D_intersects(a, b), true, "!I(a,b)");
  TEST_EQ(alias_AABB2D_intersects(a, c), false, "I(a,c)");
  TEST_EQ(alias_AABB2D_intersects(b, c), false, "I(b,c)");
  TEST_EQ(alias_AABB2D_intersects(a, d), true, "!I(a,d)");

  TEST_EQ(alias_R_fuzzy_eq(alias_AABB2D_surface_area(alias_AABB2D_union(a, b)), 40), true, "SA(U(a, b)) != 40");
  TEST_EQ(alias_R_fuzzy_eq(alias_AABB2D_surface_area(alias_AABB2D_union(a, c)), 44), true, "SA(U(a, c)) != 44");
  TEST_EQ(alias_R_fuzzy_eq(alias_AABB2D_surface_area(alias_AABB2D_union(b, c)), 26), true, "SA(U(b, c)) != 26");
}

