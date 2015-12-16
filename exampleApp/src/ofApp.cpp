#include "ofApp.h"

using namespace ofxPlugin;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundColor(40);

	// Tell the factory register to make a factory for type RectangleShape, the example module which comes with the app
	factoryRegister.add<RectangleShape>();

	// (1/2)
	// Load our plugin dll (windows) / dylib (osx)
	// The path is relative to the data folder, so we use ..
	// true = verbose mode
#ifdef _WIN32
	factoryRegister.loadPlugin("../examplePlugin.dll", true);
#else
	factoryRegister.loadPlugin("../examplePlugin.dylib", true);
#endif

	// Every time the mouse moves, we're going to choose a new shape to make (i.e. step through the list of factories)
	auto firstFactory = factoryRegister.begin();
	this->iterator = firstFactory;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofPushStyle();
	ofSetLineWidth(2.0f);
	ofNoFill();

	for (auto shape : this->shapes) {
		shape->draw();
	}

	ofPopStyle();
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

	// (2/2)
	// We call 'makeUntyped' on the factory
	// This creates a new class, which is returned in a shared_ptr<BaseShape>
	// This shared_ptr can be dynamically cast into the specific type (e.g. RectangleShape / CircleShape) if we need 
	auto shape = iterator->second->makeUntyped();

	cout << shape->getTypeName() << ", ";

	shape->x = x;
	shape->y = y;
	this->shapes.push_back(shape);

	//loop through all the factories
	iterator++; // step forwards
	if (iterator == this->factoryRegister.end()) { // if we've stepped over the end
		iterator = this->factoryRegister.begin(); // start again
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
