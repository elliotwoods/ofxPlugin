#pragma once

#include "Factory.h"

#include "ofAppRunner.h"

#include <Windows.h>
#include <map>

// If you want to have a singleton pattern. Then :
//
//	1. Inherit a class from ofxPlugin::FactoryRegister<ModuleBaseType> (e.g. called simply FactoryRegister in your namespace)
//
//  2. Use this define at the top of the class definition in the header (above 'public')
#define OFXPLUGIN_FACTORY_REGISTER_SINGLETON_HEADER(FactoryRegisterType) \
public: \
	static FactoryRegisterType & X(); \
protected: \
	static FactoryRegisterType * singleton;
//
//  3. Use this define in your source file
#define OFXPLUGIN_FACTORY_REGISTER_SINGLETON_SOURCE(FactoryRegisterType) FactoryRegisterType * FactoryRegisterType::singleton = nullptr; \
FactoryRegisterType & FactoryRegisterType::X() { \
	if (!FactoryRegisterType::singleton) { \
		FactoryRegisterType::singleton = new FactoryRegisterType(); \
	} \
\
	auto & factoryRegister = *FactoryRegisterType::singleton; \
	return factoryRegister; \
}
//
// done!

namespace ofxPlugin {
	template<typename ModuleBaseType>
	class FactoryRegister : public std::map<std::string, std::shared_ptr<BaseFactory<ModuleBaseType>>> {
	public:
		struct PluginInitArgs {
			std::shared_ptr<ofMainLoop> mainLoop;
			FactoryRegister<ModuleBaseType> * factoryRegister;
		};

		typedef void(*InitPluginFunctionType)(PluginInitArgs *);

		///Add a factory which you already have to the register
		void add(std::shared_ptr<BaseFactory<ModuleBaseType>> baseFactory) {
			this->insert(pair<std::string, std::shared_ptr<BaseFactory<ModuleBaseType>>>(baseFactory->getModuleTypeName(), baseFactory));
		}

		///Create a factory for a specific type (defined in the template arguments of the function call) and add it to the register.
		template<typename ModuleType>
		void add() {
			this->add(std::make_shared<Factory<ModuleType, ModuleBaseType>>());
		}

		///Get a factory for a specific type (defined in the template arguments of the function call). Returns an empty pointer if factory wasn't found
		template<typename ModuleType>
		std::shared_ptr<ModuleBaseType> get() {
			auto moduleTypeName = ModuleType().getTypeName();
			return this->get(moduleTypeName)
		}

		///Get a factory for a specific type (defined by moduleNameType). Returns an empty pointer if factory wasn't found
		std::shared_ptr<BaseModule> get(std::string moduleTypeName) {
			auto findFactory = this->find(moduleTypeName);
			if (findFactory == this->end()) {
				return shared_ptr<BaseFactory<ModuleBaseType>>();
			}
			else {
				return findFactory->second;
			}
		}

		///Load any factories from the plugin which match this FactoryRegister
		bool loadPlugin(std::filesystem::path path, bool verbose = false) {
			//transform path to data path
			if (path.is_relative()) {
				path = std::filesystem::path(ofToDataPath("")) / path;
			}

			//attempt to load DLL
			auto dll = LoadLibraryW(path.wstring().c_str());
			if (!dll) {
				ofLogError("ofxPlugin") << "Failed to open DLL [" << path << "]";
				return false;
			}

			//attempt to initialise plugin
			auto initPlugin = (InitPluginFunctionType)GetProcAddress(dll, "initPlugin");
			if (!initPlugin) {
				if (verbose) {
					ofLogWarning("ofxPlugin") << "This DLL file is not a plugin";
				}
				FreeLibrary(dll);
				return false;
			}
			PluginInitArgs pluginInitArgs = {
				ofGetMainLoop(),
				this
			};
			initPlugin(&pluginInitArgs);

			return true;
		}

		///Look within a path for dll's and try and find plugins there
		void loadPlugins(string searchPath = "../") {
			auto pluginFiles = getPluginFiles();
			for (auto & entry : std::filesystem::directory_iterator(searchPath)) {
				this->loadPlugin(entry.path(), false);
			}
		}
	};
}