//
//  GameOver.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/24.
//
//
// 0s シーンスタート
// 5s アヒルスイッチon
// 6s merci表示, 音声再生
// 10s merci非表示
// 11s アヒルスイッチoff
//
// アヒルが出てくるまでの時間(5s)
// merciの色
// merciを表示するまでの時間
// merciを表示している時間(4s)
// merciの音声
// アヒルが出ている時間(6s)
// アヒルが引っ込んだらタイトルに戻る

#pragma once

#include "SceneBase.h"

enum end_sequence{ END_START, END_AHIRU_IN, END_AHIRU_MESSAGE, END_END };

static const string END_IMAGE_TEXT = "images/03_thanks_text.png";

class GameOver:public SceneBase{
public:
    GameOver();
    ~GameOver();
    void init(ofVec4f targetRect);
    void update();
    void draw();
    
    bool collider(int x, int y);
    bool isEnd();
    bool enableAhiru();
    void startAhiru();
    bool enableThanks();
    void startThanks();
    
	ofParameterGroup parameters;
private:
    bool bEnd;
    ofRectangle mRect;
    ofColor mColor;
    
    ofImage gameOverImage;
    
    unsigned long long start_time;
    
	ofParameter<int> blank_duration, ahiru_in_duration, merci_duration;
	ofParameter<int> text_hue;

    end_sequence sq;
    
    bool bAhiru;
    bool bThanks;
};