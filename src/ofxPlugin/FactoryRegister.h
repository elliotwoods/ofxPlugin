#pragma once

#include "Factory.h"
#include <Windows.h>
#include "ofAppRunner.h"

#include <map>

namespace ofxPlugin {
	typedef void(*InitPluginFunctionType)(std::shared_ptr<ofMainLoop> *);

	template<typename ModuleBaseType>
	class FactoryRegister : public std::map<std::string, std::shared_ptr<BaseFactory<ModuleBaseType>>> {
	public:
		typedef void (*RegisterFactoriesFunctionType)(FactoryRegister<ModuleBaseType> *);

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
		bool loadPlugin(std::string path, bool verbose = false) {
			//attempt to load DLL
			auto transformedPath = ofToDataPath(path);
			auto wstringPath = std::wstring(transformedPath.begin(), transformedPath.end());
			auto wcharPath = wstringPath.c_str();
			auto dll = LoadLibraryW(wcharPath);

			if (!dll) {
				ofLogError("ofxPlugin") << "Failed to open DLL [" << transformedPath << "]";
				return false;
			}

			//attempt to initialise plugin
			auto initPlugin = (InitPluginFunctionType)GetProcAddress(dll, "?initPlugin@@YAXPEAV?$shared_ptr@VofMainLoop@@@std@@@Z");
			if (!initPlugin) {
				if (verbose) {
					ofLogWarning("ofxPlugin") << "This dll is not a plugin";
				}
				FreeLibrary(dll);
				return false;
			}
			auto mainLoop = ofGetMainLoop();
			initPlugin(&mainLoop);

			//attempt to find function to register new factories
			auto registerFactories = (RegisterFactoriesFunctionType)GetProcAddress(dll, "?registerFactories@@YAXPEAV?$FactoryRegister@VBaseShape@@@ofxPlugin@@@Z");
			if (!registerFactories) {
				if (verbose) {
					ofLogWarning("ofxPlugin") << "No factories for FactoryRegister<" << typeid(ModuleBaseType).name() << "> found in DLL " << path;
				}
				FreeLibrary(dll);
				return false;
			}

			//call the function to register factories
			registerFactories(this);

			return true;
		}
	};
}