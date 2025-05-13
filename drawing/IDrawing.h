#pragma once

struct IDrawing{
	virtual void setWorkingArea(double blx,double bly,double width,double height) = 0;
	virtual void drawPoint(double x, double y) = 0;
	virtual void drawSegment(double x1, double y1, double x2, double y2) = 0;
};