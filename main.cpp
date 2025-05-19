#include <iostream>

#include "bitmap.h"
#include "base/base.h"
#include "ID/idgenerator.h"
#include "objects/dot.h"
#include "objects/segment.h"

int main() {

	Base base;

	ID seg1 = base.addObject(OBJ_SEG);
	ID seg2 = base.addObject(OBJ_SEG);
	ID seg3 = base.addObject(OBJ_SEG);
	ID dot1 = base.addObject(OBJ_DOT);
	ID dot2 = base.addObject(OBJ_DOT);

	base.getSegmentStorage()->findElementByID(seg1)->data->updateStart(new dot(0, 2));
	base.getSegmentStorage()->findElementByID(seg1)->data->updateEnd(new dot(0, 1));

	base.getSegmentStorage()->findElementByID(seg2)->data->updateStart(new dot(1, 0));
	base.getSegmentStorage()->findElementByID(seg2)->data->updateEnd(new dot(2.2, 1.4));

	base.getSegmentStorage()->findElementByID(seg3)->data->updateStart(new dot(4, 9));
	base.getSegmentStorage()->findElementByID(seg3)->data->updateEnd(new dot(0.2, 2.4));

	base.getDotStorage()->findElementByID(dot2)->data->x = 1;

	// Create a storage for the segment IDs
	Storage<ID> segmentStorage;
	segmentStorage.add(seg1);
	segmentStorage.add(seg2);
	segmentStorage.add(seg3);

	// Set their relative position to orthogonal
	SRPResult result4 = base.setRelativePos(segmentStorage, MERGED_SEGMENTS);
	// SRPResult result = base.setRelativePos(segmentStorage, ORTHO_SEGMENTS);
	// SRPResult result3 = base.setRelativePos(segmentStorage, EQUAL_LENGTH_SEGMENTS);

	// Check the result
	if (result4 == ALL_OK) {
		std::cout << "Segments successfully set to orthogonal." << std::endl;
	} else {
		std::cerr << "Failed to set segments to orthogonal. Error code: " << result4 << std::endl;
	}

	// Storage<ID> dotStorage;
	// dotStorage.add(dot1);
	// dotStorage.add(dot2);
	// SRPResult result2 = base.setRelativePos(dotStorage, COINSIDENT_DOTS);

	// if (result2 == ALL_OK) {
	// 	std::cout << "Dots successfully set to coincident." << std::endl;
	// } else {
	// 	std::cerr << "Failed to set dots to coincident. Error code: " << result2 << std::endl;
	// }

	std::cout << "Segment coordinates: "
	<< base.getSegmentStorage()->findElementByID(seg1)->data->getStart().x << ", "
	<< base.getSegmentStorage()->findElementByID(seg1)->data->getStart().y
	<< " "
	<< base.getSegmentStorage()->findElementByID(seg1)->data->getEnd().x << ", "
	<< base.getSegmentStorage()->findElementByID(seg1)->data->getEnd().y
	<< " | "
	<< base.getSegmentStorage()->findElementByID(seg2)->data->getStart().x << ", "
	<< base.getSegmentStorage()->findElementByID(seg2)->data->getStart().y
	<< " "
	<< base.getSegmentStorage()->findElementByID(seg2)->data->getEnd().x << ", "
	<< base.getSegmentStorage()->findElementByID(seg2)->data->getEnd().y
	<< " | "
	<< base.getSegmentStorage()->findElementByID(seg3)->data->getStart().x << ", "
	<< base.getSegmentStorage()->findElementByID(seg3)->data->getStart().y
	<< " "
	<< base.getSegmentStorage()->findElementByID(seg3)->data->getEnd().x << ", "
	<< base.getSegmentStorage()->findElementByID(seg3)->data->getEnd().y
	<< std::endl;

	std::cout << "Dot coordinates: "
	<< base.getDotStorage()->findElementByID(dot1)->data->x << ", "
	<< base.getDotStorage()->findElementByID(dot1)->data->y
	<< " "
	<< base.getDotStorage()->findElementByID(dot2)->data->x << ", "
	<< base.getDotStorage()->findElementByID(dot2)->data->y
	<< std::endl;

	return 0;
}
