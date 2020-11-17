#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(60);
    camera.setup(ofGetWindowWidth(), ofGetWindowHeight());
    clone_.allocate(camera.getWidth(), camera.getHeight());

    gui.setup();
    gui.add(uiColor.set("color", ofVec3f(0, 1, 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1)));
    gui.add(uiThreshold.set("threshold", 0.6, 0, 1));
    
    shader.load("shader");
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    stepSize = 8;
    ySteps = camera.getHeight() / stepSize;
    xSteps = camera.getWidth() / stepSize;
    for (int y = 0; y < ySteps; y++) {
        for (int x = 0; x < xSteps; x++) {
            mesh.addVertex(ofVec3f(x * stepSize, y * stepSize, 0.0));
            mesh.addTexCoord(ofVec2f(x * stepSize, y * stepSize));
        }
    }
    for (int y = 0; y + 1 < ySteps; y++) {
        for (int x = 0; x + 1 < xSteps; x++) {
            int nw = y * xSteps + x;
            int ne = nw + 1;
            int sw = nw + xSteps;
            int se = sw + 1;
            mesh.addIndex(nw);
            mesh.addIndex(ne);
            mesh.addIndex(se);
            mesh.addIndex(nw);
            mesh.addIndex(se);
            mesh.addIndex(sw);
        }
    }
    
    // serial
    serial.setup("/dev/cu.usbmodem14201", 9600);

    // Init variables
    distortionStrength = 0.5;
}

//--------------------------------------------------------------
void ofApp::update(){
    camera.update();
    
    // Get ultrasonic data
    if (serial.available() < 0) {
        msg = "Arduino Error";
    }
    else {
        //While statement looping through serial messages when serial is being provided.
        while (serial.available() > 0) {
            //byte data is being writen into byteData as int.
            int byteData = serial.readByte();
            //printf("myByte is %d\n", byteData);

            // Use Arduino readings to determine blur of image
            byteData = INPUT_MAX - byteData;
            distortionStrength = ofMap(byteData, INPUT_MIN, INPUT_MAX, 0, 2);

            // Update message to print to console
            msg = "Distance: " + ofToString(byteData) + "; DistortionStrength: " + ofToString(distortionStrength);
        }
    }
    
    if (camera.isFrameNew()){
        clone_.setFromPixels(camera.getPixels());
        
        flow.setWindowSize(8);
        flow.calcOpticalFlow(camera);
        int i = 0;
        for (int y = 1; y + 1 < ySteps; y++) {
            for (int x = 1; x + 1 < xSteps; x++) {
                int i = y * xSteps + x;
                ofVec3f position(x * stepSize, y * stepSize, 0.0);
                ofRectangle area(position - ofVec3f(stepSize, stepSize, 0.0) / 2, stepSize, stepSize);
                ofVec2f offset = flow.getAverageFlowInRegion(area);
                mesh.setVertex(i, position + distortionStrength * offset);
                i++;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    camera.draw(0, 0);
    
    cout << msg << endl;
    
    camera.getTexture().bind();
    mesh.draw();
    camera.getTexture().unbind();
    
    shader.begin();
    shader.setUniform3f("u_color", uiColor->x, uiColor->y, uiColor->z);
    shader.setUniform1f("u_threshold", uiThreshold);
    clone_.draw(camera.getWidth(),0,-camera.getWidth(),camera.getHeight());
    shader.end();
    
    gui.draw();
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
