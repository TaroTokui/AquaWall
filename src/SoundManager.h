//
//  SoundManager.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/27.
//
//

#pragma once

#include "ofMain.h"

static const int NUM_SOUNDS = 4;    // 使用する音声の数

class SoundManager{
public:
    SoundManager();
    ~SoundManager();
    void setup();
    void update();
    
    void play(int index);
    void stop();
    void isStop();
    
    void add(string path, int index);
    
private:
    ofSoundPlayer sounds[NUM_SOUNDS];
    
    bool isCounting;
    
//    vector<ofSoundPlayer> sounds;
};