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


void add( dotStorage& ds, const dot& d){
	dot* newStorage = new dot[ds.size+1];
	// Копируем имеющееся содержимое 
	for (size_t k = 0; k < ds.size ;++k)
		newStorage[k] = ds.storage[k];
	newStorage[ds.size] = d;
	delete[] ds.storage;
	ds.storage = newStorage;
	++ds.size;
}

bool testAddDot(){
	dotStorage ds;
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

int main(){
	std::cout << "testAddDot " << (testAddDot() ? "OK":"No") << std::endl;
	return 0;
}


