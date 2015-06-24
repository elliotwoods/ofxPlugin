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

		FactoryRegister<BaseShape> factoryRegister; // NOTE : often you'll keep the factoryRegister in a global singleton rather than in a specific class
		
		map<string, shared_ptr<BaseFactory<BaseShape>>>::iterator iterator;

		vector<shared_ptr<BaseShape>> shapes;
};
