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
    void setup(int x, int y, int size, int n, float speed = 5.0);
    void update();
    void draw();
    
private:
    vector<Particle> particles;
    ofImage mImage;
    int mSize;
};
