//
//  GameOver.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/24.
//
//

#pragma once

#include "SceneBase.h"

class GameOver:public SceneBase{
public:
    GameOver();
    ~GameOver();
    void init(ofVec4f targetRect);
    void update();
    void draw();
    
    bool collider(int x, int y);
    bool isEnd();
    
	ofParameterGroup parameters;
private:
    bool bEnd;
    ofRectangle mRect;
    
    ofImage gameOverImage;
    
    unsigned long long start_time;
    
	ofParameter<int> gameover_duration;
};