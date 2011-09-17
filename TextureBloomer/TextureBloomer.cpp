#include "TextureBloomer.h"
const char * hVertShaderSource = "\
void main() {\n\
    gl_TexCoord[0] = gl_MultiTexCoord0;\n\
    gl_Position = ftransform();\n\
}\n";

const char * hFragShaderSource = "\
#extension GL_ARB_texture_rectangle : enable\n\
uniform sampler2DRect tex;\n\
uniform float radius;\n\
const float total = (1. + 8. + 28. + 56.) * 2. + 70.;\n\
void main(void) {\n\
    vec2 st = gl_TexCoord[0].st;\n\
    gl_FragColor += (1. / total) * texture2DRect(tex, st - radius * vec2(4. / 4., 0.));\n\
    gl_FragColor += (8. / total)  * texture2DRect(tex, st - radius * vec2(3. / 4., 0.));\n\
    gl_FragColor += (28. / total)  * texture2DRect(tex, st - radius * vec2(2. / 4., 0.));\n\
    gl_FragColor += (56. / total)  * texture2DRect(tex, st - radius * vec2(1. / 4., 0.));\n\
    gl_FragColor +=  (70. / total) * texture2DRect(tex, st);\n\
    gl_FragColor += (1. / total) * texture2DRect(tex, st + radius * vec2(4. / 4., 0.));\n\
    gl_FragColor += (8. / total)  * texture2DRect(tex, st + radius * vec2(3. / 4., 0.));\n\
    gl_FragColor += (28. / total)  * texture2DRect(tex, st + radius * vec2(2. / 4., 0.));\n\
    gl_FragColor += (56. / total)  * texture2DRect(tex, st + radius * vec2(1. / 4., 0.));\n\
}\n";

const char * vVertShaderSource = "\
void main() {\n\
    gl_TexCoord[0] = gl_MultiTexCoord0;\n\
    gl_Position = ftransform();\n\
}\n";

const char * vFragShaderSource = "\
#extension GL_ARB_texture_rectangle : enable\n\
uniform sampler2DRect tex;\n\
uniform float radius;\n\
// next is 1 10 45 120 210 252\n\
// then is 1 12 66 220 495 792 924\n\
const float total = (1. + 8. + 28. + 56.) * 2. + 70.;\n\
void main(void) {\n\
    vec2 st = gl_TexCoord[0].st;\n\
    gl_FragColor += (1. / total) * texture2DRect(tex, st - radius * vec2(0., 4. / 4.));\n\
    gl_FragColor += (8. / total)  * texture2DRect(tex, st - radius * vec2(0., 3. / 4.));\n\
    gl_FragColor += (28. / total)  * texture2DRect(tex, st - radius * vec2(0., 2. / 4.));\n\
    gl_FragColor += (56. / total)  * texture2DRect(tex, st - radius * vec2(0., 1. / 4.));\n\
    gl_FragColor +=  (70. / total) * texture2DRect(tex, st);\n\
    gl_FragColor += (1. / total) * texture2DRect(tex, st + radius * vec2(0., 4. / 4.));\n\
    gl_FragColor += (8. / total)  * texture2DRect(tex, st + radius * vec2(0., 3. / 4.));\n\
    gl_FragColor += (28. / total)  * texture2DRect(tex, st + radius * vec2(0., 2. / 4.));\n\
    gl_FragColor += (56. / total)  * texture2DRect(tex, st + radius * vec2(0., 1. / 4.));\n\
}\n";

void TextureBloomer::setup(int w, int h){
	fbo1.allocate(w, h);
	fbo2.allocate(w, h);

	shaderBlurH.setupShaderFromSource(GL_VERTEX_SHADER, hVertShaderSource);
    shaderBlurH.setupShaderFromSource(GL_FRAGMENT_SHADER, hFragShaderSource);
	shaderBlurV.setupShaderFromSource(GL_VERTEX_SHADER, vVertShaderSource);
    shaderBlurV.setupShaderFromSource(GL_FRAGMENT_SHADER, vFragShaderSource);
}

void TextureBloomer::update(ofBaseDraws &drawable, const int passes, const float radiuses[]){
	fbo2.begin();
        ofClear(0, 0, 0, 1);
		drawable.draw(0,0);
	fbo2.end();

	for(int pass = 0; pass < passes; pass++){
		float radius = radiuses[pass];
		fbo1.begin();
			shaderBlurH.begin();
				shaderBlurH.setUniform1f("radius", radius);
				fbo2.draw(0, 0);
			shaderBlurH.end();
		fbo1.end();

		fbo2.begin();
			shaderBlurV.begin();
				shaderBlurV.setUniform1f("radius", radius);
				fbo1.draw(0, 0);
			shaderBlurV.end();
		fbo2.end();
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
		fbo1.begin();
            ofClear(0, 0, 0, 1);
			fbo2.draw(0,0);
			drawable.draw(0,0);
		fbo1.end();
	glDisable(GL_BLEND);
}

void TextureBloomer::draw(int x, int y){
	fbo1.draw(x,y);
}
void TextureBloomer::draw(int x, int y, int w, int h){
	fbo1.draw(x,y,w,h);
}
