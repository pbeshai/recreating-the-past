#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    float width = ofGetWidth();
    float height = ofGetHeight();
    
    originalFbo.allocate(width, height);
    mask.allocate(width, height);
    
    mask.begin();
    ofClear(0,0,0);
    ofSetColor(255);
    ofSetCircleResolution(100);
    ofDrawCircle(width / 2, height / 2, width * 0.4);
    mask.end();
}

void drawLine(float x1, float y1, float x2, float y2) {
//    ofDrawLine(x1, y1, x2, y2);
    
//    ofPolyline line = ofPolyline();
//    line.addVertex(x1, y1);
//    line.addVertex(x2, y2);
// //    auto point = line.getPointAtLength(10)
//    line.draw();
    
    float slope = (y2 - y1) / (x2 - x1);
    float offset = y1 - slope * x1;
    float chunkWidth = 55;
    float x = x1;
    float y = y1;
    while (x < x2) {
        ofDrawLine(x, y, x + chunkWidth, y);
        x += chunkWidth;
        y = slope * x + offset;
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    float width = ofGetWidth();
    float height = ofGetHeight();
    
    originalFbo.begin();
    ofClear(255);
    ofSetColor(15);
    ofSetLineWidth(7);
    ofSeedRandom(649);
    
    
    int numLines = 75;
    float randomAmountMin = 20;
    float randomAmountMax = 40;
    
    for (int i = 0; i < numLines; ++i) {
        float y = ofMap(i, 0, numLines - 1, 0, height);
        float sign = ofRandom(0, 1) < 0.5 ? -1 : 1;
        float y1 = y + sign * ofRandom(randomAmountMin, randomAmountMax);
        float y2 = y1 + sign * ofRandom(randomAmountMin, randomAmountMax);
        drawLine(0, y1, width, y2);
    }
    
    
    originalFbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(230);
    originalFbo.getTexture().setAlphaMask(mask.getTexture());
    originalFbo.draw(0,0);
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
