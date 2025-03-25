#ifndef DOT_H
#define DOT_H
#include "../ID/idgenerator.h"

class  dot {
public:
	dot(double x = 0.0, double y = 0.0):m_x(x),m_y(y) {
		//m_id = generateID();
	}
	double getx()const { return m_x; }
	double gety()const { return m_y; }
	//ID getID() const { return m_id; }
private:
	//ID m_id;
	double m_x, m_y;
};
#endif // DOT_H
