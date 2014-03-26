//
//  Title.cpp
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/23.
//
//

#include "Title.h"

Title::Title(){
    titleImage.loadImage("images/title_image.png");
	parameters.setName("Title");
	parameters.add(title_duration.set("title duration",10,0,20));
}

Title::~Title(){}

void Title::init(ofVec4f targetRect)
{
    mRect.x = targetRect.x;
    mRect.y = targetRect.y;
    mRect.width = targetRect.z;
    mRect.height = targetRect.w;
    bEnd = false;
    
    start_time = ofGetElapsedTimeMillis();
}

void Title::update()
{
    if (ofGetElapsedTimeMillis() - start_time > title_duration * 1000) {
        bEnd = true;
    }
}

void Title::draw()
{
    ofSetColor(255);
    titleImage.draw(mRect);
}

bool Title::collider(int x, int y)
{
    return true;
}

bool Title::isEnd()
{
    return bEnd;
}