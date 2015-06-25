#pragma once

#include "ofMain.h"
#include "ofxPlugin.h"

#include "Modules/BaseShape.h"
#include "Modules/RectangleShape.h"

using namespace ofxPlugin;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// This is the list of factories
		// (Factories create classes)
		// Each FactoryRegister is associated with a base type,
		//	and all the factories inside it create classes which
		//	inherit from this base type.
		FactoryRegister<BaseShape> factoryRegister;
		
		// This is the currently selected factory
		map<string, shared_ptr<BaseFactory<BaseShape>>>::iterator iterator;

		// These are the classes which we've created
		vector<shared_ptr<BaseShape>> shapes;
};
