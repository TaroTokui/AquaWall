//
//  Hamon.h
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/17.
//
//

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
	ofParameter<int> size, max_hp, hibana_num, change_duration;
    ofParameter<float> hamon_speed;
};
