#include "shared.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

int width;
void part_2() {
  FILE *file;
  file = fopen("./input.txt", "r");
  char buffer[256];
  Arena arena = {0};
  Ranges ranges = {0};

  uint64_t count = 0;
  while (fscanf(file, "%255[^\n]\n", buffer) != EOF) {
    if (strchr(buffer, '-') != NULL) {
      char *token = strtok(buffer, "-");
      uint64_t first = strtoull(token, NULL, 10);
      token = strtok(NULL, "-");
      uint64_t second = strtoull(token, NULL, 10);
      arena_da_append(&arena, &ranges, ((Range){.from = first, .to = second}));
    }
  }

  // Merge ranges
  uint8_t prev_ranges_count = 0;
  while (prev_ranges_count != ranges.count) {
    prev_ranges_count = ranges.count;
    for (int i = 0; i < ranges.count; i += 1) {
      Range range = ranges.items[i];

      for (int j = 0; j < ranges.count; j += 1) {
        if (i == j) {
          continue;
        }
        Range other_range = ranges.items[j];
        uint8_t start_of_range_within =
            range.from >= other_range.from && range.from <= other_range.to;
        uint8_t end_of_range_within =
            range.to >= other_range.from && range.to <= other_range.to;
        if (start_of_range_within || end_of_range_within) {
          uint64_t min = MIN(range.from, other_range.from);
          uint64_t max = MAX(range.to, other_range.to);
          int to_remove = MAX(i, j);
          int to_keep = MIN(i, j);
          ranges.items[to_remove] = ranges.items[ranges.count - 1];
          ranges.count -= 1;
          ranges.items[to_keep].from = min;
          ranges.items[to_keep].to = max;
          i = ranges.count;
          break;
        }
      }
    }
  }

  for (int i = 0; i < ranges.count; i += 1) {
    Range range = ranges.items[i];
    uint64_t range_len = range.to + 1 - range.from;

    count += range_len ;
  }

  printf("part 2 answer: %llu\n", count);
}

