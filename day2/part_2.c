#include "shared.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
typedef struct {
  uint64_t v[10];
  uint8_t len;
} Matches;

Matches get_pattern(uint64_t num, uint64_t amount) {
  uint64_t count = count_digits(num);
  uint64_t digits_per_part = count / amount;

  Matches m = {};

  if (amount == 0 || amount > count || digits_per_part * amount != count) {
    return m;
  }

  uint64_t div = (int)pow(10.0, (double)(digits_per_part));
  m.len = amount;
  for (uint64_t i = 0; i < amount; i++) {
    m.v[amount - 1 - i] = num % div;
    num /= div;
  }

  return m;
}

void print_matches(Matches m) {
  for (int i = 0; i < 10; i += 1) {
    printf("%llu,", m.v[i]);
  }
  printf(" (len %hhu)\n ", m.len);
}

uint8_t are_matches_the_same(Matches m) {
  uint8_t same = m.len > 0;
  for (int i = 0; i < m.len - 1; i += 1) {
    uint64_t num = m.v[i];
    uint64_t num2 = m.v[i + 1];

    if (num != num2) {
      same = 0;
    }
  }

  return same;
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

        Matches m = get_pattern(j, p);
        if (are_matches_the_same(m)) {
          count += j;
          break;
        }
      }
    }
  }
  printf("part 2 answer: %llu\n", count);
}

