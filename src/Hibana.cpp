//
//  Hibana.cpp
//  Laval2014_01
//
//  Created by Taro Tokui on 2014/01/17.
//
//

#include "Hibana.h"

Hibana::Hibana(){
    mImage.loadImage("images/star.png");
}

Hibana::~Hibana(){
}

void Hibana::setup(int x, int y, int size, int n, float speed){
    
    Particle newParticle;
    for (int i=0; i<n; i++) {
        newParticle.setup(x, y, speed);
        particles.push_back(newParticle);
    }
    
    mSize = size;
    
}

void Hibana::update(){
    // particle
    vector<Particle>::iterator itp = particles.begin();
    while (itp != particles.end()) {
        itp->update();
        if ( itp->isDead() ) {
            itp = particles.erase(itp);
        }else{
            itp++;
        }
    }
}

void Hibana::draw(){
    // particleの描画
    vector<Particle>::iterator itp = particles.begin();
    while (itp != particles.end()) {
//        itp->draw();
        ofSetColor(itp->getColor());
        mImage.draw(itp->getPosition(), mSize, mSize);
        itp++;
    }
}
