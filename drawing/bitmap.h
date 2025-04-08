#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>

class BitMap {
private:
    const uint32_t rows_; // количество строк
    const uint32_t cols_; // длина строки

    uint32_t line_; // длина строки в байтах
    size_t size_ = rows_ * line_;

    uint8_t* pixel_matrix;


    bool isBlack_; // - цвет фона
    
    


    //заголовки BitMap файла
#pragma pack(push, 1) // Чтобы данные записывались вплотую
    struct bmp_header {
        uint16_t Type{ 0x4D42 }; 
        uint32_t Size{ 62 };         // Размер BMP файла в байтах
        uint16_t Reserved1{ 0 };   
        uint16_t Reserved2{ 0 };
        uint32_t offset{ 62 };       // Размер заголовка до кодирования пикселей
    };
    struct bmp_info_header {
        uint32_t Size{ 40 };       // Размер заголовка


        int32_t rows{ 0 };            // Ширина изображения
        int32_t cols{ 0 };            // Высота изображения


        uint16_t Planes{ 1 };         //всегда 1
        uint16_t Bit_Count{ 1 };      // Количество бит на пиксель
        uint32_t Compression{ 0 };    // метод сжатия
        uint32_t SizeImage{ 0 };      // Размер изображения

        int32_t XPelsPerMeter{ 0 };   // Горизонтальное разрешение
        int32_t YPelsPerMeter{ 0 };   // Вертикальное разрешение
        uint32_t colors{ 0 };         // Количество цветов
        uint32_t Important_color{ 0 };   // Количество важных цветов
        uint32_t num_color_one { 0 };
        uint32_t num_color_two{ 0xFFFFFF };
    };
#pragma pack(pop)

public:

    BitMap(uint32_t rows, uint32_t cols, bool isBlack = false) : rows_(rows), cols_(cols), isBlack_(isBlack) {

        const uint32_t tmp_ = (cols_ % 32 == 0) ? 0 : 1;
        line_ = (cols_ / 32 * 32 + tmp_) / 8; // длина строки в байтах
        size_ = rows_ * line_;

        uint8_t color = 0;
        if (!isBlack_) {
            color = 255; // - белый цвет пикселей фона
        }

        pixel_matrix = new uint8_t[line_ * rows_];
        for (int i = 0; i < size_; ++i) {
            pixel_matrix[i] = color;
        }
        

    }
    ~BitMap() {
        delete[] pixel_matrix;
    }

    void saveTo(const char* filename);
    void loadFrom(const char* filename);
    void setPixel(uint8_t x, uint8_t y, bool isBlack) const;
    bool isBlack(uint32_t x, uint32_t y);
    void drawSegment(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, bool isBlack);


};
