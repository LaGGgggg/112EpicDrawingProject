#include "idgenerator.h"

ID lastGivenId = 0;

ID generateID(){
	return ++lastGivenId;
}
