//
//  SceneBase.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/23.
//
//

#pragma once

#include "ofMain.h"

enum My_sequence{ CONFIG, CALIBRATION, TITLE, START, STAGE1, STAGE2, GAMEOVER };

class SceneBase{
public:
    virtual void init(ofVec4f targetRect) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    
    virtual bool collider(int x, int y) = 0;
    virtual bool isEnd() = 0;
private:
};