//
//  EnemyGroup.h
//  Laval2014_02
//
//  Created by Taro Tokui on 2014/01/26.
//
//

#pragma once

#include "ofMain.h"
#include "Enemy.h"

class EnemyGroup{
    
public:
    EnemyGroup();
    ~EnemyGroup();
    void setup();
    void update();
    void draw();
    
    void add(int x, int y, int w, int h);
    void add(ofVec4f targetRect);
    void clear();
    bool isEmpty();
    bool collider(int x, int y);
    
	ofParameterGroup parameters;
private:
    
    ofImage mImage;
    
    vector<Enemy> kurage;
    vector<Enemy>::iterator ite;
    
	ofParameter<int> kurage_hp;
	ofParameter<int> kurage_num;
	ofParameter<int> kurage_size;
    
    ofShader shader;
    ofPlanePrimitive plane;
};
