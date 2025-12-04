#include "shared.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
typedef struct {
  uint64_t v[10];
  uint8_t len;
} Matches;

uint8_t pattern_works(uint64_t num, uint64_t amount) {
  uint64_t count = count_digits(num);
  uint64_t digits_per_part = count / amount;

  if (amount == 0 || amount > count || digits_per_part * amount != count) {
    return 0;
  }

  uint64_t div = (int)pow(10.0, (double)(digits_per_part));
  uint64_t first;
  first = num % div;
  num /= div;

  for (uint64_t i = 1; i < amount; i++) {
    uint64_t next = num % div;
    num /= div;
    if (next != first) {
      return 0;
    }
  }

  return 1;
}

void print_matches(Matches m) {
  for (int i = 0; i < 10; i += 1) {
    printf("%llu,", m.v[i]);
  }
  printf(" (len %hhu)\n ", m.len);
}

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

void part_2() {
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
      uint64_t n = MIN(count_digits(j),10);

      for (int64_t p = 2; p <= n; p += 1) {

        if (pattern_works(j, p)) {
          count += j;
          break;
        }
      }
    }
  }
  printf("part 2 answer: %llu\n", count);
}

