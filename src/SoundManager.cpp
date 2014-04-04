//
//  SoundManager.cpp
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/27.
//
//

#include "SoundManager.h"

SoundManager::SoundManager(){}

SoundManager::~SoundManager(){}

void SoundManager::setup(){
	sounds[0].loadSound("sounds/collision.mp3");
	sounds[1].loadSound("sounds/shot.mp3");
	sounds[2].loadSound("sounds/help.mp3");
	sounds[3].loadSound("sounds/thanks.mp3");
    
    // 効果音は有限個しか読み込まないのでvector型では管理しない。2014/04/05
    // vectorに突っ込むと全部最後の音になってしまうので、結局ただの配列にした
//    ofSoundPlayer tmpSound;
//    tmpSound.loadSound("sounds/collision.mp3");
//    sounds.push_back(tmpSound);
//    tmpSound.loadSound("sounds/shot.mp3");
//    sounds.push_back(tmpSound);
 
}

void SoundManager::update(){
	// update the sound playing system:
	ofSoundUpdate();
}

void SoundManager::play(int index){
    if (index<NUM_SOUNDS)
    {
        sounds[index].play();
    }
//    if (index < sounds.size())
//    {
//        sounds[0].play();
//    }
    
//    cout << "played" << endl;
}

void SoundManager::stop(){}

void SoundManager::isStop(){}

void SoundManager::add(string path, int index){
    ofSoundPlayer tmpSound;
    tmpSound.loadSound(path);
}