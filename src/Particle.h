//
//  Particle.h
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/17.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Particle{
    
public:
    Particle();
    ~Particle();
    void setup(int x, int y, float speed = 5.0);
    void update();
    void draw();
    
    bool isDead();
    
    ofPoint getPosition();
    ofColor getColor();
    
private:
    float mX, mY;
    float mVX, mVY;
    float mAX, mAY;
    float mWidth, mHeight;
    bool bDead;
    ofColor mC;
};
