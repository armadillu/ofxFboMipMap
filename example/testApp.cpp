#include "testApp.h"


void testApp::setup(){

	ofEnableAlphaBlending();
	ofBackground(255,128,199);

	//load an img
	ofLoadImage(myTex, "benottoAlpha.png");


	ofFbo::Settings s;
	s.width = myTex.getWidth();
	s.height = myTex.getHeight();
	s.internalformat = GL_RGBA;
	s.maxFilter = GL_LINEAR;
	s.minFilter = GL_LINEAR_MIPMAP_LINEAR;
	s.numSamples = 0;
	s.numColorbuffers = 3;
	s.useDepth = false;
	s.useStencil = false;


	//alloc with mipmaps
	myFBO.allocateWithMipMaps(s);


	//draw something inside the fbo
	myFBO.begin();
		ofClear(0, 0, 0, 0);
		myTex.draw(0,0);
	myFBO.end();

}


void testApp::draw(){
	myFBO.draw(0,0, mouseX, mouseY);
}
