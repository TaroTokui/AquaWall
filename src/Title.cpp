//
//  Title.cpp
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/23.
//
//

#include "Title.h"

Title::Title():image_offset(0){
    titleImage.loadImage("images/01_title.png");
	parameters.setName("Title");
//	parameters.add(title_duration.set("title duration",10,0,20));
	parameters.add(title_speed.set("title speed",0.0,0.0,20.0));
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
}

void Title::draw()
{
    ofRectangle tmpRect = mRect;
    ofSetColor(255);
    
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