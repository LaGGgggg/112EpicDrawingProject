#include <fstream>
#include <iostream>
#include "bitmap.h"
#include <cmath>


// coздание bitmap файла
void BitMap::saveTo(const char* filename) {
    
    bmp_header header;
    bmp_info_header info_header;

    info_header.rows = cols_;
    info_header.cols = rows_;
    header.Size += line_ * rows_;
    info_header.SizeImage = line_ * rows_;
    

    //создание файла
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "File can't be created" << std::endl;
        return;
    }

    // Запись заголовков в файл
    file.write(reinterpret_cast<const char*>(&header), sizeof(bmp_header));
    file.write(reinterpret_cast<const char*>(&info_header), sizeof(bmp_info_header));


    for (int i = 0; i < size_; ++i) {

            uint8_t pixel = pixel_matrix[i]; 
            file.write(reinterpret_cast<const char*>(&pixel), 1);
        

        // Добавление пустых байтов для выравнивания строки
        uint8_t padding[3] = { 0 };
        file.write(reinterpret_cast<const char*>(padding), line_ - rows_);
    }

    file.close();
    std::cout << "File was created: " << filename << std::endl;
}


/*
bool loadBitMap(const char* filename) {
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
*/

void BitMap::setPixel(uint32_t x, uint32_t y, bool isBlack){
    if (x < 0 || x >= cols || y < 0 || y >= rows) {
        return;
    }
    size_t rowsize = cols / 32 + (cols%32? 1 : 0);
    uint32_t* row = data + y * rowsize;
    if(isBlack){
        row[x/32] |= (1 << (x % 32));
    } else{
        row[x/32] &= ~(1 << (x % 32));
    }
}

bool BitMap::isBlack(uint32_t x,uint32_t y){
    if (x < 0 || x >= cols || y < 0 || y >= rows) {
        return false;
    }
    size_t rowsize = cols / 32 + (cols%32? 1 : 0);
    uint32_t* row = data + y * rowsize;
    return (row[x/32] & (1 << (x % 32))) != 0;
}

// Отрисовка линии в BitMap файле
void BitMap::drawSegment(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, bool isBlack) {
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
