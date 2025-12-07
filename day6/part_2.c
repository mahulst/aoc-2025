#include "shared.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
typedef struct {
  enum Symbol symbol;
  int len, start;
} Operation;

typedef struct {
  Operation *items;
  size_t count;
  size_t capacity;
} Operations;

typedef struct {
  int x;
  int y;
} Coord;

Coord index_to_pos(int i, int width) {
  Coord c = {0};
  c.y = i / width;
  c.x = i % width;
  return c;
}
// 19390085134498 too high
int pos_to_index(Coord c, int width) { return c.y * width + c.x; }
void part_2() {
  int width = 0;
  FILE *file;
  file = fopen("./input.txt", "r");
  char buffer[4096];
  Arena arena = {0};
  Operations ops = {0};
  char raw_data[4096 * 16];

  uint64_t count = 0;
  int y = 0;
  while (fscanf(file, "%4095[^\n]", buffer) != EOF) {
    int ch = fgetc(file);
    if (ch == EOF)
      break;
    if (width == 0) {
      width = strlen(buffer);
    }
    if (buffer[0] != '+' && buffer[0] != '*') {
      int x = 0;

      for (size_t i = 0; buffer[i] != '\0'; i++) {
        char c = buffer[i];
        Coord coord = {.x = x, .y = y};
        raw_data[pos_to_index(coord, width)] = c;
        x += 1;
      }
      y += 1;
    } else {
      enum Symbol sym = (buffer[0] == '+') ? Plus : Times;

      int spaces = 0;
      for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '+' || buffer[i] == '*') {
          if (spaces != 0) {
            Operation op = {
                .len = spaces,
                .symbol = sym,
                .start = i - spaces - 1,
            };
            arena_da_append(&arena, &ops, op);
            spaces = 0;
            sym = (buffer[i] == '+') ? Plus : Times;
          }
        } else {
          spaces += 1;
        };
      }
      Operation op = {
          .len = spaces + 1, .start = width - spaces - 1, .symbol = sym};
      arena_da_append(&arena, &ops, op);
    }
  }
  for (int64_t i = 0; i < ops.count; i += 1) {
    Operation op = ops.items[i];
    uint64_t sum = op.symbol == Plus ? 0 : 1;

    for (int64_t n = op.start; n < op.start + op.len; n += 1) {
      char buf[y + 1];
      for (int64_t r = 0; r < y; r += 1) {
        Coord coord = {.x = n, .y = r};
        buf[r] = raw_data[pos_to_index(coord, width)];
      }
      buf[y] = '\0';
      int64_t num = strtoull(buf, NULL, 10);
      if (op.symbol == Plus) {
        sum += num;
      } else {
        sum *= num;
      }
    }
    count += sum;
  }
  printf("part 2 answer: %llu\n", count);
}

