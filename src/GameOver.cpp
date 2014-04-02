//
//  GameOver.cpp
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/24.
//
//

#include "GameOver.h"

GameOver::GameOver(){
    gameOverImage.loadImage("images/gameover.png");
	parameters.setName("GameOver");
	parameters.add(gameover_duration.set("gameover duration",10,0,20));
}

GameOver::~GameOver(){}

void GameOver::init(ofVec4f targetRect)
{
    mRect.x = targetRect.x;
    mRect.y = targetRect.y;
    mRect.width = targetRect.z;
    mRect.height = targetRect.w;
    bEnd = false;
    
    start_time = ofGetElapsedTimeMillis();
}

void GameOver::update()
{
    if (ofGetElapsedTimeMillis() - start_time > gameover_duration * 1000) {
        bEnd = true;
    }
}

void GameOver::draw()
{
    ofSetColor(255);
    gameOverImage.draw(mRect);
}

bool GameOver::collider(int x, int y)
{
    return true;
}

bool GameOver::isEnd()
{
    return bEnd;
}