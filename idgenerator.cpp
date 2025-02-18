#include "idgenerator.h"

ID lastGivenId;

ID generateID(){
	return ++lastGivenId;
}
