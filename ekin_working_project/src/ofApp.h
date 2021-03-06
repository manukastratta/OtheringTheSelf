#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"
//#include "audioTools.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void audioIn(float* input, int bufferSize, int nChannels);
		void audioOut(float* buffer, int bufferSize, int nChannels);
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
		
		ofxPanel gui;
		ofParameter <ofVec3f> uiColor;
		ofParameter <float> uiThreshold;

		ofxCvColorImage clone_;

		ofShader shader;

		ofVideoGrabber cam; 
		ofxCv::FlowFarneback flow; 
		ofMesh mesh; 
		int stepSize, xSteps, ySteps; 

		ofxCvColorImage img; 

		float distortionStrength; 
		const int INPUT_MIN = 0, INPUT_MAX = 100; 
		string msg; 

		ofSerial serial; 

		// audio
		int sampleRate;
		int bufferSize;
		vector<float> inputBuffer;

};
