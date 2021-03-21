#include "Point.h"

Point::Point() {
	x = 0;
	y = 0;
}
Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}
void Point::move(float dx, float dy) {
	x += dx;
	y -= dy;
}