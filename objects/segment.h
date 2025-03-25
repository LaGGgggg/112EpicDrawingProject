#ifndef SEGMENT_H
#define SEGMENT_H

#include "dot.h"

class segment {
public:
	segment(dot*s = nullptr, dot* e = nullptr):m_start(s),m_end(e) {
		//m_id = generateID();
	}
	dot getStart() const {return *m_start;}
	dot getEnd() const {return *m_end;}
	//ID getID() const { return m_id; }
private:
	//ID m_id;
	dot* m_start;
	dot* m_end;
};

#endif // SEGMENT_H
