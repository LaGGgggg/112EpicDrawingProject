#ifndef STORAGE_H
#define STORAGE_H

#include "dot.h"
#include "segment.h"
#include <cassert>
#include <cstddef>

struct dotStorage {
  dot* storage;
  size_t size;
};

struct segmentStorage {
  segment* storage;
  size_t size;
};

template <typename Storage, typename El>
void add(Storage& s, const El& d) {
  El* newStorage = new El[s.size + 1];
  for (size_t k = 0; k < s.size; ++k)
    newStorage[k] = s.storage[k];
  newStorage[s.size] = d;
  delete[] s.storage;
  s.storage = newStorage;
  ++s.size;
}

template <typename Storage, typename El>
void remove(Storage& s, size_t num) {
  assert(num < s.size);
  El* newStorage = new El[s.size - 1];
  for (size_t k = 0; k < num; ++k)
    newStorage[k] = s.storage[k];
  for (size_t k = num + 1; k < s.size; ++k)
    newStorage[k - 1] = s.storage[k];
  delete[] s.storage;
  s.storage = newStorage;
  --s.size;
}

dotStorage createTestDotStorage();

bool testAddDot();
bool testAddSegment();
bool testRemove();

#endif // STORAGE_H
