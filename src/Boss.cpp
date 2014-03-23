//
//  Boss.cpp
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/18.
//
//

#include "Boss.h"

Boss::Boss():bDead(false){
	parameters.setName("Boss status");
	parameters.add(size.set("size",200,0,500));
	parameters.add(max_hp.set("hp",10,0,20));
	parameters.add(grow_speed.set("grow speed",0.05, 0.0, 1.0));
	parameters.add(change_duration.set("change duration",500,0,2000));
//	parameters.add(hibana_size.set("hibana size",10,1,50));
	parameters.add(hibana_num.set("hibana num",10,1,100));
//	parameters.add(hibana_speed.set("hibana speed",5.0, 0.0, 20.0));
    
    mImage.loadImage("images/virus.png");
}

Boss::~Boss(){}

void Boss::setup(int x, int y, Enemy_type _type)
{
    mX = x;
    mY = y;
    mVX = 0;
    mVY = 0;
    mAX = 0.0;
    mAY = 0.0;
    mWidth = size;
    mHeight = size;
    scale = 0.0;
    hp = max_hp;
    bDead = false;
    mColor.setHsb(20, 255, 255);
    type = _type;
    
    start_time = ofGetElapsedTimeMillis();
    mode = SPAWN;
}

void Boss::update()
{
    // ゆらゆら動く
    mX += mVX;
    mY += mVY;
    mVX += mAX;
    mVY += mAY;
    
    // 変化時間, 変化サイズ, 位置フレームで変化する値
    // 1フレームで変化する値 = 最終的な倍率 / 何回膨張させるか(max_hp) / 変化に係る時間 * 経過時間
//    float tmpGrows = 2.0;
    
    switch (mode) {
        case NORMAL:
            break;
            
        case SPAWN:
            scale += grow_speed / (float)max_hp * 0.1;
            if( scale > 1.0 )
            {
                mode = NORMAL;
            }
            break;
            
        case DAMAGING:
            scale += grow_speed / (float)max_hp * 0.1;
            if( ofGetElapsedTimeMillis() - start_time > change_duration )
            {
                mode = NORMAL;
            }
            break;
            
        case DYING:
                scale -= grow_speed*0.1;
                if(scale < 0){
                    mode = DEAD;
                    start_time = ofGetElapsedTimeMillis();
                }
            break;
            
        case DEAD:
            if( ofGetElapsedTimeMillis() - start_time > change_duration*4)
            {
                bDead = true;
            }
            break;
            
        default:
            break;
    }
    
}

void Boss::draw()
{
    // 色設定
    // scale=1.0で初期値, scale=2.0で赤?
    if (hp>0) {
        mColor.setHsb((2.0-scale)*128, 255, 255);
    }else{
        ofSetColor(255, 0, 0);
    }
    ofSetColor(mColor);
    if (mode != DEAD) {
        ofFill();
//        ofEllipse(mX, mY, mWidth*scale, mHeight*scale);
        mImage.draw(mX - mWidth*scale *0.5, mY-mHeight*scale*0.5, mWidth*scale, mHeight*scale);
    }
    
}

bool Boss::isDead()
{
    return bDead;
}

bool Boss::doExplode()
{
    if (mode == DEAD) {
        return true;
    }else{
        return false;
    }
}

bool Boss::collider(int x, int y){
    float distance = sqrt( (mX-x)*(mX-x) + (mY-y)*(mY-y) );
    if (distance<mWidth*scale/2) {
        if (mode != DAMAGING && mode != SPAWN) {
            start_time = ofGetElapsedTimeMillis();
            hp--;
            mode = DAMAGING;
        }
        if (hp<=0 && mode != DYING) {
            mode = DYING;
            start_time = ofGetElapsedTimeMillis();
        }
        return true;
    }else{
        return false;
    }
}

int Boss::getX(){
    return mX;
}

int Boss::getY(){
    return mY;
}

//int Boss::getSparkSize(){
//    return hibana_size;
//}

int Boss::getSparkNum(){
    return hibana_num;
}

//int Boss::getSparkSpeed(){
//    return hibana_speed;
//}
