#pragma once

#include "ofMain.h"
#include "ofxFboMipMap.h"
class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	ofxFboMipMap myFBO;
	ofTexture myTex;
};
