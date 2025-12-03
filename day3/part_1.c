#include "shared.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void part_1() {
  FILE *file;
  file = fopen("./input.txt", "r");
  char buffer[128];
  uint64_t count = 0;
  while (fscanf(file, "%127[^\n]\n", buffer) != EOF) {
    size_t len = strlen(buffer);
    char first = 0;
    int first_i = len;
    char second = 0;

    // skip last as at least one adjacent battery is needed (len-1)
    for (int i = 0, n = len - 1; i < n; i += 1) {
      int x = buffer[i];
      if (x > first) {

        first = x;
        first_i = i;
      }
    }
    for (int i = first_i + 1, n = len; i < n; i += 1) {
      int x = buffer[i];
      if (x > second) {
        second = x;
      }
    }

    // char - '0' is actual number value
    int num = (first - '0') * 10 + (second - '0');
    count += num;
  }
  printf("part 2 answer: %llu\n", count);
}

