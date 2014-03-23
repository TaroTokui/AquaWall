//
//  Boss.h
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/18.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Enemy.h"

class Boss: public Enemy{
    
public:
    Boss();
    ~Boss();
    void setup(int x, int y, Enemy_type = VIRUS);
    void update();
    void draw();
    
    bool isDead();
    bool doExplode();
    bool collider(int x, int y);
    
    int getX();
    int getY();
//    int getSparkSize();
    int getSparkNum();
//    int getSparkSpeed();
    
	ofParameterGroup parameters;
private:
    float mX, mY;
    float mVX, mVY;
    float mAX, mAY;
    float mWidth, mHeight;
    float scale;
    bool bDead;
    ofColor mColor;
    
    ofImage mImage;
    
    int hp;
    Enemy_state mode;
    Enemy_type type;
    
    unsigned long long start_time;
    
    // gui
	ofParameter<int> size, max_hp, hibana_num, change_duration;
    ofParameter<float> grow_speed;
};
