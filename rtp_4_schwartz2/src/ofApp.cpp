#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    swapColors = false;
    enableColorSwapping = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    if (enableColorSwapping && ofRandom(0, 1) < 0.25) {
        swapColors = !swapColors;
    }
    
    ofColor color1 = ofColor(0);
    ofColor color2 = ofColor(255);
    
    if (swapColors) {
        ofColor swap = color1;
        color1 = color2;
        color2 = swap;
    }
    
    float cellSize = 1;
    float width = ofGetWidth();
    float height = ofGetHeight();
    int numCols = ceil(width / cellSize);
    int numRows = ceil(height / cellSize);
    
    float time = ofGetElapsedTimef();
    float noiseZoom = 0.01; //ofMap(sin(time), -1, 1, 0.006, 0.025, true);
    float bandSize = ofMap(sin(time * 0.514), -1, 1, 0.04, 0.1);
    float bandMin = ofMap(sin(time * 0.1), -1, 1, 0.3, 0.6);
    float bandMax = ofMap(sin(time * 0.1 + PI), -1, 1, 1.0, 0.8);
    float slice = time * 20;

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            ofColor color;
            bool skip = false;

            float noise = ofNoise(j * noiseZoom, i * noiseZoom, slice * noiseZoom);

            for (int b = 0; b < 1 / bandSize; ++b) {
                if (noise >= b * bandSize && noise < (b + 1) * bandSize) {
                    if (noise < bandMin || noise > bandMax) {
                        skip = true;
                        break;
                    }
                    color = b % 2 == 0 ? color1 : color2;

                }
            }

            if (!skip) {
                img.setColor(j * cellSize, i * cellSize, color);
            } else {
                // erase
                img.setColor(j * cellSize, i * cellSize, color1);
            }

        }
    }
    
    img.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofFill();
    img.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//    cout << x << "," << y << endl;
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
