#include <iostream>
#include <cmath>

#include "base.h"
#include "idgenerator.h"
#include "storage.h"

conts int OFFSET = 10;


ID Base::addObject(const ObjType otype) {
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
        throw std::invalid_argument("Invalid object type");
    }
};
void Base::removeObject(const size_t id) {
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

void Base::print()const {
   
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
    double h = (up - down) + OFFSET;
    double w = (right - left) + OFFSET;


    // Задание необходимого размера
    m_idr->setWorkingArea(left, down, w, h);


    //отрисовка точек
    for (int i = 0; i < m_dotStorage.size(); ++i) {
        m_idr->drawPoint(m_dotStorage[i].data->x, m_dotStorage[i].data->y);
               
    }
    //отрисовка отрезков
    for (int i = 0; i < m_segmentStorage.size(); ++i) {
            m_idr->drawSegment(m_segmentStorage[i].data->getStart().x,
                               m_segmentStorage[i].data->getStart().y,
                               m_segmentStorage[i].data->getEnd().x,
                               m_segmentStorage[i].data->getEnd().y);
        
    }

}
void setDrawing(IDrawing* idr) {
    m_idr = idr;
}

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

SRPResult Base::setRelativePos(Storage<ID>& objects, RelativePosType rpt) {

    m_relativePositionInfoStorage.add({&objects, rpt});

    constexpr double errorThreshold = 1e-6;
    constexpr double learningRate = 0.01;  // Step size for adjustments
    constexpr int stepsLimit = 10'000;

    int steps = 0;

    // Проверка на корректность пожеланий пользователя
    while (getError(objects, rpt) > errorThreshold && steps <= stepsLimit)  /* Условие необходимости продолжения процедуры поиска значений параметров*/ {

        std::cout << "[DEBUG] Current error: " << getError(objects, rpt) << std::endl;

        // Выбираем как изменить параметры объектов
        // (для этого надо уметь вычислять частные производные
        // от величины ошибки)

        // Меняем параметры
        // (для этого надо реализовать методы,
        // модифицирующие положение точек и отрезков)
        // Оцениваем как изменилась ситуации с точки зрения
        // выполнения пожеланий пользователя

        for (size_t i = 0; i < objects.size(); ++i) {

            std::cout << "[DEBUG] Processing object with ID: " << objects[i] << std::endl;
            const ID objId = objects[i];

            if (const dotinfo* element = m_dotStorage.findElementByID(objId)) {

                dot* d = element->data;

                const double originalError = getError(objects, rpt);

                d->x += learningRate;
                const double gradX = (getError(objects, rpt) - originalError) / learningRate;
                d->x -= learningRate;

                d->y += learningRate;
                const double gradY = (getError(objects, rpt) - originalError) / learningRate;
                d->y -= learningRate;

                d->x -= learningRate * gradX;
                d->y -= learningRate * gradY;
            }

            if (const seginfo* element = m_segmentStorage.findElementByID(objId)) {

                segment* seg = element->data;

                // Start point
                dot* start = &seg->getStart();
                double originalError = getError(objects, rpt);

                start->x += learningRate;
                const double gradStartX = (getError(objects, rpt) - originalError) / learningRate;
                start->x -= learningRate;

                start->y += learningRate;
                const double gradStartY = (getError(objects, rpt) - originalError) / learningRate;
                start->y -= learningRate;

                start->x -= learningRate * gradStartX;
                start->y -= learningRate * gradStartY;

                // End point
                dot* end = &seg->getEnd();
                originalError = getError(objects, rpt);

                end->x += learningRate;
                const double gradEndX = (getError(objects, rpt) - originalError) / learningRate;
                end->x -= learningRate;

                end->y += learningRate;
                const double gradEndY = (getError(objects, rpt) - originalError) / learningRate;
                end->y -= learningRate;

                end->x -= learningRate * gradEndX;
                end->y -= learningRate * gradEndY;
            }
        }

        ++steps;
        std::cout << "[DEBUG] Steps: " << steps << std::endl;
    }

    return SRPResult::ALL_OK;
}

double Base::getError(Storage<ID>& objects, const RelativePosType rpt) {
    switch (rpt) {
        case ORTHO_SEGMENTS: {

            if (objects.size() < 2) {
                std::cerr << "Error: Not enough objects for ORTHO_SEGMENTS" << std::endl;
                return -1.0;
            }

            // Assuming the first two objects are segments
            const segment* seg1 = m_segmentStorage.findElementByID(objects[0])->data;
            const segment* seg2 = m_segmentStorage.findElementByID(objects[1])->data;

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
            const segment* seg1 = m_segmentStorage.findElementByID(objects[0])->data;
            const segment* seg2 = m_segmentStorage.findElementByID(objects[1])->data;

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
            const dot* dot1 = m_dotStorage.findElementByID(objects[0])->data;
            const dot* dot2 = m_dotStorage.findElementByID(objects[1])->data;

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

int Base::getObjChildren(ID id, Storage<ID>& childIds) {
    return -1;
}

int Base::getObjParams(const ID id, Storage<double>& params) {

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

Storage<Base::dotinfo>* Base::getDotStorage() {
    return &m_dotStorage;
}
Storage<Base::seginfo>* Base::getSegmentStorage() {
    return &m_segmentStorage;
}
