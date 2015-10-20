#include "ofxPlugin.h"

// This file 'plugin.cpp' in your plugin is like the 'main.cpp' of your application.
// One big difference is that YOU DO HAVE TO edit this file! (unlike main.cpp generally)

// First include the headers for any classes that you want to include
#include "CircleShape.h"

OFXPLUGIN_PLUGIN_MODULES_BEGIN(BaseShape)
	OFXPLUGIN_PLUGIN_REGISTER_MODULE(CircleShape);
OFXPLUGIN_PLUGIN_MODULES_END

OFXPLUGIN_EXPORT void initPlugin();