//
//  Title.cpp
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/23.
//
//

#include "Title.h"

Title::Title(){}

Title::~Title(){}

void Title::init(ofVec4f targetRect)
{
    button1.setupButton(targetRect.x + targetRect.z/3, targetRect.y + targetRect.w/2, 200, KURAGE);
    button2.setupButton(targetRect.x + targetRect.z*2/3, targetRect.y + targetRect.w/2, 200, VIRUS);
    bEnd = false;
}

void Title::update()
{
    button1.update();
    button2.update();
    if (button1.isDead() || button2.isDead())
    {
        bEnd = true;
    }
}

void Title::draw()
{
    button1.draw();
    button2.draw();
}

bool Title::collider(int x, int y)
{
    if( button1.collider(x, y) || button2.collider(x, y) ){
        return true;
    }else{
        return false;
    }
}

bool Title::isEnd()
{
    return bEnd;
}