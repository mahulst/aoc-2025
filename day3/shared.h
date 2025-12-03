#ifndef shared_h_INCLUDED
#define shared_h_INCLUDED

#define ARENA_IMPLEMENTATION

#include "arena.h"

typedef struct {
  char *items[100];
  size_t count;
  size_t capacity;
} Banks;
#endif 
