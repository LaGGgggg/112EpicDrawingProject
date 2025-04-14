#include <gtest/gtest.h>
#include "../bitmap.h"

TEST(testBitmap, setPixel){
	BitMap bmp(32,32);
    const bool bIsBlack = true;
	bmp.setPixel(2,2,bIsBlack);
	ASSERT_TRUE(bmp.isBlack(2, 2));
	ASSERT_FALSE(bmp.isBlack(1, 2));
	ASSERT_FALSE(bmp.isBlack(3, 2));
	ASSERT_FALSE(bmp.isBlack(2, 1));
	ASSERT_FALSE(bmp.isBlack(2, 3));
}

TEST(testBitmap, saveLoadWhite) {
    const bool bIsBlack = false;
	BitMap bmp(32, 32, bIsBlack);
	bmp.saveTo("white.bmp");
	BitMap bmp1(16, 16);
	bmp1.loadFrom("white.bmp");
	for (uint32_t r = 0; r < bmp1.rows(); ++r)
		for (uint32_t c = 0; c < bmp1.rows(); ++c)
			ASSERT_FALSE(bmp1.isBlack(r, c));
}
TEST(testBitmap, saveLoadBlack) {
    const bool bIsBlack = true;
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
    const bool bIsBlack = true;
	bmp.setPixel(2, 2, bIsBlack);
	bmp.saveTo("test1.bmp");
	BitMap bmp1(16, 16);
	bmp1.loadFrom("test1.bmp");
	ASSERT_TRUE(bmp1.isBlack(2, 2));
}



TEST(testBitmap, drawVerticalSeg){
	BitMap bmp(32, 32);
    const bool bIsBlack = true;
    const uint32_t colNum = 2;
    for (unsigned r = 2; r < 30; ++r)
        bmp.setPixel(r, colNum ,bIsBlack);
	bmp.saveTo("vertSeg.bmp");	
    for (uint32_t r = 2; r < 30; ++r) {
        ASSERT_TRUE(bmp.isBlack(r,colNum));
	}
    for (uint32_t r = 2; r < 30; ++r) {
        ASSERT_FALSE(bmp.isBlack(r,colNum-1));
        ASSERT_FALSE(bmp.isBlack(r,colNum+1));
    }
}

TEST(testBitmap, drawDiagSeg){
	BitMap bmp(32, 32);
    const bool bIsBlack = true;
	bmp.drawSegment(2, 2, 6, 6, bIsBlack);
	for (uint32_t k = 2; k < 7; ++k) {
		ASSERT_TRUE(bmp.isBlack(k, k));
	}
}
