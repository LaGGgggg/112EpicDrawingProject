#pragma once
#include <cstdint>

class BitMap{
public:
	BitMap(uint32_t rows,uint32_t cols): rows(rows), cols(cols) {
		size_t rowsize = cols / 32 + (cols%32? 1 : 0);
		data = new uint32_t[(rows * rowsize)];
		std::fill(data, data + (rows * rowsize), 0);
	}
	void saveTo(const char* filename);
	void loadFrom(const char* filename);
	void setPixel(uint32_t x,uint32_t y,bool isBlack);
	bool isBlack(uint32_t x,uint32_t y);
	void drawSegment(uint32_t x1,uint32_t y1,  uint32_t x2, uint32_t y2,bool isBlack);

	~BitMap(){
		delete[] data;
	}
private:
	uint32_t rows;
	uint32_t cols;
	uint32_t* data;
};