//
//  Stage1.cpp
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/23.
//
//

#include "Stage1.h"

Stage1::Stage1()
{
	parameters.setName("stage 1");
    parameters.add(enemies.parameters);
}

Stage1::~Stage1(){}

void Stage1::init(ofVec4f targetRect)
{
    enemies.clear();
    enemies.add(targetRect);
    bEnd = false;
}

void Stage1::update()
{
    enemies.update();
    if( enemies.isEmpty() )
    {
        bEnd = true;
    }
}

void Stage1::draw()
{
    enemies.draw();
}

bool Stage1::collider(int x, int y)
{
    if (enemies.collider(x, y)) {
        return true;
    }else{
        return false;
    }
}

bool Stage1::isEnd()
{
    return bEnd;
}