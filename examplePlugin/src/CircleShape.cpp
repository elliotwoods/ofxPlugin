#include "CircleShape.h"

//----------
void CircleShape::draw() {
	ofCircle(x - 5, y - 5, 5);
}

//----------
string CircleShape::getTypeName() const {
	return "CircleShape";
}