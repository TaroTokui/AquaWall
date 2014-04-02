//
//  SoundManager.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/27.
//
//

#pragma once

#include "ofMain.h"

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
//    ofSoundPlayer sounds[6];
    
    bool isCounting;
    
    vector<ofSoundPlayer> sounds;
};