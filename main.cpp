#include "bitmap.h"

enum ObjType {
	OBJ_DOT,
	OBJ_SEG
};

enum RelativePosType {
	COINSIDENT_DOTS,
	EQUAL_LENGTH_SEGMENTS, // Отрезки должны быть одинаковы по длине
	ORTHO_SEGMENTS, // Отрезки должны быть ортогональны

};

enum SRPResult {
	ALL_OK = 0,
	INVALID_OBJECTS,
	INVALID_RELPOS
};

int main() {

	BitMap bmp(32, 32);
	const bool bIsBlack = true;
	for (unsigned y = 2; y < 30; ++y)
		bmp.setPixel(2, y,bIsBlack);
	bmp.saveTo("vertSeg.bmp");
	
	return 0;
}
