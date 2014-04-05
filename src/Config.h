//
//  Config.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/04/05.
//
//

#pragma once

#include "SceneBase.h"

static const string CONFIG_IMAGE_TEXT = "images/04_config_text.png";

class CConfig:public SceneBase{
public:
    CConfig();
    ~CConfig();
    void init(ofVec4f targetRect);
    void update();
    void draw();
    
    bool collider(int x, int y);
    bool isEnd();
    void end();
    
	ofParameterGroup parameters;
private:
    bool bEnd;
    ofRectangle mRect;
    
    ofImage configImage;
    float image_offset;
    
    unsigned long long start_time;
    
	ofParameter<int> title_hue, title_sat;
	ofParameter<float> title_speed;
    
    ofColor mColor;
};