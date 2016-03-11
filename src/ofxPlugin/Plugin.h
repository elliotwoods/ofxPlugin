#pragma once

#include "ofAppRunner.h"
#include "FactoryRegister.h"
#include "ofxSingleton.h"

#include <typeinfo>

//define the export syntax
#ifdef WIN32
#define OFXPLUGIN_EXPORT __declspec(dllexport)
#else
#define OFXPLUGIN_EXPORT
#endif


//generally we don't use the declraration
#define OFXPLUGIN_INIT_DECLARATION(ModuleBaseType) \
extern "C" { \
	OFXPLUGIN_EXPORT void initPlugin(ofxPlugin::FactoryRegister<ModuleBaseType>::PluginInitArgs * pluginInitArgs); \
}


//use this in the cpp file. If we don't have the declaration, then we need to wrap this in extern "C"
#define OFXPLUGIN_INIT_DEFINITION_BEGIN(ModuleBaseType) \
OFXPLUGIN_EXPORT const char * getPluginTypeName() { \
	return typeid(ModuleBaseType).name(); \
} \
OFXPLUGIN_EXPORT void initPlugin(ofxPlugin::FactoryRegister<ModuleBaseType>::PluginInitArgs * pluginInitArgs) { \
	//ofSetMainLoop(pluginInitArgs->mainLoop); /* set mainloop singleton from app into plugin */ \
	//ofxSingleton::Register::X().setParentRegister(pluginInitArgs->singletonRegister); // set plugin singleton register to have app's singleton register as parent

#define OFXPLUGIN_INIT_DEFINITION_END \
}


//use this once per module that you want to register
#define OFXPLUGIN_PLUGIN_REGISTER_MODULE(Module) \
		pluginInitArgs->factoryRegister->add<Module>()


//this wraps the declaration in an extern "C"
#define OFXPLUGIN_PLUGIN_MODULES_BEGIN(ModuleBaseType) \
extern "C" { \
	OFXPLUGIN_INIT_DEFINITION_BEGIN(ModuleBaseType)
	
#define OFXPLUGIN_PLUGIN_MODULES_END \
	OFXPLUGIN_INIT_DEFINITION_END \
}
