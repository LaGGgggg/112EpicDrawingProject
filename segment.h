#ifndef SEGMENT_H
#define SEGMENT_H

#include "dot.h"
#include "idgenerator.h"

class segment {
public:
	segment(const dot&s = dot(), const dot& e = dot()):m_start(s),m_end(e) {
		m_id = generateID();
	}
	dot getStart() const {return m_start;}
	dot getEnd() const {return m_end;}
private:
	ID m_id;
	dot m_start;
	dot m_end;
};

#endif // SEGMENT_H
