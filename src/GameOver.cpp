//
//  GameOver.cpp
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/24.
//
//

#include "GameOver.h"

GameOver::GameOver()
{
    gameOverImage.loadImage(END_IMAGE_TEXT);

	parameters.setName("GameOver");
	parameters.add(blank_duration.set("blank duration",5,0,10));
    parameters.add(ahiru_in_duration.set("ahiru in duration",1,0,5));
	parameters.add(merci_duration.set("merci duration",4,0,10));
    
	parameters.add(text_hue.set("text hue",0,0,255));
    
    mColor.set(255);
}

GameOver::~GameOver(){}

void GameOver::init(ofVec4f targetRect)
{
    mRect.x = targetRect.x;
    mRect.y = targetRect.y;
    mRect.width = targetRect.z;
    mRect.height = targetRect.w;
    bEnd = false;
    bAhiru = false;
    bThanks = false;
    
    start_time = ofGetElapsedTimeMillis();
    sq = END_START;
}

void GameOver::update()
{
    
    switch (sq) {
        case END_START:
            // なにもしない
            if (ofGetElapsedTimeMillis() - start_time > blank_duration * 1000)
            {
                sq = END_AHIRU_IN;
                start_time = ofGetElapsedTimeMillis();
                bAhiru = true;
            }
            break;
            
        case END_AHIRU_IN:
            if (ofGetElapsedTimeMillis() - start_time > ahiru_in_duration * 1000)
            {
                sq = END_AHIRU_MESSAGE;
                start_time = ofGetElapsedTimeMillis();
                bThanks = true;
            }
            break;
            
        case END_AHIRU_MESSAGE:
            if (ofGetElapsedTimeMillis() - start_time > merci_duration * 1000)
            {
                sq = END_END;
                start_time = ofGetElapsedTimeMillis();
            }
            break;
            
        case END_END:
            if (ofGetElapsedTimeMillis() - start_time > blank_duration * 1000)
            {
                bEnd = true;
            }
            break;
            
        default:
            break;
    }
    
    // 文字の色
    mColor.setHsb(text_hue, 255, 255);
    
}

void GameOver::draw()
{
    ofSetColor(255);
    
    ofSetColor(mColor);
    switch (sq) {
        case END_START:
            break;
            
        case END_AHIRU_IN:
            break;
            
        case END_AHIRU_MESSAGE:
            gameOverImage.draw(mRect);
            break;
            
        case END_END:
            break;
            
        default:
            break;
    }
}

bool GameOver::collider(int x, int y)
{
    return true;
}

bool GameOver::isEnd()
{
    return bEnd;
}

bool GameOver::enableAhiru(){
    return bAhiru;
}

void GameOver::startAhiru(){
    bAhiru = false;
}

bool GameOver::enableThanks(){
    return bThanks;
}

void GameOver::startThanks(){
    bThanks = false;
}