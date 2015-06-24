#include "RectangleShape.h"

//----------
void RectangleShape::draw() {
	ofRect(x - 5, y - 5, 10, 10);
}

//----------
string RectangleShape::getTypeName() const {
	return "RectangleShape";
}