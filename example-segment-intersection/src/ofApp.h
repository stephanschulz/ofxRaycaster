#pragma once

#include "ofMain.h"
#include "ofxRaycaster.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    ofxraycaster::Ray2D ray;
    glm::vec2 p1 = glm::vec2(200, 80);
    glm::vec2 p2 = glm::vec2(400, 400);
    ofFloatColor col1 = ofFloatColor(ofColor(246,233,101));
    ofFloatColor col2 = ofFloatColor(ofColor(85,255,60));
    ofFloatColor col3 = ofFloatColor(ofColor(20,164,204));
    ofFloatColor col4 = ofFloatColor(ofColor(180,0,131));
    ofFloatColor col5 = ofFloatColor(ofColor(0,0,0));
};
