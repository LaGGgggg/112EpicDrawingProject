#include "bitmap.h"
#include "base/base.h"

int main() {

	BitMap bmp(32, 32);
	const bool bIsBlack = true;
	for (unsigned y = 2; y < 30; ++y)
		bmp.setPixel(2, y,bIsBlack);
	bmp.saveTo("vertSeg.bmp");
	
	return 0;
}
