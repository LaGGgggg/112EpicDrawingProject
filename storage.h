#ifndef STORAGE_H
#define STORAGE_H

#include "dot.h"
#include "segment.h"
#include <cassert>
#include <cstddef>

template<typename El>
class Storage {
public:
<<<<<<< HEAD
  Storage() : m_storage(nullptr), m_size(0) {}

  void add(const El& d) {
    El* newStorage = new El[m_size + 1];
    for (size_t k = 0; k < m_size; ++k)
      newStorage[k] = m_storage[k];
    newStorage[m_size] = d;
    delete[] m_storage;
    m_storage = newStorage;
    ++m_size;
  }

  void remove(size_t num) {
    assert(num < m_size);
  
    El* newStorage = new El[m_size - 1];
    // Копируем имеющееся содержимое 
    for (size_t k = 0; k < num; ++k)
      newStorage[k] = m_storage[k];
    for (size_t k = num + 1; k < m_size; ++k)
      newStorage[k - 1] = m_storage[k];
      
    delete[] m_storage;
    m_storage = newStorage;
    --m_size;
  }

  size_t size() const {
    return m_size;
  }

  El* storage() const {
    return m_storage;
  }

=======
	Storage() m_storage(nullptr), m_size(0) {

	}
	void add(const El& d) {
		El* newStorage = new El[m_size + 1];
		// Копируем имеющееся содержимое 
		for (size_t k = 0; k < m_size; ++k)
			newStorage[k] = m_storage[k];
		newStorage[m_size] = d;
		delete[] m_storage;
		m_storage = newStorage;
		++m_size;
	}

El getElementPosition (int pos) {
	if (pos < m_size && pos >= 0) {
		return m_storage[pos];
	}
	throw "invalid position";
}

>>>>>>> 0dbcbfd1697110fc360fbe7ab1998642d87635e5
private:
  El* m_storage;
  size_t m_size;
};

Storage<dot> createTestDotStorage();

bool testAddDot();
bool testAddSegment();
bool testRemove();

#endif // STORAGE_H
