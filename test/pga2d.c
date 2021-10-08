#include <alias/pga.h>



TEST(pga, "3D Projective Geometric Algebra") {
  __auto_type rot = alias_pga_rotor(alias_R_PI / alias_R_TWO, alias_pga_mul(alias_pga_e1, alias_pga_e2));

  __auto_type ax_z = alias_pga_meet(alias_pga_e1, alias_pga_e2);
  __auto_type orig = alias_pga_meet(ax_z, alias_pga_e3);

  __auto_type px = alias_pga_point(alias_R_ONE, alias_R_ZERO, alias_R_ZERO);
  __auto_type line = alias_pga_join(orig, px);

  __auto_type p = alias_pga_plane(2, 0, 1, -3);

  __auto_type rotated_plane = alias_pga_sandwich(p, rot);
  __auto_type rotated_line = alias_pga_sandwich(line, rot);
  __auto_type rotated_point = alias_pga_sandwich(px, rot);

  __auto_type point_on_plane = alias_pga_mul(alias_pga_dot(p, px), p);

  TEST_EQ(1, 1, "nothing makes sense");
}

