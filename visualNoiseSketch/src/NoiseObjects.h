//
//  NoiseObjects.h
//  letItOut_2
//
//  Created by Ava Burke on 11/6/14.
//
//

#pragma once
#include "ofMain.h"

class NoiseObjects {
    //when you create the object (an instance of the class) for the first time, you feed it information about what you're doing
public:
    
    //constructor
    NoiseObjects(float mX, float mY);
    
    //update position of current noiseObjects
    void update();
    //draw current noiseObjects to screen
    void render();
    //apply physics to noiseObjects
    void applyForce();
    
    //position and velocity vectors
    ofVec2f pos;
    ofVec2f vel;
    
    //target velocity vector
    ofVec2f targetVel;
    
    //text stuff:
    string text;
    ofColor color;
    ofTrueTypeFont TTF;
    int fontSize;
    
    //how easy are the words to destroy?
    float resistance;
    
    //XML file
    ofXml noise;
    
    //number of nodes in XML file
    int numNoise;
};
