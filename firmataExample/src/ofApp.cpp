#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	ofBackground(255,0,130);
    
    smoothReading = 0.;
    
    //SOUND STUFF HERE ----------------------------------------
    
    int bufferSize = 512;
    sampleRate = 44100;
    phase = 0;
    phaseAdder = 0.0f;
    phaseAdderTarget = 0.0f;
    targetVolume = 0.5f;
    currentVolume = targetVolume;
    
    lAudio.assign(bufferSize, 0.0);
    rAudio.assign(bufferSize, 0.0);
    
    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
    
    //ARDUINO STUFF HERE -----------------------------
    
    
    
    potValue = "analog pin:";

    //connect to arduino
	ard.connect("/dev/tty.usbserial-DA00T1YT", 57600);
	
	// listen for arduino to be ready. when it is ready, call setupArduino() function
	ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
	bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
}

//--------------------------------------------------------------
void ofApp::update(){
    
	updateArduino();
    
    getAverage();
    
    //current volume is always trying to get back to target volume every loop (easing)
    currentVolume += (targetVolume - currentVolume) * 0.01;
    
    //make sure they don't go below 0
    currentVolume = ofClamp(currentVolume, 0., 1.0);
    targetVolume = ofClamp(targetVolume, 0, 1.0);

}

void ofApp::getAverage(){
    float sum = 0.;
    //set initial values to make sure they will be replaced by the incoming readings
    float highest = 0.;
    float lowest = 1000.;
    
    //replace dummy highest and lowest readings with actual readings from within the vector of allReadings
    for(int i = 0; i < allReadings.size(); i++){
        sum += allReadings[i];
        if(allReadings[i] < lowest){
            lowest = allReadings[i];
        }
        if(allReadings[i] > highest){
            highest = allReadings[i];
        }
    }
    
    //calculate the difference between the highest and lowest reading within the current vector of data
    float diff = highest - lowest;
    
    //this is the punch threshold
    float threshold = 100.;
    
    //if there's a punch...
    if (diff > threshold) {
        
        //play with these for sensitivity
        currentVolume -= 0.05f;
        targetVolume -= 0.01f;
        
        //as punch counter increases, volume -= 0.01f each time
        //current volume is affected directly by a punch (goes down a lot) but target volume goes
        //down by 0.1. current volume is trying to go back to target volume in update
        cout << "punch" << endl;
        
    }
    
    //for loop through noiseObjects vector, if diff > that object.resistance, then do something to the object
    
    smoothReading = sum / allReadings.size();
    cout << "smoothed reading: " << smoothReading << endl;
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName(); 
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();

    // set pin A0 to analog input
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
	
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EAnalogPinChanged, this, &ofApp::analogPinChanged);    
}

//--------------------------------------------------------------
void ofApp::updateArduino(){

	// update the arduino, get any data or messages.
    // the call to ard.update() is required
	ard.update();
	
	// do not send anything until the arduino has been set up
	if (bSetupArduino) {

	}

}


//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pinNum) {
    // do something with the analog input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    
    ardReading = ard.getAnalog(pinNum);
    
    potValue = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ardReading);
    
    allReadings.push_back(ardReading);
    
    //if the allReadings vector > 5, erase the oldest reading
    //play around with vector size to change sensitivity
    if(allReadings.size() > 5){
        allReadings.erase(allReadings.begin());
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0, 127);
    ofRect(510, 15, 275, 150);
    ofDisableAlphaBlending();
    
    ofSetColor(255, 255, 255);
	if (!bSetupArduino){
		ofDrawBitmapString("arduino not ready...\n", 515, 40);
	} else {
		ofDrawBitmapString(potValue + "\n" + ofToString((int)(128 + 128 * sin(ofGetElapsedTimef()))), 515, 40);

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
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
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    pan = 0.5f;
    float leftScale = 1 - pan;
    float rightScale = pan;
    
    //this creates the static sound
    for (int i = 0; i < bufferSize; i++) {
        lAudio[i] = output[i*nChannels ] = ofRandom(0, 1) * currentVolume * leftScale;
        lAudio[i] = output[i*nChannels ] = ofRandom(0, 1) * currentVolume * rightScale;
    }
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