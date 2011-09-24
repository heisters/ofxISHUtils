//
//  BlurShader.h
//
//  Created by Ian Smith-Heisters on 9/24/11.
//  Copyright 2011 Ian Smith-Heisters. All rights reserved.
//

#pragma once

#include "ofMain.h"

class BlurShader {
public:
    BlurShader() {};
    static const string horizontalSource_vert;
    static const string horizontalSource_frag;
    static const string verticalSource_vert;
    static const string verticalSource_frag;
    void setup(int width, int height);
    void update(float radius, ofBaseDraws &drawable);
    void draw(int x, int y);
    void draw(int x, int y, int w, int h);
private:
    ofShader hShader, vShader;
    ofFbo ping, pong;
};