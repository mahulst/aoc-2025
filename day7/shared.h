#ifndef shared_h_INCLUDED
#define shared_h_INCLUDED

#define ARENA_IMPLEMENTATION
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#include "arena.h"
typedef struct {
  int x;
  int y;
} Coord;

typedef enum { Splitter, Empty } Position;

typedef struct {
  Position *items;
  size_t count;
  size_t capacity;
} FloorPlan;

typedef struct { Coord key; uint64_t value; } Beams;

Coord index_to_pos(int i, int width) {
  Coord c = {0};
  c.y = i / width;
  c.x = i % width;
  return c;
}

int pos_to_index(Coord c, int width) { return c.y * width + c.x; }

uint8_t position_has_splitter(FloorPlan *fp, Coord c, int width) {
  int index = pos_to_index(c, width);
  return fp->items[index] == Splitter;
}
void print_floor_plan(FloorPlan *fp, int width) {
  for (int y = 0; y < width; y += 1) {
    for (int x = 0; x < width; x += 1) {
      uint8_t has_roll =
          position_has_splitter(fp, (Coord){.x = x, .y = y}, width);
      if (has_roll) {
        printf("^");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
}
#endif

