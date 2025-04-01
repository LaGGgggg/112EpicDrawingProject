#include "../ID/idgenerator.h"
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
