#include "testApp.h"


void testApp::setup(){

	ofEnableAlphaBlending();
	ofBackground(255,128,199);
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);
	//load an img
	ofLoadImage(myTex, "benottoAlpha.png");

	glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST); //tune performance here! mipmaps can be slow

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
	//myFBO.allocate(s);

	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	cout << "GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT : " << maxAnisotropy << endl;

}

void testApp::update(){

	//draw something inside the fbo
	myFBO.begin();
		ofClear(0, 0, 0, 0);
		ofSetColor(255);
		myTex.draw(0,0);
		ofScale(10, 10);
		ofSetColor(0);
		ofDrawBitmapString("frame: " + ofToString(ofGetFrameNum()), 20,20);
	myFBO.end();

	//makes the mipmaps look much sharper in extreme shrink / perspective cases
	//you should check for extensions yada yada
	myFBO.getTextureReference().bind();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
	myFBO.getTextureReference().unbind();

}


void testApp::draw(){
	ofSetColor(255);
	myFBO.draw(0,0, mouseX, mouseY);
}
