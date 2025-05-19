#pragma once

#include <cassert>
#include <cstddef>
#include <stdexcept>

#include "idgenerator.h"


template<typename El>
class Storage {
public:
    Storage() : m_storage(nullptr), m_size(0) {}
	Storage(const Storage<El>& s) : m_size(s.m_size) {
		m_storage = new El[m_size];
		for (size_t k = 0; k < m_size; ++k)
			m_storage[k] = s.m_storage[k];
	}
	void operator=(const Storage<El>& s) {
		delete[] m_storage;
		m_size = s.m_size;
		m_storage = new El[m_size];
		for (size_t k = 0; k < m_size; ++k)
			m_storage[k] = s.m_storage[k];
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
    void remove(const size_t num) {
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
    void insertAt(const size_t pos, const El& value) {

        if (pos > m_size) {
            throw std::out_of_range("Position out of range");
        }

        El* newStorage = new El[m_size + 1];
        for (size_t k = 0; k < pos; ++k) {
            newStorage[k] = m_storage[k];
        }
        newStorage[pos] = value;
        for (size_t k = pos; k < m_size; ++k) {
            newStorage[k + 1] = m_storage[k];
        }

        delete[] m_storage;
        m_storage = newStorage;
        ++m_size;
    }

    [[nodiscard]] size_t size() const {
        return m_size;
    }

    El& operator[](size_t pos) {

        if (pos < m_size && pos >= 0) {
            return m_storage[pos];
        }

        throw std::out_of_range("Index out of range");
    }
    El* findElementByID(ID id) {

        for (size_t i = 0; i < m_size; ++i) {
            if (m_storage[i].id == id) {
                return &m_storage[i];
            }
        }

        return nullptr;
    }

    class Iterator {
    public:

        explicit Iterator(El* ptr) : ptr(ptr) {}

        El& operator*() const { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++ptr;
            return tmp;
        }
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
		bool operator!=(const Iterator& other) const { return !(ptr == other.ptr); }
    private:
        El* ptr;
    };

    Iterator begin() { return Iterator(m_storage); }
    Iterator end() { return Iterator(m_storage + m_size); }

    ~Storage() {
        delete[] m_storage;
    }

private:
    El* m_storage;
    size_t m_size;
};
template<typename El>
void sortStorage(Storage<El>& st);

template<typename T>
size_t searchInsertPos(const Storage<T>& arr, const T& value) {

    size_t left = 0;
    size_t right = arr.size() - 1;

    while (left <= right) {

        size_t mid = left + (right - left) / 2;

        if (arr[mid] == value) {
            return mid;
        } else if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}
