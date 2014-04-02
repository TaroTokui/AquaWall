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
    mX = x;
    mY = y;
    mVX = speed;
    mVY = speed;
    mWidth = 10.0;
    mHeight = 10.0;
    mC.setHsb(ofRandom(255), 255, 255);
    alpha = 255;
    mC.a = alpha;
    scale = 0.001;
    mSpeed = speed;
}

void Ring::update()
{
    mWidth += mVX;
    mHeight += mVY;
    
    alpha -= 4;
    mC.a = alpha;
    if (alpha<0) {
        bDead = true;
    }
    
    scale += mSpeed;
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