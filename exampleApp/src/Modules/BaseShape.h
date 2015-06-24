#pragma once

#include "ofMain.h"
#include "ofxPlugin.h"

class BaseShape : public ofxPlugin::BaseModule {
public:
	virtual void draw() { };

	float x;
	float y;
};