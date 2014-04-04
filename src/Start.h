//
//  Start.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/04/03.
//
//  3秒間「START」を表示する
//  「START」をじんわり消す
//  消えたら電磁バルブを5秒間ON(アヒルのエアシリンダが動き出す)
//  アヒルが登場してから1秒後に「助けて、ウィルスがやって来た！」と表示する
//  同時に音声を再生する(約4秒)
//  電磁バルブをOFFにする
//  アヒルが引っ込んで3秒したらシーン終了
//

#pragma once

#include "SceneBase.h"

static const string START_IMAGE_TEXT = "images/02_start_text.png";
static const string START_IMAGE_VIRUS = "images/02_start_virus.png";

enum start_sequence{ START_START, START_AHIRU_IN, START_AHIRU_MESSAGE, START_END };

class CStart:public SceneBase{
public:
    CStart();
    ~CStart();
    void init(ofVec4f targetRect);
    void update();
    void draw();
    
    bool collider(int x, int y);
    bool isEnd();
    bool enableAhiru();
    void startAhiru();
    
	ofParameterGroup parameters;
private:
    bool bEnd;
    ofRectangle mRect;
    
    ofImage startImage, virusImage;
    
    unsigned long long start_time;
    
	ofParameter<float> start_duration, ahiru_duration, virus_duration, end_duration;
	ofParameter<int> text_hue;
    
    start_sequence sq;
    bool bAhiru;
    
    ofColor mColor;
};