#include <iostream>
#include <cassert>
#include "baseCore.h"
#include "storage.h"


class Base{
public:


private:
	Storage<dot> m_dotStorage;
	Storage<segment> m_segmentStorage;


};




int main() {
	Base base;
	
	Storage<dot> dotStorage;
	Storage<segment> segmentStorage;

	dot d(1.3,2.6);
	dot d1(1.22, 2.6);
	dot d2(1.2456, 12);
		
	segment s(d1,d2);
	
	dotStorage.add(d);
	
	segmentStorage.add(s);
	return 0;
}
