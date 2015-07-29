#include "ofxPlugin.h"

// This file 'plugin.cpp' in your plugin is like the 'main.cpp' of your application.
// One big difference is that YOU DO HAVE TO edit this file! (unlike main.cpp generally)

// First include the headers for any classes that you want to include
#include "CircleShape.h"

OFXPLUGIN_INIT_BEGIN(BaseShape)
	OFXPLUGIN_REGISTER(CircleShape);
OFXPLUGIN_INIT_END