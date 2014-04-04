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
    
    parameters.setName("Hibana");
    parameters.add(hibana_num.set( "hibana num", 10, 1, 50 ));
    parameters.add(hibana_size.set( "hibana size", 10, 1, 100 ));
    parameters.add(hibana_speed.set( "hibana speed", 5.0, 0.0, 50.0 ));
}

Hibana::~Hibana(){
}

void Hibana::add(int x, int y){
    add(x, y, hibana_num);
}

void Hibana::add(int x, int y, int n){
    
    Particle newParticle;
    for (int i=0; i<n; i++) {
        newParticle.setup(x, y, hibana_speed);
        particles.push_back(newParticle);
    }
    
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
        mImage.draw(itp->getPosition(), hibana_size, hibana_size);
        itp++;
    }
}
