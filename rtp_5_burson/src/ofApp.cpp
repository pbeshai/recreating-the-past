#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setDeviceID(1); // use external webcam
    grabber.setup(640, 480);
    tracker.setup();
    targetImg.load("katie.jpg");
    trackerTarget.setup();
    trackerSource.setup();
    sourceImg.allocate(640, 480, OF_IMAGE_COLOR);
    cameraFbo.allocate(640, 480);
    
    // these don't seem to do anything until in the update method
    trackerSource.update(sourceImg);
    trackerTarget.update(targetImg);
    
    shader.load("shader.vert", "shader.frag");
    
    showWireframe = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    if (grabber.isFrameNew()) {
        tracker.update(grabber);
    }
    
    if (ofGetFrameNum() % 60 == 0){
        shader.load("shader.vert", "shader.frag");
    }
}




void drawCameraFace(float x, float y, ofxFaceTracker2& tracker, ofVideoGrabber& grabber) {
    // if no tracker data
    if (tracker.size() <= 0) {
        // just draw the camera for now
        grabber.draw(0, 0);
        return;
    }
    
    auto &landmarks = tracker.getInstances()[0].getLandmarks();
    
    // find eye positions
    ofPolyline leftEye = landmarks.getImageFeature(ofxFaceTracker2Landmarks::LEFT_EYE);
    glm::vec3 leftEyeCenter = leftEye.getCentroid2D();
    ofPolyline rightEye = landmarks.getImageFeature(ofxFaceTracker2Landmarks::RIGHT_EYE);
    glm::vec3 rightEyeCenter = rightEye.getCentroid2D();
    glm::vec3 betweenEyes = glm::mix(leftEyeCenter, rightEyeCenter, 0.5);
    
    
    float desiredEyeWidth = 100;
    glm::vec3 eyeDiff = rightEyeCenter - leftEyeCenter;
    
    float angle = atan2(eyeDiff.y, eyeDiff.x);
    float scale = desiredEyeWidth / glm::length(eyeDiff);
    scale = glm::round(scale * 10) / 10;
//    cout << scale << " " << glm::length(eyeDiff) << " " << eyeDiff << " " << leftEyeCenter << " " << rightEyeCenter << endl;
    
    ofPushMatrix();
    ofTranslate(320, 207);
    ofScale(scale, scale);
    ofRotateZRad(-angle);
    grabber.setAnchorPoint(betweenEyes.x, betweenEyes.y);
    grabber.draw(0, 0);
    ofSetColor(255);

    // draw debug eyes
#ifdef DRAW_DEBUG_EYES
    ofPushMatrix();
    ofTranslate(-betweenEyes);
    ofDrawCircle(leftEyeCenter, 6);
    ofDrawCircle(rightEyeCenter, 6);
    ofDrawCircle(betweenEyes, 3);
    ofPopMatrix();
#endif
    
    // tracker.drawDebug();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    // draw main face
    cameraFbo.begin();
    drawCameraFace(0, 0, tracker, grabber);
    cameraFbo.end();
    
    ofPushMatrix();
    ofTranslate(-100, 0);
    
    // draw camera to screen
    // cameraFbo.draw(0, 0);
    
    ofMesh sourceMesh;
    ofMesh targetMesh;
    
    if (trackerSource.size() > 0) {
        auto &landmarks = trackerSource.getInstances()[0].getLandmarks();
        sourceMesh = landmarks.getImageMesh();
        //        ofPolyline allFeatures = landmarks.getImageFeature(ofxFaceTracker2Landmarks::FACE_OUTLINE);
        auto vertices = sourceMesh.getVertices();
        int numVx = vertices.size();
        
        for (int i = 0; i < numVx; ++i) {
            //            sourceMesh.addTexCoord(landmarks.getImagePoint(i));
            sourceMesh.addTexCoord(vertices[i]);
            //            if (i % 3 == 0) {
            //                sourceMesh.addTexCoord(glm::vec2(300, 200));
            //            } else if (i % 3 == 1) {
            //                sourceMesh.addTexCoord(glm::vec2(340, 200));
            //            } else {
            //                sourceMesh.addTexCoord(glm::vec2(320, 240));
            //            }
            //            if (i >= 36 && i < 40) {
            //                sourceMesh.addColor(ofColor(255, 0, 0));
            //
            //            } else {
            ////                sourceMesh.addColor(ofColor(ofMap(i, 0, numVx - 1, 0, 255), 100, 100));
            //                sourceMesh.addColor(ofColor(0, 255, 0));
            //            }
            
        }
        
        
        //        ofSetColor(255, 0, 0);
        
        sourceImg.bind();
        //        targetImg.bind();
        sourceMesh.drawFaces();
        //        targetImg.unbind();
        sourceImg.unbind();
        
        
        if (showWireframe) {
            ofSetColor(255, 0, 0);
            sourceMesh.drawWireframe();
            ofSetColor(255);
        }
        
        ofPushMatrix();
        ofTranslate(400, 0);
        
        // draw a 50% faded version of the source img
//        ofSetColor(255, 255, 255, 128);
//        sourceImg.bind();
//        sourceMesh.drawFaces();
//        sourceImg.unbind();
//
//        shader.begin();
//        shader.setUniformTexture("sourceImg", sourceImg, 0);
//        sourceMesh.drawFaces();
//        shader.end();
//
        
        ofPopMatrix();
        
        
    }
    
    
    
    // draw blended
    ofPushMatrix();
    ofTranslate(400, 0);
    ofSetColor(255);
    // sourceImg.draw(-640, 0);
//    trackerSource.drawDebug();
    
    
    
    if (trackerSource.size() > 0 && trackerTarget.size() > 0) {
        auto &sourceLandmarks = trackerSource.getInstances()[0].getLandmarks();
        ofMesh sourceMesh = sourceLandmarks.getImageMesh();
        auto sourceVx = sourceMesh.getVertices();
        int numSourceVx = sourceVx.size();
        
        auto &targetLandmarks = trackerTarget.getInstances()[0].getLandmarks();
        ofMesh targetMesh = targetLandmarks.getImageMesh();
        auto targetVx = targetMesh.getVertices();
        int numTargetVx = targetVx.size();
        
        // add the closest corresponding vertex in the target as a tex coordinate here
        // (note: order and number of vertices is not meaningful between meshes)
        for (int i = 0; i < numSourceVx; ++i) {
//            auto vx = targetVx[MIN(i, numTargetVx - 1)];
            glm::vec2 vx;
            float minDistance = 10000000;
            for (int j = 0; j < numTargetVx; ++j) {
                float dist = glm::fastDistance(sourceVx[i], targetVx[j]);
                if (dist < minDistance) {
                    vx = targetVx[j];
                    minDistance = dist;
                }
            }
            sourceMesh.addTexCoord(vx);
        }
        
        // draw a 50% img of the target texture on the source img mesh
//        ofSetColor(255, 255, 255, 128);
//        targetImg.bind();
//        sourceMesh.drawFaces();
//        targetImg.unbind();
        
        
        shader.begin();
        shader.setUniformTexture("sourceImg", sourceImg, 0);
        shader.setUniformTexture("targetImg", targetImg, 1);
        shader.setUniform2f("mouse", mouseX, mouseY);
        shader.setUniform2f("screen", ofGetWidth(), ofGetHeight());
        
        sourceMesh.drawFaces();
        shader.end();
        
        
        if (showWireframe) {
            ofSetColor(255, 0, 0);
            sourceMesh.drawWireframe();
            ofSetColor(255);
        }
        
        
    }
    ofPopMatrix();
    
    
    // draw just the face portion of the source
    // draw just the face portion of the target
    
    // normalize source and target to be the same shape
    // --> or just try drawing the target in the shape of the source.
    
    
    
    // draw target image
    ofPushMatrix();
    ofTranslate(800, 0);
    ofSetColor(255);
//    targetImg.draw(0, 0);
//    trackerTarget.drawDebug();
    
    if (trackerTarget.size() > 0) {
        auto &landmarks = trackerTarget.getInstances()[0].getLandmarks();
        ofMesh targetMesh = landmarks.getImageMesh();
        auto vertices = targetMesh.getVertices();
        int numVx = vertices.size();
        for (int i = 0; i < numVx; ++i) {
            targetMesh.addTexCoord(vertices[i]);
        }
        
        
        targetImg.bind();
        targetMesh.drawFaces();
        targetImg.unbind();
        
        
        if (showWireframe) {
            ofSetColor(0, 255, 0);
            targetMesh.drawWireframe();
            ofSetColor(255);
        }
        
    }
    
    
    ofPopMatrix();
    ofPopMatrix();
    
//    shader.begin();
//    shader.setUniform1f("time", ofGetElapsedTimef());
//    shader.setUniformTexture("rockImg", rock, 0);
//    shader.setUniformTexture("lineImg", fbo, 1);
//    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
//    shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << key << endl;
//    sourceImg.setFromPixels(grabber.getPixels());
    // save the modified data from the video camera into an image
    int leftArrow = 57356;
    int rightArrow = 57358;
    int x = 120;
    int space = 32;
    
    // replace left image
    if (key == leftArrow) {
        cameraFbo.getTexture().readToPixels(sourceImg.getPixels());
        sourceImg.update();
    // replace right image
    } else if (key == rightArrow) {
        cameraFbo.getTexture().readToPixels(targetImg.getPixels());
        targetImg.update();
        
    // reset to katie
    } else if (key == x) {
        targetImg.load("katie.jpg");
    } else if (key == space) {
        showWireframe = !showWireframe;
    }
    
    trackerSource.update(sourceImg);
    trackerTarget.update(targetImg);
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
    if (trackerSource.size() > 0) {
        auto &landmarks = trackerSource.getInstances()[0].getLandmarks();
        auto cvImagePoints = landmarks.getCvImagePoints();
        auto imgPoints = landmarks.getImagePoints();
        cout << cvImagePoints[0] << endl;
        cout << imgPoints[0] << endl;
    }
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
