#pragma once

#include "ofMain.h"
#include "NoiseObjects.h"

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
    
    //position vector
    ofVec2f pos;
    
    //vector of NoiseObjects to be drawn to screen
    vector <NoiseObjects> noiseCollection;
    
    //number of "punches" (clicks) recorded
    int punchCount;
};
