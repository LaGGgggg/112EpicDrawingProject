#include <gtest/gtest.h>
#include "../bitmap.h"

TEST(testBitmap, setPixel){
	BitMap bmp(32,32);
	bool bIsBlack = true;
	bmp.setPixel(2,2,bIsBlack);
	ASSERT_TRUE(bmp.isBlack(2, 2));
}

TEST(testBitmap, saveLoad){
	BitMap bmp(32, 32);
	bool bIsBlack = true;
	bmp.setPixel(2, 2, bIsBlack);
	bmp.saveTo("some.bmp");

	BitMap bmp1(16,16);
	bmp1.loadFrom("some.bmp");
	ASSERT_TRUE(bmp1.isBlack(2, 2));
}


TEST(testBitmap, drawVerticalSeg){
	BitMap bmp(32, 32);
	bool bIsBlack = true;
	bmp.drawSegment(2, 2, 2, 6, bIsBlack);
	for (uint32_t k = 2; k < 7; ++k) {
		ASSERT_TRUE(bmp.isBlack(2, k));
	}
}

TEST(testBitmap, drawDiagSeg){
	BitMap bmp(32, 32);
	bool bIsBlack = true;
	bmp.drawSegment(2, 2, 6, 6, bIsBlack);
	for (uint32_t k = 2; k < 7; ++k) {
		ASSERT_TRUE(bmp.isBlack(k, k));
	}
}