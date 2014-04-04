//
//  Ring.cpp
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/18.
//
//

#include "Ring.h"

Ring::Ring():bDead(false){}
Ring::~Ring(){}

void Ring::setup(int x, int y, float speed)
{
    setup(x, y, speed, 4);
}

void Ring::setup(int x, int y, float speed, float _alpha)
{
    setup(x, y, speed, _alpha, -1);
}

void Ring::setup(int x, int y, float speed, float _alpha, int hue)
{
    mX = x;
    mY = y;
    mVX = speed;
    mVY = speed;
    mWidth = 10.0;
    mHeight = 10.0;
    if (hue<0) {
        mC.setHsb(ofRandom(255), 255, 255);
    }else{
        mC.setHsb(hue, 255, 255);
    }
    alpha_speed = _alpha;
    alpha = 255;
    scale = 0.001;
    mSpeed = speed;
}

void Ring::update()
{
    mWidth += mVX;
    mHeight += mVY;
    
    alpha -= alpha_speed;
    mC.a = alpha;
    
    scale += mSpeed;
    
    if (alpha<0 || scale > ofGetWidth()) {
        bDead = true;
    }
    
}

void Ring::draw()
{
//    ofEllipse(mX, mY, mWidth, mHeight);
}

bool Ring::isDead()
{
    return bDead;
}

ofRectangle Ring::getRect(){
    ofRectangle tmpRect;
//    tmpRect.set(mX-mWidth/2, mY-mHeight/2, mWidth, mHeight);
    tmpRect.set(mX, mY, scale, scale);
    return tmpRect;
}

ofColor Ring::getColor(){
    return mC;
}