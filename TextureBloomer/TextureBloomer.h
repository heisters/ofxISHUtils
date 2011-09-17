#pragma once

#include "ofMain.h"

class TextureBloomer {
	public:
		TextureBloomer(){};
		void setup(int w, int h);
		void update(ofBaseDraws &drawable, const int passes, const float radiuses[]);
		void draw(int x, int y);
		void draw(int x, int y, int w, int h);
	private:
		ofFbo fbo1, fbo2;
		ofShader shaderBlurH, shaderBlurV;
};
