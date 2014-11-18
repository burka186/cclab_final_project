#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofBackground(0, 0, 0, 100);
    ofDisableAntiAliasing();
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    //create 500 initial NoiseObjects at random positions in the center of the screen
    //and push these back to the noiseCollection vector
    for (int i = 0; i < 500; i++) {
        NoiseObjects newNoise(ofRandom(ofGetWindowWidth()/3, ofGetWindowWidth()/2), ofRandom((2*ofGetWindowHeight())/6, (4*ofGetWindowHeight())/6));
        noiseCollection.push_back(newNoise);
        //cout << newNoise.text << endl;
    }
    
    //start punchCount at 0
    punchCount = 0;

}

//--------------------------------------------------------------
void ofApp::update(){

    //update however many objects there are in noiseCollection
    for (int i = 0; i < noiseCollection.size(); i++) {
        noiseCollection[i].update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //draw however many objects there are in noiseCollection
    for (int i = 0; i < noiseCollection.size(); i++) {
        noiseCollection[i].render();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
//simulating how words will react when integrated into other sketch
//(using a mouse click instead of a "punch")

void ofApp::mousePressed(int x, int y, int button){

    //apply force to all current noiseCollection objects
    for (int i = 0; i < noiseCollection.size(); i++) {
        noiseCollection[i].applyForce();
    }
    
    //increase punch count
    punchCount ++;
    
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
