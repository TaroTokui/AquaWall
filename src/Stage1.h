//
//  Stage1.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/23.
//
//

#pragma once

#include "SceneBase.h"
#include "EnemyGroup.h"

class Stage1:public SceneBase{
public:
    Stage1();
    ~Stage1();
    void init(ofVec4f targetRect);
    void update();
    void draw();
    
    bool collider(int x, int y);
    bool isEnd();
    
    ofParameterGroup parameters;
private:
    EnemyGroup enemies;
    bool bEnd;
};