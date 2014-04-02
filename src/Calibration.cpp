//
//  Calibration.cpp
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/24.
//
//

#include "Calibration.h"

Calibration::Calibration(){
    bgImage.loadImage("images/calib_image.png");
}

Calibration::~Calibration(){}

void Calibration::init(ofVec4f targetRect)
{
    target_window = targetRect;
    bEnd = false;
}

void Calibration::update()
{
}

void Calibration::draw()
{
    ofSetColor(255);
    bgImage.draw(target_window.x, target_window.y, target_window.z, target_window.w);
}

bool Calibration::collider(int x, int y)
{
    return true;
}

bool Calibration::isEnd()
{
    return bEnd;
}