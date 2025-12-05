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
  Ranges ranges = {0};
  Fruits fruits = {0};

  uint64_t count = 0;
  while (fscanf(file, "%255[^\n]\n", buffer) != EOF) {
    if (strchr(buffer, '-') != NULL) {
      char *token = strtok(buffer, "-");
      uint64_t first = strtoull(token, NULL, 10);
      token = strtok(NULL, "-");
      uint64_t second = strtoull(token, NULL, 10);
      arena_da_append(&arena, &ranges, ((Range){.from = first, .to = second}));
    } else {
      Fruit fruit = {.id = strtoull(buffer, NULL, 10)};
      arena_da_append(&arena, &fruits, fruit);
    }
  }
  for (int i = 0; i < fruits.count; i += 1) {
    uint64_t fruit = fruits.items[i].id;
    for (int j = 0; j < ranges.count; j += 1) {
      Range range = ranges.items[j];
      if(fruit >= range.from && fruit <= range.to){
        count +=1;
        break;
      }
    }
  }
  printf("part 1 answer: %llu\n", count);
}

