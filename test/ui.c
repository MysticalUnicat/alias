#include "local.h"

#include <alias/ui.h>

#define NUM_TRIANGLES 1024
#define NUM_VERTEXES 1024

struct {
  uint16_t a, b, c;
} triangles[NUM_TRIANGLES];

struct Vertex {
  alias_R xy[2];
  alias_R st[2];
  alias_R rgba[4];
} vertexes[NUM_VERTEXES];

  /* 0       1
   *  +----+
   *  |\   |
   *  | \  |
   *  |  \ |
   *  |   \|
   *  +----+
   * 3      2
   */

TEST(ui, "ui layouts") {
  alias_ui_Input input;
  alias_ui_Output output;
  alias_ui * ui;

  input.screen_size.width = 100;
  input.screen_size.height = 100;

  output.index_sub_buffer = alias_memory_SubBuffer_from_Buffer(
      (alias_memory_Buffer){ triangles, sizeof(triangles) }
    , 0, 0, 0, alias_memory_Format_Uint16, 1);

  output.xy_sub_buffer = alias_memory_SubBuffer_from_Buffer(
      (alias_memory_Buffer){ vertexes, sizeof(vertexes) }
    , offsetof(struct Vertex, xy), 0, sizeof(struct Vertex), alias_memory_Format_Float32, 2);

  output.st_sub_buffer = alias_memory_SubBuffer_from_Buffer(
      (alias_memory_Buffer){ vertexes, sizeof(vertexes) }
    , offsetof(struct Vertex, st), 0, sizeof(struct Vertex), alias_memory_Format_Float32, 2);

  output.rgba_sub_buffer = alias_memory_SubBuffer_from_Buffer(
      (alias_memory_Buffer){ vertexes, sizeof(vertexes) }
    , offsetof(struct Vertex, rgba), 0, sizeof(struct Vertex), alias_memory_Format_Float32, 4);

  alias_ui_initialize(alias_default_MemoryCB(), &ui);

  alias_ui_begin_frame(ui, alias_default_MemoryCB(), &input);
  alias_ui_end_frame(ui, alias_default_MemoryCB(), &output);
  TEST_EQ(output.num_triangles, 0, "");
  TEST_EQ(output.num_vertexes, 0, "");

  alias_ui_begin_frame(ui, alias_default_MemoryCB(), &input);
  alias_ui_fill(ui, alias_Color_BLACK);
  alias_ui_end_frame(ui, alias_default_MemoryCB(), &output);

  TEST_EQ(output.num_triangles, 2, "");
  TEST_EQ(triangles[0].a, 0, "");
  TEST_EQ(triangles[0].b, 1, "");
  TEST_EQ(triangles[0].c, 2, "");
  TEST_EQ(triangles[1].a, 0, "");
  TEST_EQ(triangles[1].b, 2, "");
  TEST_EQ(triangles[1].c, 3, "");

  TEST_EQ(output.num_vertexes, 4, "");
  TEST_EQ(vertexes[0].xy[0], alias_R_ZERO, "");
  TEST_EQ(vertexes[0].xy[1], alias_R_ZERO, "");
  TEST_EQ(vertexes[1].xy[0], alias_R_ZERO, "");
  TEST_EQ(vertexes[1].xy[1], 100, "");
  TEST_EQ(vertexes[2].xy[0], 100, "");
  TEST_EQ(vertexes[2].xy[1], 100, "");
  TEST_EQ(vertexes[3].xy[0], 100, "");
  TEST_EQ(vertexes[3].xy[1], alias_R_ZERO, "");

  alias_ui_begin_frame(ui, alias_default_MemoryCB(), &input);
  alias_ui_center(ui);
    alias_ui_override_size(ui, 50, 50);
    alias_ui_fill(ui, alias_Color_BLACK);
  alias_ui_end_frame(ui, alias_default_MemoryCB(), &output);

  TEST_EQ(output.num_triangles, 2, "");
  TEST_EQ(triangles[0].a, 0, "");
  TEST_EQ(triangles[0].b, 1, "");
  TEST_EQ(triangles[0].c, 2, "");
  TEST_EQ(triangles[1].a, 0, "");
  TEST_EQ(triangles[1].b, 2, "");
  TEST_EQ(triangles[1].c, 3, "");

  TEST_EQ(output.num_vertexes, 4, "");
  TEST_EQ(vertexes[0].xy[0], 25, "");
  TEST_EQ(vertexes[0].xy[1], 25, "");
  TEST_EQ(vertexes[1].xy[0], 25, "");
  TEST_EQ(vertexes[1].xy[1], 75, "");
  TEST_EQ(vertexes[2].xy[0], 75, "");
  TEST_EQ(vertexes[2].xy[1], 75, "");
  TEST_EQ(vertexes[3].xy[0], 75, "");
  TEST_EQ(vertexes[3].xy[1], 25, "");

  alias_ui_free(ui, alias_default_MemoryCB());
}

