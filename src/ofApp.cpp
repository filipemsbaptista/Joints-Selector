#include "ofApp.h"

/* -------------------------------------------------------------------
		 _____       _             ______ _      _             
		/  __ \     | |            | ___ (_)    | |            
		| /  \/ ___ | | ___  _ __  | |_/ /_  ___| | _____ _ __ 
		| |    / _ \| |/ _ \| '__| |  __/| |/ __| |/ / _ \ '__|
		| \__/\ (_) | | (_) | |    | |   | | (__|   <  __/ |   
		 \____/\___/|_|\___/|_|    \_|   |_|\___|_|\_\___|_|   
                                                       
----------------------------------------------------------------------*/
class ColorPicker : public ofBaseApp {
public:
		void setup();
		void draw();
		void mouseDragged(int x, int y);
		void mouseReleased(int x, int y);

		ofColor getColor1(), getColor2(), getColor3();

		ofFbo cP_fbo;					//Buffer to draw color picker
		float rectHeight;			//Height of the color shower
		float margin;				//Margin between color shower and color picker

		ofImage img;				//Image object for color picker
		
		ofColor color1, color2, color3, textColor;	

		float colorPickerIndex;		//0 - Left picker, 1 - Right picker, 2 - Middle picker

};

void ColorPicker::setup(){
	ofSetFrameRate(60);
	ofBackground(255, 255, 255, 255);
	
	img.loadImage("color-picker.png");

	rectHeight = 25;
	margin = 5;

	cP_fbo.allocate(img.width, img.height + rectHeight + margin, GL_RGB32F_ARB);

	color1 = ofColor(15,10,15);
	color2 = ofColor(ofColor::red);
	color3 = ofColor(ofColor::blue);
	textColor = ofColor(ofColor::black);

	colorPickerIndex = 0;
}

void ColorPicker::draw(){
	cP_fbo.begin();
	ofEnableAlphaBlending();  
		
	//Draw color gradient image
	ofSetColor(255,255,255);
	img.draw(0, rectHeight + margin);
		
	//Draw left picker
	ofSetColor(color1);
	ofFill();
	ofRect(2, 2, img.getWidth()/3, rectHeight);
		
	//Draw right picker
	ofSetColor(color2);
	ofFill();
	ofRect(img.getWidth() - (img.getWidth()/3) - 2, 2, img.getWidth()/3, rectHeight);

	//Draw middle picker
	ofSetColor(color3);
	ofFill();
	ofRect(4 + img.getWidth()/3, 2, img.getWidth()/3, rectHeight);

	ofDisableAlphaBlending();
	cP_fbo.end();

	glEnable(GL_BLEND);  
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);  

	ofSetColor(255,255,255);

	cP_fbo.draw(ofGetWidth() - cP_fbo.getWidth() - 5, ofGetHeight() - cP_fbo.getHeight() - 5);

	//Draw color picker text
	if(color1.r < 90 && color1.g < 90 && color1.b < 90)
			textColor = ofColor(255, 255, 255);
		else 
			textColor = ofColor(0, 0, 0);
	
	//Check picker text alpha value
	if(colorPickerIndex == 0)
		ofSetColor(textColor);
	else
		ofSetColor(textColor.r, textColor.g, textColor.b, 85);
	ofDrawBitmapString( "Background", ofGetWidth() - 5 - cP_fbo.getWidth(), ofGetHeight() - 5 - cP_fbo.getHeight() - 5 );
		
	if(colorPickerIndex == 1)
		ofSetColor(textColor);
	else
		ofSetColor(textColor.r, textColor.g, textColor.b, 85);
	ofDrawBitmapString( "Death", ofGetWidth() - 5 - cP_fbo.getWidth()/3, ofGetHeight() - 5 - cP_fbo.getHeight() - 5 );

	if(colorPickerIndex == 2)
		ofSetColor(textColor);
	else
		ofSetColor(textColor.r, textColor.g, textColor.b, 85);
	ofDrawBitmapString( "Birth", ofGetWidth() - 5 - cP_fbo.getWidth() + img.getWidth()/3, ofGetHeight() - 5 - cP_fbo.getHeight() - 5 );

}

