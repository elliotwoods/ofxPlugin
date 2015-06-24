#include "CirclePlugin.h"

//----------
void initPlugin(shared_ptr<ofMainLoop> * mainLoop) {
	ofSetMainLoop(*mainLoop);
}

//----------
void registerFactories(FactoryRegister<BaseShape> * factoryRegister) {
	factoryRegister->add<CircleShape>();
}

#include <iostream>

void testFunction(int shout) {
	std::cout << shout << std::endl;
}
