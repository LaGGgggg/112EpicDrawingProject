#include <iostream>
#include <cassert>
//#include "baseCore.h"
#include "storage/storage.h"
#include "tests/tests.h"


class Base{
public:
	//не могу оттестировать методы, но поидее как-то так
	/*
	ID addDot(double x, double y) {
		dot d(x, y);
		m_dotStorage.add(d);
		return d.getID();
	}

	//Если мы хотим добавлять отрезок по id точек (просто не помню что мы решили по добавлению отрезков)
	ID addSegment(ID startID, ID endID) {
		dot* start = m_dotStorage.findElementByID(startID);
		dot* end = m_dotStorage.findElementByID(endID);
		
		if (!start || !end) {
			return -1;
		}

		segment s(*start, *end);
		m_segmentStorage.add(s);
		return s.getID();
	}
	*/
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
	
	std::cout << "testAddDot " << (testAddDot() ? "OK" : "No") << std::endl;
	std::cout << "testAddSegment " << (testAddSegment() ? "OK" : "No") << std::endl;
	std::cout << "testRemove " << (testRemove() ? "OK" : "No") << std::endl;
	std::cout << "testGetElement " << (testGetElement() ? "OK" : "No") << std::endl;
	return 0;
}
