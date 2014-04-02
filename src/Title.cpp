//
//  Title.cpp
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/23.
//
//

#include "Title.h"

Title::Title():image_offset(0){
    titleImage.loadImage(TITLE_IMAGE_TEXT);
    // ここであひる画像の読み込み
	parameters.setName("Title");
	parameters.add(title_speed.set("title speed",0.0,0.0,20.0));
	parameters.add(title_hue.set("title hue",0,0,255));
	parameters.add(title_sat.set("title sat",255,0,255));
    mColor.set(255);
}

Title::~Title(){}

void Title::init(ofVec4f targetRect)
{
    mRect.x = targetRect.x;
    mRect.y = targetRect.y;
    mRect.width = targetRect.z;
    mRect.height = targetRect.w;
    bEnd = false;
    image_offset = 0;
    
//    start_time = ofGetElapsedTimeMillis();
}

void Title::update()
{
//    if (ofGetElapsedTimeMillis() - start_time > title_duration * 1000) {
//        bEnd = true;
//    }
#if 0
    image_offset += title_speed;
    if (image_offset>ofGetWidth()) {
        image_offset = 0;
    }
#else
    image_offset -= title_speed;
    if (image_offset<0) {
        image_offset = ofGetWidth();
    }
#endif
    mColor.setHsb(title_hue, title_sat, 255);
}

void Title::draw()
{
    ofRectangle tmpRect = mRect;
    ofSetColor(mColor);
    
    // 一枚目の画像
    tmpRect.x += image_offset;
    titleImage.draw(tmpRect);
    tmpRect.x -= ofGetWidth();
    titleImage.draw(tmpRect);
}

bool Title::collider(int x, int y)
{
    return true;
}

bool Title::isEnd()
{
    return bEnd;
}

void Title::end()
{
    bEnd = true;
}