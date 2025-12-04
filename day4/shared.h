#ifndef shared_h_INCLUDED
#define shared_h_INCLUDED

#define ARENA_IMPLEMENTATION

#include "arena.h"
typedef struct {
  int x;
  int y;
} Coord;

typedef enum { Roll, Empty } Position;

typedef struct {
  Position *items;
  size_t count;
  size_t capacity;
} FloorPlan;
Coord index_to_pos(int i, int width) {
  Coord c = {0};
  c.y = i / width;
  c.x = i % width;
  return c;
}

int pos_to_index(Coord c, int width) { return c.y * width + c.x; }

uint8_t position_has_roll(FloorPlan *fp, Coord c, int width) {
  int index = pos_to_index(c, width);
  return fp->items[index] == Roll;
}
void print_floor_plan(FloorPlan *fp, int width) {
  for (int y = 0; y < width; y += 1) {
    for (int x = 0; x < width; x += 1) {
      uint8_t has_roll = position_has_roll(fp, (Coord){.x = x, .y = y}, width);
      if (has_roll) {
        printf("@");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
}
#endif

