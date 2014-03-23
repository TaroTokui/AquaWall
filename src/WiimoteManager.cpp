//
//  WiimoteManager.cpp
//  OscGame
//
//  Created by Taro Tokui on 2013/11/26.
//
//

#include "WiimoteManager.h"

//--------------------------
wiimoteManager::wiimoteManager():wiiX(0),wiiY(0){
    // listen on the given port
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup( PORT );
}

void wiimoteManager::start(){
    startThread(true, false);   // blocking, verbose
}

void wiimoteManager::stop(){
    stopThread();
}

//--------------------------
void wiimoteManager::threadedFunction(){
    
    while( isThreadRunning() != 0 ){
        if( lock() ){
            
            while( receiver.hasWaitingMessages() )
            {
                ofxOscMessage m;
                receiver.getNextMessage( &m );
                
                string tmpAddress = m.getAddress();
                // addressからwiimoteの番号を抜き出す
                words.clear();
                words = split(tmpAddress, '/');
                
                if (words.size() == 5)
                {
                    wiiID = ofToInt(words[2]);
                    
                    if ( tmpAddress == "/wii/1/ir/0" )
                    {
                        wiiPos[0].x = m.getArgAsFloat( 0 );
                    }
                    
                    else if ( tmpAddress == "/wii/1/ir/1" )
                    {
                        wiiPos[0].y = 1.0 - m.getArgAsFloat( 0 );
                    }
                    
                    else if ( tmpAddress == "/wii/1/button/1" )
                    {
                        button[0].push("one");
                    }
                    
                    else if ( tmpAddress == "/wii/2/ir/0" )
                    {
                        wiiPos[1].x = m.getArgAsFloat( 0 );
                    }
                    
                    else if ( tmpAddress == "/wii/2/ir/1" )
                    {
                        wiiPos[1].y = 1.0 - m.getArgAsFloat( 0 );
                    }
                    
                    else if ( tmpAddress == "/wii/2/button/1" )
                    {
                        button[1].push("two");
                    }
                }
            }
            
            unlock();
        }
        
    }
}

//--------------------------
void wiimoteManager::getXY(float &_x, float &_y){
    _x = wiiX;
    _y = wiiY;
}

//--------------------------
void wiimoteManager::getXY(float &_x, float &_y, const int _ID){
    _x = wiiPos[_ID].x;
    _y = wiiPos[_ID].y;
}

//--------------------------
string wiimoteManager::getButton(int _ID){
    string btn;
    if( lock() ){
        if (!button[_ID].empty()) {
            btn = button[_ID].front();
            button[_ID].pop();
        }
        unlock();
    }
    return btn;
}

//--------------------------
int wiimoteManager::getID(){
    return wiiID;
}

vector<string> wiimoteManager::split(const string &str, char delim){
    vector<string> res;
    size_t current = 0, found;
    while((found = str.find_first_of(delim, current)) != string::npos){
        res.push_back(string(str, current, found - current));
        current = found + 1;
    }
    res.push_back(string(str, current, str.size() - current));
    return res;
}
