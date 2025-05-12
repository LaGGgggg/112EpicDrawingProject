#pragma once

#include <iostream>

#include "../ID/idgenerator.h"
#include "../storage/storage.h"
#include "../drawing/bitmap.h"


enum ObjType {
    OBJ_DOT,
    OBJ_SEG
};

enum RelativePosType {
    COINSIDENT_DOTS,
    EQUAL_LENGTH_SEGMENTS, // Отрезки должны быть одинаковы по длине
    ORTHO_SEGMENTS, // Отрезки должны быть ортогональны
};

enum SRPResult {
    ALL_OK = 0,
    INVALID_OBJECTS,
    INVALID_RELPOS
};


class Base {
public:
    ID addObject(ObjType otype) {
        switch (otype) {
        case OBJ_DOT:
            m_dotStorage.add({ generateID(), new dot()});
            return m_dotStorage[m_dotStorage.size() - 1].id;
            break;
        case OBJ_SEG:
            m_segmentStorage.add({ generateID(), new segment(new dot(), new dot())});
            return m_segmentStorage[m_segmentStorage.size() - 1].id;
            break;
        default:
            std::cerr << "Invalid object type" << std::endl;
        }
    };
    void removeObject(int id) {
		for (size_t k = 0; k < m_dotStorage.size(); ++k) {
			if (m_dotStorage[k].id == id) {
				delete m_dotStorage[k].data;
				m_dotStorage.remove(k);
				return;
			}
		}
		for (size_t k = 0; k < m_segmentStorage.size(); ++k) {
			if (m_segmentStorage[k].id == id) {
				delete m_segmentStorage[k].data;
				m_segmentStorage.remove(k);
				return;
			}
		}
    }

    SRPResult setRelativePos(Storage<ID>& objects, RelativePosType rpt) {
        // Проверка на корректность пожеланий пользователя

        const double errorThreshold = 1e-6;

        while (getError(objects, rpt) > errorThreshold)  /* Условие необходимости продолжения процедуры поиска значений параметров*/ {

            // Выбираем как изменить параметры объектов 
            // (для этого надо уметь вычислять частные производные 
            // от величины ошибки)

            // Меняем параметры 
            // (для этого надо реализовать методы, 
            // модифицирующие положение точек и отрезков)
            // Оцениваем как изменилась ситуации с точки зрения 
            // выполнения пожеланий пользователя
        }
    }

    double getError(Storage<ID>& objects, RelativePosType rpt);

    int getObjChildren(ID id, Storage<ID>& childIds) {

    }

    int getObjParams(ID id, Storage<double>& params) {
        for (size_t k = 0; k < m_dotStorage.size(); ++k) {
            if (m_dotStorage[k].id == id) {
                params.add(m_dotStorage[k].data->x);
                params.add(m_dotStorage[k].data->y);
                return 0;
            }
        }

        for (size_t k = 0; k < m_segmentStorage.size(); ++k) {
            if (m_segmentStorage[k].id == id) {
                params.add(m_segmentStorage[k].data->getStart().x);
                params.add(m_segmentStorage[k].data->getStart().y);
                params.add(m_segmentStorage[k].data->getEnd().x);
                params.add(m_segmentStorage[k].data->getEnd().y);
            }
        }
        return -1;
    }

    void Print (const char* filename, int hight, int weight) {

        //крайние точки изображения
        double up = 0, down = 0, left = 0, right = 0;
        double x, y;


        // перебор точек
        for (int i = 0; i < m_dotStorage.size(); ++i) {

            x = m_dotStorage[i].data->x;
            y = m_dotStorage[i].data->y;

            if (x < left) {
                left = x;
            }
            else if (x > right) {
                right = x;
            }
            
            if (y < down) {
                down = y;
            }
            else if (y > up) {
                up = y;
            }
        }
        // перебор отрезков
        for (int i = 0; i < m_segmentStorage.size(); ++i) {
            
            //начало
            x = m_segmentStorage[i].data->getStart().x;
            y = m_segmentStorage[i].data->getStart().y;
            
            if (x < left) {
                left = x;
            }
            else if (x > right) {
                right = x;
            }
            if (y < down) {
                down = y;
            }
            else if (y > up) {
                up = y;
            }

            //конец
            x = m_segmentStorage[i].data->getEnd().x;
            y = m_segmentStorage[i].data->getEnd().y;

            if (x < left) {
                left = x;
            }
            else if (x > right) {
                right = x;
            }
            if (y < down) {
                down = y;
            }
            else if (y > up) {
                up = y;
            }
        }


        //Вычисление размера
        double h = (up - down)+ 2;
        double w = (right - left) + 2;
       
        double dif_h = hight - h;
        double dif_w = weight - w;

        double index;


        // масштаб не изменятся
        if ((dif_h == 0 && dif_w <= 0) || (dif_w == 0 && dif_h <= 0)) {
            index = 1;
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


        BitMap bmp(static_cast<int>(hight), static_cast<int>(weight));


        int x_1, y_1, x_2, y_2;
        //отрисовка точек
        for (int i = 0; i < m_dotStorage.size(); ++i) {


            x_1 = static_cast<int>(((m_dotStorage[i].data->x) - left + 1) * index);
            y_1 = static_cast<int>(((m_dotStorage[i].data->y) - down + 1) * index);

            bmp.setPixel(x_1, y_1);
           
        }
        //отрисовка отрезков
        for (int i = 0; i < m_segmentStorage.size(); ++i) {

            //начало
            int tmp = (m_segmentStorage[i].data->getStart().x);

            x_1 = static_cast<int>(((m_segmentStorage[i].data->getStart().x) - left + 1) * index);
            y_1 = static_cast<int>(((m_segmentStorage[i].data->getStart().y) - down + 1) * index);
            //конец
            x_2 = static_cast<int>(((m_segmentStorage[i].data->getEnd().x) - left + 1) * index);
            y_2 = static_cast<int>(((m_segmentStorage[i].data->getEnd().y) - down + 1) * index);

            bmp.drawSegment(x_1, y_1, x_2, y_2);
            
        }

        bmp.saveTo(filename);
    }
        

private:
    struct dotinfo {
        ID id;
        dot* data;
    };

    struct seginfo {
        ID id;
        segment* data;
    };

    Storage<dotinfo> m_dotStorage;
    Storage<seginfo> m_segmentStorage;
};


