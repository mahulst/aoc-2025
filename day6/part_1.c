#include "shared.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void part_1() {
  FILE *file;
  file = fopen("./input.txt", "r");
  char buffer[4096];
  Arena arena = {0};
  Input input = {0};
  Symbols symbols = {0};
  uint64_t rows = 0;
  uint64_t columns = 0;
  uint64_t count = 0;
  while (fscanf(file, "%4095[^\n]\n", buffer) != EOF) {
    rows += 1;
    char *token = strtok(buffer, " \t\n");
    while (token != NULL) {
      if (token[0] != '+' && token[0] != '*') {
        uint64_t n = strtoull(token, NULL, 10);
      printf("%llu\n", n);
        arena_da_append(&arena, &input, (n));
      } else {
        columns += 1;
        if (token[0] == '+') {
          arena_da_append(&arena, &symbols, (Plus));

        } else {
          arena_da_append(&arena, &symbols, (Times));
        }
      }
      token = strtok(NULL, " \t\n");
    }
  }
  rows -= 1;
  for (int i = 0; i < columns; i += 1) {
    enum Symbol s = symbols.items[i];
    uint64_t sum = s == Plus ? 0 : 1;

    for (int j = 0; j < rows; j += 1) {
      printf("\t index: %d \n",rows * j + i);
      uint64_t num = input.items[columns * j + i];
      if (s == Plus) {
        printf("\t %llu + %llu = %llu\n", sum, num, sum + num);
        sum += num;
      } else {
        printf("\t %llu * %llu = %llu\n", sum, num, sum * num);
        sum *= num;
      }
    }
    count += sum;
  }
  printf("%llu , r: %llu\n", columns, rows);
  printf("part 1 answer: %llu\n", count);
}

