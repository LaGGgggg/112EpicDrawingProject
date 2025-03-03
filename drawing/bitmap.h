#pragma once
#include <cstdint>

struct BitMap {
	int rows;
	int cols;
	uint8_t* data;
};

bool loadBitMap(const char* filename, BitMap&);
bool isFree(int x, int y, const BitMap&);