void ColorPicker::mouseDragged(int mouseX, int mouseY){
	//Check drag on color gradient
	if(mouseX < ofGetWidth() - 20 && mouseX > ofGetWidth() - 20 - img.width && mouseY < ofGetHeight() - 20 && mouseY > ofGetHeight() - 20 - img.height){
		cP_fbo.begin();
		GLubyte RGB[3];
		float x = cP_fbo.getWidth() - (ofGetWidth() - mouseX - 20);
		float y = cP_fbo.getHeight() - (ofGetHeight() - mouseY - 20);

		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &RGB[0]);
		if(colorPickerIndex == 0)
			color1 = ofColor(RGB[0], RGB[1], RGB[2], 255);
		else
			if(colorPickerIndex == 1)
				color2 = ofColor(RGB[0], RGB[1], RGB[2], 255);	
			else
				color3 = ofColor(RGB[0], RGB[1], RGB[2], 255);
		cP_fbo.end();
	}
}

void ColorPicker::mouseReleased(int mouseX, int mouseY){
	//Check click on color gradient
	if(mouseX < ofGetWidth() - 20 && mouseX > ofGetWidth() - 20 - img.width && mouseY < ofGetHeight() - 20 && mouseY > ofGetHeight() - 20 - img.height){
		cP_fbo.begin();
		GLubyte RGB[3];
		float x = cP_fbo.getWidth() - (ofGetWidth() - mouseX - 20);
		float y = cP_fbo.getHeight() - (ofGetHeight() - mouseY - 20);

		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &RGB[0]);
		if(colorPickerIndex == 0)
			color1 = ofColor(RGB[0], RGB[1], RGB[2], 255);
		else
			if(colorPickerIndex == 1)
				color2 = ofColor(RGB[0], RGB[1], RGB[2], 255);	
			else
				color3 = ofColor(RGB[0], RGB[1], RGB[2], 255);
		cP_fbo.end();
	}
	
	//Check click on first picker
	if(mouseX < (ofGetWidth() - 20 - img.getWidth() + 2) + img.getWidth()/3 &&
		mouseX > ofGetWidth() - 20 - img.getWidth() + 2 &&
		mouseY < ofGetHeight() - 20 - cP_fbo.getHeight() + 2 + rectHeight &&
		mouseY > ofGetHeight() - 20 - cP_fbo.getHeight() + 2){
			colorPickerIndex = 0;
			cout << "Clicked on left picker!" << endl;
	}

	//Check click on second picker
	if(mouseX < ofGetWidth() - 20 - 2 &&
		mouseX > ofGetWidth() - 20 - 2 - img.getWidth()/3 &&
		mouseY < ofGetHeight() - 20 - cP_fbo.getHeight() + 2 + rectHeight &&
		mouseY > ofGetHeight() - 20 - cP_fbo.getHeight() + 2){
			colorPickerIndex = 1;
			cout << "Clicked on rigth picker!" << endl;
	}

	//Check click on second picker
	if(mouseX < ofGetWidth() - 20 - img.getWidth() + img.getWidth()/3 + 2 + img.getWidth()/3 &&
		mouseX > ofGetWidth() - 20 - img.getWidth() + img.getWidth()/3 + 2 &&
		mouseY < ofGetHeight() - 20 - cP_fbo.getHeight() + 2 + rectHeight &&
		mouseY > ofGetHeight() - 20 - cP_fbo.getHeight() + 2){
			colorPickerIndex = 2;
			cout << "Clicked on middle picker!" << endl;
	}
}

ofColor ColorPicker::getColor1(){
	return color1;
}

ofColor ColorPicker::getColor2(){
	return color2;
}

ofColor ColorPicker::getColor3(){
	return color3;
}



/* ----------------------------------------------------------
		 _____         _      ___              
		|_   _|       | |    / _ \             
		  | | ___  ___| |_  / /_\ \_ __  _ __  
		  | |/ _ \/ __| __| |  _  | '_ \| '_ \ 
		  | |  __/\__ \ |_  | | | | |_) | |_) |
		  \_/\___||___/\__| \_| |_/ .__/| .__/ 
								  | |   | |    
								  |_|   |_|    
--------------------------------------------------------------*/
float radius = 8;
ColorPicker cP;

void ofApp::setup(){
	ofSetFrameRate(60);
	ofBackground(255, 255, 255, 255);
	
	visible = true;

	img.loadImage("body_silhouette.jpeg");

	fbo.allocate(img.width, img.height, GL_RGB32F_ARB);

	headActivated = neckActivated = shoulderLActivated = shoulderRActivated = elbowRActivated = handRActivated = 
		torsoActivated = hipLActivated = kneeLActivated = kneeRActivated = footLActivated = footRActivated = false;

	elbowLActivated = handLActivated = hipRActivated = true;

	hover_head = hover_neck = hover_shoulderL = hover_shoulderR = hover_elbowL = hover_elbowR = hover_handL = hover_handR =
			hover_torso = hover_hipL = hover_hipR = hover_kneeL = hover_kneeR = hover_footL = hover_footR = false;

	jointSelected = 0;

	setupJointsPositions();

	cP.setup();
}

