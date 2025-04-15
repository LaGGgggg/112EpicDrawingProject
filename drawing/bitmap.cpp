#include <fstream>
#include <iostream>
#include "bitmap.h"
#include <cmath>


// coздание bitmap файла
int BitMap::saveTo(const char* filename) {
    
    bmp_header header;
    bmp_info_header info_header;

    info_header.rows = cols_;
    info_header.cols = rows_;
    header.Size += size_;
    info_header.SizeImage = size_;
    
    //создание файла
    std::ofstream file(filename, std::ios_base::binary);
    if (!file)
        return -1;

    // Запись заголовков в файл
    file.write(reinterpret_cast<const char*>(&header), sizeof(bmp_header));
    file.write(reinterpret_cast<const char*>(&info_header), sizeof(bmp_info_header));

    file.write(reinterpret_cast<const char*>(pixel_matrix_),size_);

    file.close();

    std::cout << "File was created: " << filename << std::endl;

    return 0;
}

void BitMap::setPixel(const uint32_t r, const uint32_t c, const bool isBlack) {
    if (c >= cols_ || r >= rows_) {
        throw std::out_of_range("Pixel coordinates out of bounds");
    }

    const size_t byteIndex = (rows_ - r - 1) * line_ + c / 8;
    const uint8_t bitMask = 1 << (7 - c % 8);

    if (isBlack) {
        pixel_matrix_[byteIndex] &= ~bitMask;
    } else {
        pixel_matrix_[byteIndex] |= bitMask;
    }
}

void BitMap::drawSegment(uint32_t x1, uint32_t y1, const uint32_t x2, const uint32_t y2, const bool isBlack) {

    const int dx = abs(static_cast<int>(x2) - static_cast<int>(x1));
    const int dy = abs(static_cast<int>(y2) - static_cast<int>(y1));
    const int sx = x1 < x2 ? 1 : -1;
    const int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (true) {

        setPixel(x1, y1, isBlack);

        if (x1 == x2 && y1 == y2) {
            break;
        }

        const int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

int BitMap::loadFrom(const char* filename){
    std::ifstream ifs;
    ifs.open(filename, std::ios_base::in | std::ios_base::binary);
    if (!ifs.is_open())
        return -1;

    bmp_header header;
    bmp_info_header info_header;

    // Чтение заголовков из файла
    ifs.read(reinterpret_cast<char*>(&header), sizeof(bmp_header));
    ifs.read(reinterpret_cast<char*>(&info_header), sizeof(bmp_info_header));

    cols_ = info_header.cols;
    rows_ = info_header.rows;
    size_ = info_header.SizeImage;
    line_ = size_ / rows_;

    pixel_matrix_ = new uint8_t[rows_*line_];
    ifs.read(reinterpret_cast<char*>(pixel_matrix_), size_);

    ifs.close();
    return 0;
}

bool BitMap::isBlack(const uint32_t r, const uint32_t c){

    if (c >= cols_ || r >= rows_) {
        throw std::out_of_range("Pixel coordinates out of bounds");
    }

    const size_t byteIndex = (rows_ - r - 1) * line_ + c / 8;
    const uint8_t bitMask = 1 << (7 - c % 8);

    return (pixel_matrix_[byteIndex] & bitMask) == 0;
}
