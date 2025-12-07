#ifndef shared_h_INCLUDED
#define shared_h_INCLUDED

#include <stdint.h>
#define ARENA_IMPLEMENTATION

#include "arena.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
  uint64_t *items;
  size_t count;
  size_t capacity;
} Input;

typedef enum Symbol {
  Plus,
  Times
};

typedef struct {
  enum Symbol *items;
  size_t count;
  size_t capacity;
} Symbols;
#endif

