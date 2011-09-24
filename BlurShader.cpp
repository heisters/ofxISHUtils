#include "BlurShader.h"

const string BlurShader::horizontalSource_vert = "\
void main() {\n\
gl_TexCoord[0] = gl_MultiTexCoord0;\n\
gl_Position = ftransform();\n\
}\n";

const string BlurShader::horizontalSource_frag = "\
#extension GL_ARB_texture_rectangle : enable\n\
uniform sampler2DRect tex;\n\
uniform float radius;\n\
const float total = (1. + 8. + 28. + 56.) * 2. + 70.;\n\
void main() {\n\
vec2 st = gl_TexCoord[0].st;\n\
gl_FragColor += (1. / total) * texture2DRect(tex, st - radius * vec2(4. / 4., 0.));\n\
gl_FragColor += (8. / total)  * texture2DRect(tex, st - radius * vec2(3. / 4., 0.));\n\
gl_FragColor += (28. / total)  * texture2DRect(tex, st - radius * vec2(2. / 4., 0.));\n\
gl_FragColor += (56. / total)  * texture2DRect(tex, st - radius * vec2(1. / 4., 0.));\n\
gl_FragColor += (70. / total) * texture2DRect(tex, st);\n\
gl_FragColor += (1. / total) * texture2DRect(tex, st + radius * vec2(4. / 4., 0.));\n\
gl_FragColor += (8. / total)  * texture2DRect(tex, st + radius * vec2(3. / 4., 0.));\n\
gl_FragColor += (28. / total)  * texture2DRect(tex, st + radius * vec2(2. / 4., 0.));\n\
gl_FragColor += (56. / total)  * texture2DRect(tex, st + radius * vec2(1. / 4., 0.));\n\
}\n";

const string BlurShader::verticalSource_vert = "\
void main() {\n\
gl_TexCoord[0] = gl_MultiTexCoord0;\n\
gl_Position = ftransform();\n\
}\n";

const string BlurShader::verticalSource_frag = "\
#extension GL_ARB_texture_rectangle : enable\n\
uniform sampler2DRect tex;\n\
uniform float radius;\n\
// next is 1 10 45 120 210 252\n\
// then is 1 12 66 220 495 792 924\n\
const float total = (1. + 8. + 28. + 56.) * 2. + 70.;\n\
void main() {\n\
vec2 st = gl_TexCoord[0].st;\n\
gl_FragColor += (1. / total) * texture2DRect(tex, st - radius * vec2(0., 4. / 4.));\n\
gl_FragColor += (8. / total)  * texture2DRect(tex, st - radius * vec2(0., 3. / 4.));\n\
gl_FragColor += (28. / total)  * texture2DRect(tex, st - radius * vec2(0., 2. / 4.));\n\
gl_FragColor += (56. / total)  * texture2DRect(tex, st - radius * vec2(0., 1. / 4.));\n\
gl_FragColor += (70. / total) * texture2DRect(tex, st);\n\
gl_FragColor += (1. / total) * texture2DRect(tex, st + radius * vec2(0., 4. / 4.));\n\
gl_FragColor += (8. / total)  * texture2DRect(tex, st + radius * vec2(0., 3. / 4.));\n\
gl_FragColor += (28. / total)  * texture2DRect(tex, st + radius * vec2(0., 2. / 4.));\n\
gl_FragColor += (56. / total)  * texture2DRect(tex, st + radius * vec2(0., 1. / 4.));\n\
}\n";

void BlurShader::setup(int width, int height){
    hShader.setupShaderFromSource(GL_VERTEX_SHADER, horizontalSource_vert);
    hShader.setupShaderFromSource(GL_FRAGMENT_SHADER, horizontalSource_frag);
	vShader.setupShaderFromSource(GL_VERTEX_SHADER, verticalSource_vert);
    vShader.setupShaderFromSource(GL_FRAGMENT_SHADER, verticalSource_frag);
    hShader.linkProgram();
    vShader.linkProgram();
    ping.allocate(width, height);
    pong.allocate(width, height);
}

void BlurShader::update(float radius, ofBaseDraws &drawable){
    ping.begin();
        hShader.begin();
            hShader.setUniform1f("radius", radius);
            drawable.draw(0,0);
        hShader.end();
    ping.end();
    
    pong.begin();
        vShader.begin();
            vShader.setUniform1f("radius", radius);
            ping.draw(0,0);
        vShader.end();
    pong.end();
}

void BlurShader::draw(int x, int y){
    pong.draw(x, y);
}

void BlurShader::draw(int x, int y, int w, int h){
    pong.draw(x, y, w, h);
}