#include <iostream>
#include <cassert>

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

template <typename Storage, typename El>
void remove(Storage& s, size_t num){
	assert(num < s.size);
	/*if(num > s.size + 1)
		throw std::out_of_range("Incorrect index");
	*/
	El* newStorage = new El[s.size-1];
	for (size_t k = 0; k < num; ++k)
		newStorage[k] = s.storage[k];
	for (size_t k = num + 1; k < s.size; ++k)
		newStorage[k - 1] = s.storage[k];
	
	delete[] s.storage;
	s.storage = newStorage;
	--s.size;
}

dotStorage createTestDotStorage(){
	dotStorage ds{nullptr, 0};
	dot d1{1.1, 1.1};
	dot d2{2.2, 2.2};
	dot d3{3.3, 3.3};
	add(ds, d1);
	add(ds, d2);
	add(ds, d3);
	return ds;
}

bool testRemove(){
	//test 1: del first el
	dotStorage ds = createTestDotStorage();
	remove<dotStorage, dot>(ds, static_cast<size_t>(0));
	if(ds.size != 2)
		return false;
	if(ds.storage[0].x != 2.2 && ds.storage[0].y != 2.2)
		return false;
	if(ds.storage[1].x != 3.3 && ds.storage[1].y != 3.3)
		return false;

	//test 2: del second el
	ds = createTestDotStorage();
	remove<dotStorage, dot>(ds, static_cast<size_t>(1));
	if(ds.size != 2)
		return false;
	if(ds.storage[0].x != 1.1 && ds.storage[0].y != 1.1)
		return false;
	if(ds.storage[1].x != 3.3 && ds.storage[1].y != 3.3)
		return false;

	//test 3: del third el
	ds = createTestDotStorage();
	remove<dotStorage, dot>(ds, static_cast<size_t>(2));
	if(ds.size != 2)
		return false;
	if(ds.storage[0].x != 1.1 && ds.storage[0].y != 1.1)
		return false;
	if(ds.storage[1].x != 2.2 && ds.storage[1].y != 2.2)
		return false;

	//test 4: del second & third el
	ds = createTestDotStorage();
	remove<dotStorage, dot>(ds, static_cast<size_t>(1));
	remove<dotStorage, dot>(ds, static_cast<size_t>(1));
	if(ds.size != 1)
		return false;
	if(ds.storage[0].x != 1.1 && ds.storage[0].y != 1.1)
		return false;
		
	return true;
}

int main(){
	std::cout << "testAddDot " << (testAddDot() ? "OK":"No") << std::endl;
	std::cout << "testAddSegment" << (testAddSegment() ? "OK":"No") << std::endl;
	std::cout << "testRemove" << (testRemove() ? "OK":"No") << std::endl;
	return 0;
}
