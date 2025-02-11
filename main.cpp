#include <iostream>

struct dot{
	double x,y;
};
struct segment{
	dot start; 
	dot end;
};

struct dotStorage{
	dot* storage;
	size_t size;
};

template <typename Storage, typename El>
void add(Storage& s, const El& d){
	El* newStorage = new El[s.size+1];
	// Копируем имеющееся содержимое 
	for (size_t k = 0; k < s.size ;++k)
		newStorage[k] = s.storage[k];
	newStorage[s.size] = d;
	delete[] s.storage;
	s.storage = newStorage;
	++s.size;
}

template <typename Storage, typename El>
void remove(Storage& s, size_t num) {
	
	El* newStorage = new El[s.size - 1];
	// Копируем имеющееся содержимое 
	for (size_t k = 0; k < num; ++k)
		newStorage[k] = s.storage[k];
	for (size_t k = num+1; k < ds.size; ++k)
		newStorage[k-1] = s.storage[k];
		
	delete[] s.storage;
	s.storage = newStorage;
	--s.size;
}


bool testAddDot(){
	dotStorage ds{nullptr, 0};
	dot d1{1.4,2.5};
	add(ds,d1);

	if (ds.size != 1) return false;
	if ( ds.storage[0].x != 1.4 ) return false;
	if ( ds.storage[0].y != 2.5 ) return false;

	return true;
}

struct segmentStorage{
	segment* storage;
	size_t size;
};

bool testAddSegment(){
	segmentStorage ss{nullptr, 0};
	segment s1{{1.4, 2.5}, {2.4, 3.5}};
	add(ss,s1);

	if (ss.size != 1) return false;
	if ( ss.storage[0].start.x != s1.start.x || ss.storage[0].start.y != s1.start.y ) return false;
	if ( ss.storage[0].end.x != s1.end.x || ss.storage[0].end.y != s1.end.y ) return false;

	return true;
}

int main(){
	std::cout << "testAddDot " << (testAddDot() ? "OK":"No") << std::endl;
	std::cout << "testAddSegment" << (testAddSegment() ? "OK":"No") << std::endl;
	return 0;
}


