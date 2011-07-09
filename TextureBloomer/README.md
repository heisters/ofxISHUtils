An easy-to-use FBO-based bloom filter.

    #include "TextureBloomer/TextureBloomer.h"

    class testApp : public ofBaseApp {
      TextureBloomer bloomer;
      ofxFBOTexture fbo;
      void setup(){
        bloomer.setup(ofGetWidth(), ofGetHeight());
      }

      void update(){
        fbo.begin();
          // ... draw shit
        fbo.end();
        const int passes = 5;
        const float radiuses[passes] = {2.f, 3.f, 4.f, 5.f, 6.f};
        bloomer.update(fbo, passes, radiuses);
      }

      void draw(){
        bloomer.draw(0, 0, ofGetWidth(), ofGetHeight());
      }
    }

Requires ofxFBOTexture and ofxShader.
