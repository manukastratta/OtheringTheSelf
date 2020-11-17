#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sampleRate = 48000;
    bufferSize = 512;
    
    inputBuffer.resize(bufferSize * 1); // *1 bc 1 input chanel
    
    ofSoundStreamSetup(2, 1, sampleRate, bufferSize, 4); // 4 for number of buffers 
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

void ofApp::audioIn(float* input, int bufferSize, int nChannels) { // will be called automatically once buffer is full of audio samples
    for(int i = 0; i < bufferSize; i++) {
        inputBuffer[i*nChannels+0] = input[i];
    }
}

void ofApp::audioOut(float* buffer, int bufferSize, int nChannels) {
    // take input and push to output!
    
    for(int i = 0; i < bufferSize; i++) {
        float inputSample;
        float currentSample;
        
        inputSample = inputBuffer[i]; // the next sample of the input
        
        currentSample = inputSample;
        
        buffer[i*nChannels+0] = currentSample;
        buffer[i*nChannels + 1] = currentSample;
    }
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

void ofApp::exit() {
    ofSoundStreamClose();
}
