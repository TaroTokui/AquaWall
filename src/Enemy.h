//
//  Enemy.h
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/14.
//
//
#pragma once

#include "ofMain.h"

typedef enum { NORMAL, SPAWN, DAMAGING, DYING, DEAD } Enemy_state;
typedef enum { VIRUS, KURAGE, CIRCLE } Enemy_type;

class Enemy{
    
public:
    Enemy();
    ~Enemy();
    void setup(ofRectangle area, int hp = 0, int size = 100, float speed=5.0);
    void setupButton(int x, int y, int size, Enemy_type _type = VIRUS);
    void update();
    void draw();
    
    bool isDead();
    bool collider(int x, int y);
    
    ofRectangle getPosition();
    ofColor getColor();
    
	ofParameterGroup parameters;
private:
    float mX, mY;
    float mVX, mVY;
    float mAX, mAY;
    float mWidth, mHeight;
    bool bDead;
    float scale;
    ofColor mColor;
    ofRectangle mArea;
    
    int hp;
    Enemy_state mode;
    Enemy_type mType;
    
    ofImage mImage;
    
};
