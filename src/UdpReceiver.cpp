//
//  UdpReceiver.cpp
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/28.
//
//

#include "UdpReceiver.h"

//--------------------------
UdpReceiver::UdpReceiver()
{
	parameters.setName("Calibration");
	parameters.add(offset.set("offset",ofVec2f(0, 0),ofVec2f(-500, -500),ofVec2f(500, 500)));
	parameters.add(window_size.set("window_size",ofVec2f(1920, 1080),ofVec2f(0, 0),ofVec2f(1920, 1080)));
    
	parameters.add(cursor_size.set("cursor size",20,0,200));
	parameters.add(cursor_width.set("cursor width",2,0,10));
	parameters.add(show_cursor.set("show cursor",true));
}
UdpReceiver::~UdpReceiver(){
    udpConnection.Close();
}

void UdpReceiver::setup(int PORT1)
{
    udpConnection.Create();
    udpConnection.Bind(PORT1);
    udpConnection.SetNonBlocking(true);
    
}

void UdpReceiver::draw(){
    if (show_cursor) {
        for (int i=0; i<NUM_INPUT_CAMERAS; i++) {
            ofEllipse(mPos[i].x * ofGetWidth(), mPos[i].y * ofGetHeight(), 10, 10);
            drawCross(mPos[i]);
        }
    }
}

void UdpReceiver::drawCross(ofPoint pos){
    ofSetColor(255);
    ofSetLineWidth(cursor_width);
    
    ofCircle(0, 0, 20);
    
    int x = pos.x*ofGetWidth();
    int y = pos.y*ofGetHeight();
//    ofLine(x-cursor_size, y, x+cursor_size, y);
//    ofLine(x, y-cursor_size, x, y+cursor_size);
    ofFill();
    ofRect(x-cursor_size/2+cursor_width/2, y, cursor_size, cursor_width);
    ofRect(x, y-cursor_size/2+cursor_width/2, cursor_width, cursor_size);
}

void UdpReceiver::start(){
    startThread(true, false);   // blocking, verbose
}

void UdpReceiver::stop(){
    stopThread();
}

//--------------------------
void UdpReceiver::threadedFunction(){
    
    while( isThreadRunning() != 0 ){
        if( lock() ){
            
            char udpMessage[100];
            udpConnection.Receive(udpMessage,100);
            string message=udpMessage;
            
            if(message!=""){
                float x,y;
                vector<string> strPoints = ofSplitString(message,"[/p]");
                for(unsigned int i=0;i<strPoints.size();i++){
                    vector<string> point = ofSplitString(strPoints[i],"|");
                    if( point.size() == 3 ){
                        x=atof(point[0].c_str());
                        y=atof(point[1].c_str());
                        cout << "ID:" << atoi(point[2].c_str()) << " x:" << x << " y:" << y << endl;
                        mPos[atoi(point[2].c_str())].set(x, y);
                    }
                }
            }
            
            unlock();
            ofSleepMillis(1);
        }
        
    }
}

//--------------------------
void UdpReceiver::getXY(float &_x, float &_y, const int _ID)
{
    _x = mPos[_ID].x * ofGetWidth();
    _y = mPos[_ID].y * ofGetHeight();
}

void UdpReceiver::getXY(ofPoint &_pos, const int _ID){
    _pos.x = mPos[_ID].x * ofGetWidth();
    _pos.y = mPos[_ID].y * ofGetHeight();
}