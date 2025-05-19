#pragma once

#include"IDrawing.h"
#include"bitmap.h"

class Bitmap_manager : public IDrawing {
	
	BitMap* bmp_;
	std::string filename_;


	double left_;
	double down_;
	double index_;

public:

	Bitmap_manager(const char* filename) : filename_(filename), bmp_(nullptr){}
	Bitmap_manager(const char* filename, uint32_t rows, uint32_t cols, bool isBlack = false)
		: filename_(filename), bmp_(BitMap*(rows, cols, isBlack))
	{}

	 void setWorkingArea(double, double, double, double);
	 void drawPoint(double x, double y);
	 void drawSegment(double x1, double y1, double x2, double y2);
	 void save();


	 ~Bitmap_manager() {
		 delete bmp_;
	 }
};


