//
//  Boss.h
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/18.
//
//
// 赤色
// 中央付近をウロウロ動く：後回し、trigonoなんとかのサンプルで動きつくろうかな
// 空気砲が当たると色が黄色くなって大きさが振動する(5秒)
// その後、突然大きくなって爆発して消える
// このとき、電磁バルブをONにする


#pragma once

#include "ofMain.h"
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
	ofParameter<int> size, max_hp, hibana_num, change_duration, dying;
    ofParameter<float> grow_speed;
};
