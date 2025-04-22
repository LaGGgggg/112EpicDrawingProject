#pragma once

#include <cassert>

#include "dot.h"


class segment {
public:

	explicit segment(dot* s = nullptr, dot* e = nullptr) : m_start(s), m_end(e) {}

	[[nodiscard]] dot getStart() const {
		assert(m_start);
		return *m_start;
	}
	[[nodiscard]] dot getEnd() const {
		assert(m_start);
		return *m_end;
	}

	void updateStart(dot* s) {
		assert(s);
		m_start = s;
	}
	void updateEnd(dot* e) {
		assert(e);
		m_end = e;
	}

private:
	dot* m_start;
	dot* m_end;
};
