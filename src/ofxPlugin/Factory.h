#pragma once

#include "BaseModule.h"

#include <memory>

namespace ofxPlugin {
	template<typename ModuleBaseType>
	class BaseFactory {
	public:
		virtual std::shared_ptr<ModuleBaseType> makeUntyped() = 0;
		const std::string & getModuleTypeName() const {
			return this->moduleTypeName;
		}
	protected:
		std::string moduleTypeName;
	};

	template<typename ModuleType, typename ModuleBaseType>
	class Factory : public BaseFactory<ModuleBaseType> {
	public:
		Factory() {
			//briefly instantiate a test module so that we can take its name
			auto testModule = this->make();
			auto testModuleBaseTyped = std::static_pointer_cast<ModuleBaseType>(testModule);
			this->moduleTypeName = testModuleBaseTyped->getTypeName();
		}

		std::shared_ptr<ModuleBaseType> makeUntyped() override {
			return static_pointer_cast<ModuleBaseType>(this->make());
		}

		std::shared_ptr<ModuleBaseType> make() {
			return std::make_shared<ModuleType>();
		}
	};
}