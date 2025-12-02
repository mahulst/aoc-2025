#include "shared.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void part_1() {
  Arena arena = {0};
  Entries entries = {0};
  FILE *file;
  file = fopen("./input.txt", "r");
  char buffer[256];
  while (fscanf(file, "%255[^,],", buffer) != EOF) {
    char *token = strtok(buffer, "-");
    uint64_t first = strtoull(token, NULL, 10);
    token = strtok(NULL, "-");
    uint64_t second = strtoull(token, NULL, 10);
    arena_da_append(&arena, &entries,
                    ((Products){.from = first, .to = second}));
  }
  int64_t count = 0;
  for (uint64_t i = 0; i < entries.count; i += 1) {
    Products ps = entries.items[i];
    for (int64_t j = ps.from; j <= ps.to; j += 1) {
      Halves h = get_halves(j);
      if (h.first == h.second) {
        count += j;
      }
    }
  }
  printf("part 1 answer: %llu\n", count);
}
