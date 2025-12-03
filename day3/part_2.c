#include "shared.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void part_2() {
  FILE *file;
  file = fopen("./input.txt", "r");
  char buffer[128];
  uint64_t count = 0;
  while (fscanf(file, "%127[^\n]\n", buffer) != EOF) {
    size_t len = strlen(buffer);
    char bank[11] = {0};
    int largest_i = 0;
    for (int i = 0, end = 12; i < end; i += 1) {
      char largest = 0;
      for (int j = largest_i, n = len - (12 - i); j <= n; j += 1) {
        int x = buffer[j];
        if (x > largest) {
          largest = x;
          largest_i = j + 1;
        }
      }
      bank[i] = largest;
    }
    uint64_t num = strtoull(bank, NULL, 10);

    count += num;
  }
  printf("part 2 answer: %llu\n", count);
}

