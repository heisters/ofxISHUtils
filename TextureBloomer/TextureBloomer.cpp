#include "TextureBloomer.h"

// cribbed from ofxShader, adapted to read from the local directory
string loadShaderCode(string filename) {
	ifstream file;
	// HAXX: I see lots of posts that say it won't work. But it does for
	// me, for now.
	string currentFile (__FILE__);
	currentFile.replace(currentFile.find("TextureBloomer.cpp"), 18, "");
	// end HAXX
	file.open((currentFile + filename).c_str());
	if(file.is_open()) {
		string text;
		while(!file.eof()) {
			string line;
			getline(file, line);
			text += line + '\n';
		}
		file.close();
		stringstream msg;
		msg << "Loaded " << filename << ", " << text.size() << " characters.";
		ofLog(OF_LOG_VERBOSE, msg.str());
		return text;
	} else {
		ofLog(OF_LOG_ERROR, "Could not open " + filename);
	}
}

void TextureBloomer::setup(int w, int h){
	fbo1.allocate(w, h);
	fbo2.allocate(w, h);

	shaderBlurH.setupInline(loadShaderCode("shaders/blur_horizontal.vert"), loadShaderCode("shaders/blur_horizontal.frag"));
	shaderBlurV.setupInline(loadShaderCode("shaders/blur_vertical.vert"), loadShaderCode("shaders/blur_vertical.frag"));
}

void TextureBloomer::update(ofTexture & tex, const int passes, const float radiuses[]){
	fbo1.clear();
	fbo2.clear();

	fbo2.begin();
		tex.draw(0,0);
	fbo2.end();

	for(int pass = 0; pass < passes; pass++){
		float radius = radiuses[pass];
		fbo1.begin();
			shaderBlurH.begin();
				shaderBlurH.setUniform("radius", radius);
				fbo2.draw(0, 0);
			shaderBlurH.end();
		fbo1.end();

		fbo2.begin();
			shaderBlurV.begin();
				shaderBlurV.setUniform("radius", radius);
				fbo1.draw(0, 0);
			shaderBlurV.end();
		fbo2.end();
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
		fbo1.begin();
			fbo2.draw(0,0);
			tex.draw(0,0);
		fbo1.end();
	glDisable(GL_BLEND);
}

void TextureBloomer::draw(int x, int y){
	fbo1.draw(x,y);
}
void TextureBloomer::draw(int x, int y, int w, int h){
	fbo1.draw(x,y,w,h);
}
