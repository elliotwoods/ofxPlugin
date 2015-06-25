#pragma once
#include "ofAppRunner.h"
#include "FactoryRegister.h"

//define the export syntax
#define OFXPLUGIN_EXPORT __declspec(dllexport)


//generally we don't use the declraration
#define OFXPLUGIN_INIT_DECLARATION(ModuleBaseType) \
extern "C" { \
	OFXPLUGIN_EXPORT void initPlugin(ofxPlugin::FactoryRegister<ModuleBaseType>::PluginInitArgs * pluginInitArgs); \
}


//use this in the cpp file. If we don't have the declaration, then we need to wrap this in extern "C"
#define OFXPLUGIN_INIT_DEFINITION_BEGIN(ModuleBaseType) \
OFXPLUGIN_EXPORT void initPlugin(ofxPlugin::FactoryRegister<ModuleBaseType>::PluginInitArgs * pluginInitArgs) { \
	ofSetMainLoop(pluginInitArgs->mainLoop);

#define OFXPLUGIN_INIT_DEFINITION_END \
}


//use this once per module that you want to register
#define OFXPLUGIN_REGISTER(Module) \
		pluginInitArgs->factoryRegister->add<Module>()


//this wraps the declaration in an extern "C"
#define OFXPLUGIN_INIT_BEGIN(ModuleBaseType) \
extern "C" { \
	OFXPLUGIN_INIT_DEFINITION_BEGIN(ModuleBaseType)
	
#define OFXPLUGIN_INIT_END \
	OFXPLUGIN_INIT_DEFINITION_END \
}
