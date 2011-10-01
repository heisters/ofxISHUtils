#include "TextureBloomer.h"

void TextureBloomer::setup(int w, int h){
	fbos.allocate(w, h);
    shader.setup(w, h);
}

void TextureBloomer::setBlend(GLenum sfactor, GLenum dfactor) {
    blendSFactor = sfactor;
    blendDFactor = dfactor;
}

void TextureBloomer::update(ofBaseDraws &drawable, const int passes, const float radiuses[]){
	fbos.current().begin();
        ofClear(0, 0, 0, 0);
		drawable.draw(0,0);
	fbos.current().end();

	for(int pass = 0; pass < passes; pass++){
		float radius = radiuses[pass];
        fbos.inc();
        shader.update(radius, fbos.prev());

        fbos.current().begin();
            shader.draw(0,0);
        fbos.current().end();
	}

    fbos.inc();
	glEnable(GL_BLEND);
	glBlendFunc(blendSFactor, blendDFactor);
		fbos.current().begin();
            ofClear(0, 0, 0, 0);
			fbos.prev().draw(0,0);
			drawable.draw(0,0);
		fbos.current().end();
	glDisable(GL_BLEND);
}

void TextureBloomer::draw(int x, int y){
	fbos.current().draw(x,y);
}
void TextureBloomer::draw(int x, int y, int w, int h){
	fbos.current().draw(x,y,w,h);
}
