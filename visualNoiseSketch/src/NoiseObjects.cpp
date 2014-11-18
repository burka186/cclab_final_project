//
//  NoiseObjects.cpp
//  letItOut_2
//
//  Created by Ava Burke on 11/6/14.
//
//

#include "NoiseObjects.h"

//custom constructor: create new instance of NoiseObjects class
NoiseObjects::NoiseObjects(float mX, float mY) {
    //pass in position
    pos.set(mX, mY);
    //random starting velocity
    vel.x = ofRandom(-10, 10);
    vel.y = ofRandom(-5, 5);
    
    //initialize targetVel at same as vel
    targetVel = vel;
    
    //pull data from XML file (this used to be in the main setup loop but is much more efficient here within the class)
    noise.load("rage_noise.xml");
    //set to parent node:
    noise.setTo("noise_objects");
    //how many children are there?
    numNoise = noise.getNumChildren();
    
    //pick a random index number between 0 and the number of nodes...
    int randNum = ofRandom(0, numNoise);
    noise.setToChild(randNum);
    
    //get the value of the selected node:
    text = noise.getValue();
    
    //load font
    fontSize = ofRandom(12, 30);
    TTF.loadFont("mono.ttf", fontSize);
    
    //random shade of grey...
    color = ofRandom(255);
    
    //randomize resistance (resistance will corrolate to how 'stubborn' each
    //noise object is to being removed when you "punch" (or, for these purposes, click)
    resistance = ofRandom(100, 200);
    
}


void NoiseObjects::update() {
    
    //move the NoiseObjects:
    pos += vel;
    
    //if they go off-screen, re-populate them at random positions (this keeps the high initial noise level high)
    if (pos.x > (ofGetWindowWidth()) || pos.x < 0) {
        pos.x = ofRandom(0, ofGetWindowWidth());
    }
    if (pos.y > ofGetWindowHeight() || pos.y < 0) {
        pos.y = ofRandom(0, ofGetWindowHeight());
    }

}

void NoiseObjects::render() {
    
    //set color (duh)
    ofSetColor(color);
    
    //draw the noise object to screen
    TTF.drawString(text, pos.x, pos.y);
}

//this is where I'm simulating how I want the noise objects to react when there is a "punch"
void NoiseObjects::applyForce() {

    
    //if the randomly assigned resistance is low, have the words get slightly smaller and darker with each "punch". if it's higher (i.e. the word is more stubborn), decrease color more slowly and do not decrease size
    if (resistance < 150) {
        fontSize -= 10;
        color -= 20;
    } else {
        color -= 10;
    }
    
    //increase resistance on all remaining particles with each 'punch' recorded
    resistance++;
    
}

