//
//  Config.cpp
//  AquaWall
//
//  Created by Taro Tokui on 2014/04/05.
//
//

#include "Config.h"

CConfig::CConfig():image_offset(0){
    configImage.loadImage(CONFIG_IMAGE_TEXT);
	parameters.setName("Config");
	parameters.add(title_speed.set("config speed",0.0,0.0,20.0));
	parameters.add(title_hue.set("config hue",0,0,255));
	parameters.add(title_sat.set("config sat",255,0,255));
    mColor.set(255);
}

CConfig::~CConfig(){}

void CConfig::init(ofVec4f targetRect)
{
    mRect.x = targetRect.x;
    mRect.y = targetRect.y;
    mRect.width = targetRect.z;
    mRect.height = targetRect.w;
    bEnd = false;
    image_offset = 0;
    
}

void CConfig::update()
{
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

void CConfig::draw()
{
    ofRectangle tmpRect = mRect;
    
    // 一枚目の画像
    ofSetColor(mColor);
    tmpRect.x += image_offset;
    configImage.draw(tmpRect);
    tmpRect.x -= ofGetWidth();
    configImage.draw(tmpRect);
}

bool CConfig::collider(int x, int y)
{
    return true;
}

bool CConfig::isEnd()
{
    return bEnd;
}

void CConfig::end()
{
    bEnd = true;
}