#include "shared.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void part_1() {
  int width = 0;;
  int height = 0;;
  FILE *file;
  file = fopen("./test_input.txt", "r");
  char buffer[256];
  Arena arena = {0};
  FloorPlan floor_plan = {0};
  Beams *beams = NULL;
  uint64_t count = 0;
  while (fscanf(file, "%255[^\n]\n", buffer) != EOF) {
    height += 1;
    size_t len = strlen(buffer);
    if (width == 0) {
      width = len;
      floor_plan.items =
          arena_realloc(&arena, floor_plan.items,
                        floor_plan.capacity * sizeof(floor_plan.items),
                        width * width * sizeof(floor_plan.items));
      floor_plan.capacity = width * width;
    }
    Position pos;
    for (int i = 0; i < len; i += 1) {
      if (buffer[i] == '^') {
        pos = Splitter;
      } else if (buffer[i] == 'S') {
        Coord c = {.x = i, .y = 0};
        hmput(beams, c, 1);
      } else {
        pos = Empty;
      }
      arena_da_append(&arena, &floor_plan, pos);
    }
  }
  height -= 1;
  for (int y = 0; y < height; y += 1) {
    Beams *new_beams = NULL;

    for (int i = 0, n = hmlen(beams); i < n; i += 1) {

      Coord beam = beams[i].key;

      Coord next_pos = {.x = beam.x, .y = beam.y + 1};
      if (position_has_splitter(&floor_plan, next_pos, width)) {
        count += 1;
        Coord extra_beam = {.x = next_pos.x - 1, .y = beam.y + 1};
        hmput(new_beams, extra_beam, 1);
        Coord extra_beam2 = {.x = next_pos.x + 1, .y = beam.y + 1};
        hmput(new_beams, extra_beam2, 1);
      } else {
        hmput(new_beams, next_pos, 1);
      }
    }
    beams = new_beams;
  }
  printf("part 1 answer: %llu\n", count);
}
