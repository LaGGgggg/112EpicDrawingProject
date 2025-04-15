#pragma once

#include <iostream>

#include "idgenerator.h"
#include "storage.h"


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
            m_dotStorage.add({ generateID(), new dot() });
            return m_dotStorage[m_dotStorage.size() - 1].id;
            break;
        case OBJ_SEG:
            m_segmentStorage.add({ generateID(), new segment(new dot(), new dot()) });
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

        constexpr double errorThreshold = 1e-6;

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

    int getObjParams(const ID id, Storage<double>& params) {

        for (auto& [dot_id, dot_data] : m_dotStorage) {
            if (dot_id == id) {
                params.add(dot_data->x);
                params.add(dot_data->y);
                return 0;
            }
        }

        for (auto& [segment_id, segment_data] : m_segmentStorage) {
            if (segment_id == id) {
                params.add(segment_data->getStart().x);
                params.add(segment_data->getStart().y);
                params.add(segment_data->getEnd().x);
                params.add(segment_data->getEnd().y);
            }
        }

        return -1;
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
