#include "ofApp.h"

void ofApp::setup(){
    ray.setup(glm::vec3(350, 0, 0), glm::vec3(-1, 0, 0));

    icosphere.set(200, 1);
    mesh.append(icosphere.getMesh());

    light.setAmbientColor(col4);
    light.setup();
    light.setPosition(200,600,400);
    light.enable();

    material.setAmbientColor(col4);

      ofEnableAlphaBlending();
    ofEnableDepthTest();
}

void ofApp::update(){;
    
//    ofVec3f cur =   ofVec3f cur = easyCam.worldToScreen(speaker->center_position, viewMain);
    ray.setOrigin(glm::vec3(mouseX, 0,0));
    float time = ofGetElapsedTimef();
    float sinedTime = sin(time * 1.3);
    float cosedTime = cos(ofGetElapsedTimef()* 1.3) * 0.5;
    ray.setDirection(glm::normalize(glm::vec3(-1, cosedTime, 0)));

    node.panDeg(1);
    node.boom(sin(time)*2.5);

}

void ofApp::draw(){
  
    ofBackground(col3);
    cam.begin();
    light.draw();
    ray.draw(5);

    glm::vec3 baricentricCoordinates;
    glm::vec3 intNormal;
    bool intersects;

    if (transformation) {
        node.transformGL();
        material.begin();
//        mesh.draw();
        material.end();
        ofSetColor(col5);
        mesh.drawWireframe();
//        intersects = ray.intersectsMesh(mesh,
//                                        node.getGlobalTransformMatrix(),
//                                        baricentricCoordinates,
//                                        intNormal);
        
        countIntersections = ray.intersectsMesh(mesh,
                                                node.getGlobalTransformMatrix(),
                                                baricentricCoordinates,
                                                intNormal);
        
        if(countIntersections > 0) intersects = true;
        else intersects = false;
        
        if(countIntersections % 2 == 0) bInside = false;
        else bInside = true;
        
        node.restoreTransformGL();
    } else {
         ofSetColor(col4);
        material.begin();
//        mesh.draw();
        material.end();
        
        ofSetColor(col5);
        mesh.drawWireframe();
        countIntersections = ray.intersectsMesh(mesh,baricentricCoordinates,intNormal);
        
        if(countIntersections > 0) intersects = true;
        else intersects = false;
        
        if(countIntersections % 2 == 0) bInside = false;
        else bInside = true;
    }
    
    
    
    // is there an intersection between the segment and the ray?
    if (intersects) {
        ofPushStyle();

        auto intersection =
            ray.getOrigin() + ray.getDirection() * baricentricCoordinates.z;

        // draw the ray that hits the icosphere
        ofSetColor(col1);
        ofDrawLine(ray.getOrigin(), intersection);
        // draw the intersection point
        ofDrawSphere(intersection, 5);

        // draw the reflected light
        auto reflLight = glm::reflect(ray.getDirection(),intNormal);
        ofSetColor(col2);
        ofDrawLine(intersection, intersection + 100 * reflLight);
        ofPopStyle();
    }
    cam.end();

    string mode = transformation ? "intersect mesh with transformation applied" : "intersect mesh" ;
    string msg = "press 'm' to change the mode. Current mode: "+mode +"\n";
    msg += "bInside = "+ofToString(bInside)+ ", countIntersections = " + ofToString(countIntersections)+"\n";
    ofDrawBitmapString(msg, 20, 20);
    
    
}

void ofApp::keyPressed(int key){
    if (key == 'm') {
        transformation = !transformation;
    }
};

