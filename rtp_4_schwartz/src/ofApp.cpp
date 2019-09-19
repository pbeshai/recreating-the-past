#include "ofApp.h"



void dilate( ofImage & imgA, ofImage & imgB){
    
    
    for (int i = 0; i < imgA.getWidth(); i++){
        for (int j = 0; j < imgA.getHeight(); j++){
            
            ofColor nw = imgA.getColor( ofClamp(i-1, 0, imgA.getWidth()-1),
                                       ofClamp(j-1, 0, imgA.getHeight()-1));
            ofColor n_ = imgA.getColor( ofClamp(i, 0, imgA.getWidth()-1),
                                       ofClamp(j-1, 0, imgA.getHeight()-1));
            ofColor ne = imgA.getColor( ofClamp(i+1, 0, imgA.getWidth()-1),
                                       ofClamp(j-1, 0, imgA.getHeight()-1));
            ofColor e_ = imgA.getColor( ofClamp(i+1, 0, imgA.getWidth()-1),
                                       ofClamp(j, 0, imgA.getHeight()-1));
            ofColor se = imgA.getColor( ofClamp(i+1, 0, imgA.getWidth()-1),
                                       ofClamp(j+1, 0, imgA.getHeight()-1));
            ofColor s_ = imgA.getColor( ofClamp(i, 0, imgA.getWidth()-1),
                                       ofClamp(j+1, 0, imgA.getHeight()-1));
            ofColor sw = imgA.getColor( ofClamp(i-1, 0, imgA.getWidth()-1),
                                       ofClamp(j+1, 0, imgA.getHeight()-1));
            ofColor w_ = imgA.getColor( ofClamp(i-1, 0, imgA.getWidth()-1),
                                       ofClamp(j, 0, imgA.getHeight()-1));
            
            
            ofColor color = imgA.getColor(i,j);
            if (color.getBrightness() < 127){
                if (nw.getBrightness() > 127 ||
                    n_.getBrightness() > 127 ||
                    ne.getBrightness() > 127 ||
                    e_.getBrightness() > 127 ||
                    se.getBrightness() > 127 ||
                    s_.getBrightness() > 127 ||
                    sw.getBrightness() > 127 ||
                    w_.getBrightness() > 127){
                    imgB.setColor(i,j, ofColor(255));
                } else {
                    imgB.setColor(i,j, ofColor(0));
                }
                
            } else {
                imgB.setColor(i,j,color);
            }
            //imgB.setColor(i,j,color);
        }
    }
    
    
}


void erode( ofImage & imgA, ofImage & imgB){
    
    
    for (int i = 0; i < imgA.getWidth(); i++){
        for (int j = 0; j < imgA.getHeight(); j++){
            
            ofColor nw = imgA.getColor( ofClamp(i-1, 0, imgA.getWidth()-1),
                                       ofClamp(j-1, 0, imgA.getHeight()-1));
            ofColor n_ = imgA.getColor( ofClamp(i, 0, imgA.getWidth()-1),
                                       ofClamp(j-1, 0, imgA.getHeight()-1));
            ofColor ne = imgA.getColor( ofClamp(i+1, 0, imgA.getWidth()-1),
                                       ofClamp(j-1, 0, imgA.getHeight()-1));
            ofColor e_ = imgA.getColor( ofClamp(i+1, 0, imgA.getWidth()-1),
                                       ofClamp(j, 0, imgA.getHeight()-1));
            ofColor se = imgA.getColor( ofClamp(i+1, 0, imgA.getWidth()-1),
                                       ofClamp(j+1, 0, imgA.getHeight()-1));
            ofColor s_ = imgA.getColor( ofClamp(i, 0, imgA.getWidth()-1),
                                       ofClamp(j+1, 0, imgA.getHeight()-1));
            ofColor sw = imgA.getColor( ofClamp(i-1, 0, imgA.getWidth()-1),
                                       ofClamp(j+1, 0, imgA.getHeight()-1));
            ofColor w_ = imgA.getColor( ofClamp(i-1, 0, imgA.getWidth()-1),
                                       ofClamp(j, 0, imgA.getHeight()-1));
            
            
            ofColor color = imgA.getColor(i,j);
            if (color.getBrightness() > 127){
                if (nw.getBrightness() < 127 ||
                    n_.getBrightness() < 127 ||
                    ne.getBrightness() < 127 ||
                    e_.getBrightness() < 127 ||
                    se.getBrightness() < 127 ||
                    s_.getBrightness() < 127 ||
                    sw.getBrightness() < 127 ||
                    w_.getBrightness() < 127){
                    imgB.setColor(i,j, ofColor(0));
                } else {
                    imgB.setColor(i,j, ofColor(255));
                }
                
            } else {
                imgB.setColor(i,j,color);
            }
            //imgB.setColor(i,j,color);
        }
    }
    
    
}

void drawConcRect(float x, float y, float width, float height, float thickness = 10) {
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    ofTranslate(x, y);
    
    float w = width;
    float h = height;
    float color = 255;
    while (w > thickness && h > thickness) {
        ofSetColor(color);
        ofFill();
        ofDrawRectangle(0, 0, w, h);
        
        w -= 2 * thickness;
        h -= 2 * thickness;
        color = color == 255 ? 0 : 255;
    }
    
    ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::setup(){
    /*
     QUESTIONS
     ofFbo or ofImage or ofPixels? which to use for this?
     */
//    imgBuffer1.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
//    imgBuffer2.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
//    pxBuffer1.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
//    pxBuffer1.begin();
    fboBuffer1.allocate(ofGetWidth(), ofGetHeight());
    fboBuffer1.begin();
    ofBackground(0);
    ofSetColor(255);
    ofFill();
    
    ofPushMatrix();
    drawConcRect(ofGetWidth() / 2, ofGetHeight() / 2, 95, 95, 10);
    ofPopMatrix();
//    pxBuffer1.end();
//    imgBuffer1.setFromPixels(pxBuffer1);
//
    fboBuffer1.end();
    fboBuffer1.readToPixels(pxBuffer1);
    imgBuffer1.setFromPixels(pxBuffer1);
    imgBuffer2.setFromPixels(pxBuffer1);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofFill();
//
//    ofPushMatrix();
//
//    drawConcRect(ofGetWidth() / 2, ofGetHeight() / 2, 95, 95, 10);
//
//    ofPopMatrix();
    imgBuffer1.draw(0, 0);
//    fboBuffer1.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    erode(imgBuffer1, imgBuffer2);
    imgBuffer1.setFromPixels(imgBuffer2);
//    imgBuffer1.update();
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
