#include <iostream>
#include "bitmap.h"

bool testSetPixel(){
	BitMap bmp(32,32);
	bool bIsBlack = true;
	bmp.setPixel(2,2,bIsBlack);
	if ( bmp.isBlack(2,2) ) return true;
	return false;
}

bool testSaveLoad() {
	BitMap bmp(32, 32);
	bool bIsBlack = true;
	bmp.setPixel(2, 2, bIsBlack);
	bmp.saveTo("some.bmp");

	BitMap bmp1(16,16);
	bmp1.loadFrom("some.bmp");
	if (bmp1.isBlack(2, 2)) return true;
	return false;
}


bool testDrawVerticalSeg() {
	BitMap bmp(32, 32);
	bool bIsBlack = true;
	bmp.drawSegment(2, 2, 2, 6, bIsBlack);
	for (uint32_t k = 2; k < 7; ++k) {
		if (!bmp.isBlack(2, k)) return false;
	}
	return true;
}

bool testDrawDiagSeg() {
	BitMap bmp(32, 32);
	bool bIsBlack = true;
	bmp.drawSegment(2, 2, 6, 6, bIsBlack);
	for (uint32_t k = 2; k < 7; ++k) {
		if (!bmp.isBlack(k, k)) return false;
	}
	return true;
}






int main() {
	std::cout << "testSetPixel " << (testSetPixel() ? "passed" : "failed") << std::endl;
	std::cout << "testDrawVerticalSeg " << (testDrawVerticalSeg() ? "passed" : "failed") << std::endl;
	std::cout << "testDrawDiagSeg " << (testDrawDiagSeg() ? "passed" : "failed") << std::endl;
    std::cout << "testSaveLoad " << (testSaveLoad() ? "passed" : "failed") << std::endl;
	return 0;
}
