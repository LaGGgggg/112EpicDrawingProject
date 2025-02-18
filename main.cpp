#include <iostream>
#include "storage.h"

int main() {
	std::cout << "testAddDot " << (testAddDot() ? "OK" : "No") << std::endl;
	std::cout << "testAddSegment " << (testAddSegment() ? "OK" : "No") << std::endl;
	std::cout << "testRemove " << (testRemove() ? "OK" : "No") << std::endl;
	return 0;
}
