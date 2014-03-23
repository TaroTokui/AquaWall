//
//  Title.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/23.
//
//

#pragma once

#include "SceneBase.h"
#include "Enemy.h"

class Title:public SceneBase{
public:
    Title();
    ~Title();
    void init(ofVec4f targetRect);
    void update();
    void draw();
    
    bool collider(int x, int y);
    bool isEnd();
private:
    Enemy button1, button2;
    bool bEnd;
};