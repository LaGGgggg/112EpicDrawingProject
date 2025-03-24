#include <iostream>
#include <cassert>

#include "storage.h"
#include "dot.h"
#include "segment.h"
#include "idgenerator.h"

enum ObjType {
	OBJ_DOT,
	OBJ_SEG
};

enum RelativePosType {
	
	EQUAL_LENGTH_SEGMENTS, // Отрезки должны быть одинаковы по длине
	ORTHO_SEGMENTS, // Отрезки должны быть ортогональны

};

enum SRPResult {
	ALL_OK = 0,
	INVALID_OBJECTS,
	INVALID_RELPOS
};


class Base{
public:
	ID addObject(ObjType otype) {
		switch (otype) {
		case OBJ_DOT:
			m_dotStorage.add(dot());
			return m_dotStorage.getElementPosition(m_dotStorage.size() - 1).getID();
			break;
		case OBJ_SEG:
			m_segmentStorage.add(segment(dot(), dot()));
			return m_segmentStorage.getElementPosition(m_segmentStorage.size() - 1).getID();
			break;
		}

		default:
			std::cerr << "Invalid object type" << std::endl;
	};

	SRPResult setRelativePos(Storage<ID>& objects, RelativePosType rpt) {
		// Проверка на корректность пожеланий пользователя
		
		const double errorThreshold = 1e-6;

		while ( getError( objects, rpt) > errorThreshold )  /* Условие необходимости продолжения процедуры поиска значений параметров*/ {

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

	
	int getObjParams(ID id, Storage<double>& params) {
		for (size_t k = 0; k < m_dotStorage.size(); ++k) {
			if (m_dotStorage.getElementPosition(k).getID() == id) {
				params.add(m_dotStorage.getElementPosition(k).getx());
				params.add(m_dotStorage.getElementPosition(k).gety());
				return 0;
			}
		}
		return -1;
	}

	
private:
	Storage<dot> m_dotStorage;
	Storage<segment> m_segmentStorage;
};




int main() {
	Base base;
	ID firstPointId = base.addObject(OBJ_DOT);
	Storage<double> firstPointParams;
	if (base.getObjParams(firstPointId, firstPointParams) == 0) {
		for (size_t k = 0; k < firstPointParams.size(); ++k)
			std::cout << firstPointParams.getElementPosition(k) << std::endl;
	}
	
	return 0;
}
