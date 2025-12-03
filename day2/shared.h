#ifndef shared_h_INCLUDED
#define shared_h_INCLUDED
#include <math.h>

#define ARENA_IMPLEMENTATION

#include "arena.h"

typedef struct {
  char *items;
  size_t count;
  size_t capacity;
} String_Builder;

typedef struct {
  uint64_t from;
  uint64_t to;
} Products;

typedef struct {
  uint64_t first;
  uint64_t second;
} Halves;

typedef struct {
  Products *items;
  size_t count;
  size_t capacity;
} Entries;

uint64_t count_digits(uint64_t number) {
  uint64_t tmp = number;
  uint64_t digits = 0;
  while (tmp > 0) {
    tmp /= 10;
    digits += 1;
  }
  return digits;
}

Halves get_halves(uint64_t num) {
  uint64_t count = count_digits(num);
  uint64_t half = count / 2;
  if (half * 2 != count) {
    return (Halves){.first = 1, .second = 2};
  }
  uint64_t div = (int)pow(10.0, (double)(half));
  return (Halves){.first = num / div, .second = num % div};
}
#endif 
