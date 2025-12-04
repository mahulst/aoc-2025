#include "shared.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
int width;

void part_1() {
  FILE *file;
  file = fopen("./input.txt", "r");
  char buffer[256];
  Arena arena = {0};
  FloorPlan floor_plan = {0};
  uint64_t count = 0;
  while (fscanf(file, "%255[^\n]\n", buffer) != EOF) {
    size_t len = strlen(buffer);
    if (width == 0) {
      width = len;
      floor_plan.items =
          arena_realloc(&arena, floor_plan.items,
                        floor_plan.capacity * sizeof(floor_plan.items),
                        width * width * sizeof(floor_plan.items));
      floor_plan.capacity = width * width;
    }

    for (int i = 0; i < len; i += 1) {
      Position pos;
      if (buffer[i] == '@') {
        pos = Roll;
      } else {
        pos = Empty;
      }
      arena_da_append(&arena, &floor_plan, pos);
    }
  }

  for (int y = 0; y < width; y += 1) {
    for (int x = 0; x < width; x += 1) {
      int adjacent_rolls = 0;
      uint8_t has_roll =
          position_has_roll(&floor_plan, (Coord){.x = x, .y = y}, width);
      if (!has_roll) {
        continue;
      }
      for (int dy = y - 1; dy <= y + 1; dy += 1) {
        for (int dx = x - 1; dx <= x + 1; dx += 1) {
          // Bounds checking for floorplan
          if (dx < 0 || dy < 0 || dx >= width || dy >= width) {
            continue;
          }

          // Skip the roll that adjacent rolls are counted for
          if (dx == x && dy == y) {
            continue;
          }

          if (position_has_roll(&floor_plan, (Coord){.x = dx, .y = dy},
                                width)) {
            adjacent_rolls += 1;
            if (adjacent_rolls > 3) {
              // Also break out of y loop
              dy = y + 2;
              break;
            }
          }
        }
      }
      if (adjacent_rolls < 4) {
        count += 1;
      }
    }
  }

  printf("part 1 answer: %llu\n", count);
}

