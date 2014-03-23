//
//  Enemy.cpp
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/14.
//
//

#include "Enemy.h"

Enemy::Enemy():bDead(false){
    // 画像は共通なのでここでは読み込まないほうがいい
//    mImage.loadImage("images/boss.png");
}
Enemy::~Enemy(){}

void Enemy::setup(ofRectangle area, int _hp, int size, float speed)
{
    mX = ofRandom(area.width)+area.x;
    mY = ofRandom(area.height)+area.y;
    mVX = ofRandom(speed)-speed/2.0;
    mVY = ofRandom(speed)-speed/2.0;
    mAX = 0.0;
    mAY = 0.0;
    mWidth = size;
    mHeight = size;
    hp = _hp;
    bDead = false;
    mode = SPAWN;
    scale = 0.0;
    mArea = area;
    mType = KURAGE;
    mColor.setHsb(0, 255, 255);
}

void Enemy::setupButton(int x, int y, int size, Enemy_type _type)
{
    mX = x;
    mY = y;
    mVX = 0.0;
    mVY = 0.0;
    mAX = 0.0;
    mAY = 0.0;
    mWidth = size;
    mHeight = size;
    hp = 1;
    bDead = false;
    mode = SPAWN;
    scale = 0.0;
    mType = _type;
    
    switch (mType) {
        case VIRUS:
            mImage.loadImage("images/virus.png");
            mColor.setHsb(0, 255, 255);
            break;
            
        case KURAGE:
            mImage.loadImage("images/boss.png");
            mColor.setHsb(0, 255, 255);
            break;
            
        case CIRCLE:
            mColor.setHsb(0, 255, 255);
            break;
            
        default:
            break;
    }
    
}

void Enemy::update()
{
    mX += mVX;
    mY += mVY;
    mVX += mAX;
    mVY += mAY;
    
    switch (mode) {
        case NORMAL:
            break;
            
        case SPAWN:
            scale += 0.01;
            if( scale > 1.0 )
            {
                mode = NORMAL;
            }
            break;
            
        case DAMAGING:
            break;
            
        case DYING:
            scale += 0.01;
            if(scale > 2.0){
                mode = DEAD;
            }
            break;
            
        case DEAD:
            bDead = true;
            break;
            
        default:
            break;
    }
    
    if (mX < mArea.x || mArea.x + mArea.width < mX){
        mVX *= -1;
    }
    if(mY < mArea.y || mArea.y + mArea.height < mY) {
        mVY *= -1;
    }
    
    if (scale > 1.0 && scale <= 2.0) {
        mColor.a = (2.0 - scale)*255;
    }
}

void Enemy::draw()
{
    switch (mType) {
        case VIRUS:
        case KURAGE:
//            ofFill();
            ofSetColor(mColor);
            mImage.draw(mX - mWidth*scale *0.5, mY-mHeight*scale*0.5, mWidth*scale, mHeight*scale);
            break;
            
        case CIRCLE:
            ofFill();
            ofSetColor(mColor);
            ofEllipse(mX, mY, mWidth*scale, mHeight*scale);
            break;
            
        default:
            break;
    }
    
//    mImage.draw(mX - mWidth*scale *0.5, mY-mHeight*scale*0.5, mWidth*scale, mHeight*scale);
}

bool Enemy::isDead()
{
    return bDead;
}

bool Enemy::collider(int x, int y){
    float distance = sqrt( (mX-x)*(mX-x) + (mY-y)*(mY-y) );
    if (distance<mWidth/2) {
        hp--;
        if (hp<=0) {
            mode = DYING;
        }
        return true;
    }else{
        return false;
    }
}

ofRectangle Enemy::getPosition(){
//    ofRectangle tmpRect(mX - mWidth*scale *0.5, mY-mHeight*scale*0.5, mWidth*scale, mHeight*scale);
    ofRectangle tmpRect(mX, mY, scale, scale);   // for GL3.0
    return tmpRect;
}

ofColor Enemy::getColor(){
    return mColor;
}