#ifndef STORAGE_H
#define STORAGE_H

#include "dot.h"
#include "segment.h"
#include <cassert>
#include <cstddef>
#include <cassert>

template<typename El> class Storage {
public:
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
private:
	El* m_storage;
	size_t m_size;
};

template <typename Storage, typename El>
void remove(Storage& s, size_t num) {
	assert(num < s.size);
	/*if (num > s.size + 1) 
		throw std::out_of_range("Incorrect index");	
		*/

	El* newStorage = new El[s.size - 1];
	// Копируем имеющееся содержимое 
	for (size_t k = 0; k < num; ++k)
		newStorage[k] = s.storage[k];
	for (size_t k = num+1; k < s.size; ++k)
		newStorage[k-1] = s.storage[k];
		
	delete[] s.storage;
	s.storage = newStorage;
	--s.size;
}


dotStorage createTestDotStorage();

bool testAddDot();
bool testAddSegment();
bool testRemove();

#endif // STORAGE_H
