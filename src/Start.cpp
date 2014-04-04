//
//  Start.cpp
//  AquaWall
//
//  Created by Taro Tokui on 2014/04/03.
//
//

#include "Start.h"

CStart::CStart()
{
    startImage.loadImage(START_IMAGE_TEXT);
    virusImage.loadImage(START_IMAGE_VIRUS);
    
	parameters.setName("Start");
	parameters.add(start_duration.set("start duration",3,0,10));
	parameters.add(ahiru_duration.set("ahiru duration",5,0,10));
	parameters.add(virus_duration.set("virus duration",4,0,10));
	parameters.add(end_duration.set("end duration",3,0,10));
	parameters.add(text_hue.set("text hue",0,0,255));
    
}

CStart::~CStart(){}

void CStart::init(ofVec4f targetRect)
{
    mRect.x = targetRect.x;
    mRect.y = targetRect.y;
    mRect.width = targetRect.z;
    mRect.height = targetRect.w;
    bEnd = false;
    bAhiru = false;
    
    start_time = ofGetElapsedTimeMillis();
    sq = START_START;
}

void CStart::update()
{
    switch (sq) {
        case START_START:
            // startの透明度を上げる
            if (ofGetElapsedTimeMillis() - start_time > start_duration * 1000)
            {
                sq = START_AHIRU_IN;
                start_time = ofGetElapsedTimeMillis();
                bAhiru = true;
            }
            break;
            
        case START_AHIRU_IN:
            if (ofGetElapsedTimeMillis() - start_time > ahiru_duration * 1000)
            {
                sq = START_AHIRU_MESSAGE;
                start_time = ofGetElapsedTimeMillis();
            }
            break;
            
        case START_AHIRU_MESSAGE:
            if (ofGetElapsedTimeMillis() - start_time > virus_duration * 1000)
            {
                sq = START_END;
                start_time = ofGetElapsedTimeMillis();
            }
            break;
            
        case START_END:
            if (ofGetElapsedTimeMillis() - start_time > end_duration * 1000)
            {
                bEnd = true;
            }
            break;
            
        default:
            break;
    }
    
    // 文字の色
    mColor.setHsb(text_hue, 255, 255);
}

void CStart::draw()
{
    ofSetColor(mColor);
    switch (sq) {
        case START_START:
            startImage.draw(mRect);
            break;
            
        case START_AHIRU_IN:
            break;
            
        case START_AHIRU_MESSAGE:
            virusImage.draw(mRect);
            break;
            
        case START_END:
            break;
            
        default:
            break;
    }
}

bool CStart::collider(int x, int y)
{
    return true;
}

bool CStart::isEnd()
{
    return bEnd;
}

bool CStart::enableAhiru(){
    return bAhiru;
}

void CStart::startAhiru(){
    bAhiru = false;
}