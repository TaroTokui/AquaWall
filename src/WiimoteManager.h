//
//  WiimoteManager.h
//  OscGame
//
//  Created by Taro Tokui on 2013/11/26.
//
//

#ifndef __OscGame__WiimoteManager__
#define __OscGame__WiimoteManager__

#include <iostream>

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 9000

class wiimoteManager : public ofThread{
    
public:
    
    //--------------------------
    wiimoteManager();
    
    void start();
    void stop();
    
    //--------------------------
    void threadedFunction();
    
    //--------------------------
    void getXY(float &_x, float &_y);
    void getXY(float &_x, float &_y, const int _ID);
    string getButton(int _ID);
    int getID();
    
    //--------------------------
    void setHomography();   // 0~1.0に正規化して渡す
    
private:
    ofxOscReceiver receiver;
    float wiiX, wiiY;
    ofVec2f wiiPos[2];
    int wiiID;
    queue<string> button[2];
    vector<string> words;
    
    vector<string> split(const string &str, char delim);
};

#endif /* defined(__OscGame__WiimoteManager__) */
