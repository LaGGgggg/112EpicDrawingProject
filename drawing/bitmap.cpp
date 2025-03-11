#include <fstream>
#include <iostream>
#include "bitmap.h"
#include <cmath>

bool loadBitMap(const char* filename, BitMap&bm) {
	std::fstream fs;
	fs.open(filename, std::ios_base::in | std::ios_base::binary);
	if (!fs.is_open())
		return false;
	const int DATA_OFFSET_POS = 10;
	fs.seekg(DATA_OFFSET_POS);
	int dataOffset = 0;
	fs.read(reinterpret_cast<char*>(&dataOffset), 4);

	std::cout << "Data offset " << dataOffset << std::endl;

	const int WIDTH_POS = 18;

	fs.read(reinterpret_cast<char*>(&bm.cols), 4);
	std::cout << "Width " << bm.cols << std::endl;

	fs.read(reinterpret_cast<char*>(&bm.rows), 4);
	std::cout << "Height " << bm.rows << std::endl;


	const int bytes_in_row = (bm.cols / 8) + (bm.cols % 8 ? 1 : 0) * 4;
	std::cout << "bytes_in_row = " << bytes_in_row << std::endl;

	bm.data = new uint8_t[bytes_in_row*bm.rows];
	fs.seekg(dataOffset);
	fs.read(reinterpret_cast<char*>(bm.data), bytes_in_row*bm.rows);
}


bool isFree(int x, int y, const BitMap&bm) {
	if (x < 0 || x >= bm.cols || y < 0 || y >= bm.rows)
		return false;

}

// Отрисовка линии в BitMap файле
void BitMap::drawSegment(int x1, int y1, int x2, int y2, bool isBlack) {
    uint32_t diff_x, diff_y;
    if (x1 <= x2) {
         diff_x = x2 - x1;
         diff_y = y2 - y1;
    }
    else {
        diff_x = x1 - x2;
        diff_y = y1 - y2;
    }

    uint32_t sign_x = x1 < x2 ? 1 : -1;
    uint32_t sign_y = y1 < y2 ? 1 : -1;

    uint32_t error = diff_x - diff_y;

    setPixel(x2, y2, isBlack);

    while (x1 != x2 || y1 != y2)
    {
        setPixel(x1, y1, isBlack);

        uint32_t error2 = error * 2;
        if (error2 > -diff_y)
        {
            error -= diff_y;
            x1 -= sign_x;
        }
        if (error2 < diff_x)
        {
            error += sign_x;
            y1 -= sign_y;
        }
    }
}
