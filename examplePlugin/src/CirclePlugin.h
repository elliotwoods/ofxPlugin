#pragma once

#include "CircleShape.h"
#include "ofxPlugin.h"

using namespace ofxPlugin;

OFXPLUGIN_EXPORT void initPlugin(shared_ptr<ofMainLoop> * mainLoop);
OFXPLUGIN_EXPORT void registerFactories(FactoryRegister<BaseShape> * factoryRegister);

extern "C" {
	OFXPLUGIN_EXPORT void testFunction(int shout);
}