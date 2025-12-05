#ifndef shared_h_INCLUDED
#define shared_h_INCLUDED

#define ARENA_IMPLEMENTATION

#include "arena.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
typedef struct {
  uint64_t from;
  uint64_t to;
} Range;

typedef struct {
  uint64_t id;
} Fruit;

typedef struct {
  Range *items;
  size_t count;
  size_t capacity;
} Ranges;
typedef struct {
  Fruit *items;
  size_t count;
  size_t capacity;
} Fruits;
#endif

