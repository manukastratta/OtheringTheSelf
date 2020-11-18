#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

#define SAMPLE_LENGTH 441000  // ten seconds

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void audioIn(float * input, int bufferSize, int nChannels);
        void audioOut(float * output, int bufferSize, int nChannels);
    
    ofSoundStream soundStreamInput;
    ofSoundStream soundStreamOutput;
    
    float recording[SAMPLE_LENGTH];
    int recordingBufferOffset;
    int playingBufferOffset;
    
    bool isPlaying;
    bool isRecording;
    
    int bufferSize;
    
    ofxPanel gui;
    ofParameter <ofVec3f> uiColor;
    ofParameter <float> uiThreshold;
    
    ofVideoGrabber camera;
    ofxCvColorImage clone_;
    
    ofxCv::FlowFarneback flow;
    ofMesh mesh;
    int stepSize, xSteps, ySteps;
    float distortionStrength;
    const int INPUT_MIN = 0, INPUT_MAX = 200;
    
    string msg;
    
    ofShader shader;
    
    ofSerial serial; 
};
