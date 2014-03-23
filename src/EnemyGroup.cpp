//
//  EnemyGroup.cpp
//  Laval2014_02
//
//  Created by Taro Tokui on 2014/01/26.
//
//

#include "EnemyGroup.h"

EnemyGroup::EnemyGroup(){
    mImage.loadImage("images/virus.png");
    
	parameters.setName("Enemy status");
    parameters.add(kurage_hp.set( "kurage hp", 5, 0, 10 ));
    parameters.add(kurage_num.set( "kurage num", 5, 0, 20 ));
    parameters.add(kurage_size.set( "kurage size", 100, 10, 500 ));
    
    shader.load("shaders/sprite");
    
    plane.set(mImage.getWidth(), mImage.getHeight(), 2, 2, OF_PRIMITIVE_TRIANGLES);
    // setup
    plane.mapTexCoordsFromTexture(mImage.getTextureReference());
}

EnemyGroup::~EnemyGroup(){}

void EnemyGroup::setup(){
}

void EnemyGroup::update(){
    
    ite = kurage.begin();
    
    while (ite != kurage.end())
    {
        ite->update();
        if ( ite->isDead() ) {
            ite = kurage.erase(ite);
        }else{
            ite++;
        }
    }
    
}

void EnemyGroup::draw()
{
    
    // bind our texture. in our shader this will now be tex0 by default
    // so we can just go ahead and access it there.
    mImage.getTextureReference().bind();
    
    // start our shader, in our OpenGL3 shader this will automagically set
    // up a lot of matrices that we want for figuring out the texture matrix
    // and the modelView matrix
    shader.begin();
    
    ite = kurage.begin();
    
    while (ite != kurage.end())
    {
//        ofSetColor(ite->getColor());
//        mImage.draw( ite->getPosition() );
        ofColor tmpColor = ite->getColor();
        shader.setUniform1f("red", (float)tmpColor.r / 255.0 );
        shader.setUniform1f("green", (float)tmpColor.g / 255.0);
        shader.setUniform1f("blue", (float)tmpColor.b / 255.0);
        shader.setUniform1f("alpha", (float)tmpColor.a / 255.0);
        
        ofPushMatrix();
        ofTranslate( (ite->getPosition()).getX(), (ite->getPosition()).getY() );
        ofScale((ite->getPosition()).getWidth(), (ite->getPosition()).getHeight());
        plane.draw();
        ofPopMatrix();
        
        ite++;
    }
    
    shader.end();
    mImage.getTextureReference().unbind();
    
}

void EnemyGroup::add(int x, int y, int w, int h){
    plane.setWidth(kurage_size);
    plane.setHeight(kurage_size);
    for (int i=0; i<kurage_num; i++) {
        Enemy newEnemy;
        newEnemy.setup(ofRectangle(x, y, w, h), kurage_hp, kurage_size);
        kurage.push_back(newEnemy);
    }
}

void EnemyGroup::add(ofVec4f targetRect){
    add(targetRect.x, targetRect.y, targetRect.z, targetRect.w);
}

void EnemyGroup::clear(){
    kurage.clear();
}

bool EnemyGroup::isEmpty(){
    if( kurage.size() == 0 ){
        return true;
    }
    return false;
}

bool EnemyGroup::collider(int x, int y){
    ite = kurage.begin();
    while (ite != kurage.end())
    {
        if( ite->collider(x,y) ) return true;
        ite++;
    }
    return false;
}