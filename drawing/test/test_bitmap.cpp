#include <gtest/gtest.h>
#include "../bitmap.h"

TEST(testBitmap, setPixel){
	BitMap bmp(32,32);
	bool bIsBlack = true;
	bmp.setPixel(2,2,bIsBlack);
	ASSERT_TRUE(bmp.isBlack(2, 2));
	ASSERT_FALSE(bmp.isBlack(1, 2));
	ASSERT_FALSE(bmp.isBlack(3, 2));
	ASSERT_FALSE(bmp.isBlack(2, 1));
	ASSERT_FALSE(bmp.isBlack(2, 3));
}

TEST(testBitmap, saveLoadWhite) {
	bool bIsBlack = false;
	BitMap bmp(32, 32, bIsBlack);
	bmp.saveTo("white.bmp");
	BitMap bmp1(16, 16);
	bmp1.loadFrom("white.bmp");
	for (uint32_t r = 0; r < bmp1.rows(); ++r)
		for (uint32_t c = 0; c < bmp1.rows(); ++c)
			ASSERT_FALSE(bmp1.isBlack(r, c));
}
TEST(testBitmap, saveLoadBlack) {
	bool bIsBlack = true;
	BitMap bmp2(32, 32, bIsBlack);
	bmp2.saveTo("black.bmp");
	BitMap bmp3(16, 16);
	bmp3.loadFrom("black.bmp");
	for (uint32_t r = 0; r < bmp3.rows(); ++r)
		for (uint32_t c = 0; c < bmp3.rows(); ++c)
			ASSERT_TRUE(bmp3.isBlack(r, c));
}
	
TEST(testBitmap, saveLoad) {
	BitMap bmp(32, 32);
	bool bIsBlack = true;
	bmp.setPixel(2, 2, bIsBlack);
	bmp.saveTo("test1.bmp");
	BitMap bmp1(16, 16);
	bmp1.loadFrom("test1.bmp");
	ASSERT_TRUE(bmp1.isBlack(2, 2));
}



TEST(testBitmap, drawVerticalSeg){
	BitMap bmp(32, 32);
	bool bIsBlack = true;
	for (unsigned y = 2; y < 30; ++y)
		bmp.setPixel(2, y,bIsBlack);
	bmp.saveTo("vertSeg.bmp");	
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
