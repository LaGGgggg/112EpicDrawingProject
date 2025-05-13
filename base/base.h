#pragma once

#include <iostream>
#include "idgenerator.h"
#include "storage.h"
#include "../drawing/bitmap.h"
#include "../drawing/IDrawing.h"
#include "../objects/dot.h"
#include "../objects/segment.h"


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

    struct dotinfo {
        ID id;
        dot* data;
    };

    struct seginfo {
        ID id;
        segment* data;
    };

    ID addObject(ObjType otype);
    void removeObject(size_t id);

    SRPResult setRelativePos(Storage<ID>& objects, RelativePosType rpt);
    double getError(Storage<ID>& objects, RelativePosType rpt);
    int getObjChildren(ID id, Storage<ID>& childIds);
    int getObjParams(ID id, Storage<double>& params);

    Storage<dotinfo>* getDotStorage();
    Storage<seginfo>* getSegmentStorage();

   void print() const {
	//1.
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

        // double dif_h = hight - h;
        // double dif_w = weight - w;

		m_idr->setWorkingArea(0, 0, h, w);










		/* Это перенесем в BitmapManager
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
		*/

        //отрисовка точек
        for (int i = 0; i < m_dotStorage.size(); ++i) {
			m_idr->drawPoint(m_dotStorage[i].data->x,m_dotStorage[i].data->y);
			/*
			Это перенесем в BitmapManager
            x_1 = static_cast<int>(((m_dotStorage[i].data->x) - left + 1) * index);
            y_1 = static_cast<int>(((m_dotStorage[i].data->y) - down + 1) * index);

            bmp.setPixel(x_1, y_1);
           */
        }
        //отрисовка отрезков
        for (int i = 0; i < m_segmentStorage.size(); ++i) {
			m_idr->drawSegment(m_segmentStorage[i].data->getStart().x,
							   m_segmentStorage[i].data->getStart().y,
							   m_segmentStorage[i].data->getEnd().x,
							   m_segmentStorage[i].data->getEnd().y);
            /*Это перенесем в BitmapManager


			int tmp = (m_segmentStorage[i].data->getStart().x);

            x_1 = static_cast<int>(((m_segmentStorage[i].data->getStart().x) - left + 1) * index);
            y_1 = static_cast<int>(((m_segmentStorage[i].data->getStart().y) - down + 1) * index);
            //конец
            x_2 = static_cast<int>(((m_segmentStorage[i].data->getEnd().x) - left + 1) * index);
            y_2 = static_cast<int>(((m_segmentStorage[i].data->getEnd().y) - down + 1) * index);

            bmp.drawSegment(x_1, y_1, x_2, y_2);
            */
        }

        //bmp.saveTo(filename);
    }
	void setDrawing(IDrawing *idr) { m_idr = idr; }
private:

    class relativePositionInfo {
    public:

        Storage<ID>* ids_storage;
        RelativePosType type;

        relativePositionInfo(Storage<ID>* ids_storage, const RelativePosType t) : ids_storage(ids_storage), type(t) {}
        relativePositionInfo() : ids_storage(nullptr), type(ORTHO_SEGMENTS) {}
    };

    Storage<dotinfo> m_dotStorage;
    Storage<seginfo> m_segmentStorage;

    Storage<relativePositionInfo> m_relativePositionInfoStorage;

	mutable IDrawing* m_idr;
};
