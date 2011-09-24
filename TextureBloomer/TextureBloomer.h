#pragma once

#include "ofMain.h"
#include "BlurShader.h"
#include "Ringbuffer.h"

class TextureBloomer {
public:
    TextureBloomer() : blendSFactor(GL_ONE), blendDFactor(GL_ONE) {};
    void setup(int w, int h);
    void update(ofBaseDraws &drawable, const int passes, const float radiuses[]);
    void draw(int x, int y);
    void draw(int x, int y, int w, int h);
    void setBlend(GLenum sfactor, GLenum dfactor);
private:
    FBORingbuffer<ofFbo, 2> fbos;
    BlurShader shader;
    GLenum blendSFactor, blendDFactor;
};
