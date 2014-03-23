//
//  Stage2.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/23.
//
//

#pragma once

#include "SceneBase.h"
#include "Boss.h"

class Stage2:public SceneBase{
public:
    Stage2();
    ~Stage2();
    void init(ofVec4f targetRect);
    void update();
    void draw();
    
    bool collider(int x, int y);
    bool isEnd();
    bool isExplode();
    
    int getHibanaAmount();
    
    ofParameterGroup parameters;
private:
    Boss boss;
    bool bEnd;
    bool bExplode;
};