void ofApp::update(){
	//Check if mouse is inside joints selector
	if(mouseX > ofGetWidth() - fbo.getWidth() - 15 && mouseX < ofGetWidth() - 15 && mouseY > 50 && mouseY < 50 + fbo.getHeight()){
		
		//CHECK MOUSE HOVER
		//Head
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + headPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + headPos.x - radius)
			&& mouseY > (50 + headPos.y - radius) && mouseY < (50 + headPos.y + radius)){
			hover_head = true;
		}
		else
			hover_head = false;
		//Neck
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + neckPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + neckPos.x - radius)
			&& mouseY > (50 + neckPos.y - radius) && mouseY < (50 + neckPos.y + radius)){
			hover_neck = true;
		}
		else
			hover_neck = false;
		//Shoulders
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + shoulderLPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + shoulderLPos.x - radius)
			&& mouseY > (50 + shoulderLPos.y - radius) && mouseY < (50 + shoulderLPos.y + radius)){
			hover_shoulderL = true;
		}
		else
			hover_shoulderL = false;

		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + shoulderRPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + shoulderRPos.x - radius)
			&& mouseY > (50 + shoulderRPos.y - radius) && mouseY < (50 + shoulderRPos.y + radius)){
			hover_shoulderR = true;
		}
		else
			hover_shoulderR = false;
		//Elbows
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + elbowLPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + elbowLPos.x - radius)
			&& mouseY > (50 + elbowLPos.y - radius) && mouseY < (50 + elbowLPos.y + radius)){
			hover_elbowL = true;
		}
		else
			hover_elbowL = false;

		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + elbowRPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + elbowRPos.x - radius)
			&& mouseY > (50 + elbowRPos.y - radius) && mouseY < (50 + elbowRPos.y + radius)){
			hover_elbowR = true;
		}
		else
			hover_elbowR= false;
		//Hands
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + handLPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + handLPos.x - radius)
			&& mouseY > (50 + handLPos.y - radius) && mouseY < (50 + handLPos.y + radius)){
			hover_handL = true;
		}
		else
			hover_handL = false;

		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + handRPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + handRPos.x - radius)
			&& mouseY > (50 + handRPos.y - radius) && mouseY < (50 + handRPos.y + radius)){
			hover_handR = true;
		}
		else
			hover_handR = false;
		//Torso
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + torsoPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + torsoPos.x - radius)
			&& mouseY > (50 + torsoPos.y - radius) && mouseY < (50 + torsoPos.y + radius)){
			hover_torso = true;
		}
		else
			hover_torso = false;
		//Hips
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + hipLPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + hipLPos.x - radius)
			&& mouseY > (50 + hipLPos.y - radius) && mouseY < (50 + hipLPos.y + radius)){
			hover_hipL = true;
		}
		else
			hover_hipL = false;

		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + hipRPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + hipRPos.x - radius)
			&& mouseY > (50 + hipRPos.y - radius) && mouseY < (50 + hipRPos.y + radius)){
			hover_hipR = true;
		}
		else
			hover_hipR = false;
		//Knees
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + kneeLPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + kneeLPos.x - radius)
			&& mouseY > (50 + kneeLPos.y - radius) && mouseY < (50 + kneeLPos.y + radius)){
			hover_kneeL = true;
		}
		else
			hover_kneeL = false;

		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + kneeRPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + kneeRPos.x - radius)
			&& mouseY > (50 + kneeRPos.y - radius) && mouseY < (50 + kneeRPos.y + radius)){
			hover_kneeR = true;
		}
		else
			hover_kneeR = false;
		//Feet
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + footLPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + footLPos.x - radius)
			&& mouseY > (50 + footLPos.y - radius) && mouseY < (50 + footLPos.y + radius)){
			hover_footL = true;
		}
		else
			hover_footL = false;

		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + footRPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + footRPos.x - radius)
			&& mouseY > (50 + footRPos.y - radius) && mouseY < (50 + footRPos.y + radius)){
			hover_footR = true;
		}
		else
			hover_footR = false;
		//---------------- END OF HOVER CHECK  ----------------
	}


	cP.update();
}

