#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofTrueTypeFontSettings settings("MPLUS1p-Black.ttf", 172);
    settings.antialiased = true;
    settings.dpi = 72;
    settings.direction = OF_TTF_LEFT_TO_RIGHT;
    settings.contours = true;
    settings.addRanges(ofAlphabet::Japanese);
    
    font.load(settings);
    font.setLetterSpacing(0.4);
}

//--------------------------------------------------------------
void ofApp::update(){

}

void drawLetter(ofPath& letter, float x, float y) {
    vector<ofPolyline> lines = letter.getOutline();
    ofPushMatrix();
    ofTranslate(x, y);
    
    for (int j = 0; j < lines.size(); ++j) {
        ofPolyline &line = lines[j];
        line.draw();
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::draw(){
    float width = ofGetWidth();
    float height = ofGetHeight();
    ofBackground(255);
    ofSetColor(0);
    ofSeedRandom(0);
    
    
    string morisawa = "モリサワ";
    ofRectangle textbbox = font.getStringBoundingBox(morisawa, 0, 0);
    
    ofPushMatrix();
    // draw main string at top (-4, -19) to center within bbox dimensions
    ofTranslate((width - textbbox.width) / 2 - 4, textbbox.height - 19);
    
    // draw outlines for each letter
    vector<ofPath> letters = font.getStringAsPoints(morisawa, true, false);
    ofNoFill();
    
    ofSetLineWidth(1);
    
    int numRepeats = 250;
    int numLetters = letters.size();
    for (int i = 0; i < numLetters; ++i) {
        float xFreq = -0.027; //mouseX * -0.001; //ofRandom(0.01, 0.02);
        float xAmplitude = -178.5; //-mouseY * 0.5; //ofRandom(240, 314);
        
        ofPushMatrix();
        for (int j = 0; j < numRepeats; ++j) {
            
            float x = sin(j * xFreq) * xAmplitude * ofNoise(j * 0.01 + i * 4) * 1.63;
            if (i >= numLetters / 2.0) {
                x *= -1;
            }
            float y = 6 * (j + 1);
//            x = 0;
            ofTranslate(textbbox.width * 0.25 * (i + 1), textbbox.height / 2.0);
            ofRotateZDeg(ofSignedNoise(i * 0.01 + i * 4, j * 0.01 + i) * 0.5);
//            ofRotateZDeg(ofRandom(-0.25, 0.4));
//            ofRotateYDeg(ofRandom(1, 5));
            ofTranslate(-textbbox.width * 0.25 * (i + 1), -textbbox.height / 2.0);
//            ofRotateXDeg(mouseX * 0.01);
//            ofRotateDeg(0.5, 0, 0.5 * mouseY, mouseX); //mouseX * 0.01);
//            ofRotateXDeg(mouseX * 0.05);
//            float noise = ofNoise(i * mouseX * 0.01, j * mouseY * 0.01);
//            x = noise * 100;
            ofSetColor(120, 120, 120, ofMap(y, 0, height - textbbox.height + 19, 255, 0));
            drawLetter(letters[i], x, y);
        }
        ofPopMatrix();
    }
    
    
    // draw main text (draw last to overlap
    ofSetColor(0);
    font.drawString(morisawa, 0, 0);
    
    ofPopMatrix();
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
    cout << x << "," << y << endl;
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
