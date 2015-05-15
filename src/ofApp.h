#pragma once

#include "ofMain.h"

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofFbo fbo;
		ofImage img;

		void setupJointsPositions();
		ofPoint  headPos, neckPos, shoulderLPos, shoulderRPos, elbowLPos, elbowRPos, handLPos, handRPos,
			torsoPos, hipLPos, hipRPos, kneeLPos, kneeRPos, footLPos, footRPos;
		
		bool visible;

		bool headSelected, neckSelected, shoulderLSelected, shoulderRSelected, elbowLSelected, elbowRSelected, handLSelected, handRSelected,
			torsoSelected, hipLSelected, hipRSelected, kneeLSelected, kneeRSelected, footLSelected, footRSelected;
		
};
