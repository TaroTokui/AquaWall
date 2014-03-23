//
//  Particle.cpp
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/17.
//
//

#include "Particle.h"

Particle::Particle():bDead(false){
//    cout << "new particle" << endl;
}
Particle::~Particle(){
//    cout << "delete particle" << endl;
}

void Particle::setup(int x, int y, float speed)
{
    mX = x;
    mY = y;
    mVX = ofRandom(speed)-speed/2.0;
    mVY = ofRandom(speed)-speed/2.0;
    mAX = 0.0;
    mAY = 0.2;
    mWidth = 10.0;
    mHeight = 10.0;
    mC.setHsb(ofRandom(255), 255, 255);
    mC.a = 200;
}

void Particle::update()
{
    mX += mVX;
    mY += mVY;
    mVX += mAX;
    mVY += mAY;
    
    if (mX < 0 || ofGetWidth() < mX || mY < 0 || ofGetHeight() < mY) {
        bDead = true;
    }
    
}

void Particle::draw()
{
    ofEllipse(mX, mY, mWidth, mHeight);
}

bool Particle::isDead()
{
    return bDead;
}

ofPoint Particle::getPosition(){
    ofPoint tmpPoint;
    tmpPoint.x = mX;
    tmpPoint.y = mY;
    return tmpPoint;
}

ofColor Particle::getColor(){
    return mC;
}