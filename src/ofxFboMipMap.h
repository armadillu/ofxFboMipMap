//
//  ofxFboMipMap.h
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 13/03/14.
//
//

#ifndef __BaseApp__ofxFboMipMap__
#define __BaseApp__ofxFboMipMap__

#include "ofMain.h"

class ofxFboMipMap: public ofFbo{

public:

	void allocateWithMipMaps(ofFbo::Settings s){

		bool reEnableARB = false;

		if ( ofGetUsingArbTex() ){
			ofLog(OF_LOG_WARNING, "ofxFboMipMap >> allocating fbo but ARB_TEX is enabled! mipmaps wont draw correclty! disabling ARB for you before allocating, enabling it back afterwards!");
			ofDisableArbTex();
			reEnableARB = true;
		}
		if (s.textureTarget != GL_TEXTURE_2D){
			ofLog(OF_LOG_WARNING, "ofxFboMipMap >> allocating fbo with textureTarget not set to GL_TEXTURE_2D?? Are you sure? Setting it for you!");
			s.textureTarget = GL_TEXTURE_2D;
		}

		if (s.minFilter != GL_LINEAR_MIPMAP_LINEAR){
			ofLog(OF_LOG_WARNING, "ofxFboMipMap >> allocating fbo with minFilter not set to GL_LINEAR_MIPMAP_LINEAR?? Are you sure?");
		}

		ofLogLevel l = ofGetLogLevel();
		ofSetLogLevel(OF_LOG_SILENT); //shush fbo creation verbose 
		ofFbo::allocate(s);
		ofSetLogLevel(l);
		//ofFbo::getTextureReference().setCompression(OF_COMPRESS_MIPMAPS);

		if(reEnableARB){
			ofEnableArbTex();
		}
	};

	void setMipMapBias(float bias){
		getTextureReference().bind();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, bias);
		getTextureReference().unbind();
	}

	void end(){ //this updates the mipmaps!

		//end through superClass
		ofFbo::end();

		//update the mipmap afterwards
		getTextureReference().bind();
			glGenerateMipmap(ofFbo::getTextureReference().texData.textureTarget);
		getTextureReference().unbind();
	}
};

#endif
