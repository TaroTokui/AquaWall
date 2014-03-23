//
//  Stage2.cpp
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/23.
//
//

#include "Stage2.h"

Stage2::Stage2()
{
	parameters.setName("stage 2");
    parameters.add(boss.parameters);
}

Stage2::~Stage2(){}

void Stage2::init(ofVec4f targetRect)
{
    
    boss.setup(targetRect.x+targetRect.z/2, targetRect.y+targetRect.w/2);
    bEnd = false;
    bExplode = false;
}

void Stage2::update()
{
    boss.update();
    if (boss.isDead())
    {
        bEnd = true;
    }
    
    if (boss.doExplode())
    {
        // DYINGだったらhibana発生
        bExplode = true;
    }

}

void Stage2::draw()
{
    boss.draw();
}

bool Stage2::collider(int x, int y)
{
    if( boss.collider(x, y) )
    {
        return true;
    }else{
        return false;
    }
}

bool Stage2::isEnd()
{
    return bEnd;
}

bool Stage2::isExplode()
{
    return bExplode;
}

int Stage2::getHibanaAmount(){
    return boss.getSparkNum();
}