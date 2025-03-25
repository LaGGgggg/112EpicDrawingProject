#include <iostream>
#include <cassert>

#include "storage.h"
#include "dot.h"
#include "segment.h"
#include "idgenerator.h"
#include "base/base.h"

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
