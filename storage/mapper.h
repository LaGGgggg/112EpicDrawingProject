#pragma once
#include "storage.h"

template <typename Key, typename Value>
struct KV {
	Key key;
	Value value;
};



template <typename Key, typename Value>
class Mapper {
public:
	Mapper() {}
	Value& operator[](const Key& k_in) {
		for (int k = 0; k < m_sto.size(); ++k)
			if (m_sto[k].key == k_in) {
				return m_sto[k].value;
			}
		m_sto.add({ k_in,Value() });
		return m_sto[m_sto.size() - 1].value;
	}
    const Value& operator[](const Key& k_in)const {
		for (int k = 0; k < m_sto.size(); ++k)
			if (m_sto[k].key == k_in) {
				return m_sto[k].value;
			}
		throw std::invalid_argument("Can't find");
	}

	size_t size()const { return m_sto.size(); }

/*
	class Iterator {

	public:
		explicit Iterator(
			//	El* ptr
		) : {}

		KV& operator*() const {
			//	return *ptr; 
		}
		Iterator& operator++() {
			//++ptr; return *this; 
		}
		Iterator operator++(int) {
			/*Iterator tmp = *this;
			++ptr;
            return tmp;
		}
		bool operator==(const Iterator& other) const { return ptr == other.ptr; }
		bool operator!=(const Iterator& other) const { return !(ptr == other.ptr); }
	private:
		//El * ptr;
	};
*/
private:

	Storage< KV<Key, Value> > m_sto;
};
