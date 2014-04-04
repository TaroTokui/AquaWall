//
//  Hamon.h
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/17.
//
//
// gui で半径、色、スピードを変えられるようにする
// 色が負の時はランダムな色になる

#pragma once

#include "ofMain.h"
#include "Ring.h"

class Hamon{
    
public:
    Hamon();
    ~Hamon();
    void setup(int x, int y, int n);
    void update();
    void draw();
    
	ofParameterGroup parameters;
private:
    vector<Ring> rings;
    vector<Ring>::iterator it;
    
    ofImage mImage;
    
    ofShader shader;
    ofPlanePrimitive plane;
    
    // GUI
	ofParameter<int> hamon_color;
    ofParameter<float> hamon_alpha, hamon_speed;
};
