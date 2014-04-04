//
//  Title.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/23.
//
//

#pragma once

#include "SceneBase.h"

static const string TITLE_IMAGE_TEXT = "images/01_title_text.png";
static const string TITLE_IMAGE_DUCK = "images/01_title_duck.png";

class Title:public SceneBase{
public:
    Title();
    ~Title();
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
    
    ofImage titleImage, ahiruImage;
    float image_offset;
    
    unsigned long long start_time;
    
	ofParameter<int> title_hue, title_sat;
	ofParameter<float> title_speed;
    
    ofColor mColor;
};