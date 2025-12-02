#include <stdint.h>
#define ARENA_IMPLEMENTATION

#include "arena.h"
#include <stdio.h>

typedef enum Dir { Left, Right } Dir;
typedef struct {
  enum Dir dir;
  uint32_t amount;
} Turn;

typedef struct {
  Turn *items;
  size_t count;
  size_t capacity;
} TurnArray;

void part_2() {
  Arena arena = {0};
  TurnArray turns = {0};
  FILE *file;
  file = fopen("./input.txt", "r");
  char buffer[256];
  while (fscanf(file, "%255[^\n]\n", buffer) != EOF) {
    Dir dir;
    if (buffer[0] == 'L') {
      dir = Left;
    } else {
      dir = Right;
    }
    uint32_t amount = atoi(buffer + 1);
    Turn t = {.dir = dir, .amount = amount};

    arena_da_append(&arena, &turns, t);
  }

  int32_t dial = 50;
  uint32_t counter = 0;
  int32_t prev = 50;
  for (uint32_t i = 0, n = turns.count; i < n; i += 1) {
    Turn t = turns.items[i];
    uint32_t rounds = (t.amount / 100);
    counter += rounds;

    if (t.dir == Left) {
      dial -= (t.amount % 100);
    }
    if (t.dir == Right) {
      dial += (t.amount % 100);
    }
    if (dial < 0) {
      if (prev != 0) {
        counter += 1;
      }
      dial += 100;
    } else if (dial > 100) {
      counter += 1;
    }
    dial = abs(dial % 100);
    if (dial == 0) {
      counter += 1;
    }
    prev = dial;
  }

  if (counter == 6907) {
    printf("Correct!\n");
  } else {
    printf("Wrong %d!\n", counter);
  }
}

