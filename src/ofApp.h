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
		void drawJoints(), drawBones();

		ofPoint  headPos, neckPos, shoulderLPos, shoulderRPos, elbowLPos, elbowRPos, handLPos, handRPos,
			torsoPos, hipLPos, hipRPos, kneeLPos, kneeRPos, footLPos, footRPos;
		
		bool visible;

		bool headActivated, neckActivated, shoulderLActivated, shoulderRActivated, elbowLActivated, elbowRActivated, handLActivated, handRActivated,
			torsoActivated, hipLActivated, hipRActivated, kneeLActivated, kneeRActivated, footLActivated, footRActivated;

		bool hover_head, hover_neck, hover_shoulderL, hover_shoulderR, hover_elbowL, hover_elbowR, hover_handL, hover_handR,
			hover_torso, hover_hipL, hover_hipR, hover_kneeL, hover_kneeR, hover_footL, hover_footR;

		int jointSelected;
};
