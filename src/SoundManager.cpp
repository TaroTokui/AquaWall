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
//	sounds[0].loadSound("sounds/akira/1.mp3");
//	sounds[1].loadSound("sounds/akira/2.mp3");
//	sounds[2].loadSound("sounds/akira/3.mp3");
//	sounds[3].loadSound("sounds/akira/kotti.mp3");
//	sounds[4].loadSound("sounds/akira/satueishimasu.mp3");
//	sounds[5].loadSound("sounds/akira/kotti.mp3");
//    
//    cout << "souds are loaded" << endl;
//    
//	sounds[0].setVolume(0.75f);
}

void SoundManager::update(){
	// update the sound playing system:
	ofSoundUpdate();
}

void SoundManager::play(int index){
//    sounds[index].play();
    cout << "played" << endl;
}

void SoundManager::stop(){}

void SoundManager::isStop(){}

void SoundManager::add(string path, int index){
    ofSoundPlayer tmpSound;
    tmpSound.loadSound(path);
}