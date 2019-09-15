#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(640,480);
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
}

void drawPebble(float size, float rMin = 3, float rMax = 100, int numSegments = 100, float noiseSmooth = 0.8, float noiseMin = 0, float noiseMax = 1) {
    float rBase = ofMap(size, 0, 1, rMin, rMax);
    float noiseOffset = ofRandom(0, 1000);
    
    ofPath path;
    for (int i = 0; i < numSegments; ++i) {
        float theta = TWO_PI * i / ((float) numSegments);
        float noise = ofMap(ofNoise(cos(theta) * noiseSmooth + noiseOffset, sin(theta) * noiseSmooth), 0, 1, noiseMin, noiseMax);
        float r = rBase* noise;
        
        float x = r * cos(theta);
        float y = r * sin(theta);
        if (i == 0) {
            path.moveTo(x, y);
        } else {
            path.lineTo(x, y);
        }
    }
    path.close();
    path.draw();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
//    grabber.draw(640,0);
    
    
    float width = ofGetWidth();
    float height = ofGetHeight();
    
    
    ofSeedRandom(0);
    
    float time = ofGetElapsedTimef();
    float cellSize = ofMap(sin(time * 0.5 + PI), -1, 1, 8, 24);
    float noiseSmooth = ofMap(sin(time), -1, 1, 0.1, 0.8);
    int numPoints = (width * height) / cellSize;
    
    // theta determines the spiral of the layout
    float theta = PI * (3 - sqrt(5));
    float pointRadius = cellSize / 2.0;
    ofPushMatrix();
    ofTranslate(width / 2.0, height / 2.0);
    float thetaOffset = ofMap(sin(time * 0.1), -1, 1, -0.002, 0.002);
    
    for (int i = 0; i < numPoints; i += 1) {
        int index = i;
        float thetaOffsetAmount = i / ((float)numPoints);
        float phylloX = pointRadius * sqrt(index) * cos(index * (theta + thetaOffset * thetaOffsetAmount));
        float phylloY = pointRadius * sqrt(index) * sin(index * (theta + thetaOffset * thetaOffsetAmount));
        float imageX = (phylloX + width / 2.0);
        float imageY = (phylloY + height / 2.0);
        
        // skip for efficiency
        if (imageX < -cellSize || imageX > width + cellSize || imageY < -cellSize || imageY > height + cellSize) {
            continue;
        }
        
        
        
        ofColor color = grabber.getPixels().getColor(
                                                     ofClamp(floor(imageX), 0, width - 1),
                                                     ofClamp(floor(imageY), 0, height -1 ));
        float brightness = color.getBrightness();
        ofPushMatrix();
        ofTranslate(phylloX, phylloY);
//        ofDrawCircle(0, 0, pointRadius * 0.8);
        
        ofTranslate(pointRadius, pointRadius);
        drawPebble(brightness / 255.0, cellSize * 0.02, cellSize * 0.4, 30,
                   noiseSmooth,
                   0.6, 1.5);
        
        ofPopMatrix();
    }
    ofPopMatrix();
////
//
////    int cellSize = ofMap(mouseY, 0, ofGetHeight(), 3, 100);
//    
////    float width = ofGetWidth();
////    float height = ofGetHeight();
////    ofPushMatrix();
//
//    for (float i = 0; i < grabber.getWidth(); i += cellSize){
//        for (float j = 0; j < grabber.getHeight(); j += cellSize){
////            float x = ofClamp(i > width / 2.0 ? i : width / 2.0 - i, 0, width - 1);
////            float y = ofClamp(j > height / 2.0 ? j : height / 2.0 - j, 0, height - 1);
//
////            ofColor color = grabber.getPixels().getColor(floor(x),floor(y));
////            float brightness = color.getBrightness();
////
////            ofPushMatrix();
////            ofTranslate(x + cellSize / 2.0, y + cellSize / 2.0);
////            drawPebble(brightness / 255.0, cellSize * 0.05, cellSize * 0.5, 30,
////                       noiseSmooth,
////                       0.6, 1.5);
////            ofPopMatrix();
//        }
//    }
//    ofPopMatrix();
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
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
