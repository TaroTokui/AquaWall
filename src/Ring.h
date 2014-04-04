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
    void setup(int x, int y, float speed, float _alpha);
    void setup(int x, int y, float speed, float _alpha, int hue);
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
    int alpha_speed;
    float scale;
    float mSpeed;
};