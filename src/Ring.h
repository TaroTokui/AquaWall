//
//  Ring.h
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/18.
//
//

#pragma once

#include "ofMain.h"

class Ring{
    
public:
    Ring();
    ~Ring();
    void setup(int x, int y, float speed);
    void update();
    void draw();
    
    bool isDead();
    
    ofRectangle getRect();
    ofColor getColor();
    
private:
    float mX, mY;
    float mVX, mVY;
    float mWidth, mHeight;
    bool bDead;
    ofColor mC;
    int alpha;
    float scale;
    float mSpeed;
};