#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  grabber.setup(640,480);
  img.allocate(grabber.getWidth(), grabber.getHeight(), OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){
  grabber.update();
  
  int speed = 5;
  // shuffle the frames
  for (int i = 0; i < speed; ++i) {
    ofImage temp;
    frames.push_back(temp);
    frames.back().setUseTexture(false);
    frames.back().setFromPixels(grabber.getPixels());
    if (frames.size() > 60){
      frames.erase(frames.begin());
    }
  }
  
  // for each line in the camera
  for (int j = 0; j < grabber.getHeight(); j++) {
    
    // find the frame for that line
    int whichFrame = ofMap(j, 0, grabber.getHeight(), 0, frames.size());
    for (int i = 0; i < grabber.getWidth(); i++){
      img.setColor(i, j, frames[whichFrame].getColor(i, j));
    }
  }
  
  img.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);
  ofSetColor(255);
  
  ofPushMatrix();
  ofTranslate(0, ofGetHeight() / 2);
  ofRotateXDeg(ofMap(mouseY, 0, ofGetHeight(), 0, 90, true));
  ofTranslate(0, -ofGetHeight() / 2);
  ofScale(2, 2);
  int yInc = 2;
  int xInc = 2;
  float time = ofGetElapsedTimef();
  float yMaxOffset = ofMap(sin(time), -1, 1, 20, 30);
  
  ofMesh mesh;
  
  for (int i = 0; i < img.getHeight(); i+= yInc){
    for (int j =0; j < img.getWidth() - 40; j += xInc){
      ofColor col = img.getPixels().getColor(j,i);
      int brightness = col.getBrightness();
      float y = i + ofMap(brightness, 0, 255, 0, yMaxOffset);
      float z = 0;
      mesh.addVertex(ofPoint(j, y, z));
      mesh.addColor(ofColor(
                            sin(time + i * 0.01) * 100 + 155,
                            cos(time + j * 0.01) * 100 + 155,
                            sin(time * 3 + j * 0.01) * 100 + 155
                            ));
      
    }

    mesh.draw();
  }
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
