#include "ofApp.h"

using namespace ofxPlugin;

//--------------------------------------------------------------
void ofApp::setup() {
	//tell the factory register to make a factory for type RectangleShape, the example module which comes with the app
	factoryRegister.add<RectangleShape>();

	factoryRegister.loadPlugin("../examplePlugin.dll", true); // relative to data path

	auto firstFactory = factoryRegister.begin();
	this->iterator = firstFactory;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	for (auto shape : this->shapes) {
		shape->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {
		this->shapes.clear();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	auto shape = iterator->second->makeUntyped();
	cout << shape->getTypeName() << ", ";

	shape->x = x;
	shape->y = y;
	this->shapes.push_back(shape);

	//loop through all the factories
	iterator++;
	if (iterator == this->factoryRegister.end()) {
		iterator = this->factoryRegister.begin();
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
