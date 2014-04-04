//
//  UdpReceiver.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/28.
//
//

#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

static const int NUM_INPUT_CAMERAS = 2;

struct camera_pos {
    float x;
    float y;
};


class UdpReceiver : public ofThread{
public:
    UdpReceiver();
    ~UdpReceiver();
    
    void setup(int PORT1, int PORT2);
    void draw();    // デバッグ用
    
    void start();
    void stop();
    
    //--------------------------
    void threadedFunction();
    
    //--------------------------
    void getXY(float &_x, float &_y, const int _ID=0);
    void getXY(ofPoint &_pos, const int _ID=0);
    
    ofParameterGroup parameters;
private:
    void drawCross(ofPoint pos);
    
    ofxUDPManager udpConnection1, udpConnection2;
    
    ofPoint mPos[NUM_INPUT_CAMERAS];
    
	ofParameter<ofVec2f> offset, window_size;
    
	ofParameter<int> cursor_size;
	ofParameter<float> cursor_width;
	ofParameter<bool> show_cursor;
    
};