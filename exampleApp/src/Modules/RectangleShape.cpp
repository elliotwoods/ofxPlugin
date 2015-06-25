#include "RectangleShape.h"

//----------
void RectangleShape::draw() {
	ofPushStyle();

	ofSetColor(100, 100, 255);
	ofRect(x - 15, y - 15, 30, 30);

	ofPopStyle();
}

//----------
string RectangleShape::getTypeName() const {
	return "RectangleShape";
}