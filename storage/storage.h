#ifndef STORAGE_H
#define STORAGE_H

#include "../objects/dot.h"
#include "../objects/segment.h"
#include <cassert>
#include <cstddef>

template<typename El>
class Storage {
public:
    Storage() : m_storage(nullptr), m_size(0) {}

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

    El& operator[](int pos) {
        if (pos < m_size && pos >= 0) {
            return m_storage[pos];
        }
        throw "invalid position";
    }

    /*
    El* findElementByID(ID id) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_storage[i].getID() == id) {
                return &m_storage[i];
            }
        }
        return nullptr;
    }
    */

    ~Storage() {
        delete[] m_storage;
    }

private:
    El* m_storage;
    size_t m_size;
};

#endif // STORAGE_H
