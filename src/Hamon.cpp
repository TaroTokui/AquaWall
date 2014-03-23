//
//  Hamon.cpp
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/17.
//
//

#include "Hamon.h"

Hamon::Hamon(){
    mImage.loadImage("images/ring.png");
    
    shader.load("shaders/sprite");
    
    plane.set(mImage.getWidth(), mImage.getHeight(), 2, 2, OF_PRIMITIVE_TRIANGLES);
    // setup
    plane.mapTexCoordsFromTexture(mImage.getTextureReference());
}

Hamon::~Hamon(){
}

void Hamon::setup(int x, int y, int n){
    
    Ring newRing;
    for (int i=0; i<1; i++) {
        newRing.setup(x, y, 0.04);
        rings.push_back(newRing);
    }
    
}

void Hamon::update(){
    it = rings.begin();
    while (it != rings.end()) {
        // 大きさと透明度で消す
        it->update();
        if ( it->isDead() ) {
            it = rings.erase(it);
        }else{
            it++;
        }
    }
}

void Hamon::draw(){
    
    // bind our texture. in our shader this will now be tex0 by default
    // so we can just go ahead and access it there.
    mImage.getTextureReference().bind();
    
    // start our shader, in our OpenGL3 shader this will automagically set
    // up a lot of matrices that we want for figuring out the texture matrix
    // and the modelView matrix
    shader.begin();
    
    it = rings.begin();
    
    while (it != rings.end())
    {
        ofColor tmpColor = it->getColor();
        shader.setUniform1f("red", (float)tmpColor.r / 255.0 );
        shader.setUniform1f("green", (float)tmpColor.g / 255.0);
        shader.setUniform1f("blue", (float)tmpColor.b / 255.0);
        shader.setUniform1f("alpha", (float)tmpColor.a / 255.0);
        
        ofPushMatrix();
        ofTranslate( (it->getRect()).getX(), (it->getRect()).getY() );
        ofScale((it->getRect()).getWidth(), (it->getRect()).getHeight());
        plane.draw();
        ofPopMatrix();
        
        it++;
    }
    
    shader.end();
    mImage.getTextureReference().unbind();
}
