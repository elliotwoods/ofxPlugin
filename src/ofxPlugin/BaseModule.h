#pragma once

#include <string>

namespace ofxPlugin {
	class BaseModule {
	public:
		virtual std::string getTypeName() const = 0;
	};
}