void ofApp::draw(){
	ofBackgroundGradient(ofColor::white, ofColor::black, OF_GRADIENT_CIRCULAR);

	if(visible){
		fbo.begin();
		ofEnableSmoothing();

		//1. Draw body image
		ofSetColor(255,255,255);
		img.draw(0, 0);


		//2. Draw joints
		ofEnableAlphaBlending();  
		ofFill();
		ofSetColor(ofColor::green);
		drawJoints();

		
		//3. Draw bones
		drawBones();
		
		//Draw hover information
		if(hover_head){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(headPos.x, headPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		if(hover_neck){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(neckPos.x, neckPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		if(hover_shoulderL){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(shoulderLPos.x, shoulderLPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		if(hover_shoulderR){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(shoulderRPos.x, shoulderRPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		if(hover_elbowL){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(elbowLPos.x, elbowLPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		if(hover_elbowR){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(elbowRPos.x, elbowRPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		if(hover_handL){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(handLPos.x, handLPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		if(hover_handR){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(handRPos.x, handRPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);

		}
		if(hover_torso){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(torsoPos.x, torsoPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		if(hover_hipL){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(hipLPos.x, hipLPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		if(hover_hipR){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(hipRPos.x, hipRPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		if(hover_kneeL){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(kneeLPos.x, kneeLPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		if(hover_kneeR){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(kneeRPos.x, kneeRPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		if(hover_footL){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(footLPos.x, footLPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		if(hover_footR){
			ofNoFill();
			ofSetLineWidth(4);
			ofSetColor(ofColor::grey);
			ofCircle(footRPos.x, footRPos.y, 1, radius);
			ofFill();
			ofSetLineWidth(1);
		}
		fbo.end();
		glEnable(GL_BLEND);  
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);  

		ofSetColor(255,255,255);
		fbo.draw(ofGetWidth() - fbo.getWidth() - 15, 50);

		//Draw Joint GUI
		switch (jointSelected){
			case 0:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + headPos.x, 50 + headPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 1:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + neckPos.x, 50 + neckPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 2:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + shoulderLPos.x, 50 + shoulderLPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 3:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + shoulderRPos.x, 50 + shoulderRPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 4:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + elbowLPos.x, 50 + elbowLPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 5:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + elbowRPos.x, 50 + elbowRPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 6:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + handLPos.x, 50 + handLPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 7:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + handRPos.x, 50 + handRPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 8:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + torsoPos.x, 50 + torsoPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 9:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + hipLPos.x, 50 + hipLPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 10:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + hipRPos.x, 50 + hipRPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 11:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + kneeLPos.x, 50 + kneeLPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 12:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + kneeRPos.x, 50 + kneeRPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 13:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + footLPos.x, 50 + footLPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
			case 14:
				ofNoFill();
				ofSetLineWidth(3);
				ofCircle(ofGetWidth() - fbo.getWidth() - 16 + footRPos.x, 50 + footRPos.y, 1, radius + 1);
				ofSetLineWidth(1);
				break;
		}

		//Draw color picker
		cP.draw();
	}
}

void ofApp::setupJointsPositions(){
	headPos = ofPoint(fbo.getWidth()/2, 25);
	neckPos = ofPoint(fbo.getWidth()/2, 65);
	shoulderLPos = ofPoint(fbo.getWidth()/2 - 30, 75);
	shoulderRPos = ofPoint(fbo.getWidth()/2 + 30, 75);
	elbowLPos = ofPoint(fbo.getWidth()/2 - 40, 125);
	elbowRPos = ofPoint(fbo.getWidth()/2 + 40, 125);
	handLPos = ofPoint(fbo.getWidth()/2 - 58, 185);
	handRPos = ofPoint(fbo.getWidth()/2 + 58, 185);
	torsoPos = ofPoint(fbo.getWidth()/2, 120);
	hipLPos = ofPoint(fbo.getWidth()/2 - 20, 170);
	hipRPos = ofPoint(fbo.getWidth()/2 + 20, 170);
	kneeLPos = ofPoint(fbo.getWidth()/2 - 18, 240);
	kneeRPos = ofPoint(fbo.getWidth()/2 + 20, 240);
	footLPos = ofPoint(fbo.getWidth()/2 - 21, 305);
	footRPos = ofPoint(fbo.getWidth()/2 + 26, 305);
}

void ofApp::drawJoints(){
	//Draw head joint
		if(headActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(headPos.x, headPos.y, 1, radius);

		//Draw neck joint
		if(neckActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(neckPos.x, neckPos.y, 1, radius);

		//Draw shoulders joints
		if(shoulderLActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(shoulderLPos.x, shoulderLPos.y, 1, radius);

		if(shoulderRActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(shoulderRPos.x, shoulderRPos.y, 1, radius);

		//Draw elbows joints
		if(elbowLActivated)
			ofFill();	
		else
			ofNoFill();
		ofCircle(elbowLPos.x, elbowLPos.y, 1, radius);

		if(elbowRActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(elbowRPos.x, elbowRPos.y, 1, radius);

		//Draw hands joints
		if(handLActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(handLPos.x, handLPos.y, 1, radius);

		if(handRActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(handRPos.x, handRPos.y, 1, radius);

		//Draw torso joint
		if(torsoActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(torsoPos.x, torsoPos.y, 1, radius);

		//Draw hips joints
		if(hipLActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(hipLPos.x, hipLPos.y, 1, radius);

		if(hipRActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(hipRPos.x, hipRPos.y, 1, radius);

		//Draw knees joints
		if(kneeLActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(kneeLPos.x, kneeLPos.y, 1, radius);

		if(kneeRActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(kneeRPos.x, kneeRPos.y, 1, radius);

		//Draw feet joints
		if(footLActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(footLPos.x, footLPos.y, 1, radius);

		if(footRActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(footRPos.x, footRPos.y, 1, radius);
}

void ofApp::drawBones(){
		ofLine(ofPoint(headPos.x, headPos.y + radius), ofPoint(neckPos.x, neckPos.y - radius));
		ofLine(ofPoint(neckPos.x - radius, neckPos.y), ofPoint(shoulderLPos.x + radius, shoulderLPos.y - 5));
		ofLine(ofPoint(neckPos.x + radius, neckPos.y), ofPoint(shoulderRPos.x - radius, shoulderRPos.y - 5));
		ofLine(ofPoint(shoulderLPos.x - 3, shoulderLPos.y + 8), ofPoint(elbowLPos.x + 2, elbowLPos.y - 8));
		ofLine(ofPoint(shoulderRPos.x + 3, shoulderRPos.y + 8), ofPoint(elbowRPos.x - 2, elbowRPos.y - 8));
		ofLine(ofPoint(elbowLPos.x - 2, elbowLPos.y + 8), ofPoint(handLPos.x + 2, handLPos.y - 8));
		ofLine(ofPoint(elbowRPos.x + 2, elbowLPos.y + 8), ofPoint(handRPos.x - 2, handLPos.y - 8));
		ofLine(ofPoint(shoulderLPos.x + radius - 2, shoulderLPos.y + radius - 3), ofPoint(torsoPos.x - 3, torsoPos.y - radius));
		ofLine(ofPoint(shoulderRPos.x - radius + 2, shoulderRPos.y + radius - 3), ofPoint(torsoPos.x + 3, torsoPos.y - radius));
		ofLine(ofPoint(torsoPos.x - 3, torsoPos.y + radius), ofPoint(hipLPos.x + 2, hipLPos.y - radius));
		ofLine(ofPoint(torsoPos.x + 3, torsoPos.y + radius), ofPoint(hipRPos.x - 2, hipRPos.y - radius));
		ofLine(ofPoint(hipLPos.x + radius, hipLPos.y), ofPoint(hipRPos.x - radius, hipRPos.y));
		ofLine(ofPoint(hipLPos.x, hipLPos.y + radius), ofPoint(kneeLPos.x, kneeLPos.y - radius));
		ofLine(ofPoint(hipRPos.x, hipRPos.y + radius), ofPoint(kneeRPos.x, kneeRPos.y - radius));
		ofLine(ofPoint(kneeLPos.x, kneeLPos.y + radius), ofPoint(footLPos.x, footLPos.y - radius));
		ofLine(ofPoint(kneeRPos.x, kneeRPos.y + radius), ofPoint(footRPos.x, footRPos.y - radius));
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == OF_KEY_RETURN){
		visible = !visible;
	}
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
	if(hover_head){
		jointSelected = 0;
	}
	if(hover_neck){
		jointSelected = 1;
	}
	if(hover_shoulderL){
		jointSelected = 2;
	}
	if(hover_shoulderR){
		jointSelected = 3;
	}
	if(hover_elbowL){
		jointSelected = 4;

	}
	if(hover_elbowR){
		jointSelected = 5;
	}
	if(hover_handL){
		jointSelected = 6;
	}
	if(hover_handR){
		jointSelected = 7;
	}
	if(hover_torso){
		jointSelected = 8;
	}
	if(hover_hipL){
		jointSelected = 9;
	}
	if(hover_hipR){
		jointSelected = 10;
	}
	if(hover_kneeL){
		jointSelected = 11;
	}
	if(hover_kneeR){
		jointSelected = 12;
	}
	if(hover_footL){
		jointSelected = 13;
	}
	if(hover_footR){
		jointSelected = 14;
	}
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
