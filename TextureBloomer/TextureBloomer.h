#pragma once

#include "ofxFBOTexture.h"
#include "ofxShader.h"

class TextureBloomer {
	public:
		TextureBloomer(){};
		void setup(int w, int h);
		void update(ofTexture & tex, const int passes, const float radiuses[]);
		void draw(int x, int y);
		void draw(int x, int y, int w, int h);
	private:
		ofxFBOTexture fbo1, fbo2;
		ofxShader shaderBlurH, shaderBlurV;
};
