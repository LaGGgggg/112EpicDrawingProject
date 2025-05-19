#include "bitmap_manager.h"

// class Bitmap_manager====================================================

void Bitmap_manager::setWorkingArea(double left, double down, double w, double h) {

    left_ = left;
    down_ = down;
    

    if (bmp_) { // если будем записывать в существующий bitmap
        double dif_h = bmp_.height() - h;
        double dif_w = bmp_.width() - w;

        // масштаб не изменятся
        if ((dif_h == 0 && dif_w <= 0) || (dif_w == 0 && dif_h <= 0)) {
            index_ = 1;
        }
        // изменение масштаба
        else {

            if (dif_h < dif_w) {
                index = hight / h;
            }
            else {
                index = weight / w;
            }
        }

    }
    else {
        index_ = 1;
    }

    
    //BitMap bmp(static_cast<int>(hight), static_cast<int>(weight));

}
void Bitmap_manager::drawPoint(double x, double y) {

    int x_1, y_1;

    x_1 = static_cast<int>((x - left + 1) * index_);
    y_1 = static_cast<int>((y - down + 1) * index_);

    bmp.setPixel(x_1, y_1);

}
void Bitmap_manager::drawSegment(double x1, double y1, double x2, double y2) {

    int x_1, x_2, y_1, y_2;


    //начало
    x_1 = static_cast<int>((x_1 - left + 1) * index);
    y_1 = static_cast<int>((y_1 - down + 1) * index);

    //конец
    x_2 = static_cast<int>((x_2 - left + 1) * index);
    y_2 = static_cast<int>((y_2 - down + 1) * index);

     
    bmp.drawSegment(x_1, y_1, x_2, y_2);
        
}
void Bitmap_manager::save() {
    bmp_->saveTo(filename_);
}

