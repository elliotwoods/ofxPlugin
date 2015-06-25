#include "CircleShape.h"

//----------
void CircleShape::draw() {
	ofPushStyle();

	ofSetColor(255, 100, 100);
	ofCircle(x, y, 15);

	ofPopStyle();
}

//----------
string CircleShape::getTypeName() const {
	return "CircleShape";
}