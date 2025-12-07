#include "shared.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

int width;
void part_2() {
  FILE *file;
  file = fopen("./test_input.txt", "r");
  char buffer[4096];
  Arena arena = {0};
  Input input = {0};

  uint64_t count = 0;
  while (fscanf(file, "%4095[^\n]\n", buffer) != EOF) {
    char *token = strtok(buffer, " ");
  }
  printf("part 2 answer: %llu\n", count);
}

