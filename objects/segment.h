#pragma once


#include "dot.h"
#include <cassert>
#include "../ID/idgenerator.h"

class segment {
public:
	segment(dot*s = nullptr, dot* e = nullptr):m_start(s),m_end(e) {
		//m_id = generateID();
	}
	dot getStart() const {
		assert(m_start);
		return *m_start;
	}
	dot getEnd() const {
		assert(m_start);
		return *m_end;
	}
	//ID getID() const { return m_id; }
private:
	//ID m_id;
	dot* m_start;
	dot* m_end;
};
