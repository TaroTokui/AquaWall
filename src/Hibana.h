//
//  Hibana.h
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/17.
//
//

#pragma once

#include "ofMain.h"
#include "Particle.h"

class Hibana{
    
public:
    Hibana();
    ~Hibana();
    void add(int x, int y);
    void add(int x, int y, int n);
    void update();
    void draw();
    
	ofParameterGroup parameters;
private:
    vector<Particle> particles;
    ofImage mImage;
    
	ofParameter<int> hibana_num;
	ofParameter<int> hibana_size;
	ofParameter<float> hibana_speed;
};
