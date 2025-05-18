#pragma once

#include <iostream>
#include <cmath>

#include "../ID/idgenerator.h"
#include "../storage/storage.h"


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

        m_relativePositionInfoStorage.add({&objects, rpt});

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

    double getError(Storage<ID>& objects, const RelativePosType rpt) {
        switch (rpt) {
            case ORTHO_SEGMENTS: {

                if (objects.size() < 2) {
                    std::cerr << "Error: Not enough objects for ORTHO_SEGMENTS" << std::endl;
                    return -1.0;
                }

                // Assuming the first two objects are segments
                const segment* seg1 = m_segmentStorage[objects[0]].data;
                const segment* seg2 = m_segmentStorage[objects[1]].data;

                const double dx1 = seg1->getEnd().x - seg1->getStart().x;
                const double dy1 = seg1->getEnd().y - seg1->getStart().y;
                const double dx2 = seg2->getEnd().x - seg2->getStart().x;
                const double dy2 = seg2->getEnd().y - seg2->getStart().y;

                // Scalar multiplication
                const double scalarProduct = dx1 * dx2 + dy1 * dy2;

                return std::abs(scalarProduct); // Error is the absolute value of the scalar product
            }
            case EQUAL_LENGTH_SEGMENTS: {

                if (objects.size() < 2) {
                    std::cerr << "Error: Not enough objects for EQUAL_LENGTH_SEGMENTS" << std::endl;
                    return -1.0;
                }

                // Assuming the first two objects are segments
                const segment* seg1 = m_segmentStorage[objects[0]].data;
                const segment* seg2 = m_segmentStorage[objects[1]].data;

                // Calculate lengths
                const double length1 = std::sqrt(
                    std::pow(seg1->getEnd().x - seg1->getStart().x, 2)
                    + std::pow(seg1->getEnd().y - seg1->getStart().y, 2)
                );
                const double length2 = std::sqrt(
                    std::pow(seg2->getEnd().x - seg2->getStart().x, 2)
                    + std::pow(seg2->getEnd().y - seg2->getStart().y, 2)
                );

                return std::abs(length1 - length2); // Error is the absolute difference in lengths
            }
            case COINSIDENT_DOTS: {

                if (objects.size() < 2) {
                    std::cerr << "Error: Not enough objects for COINSIDENT_DOTS" << std::endl;
                    return -1.0;
                }

                // Assuming the first two objects are dots
                const dot* dot1 = m_dotStorage[objects[0]].data;
                const dot* dot2 = m_dotStorage[objects[1]].data;

                const double dx = dot1->x - dot2->x;
                const double dy = dot1->y - dot2->y;

                return std::sqrt(dx * dx + dy * dy); // Error is the distance between the dots
            }
            default: {
                std::cerr << "Error: Unsupported RelativePosType" << std::endl;
                return -1.0;
            }
        }
    }

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
};
