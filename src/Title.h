//
//  Title.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/23.
//
//

#pragma once

#include "ofxGui.h"
#include "SceneBase.h"

static const string TITLE_IMAGE = "images/01_title.png";

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
    
//	ofParameter<int> title_duration;
	ofParameter<float> title_speed;
};