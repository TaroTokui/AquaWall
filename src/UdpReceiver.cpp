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
    udpConnection1.Close();
    udpConnection2.Close();
}

void UdpReceiver::setup(int PORT1, int PORT2)
{
    udpConnection1.Create();
    udpConnection1.Bind(PORT1);
    udpConnection1.SetNonBlocking(true);
    
    udpConnection2.Create();
    udpConnection2.Bind(PORT2);
    udpConnection2.SetNonBlocking(true);
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
            
            // 8byte受け取る, float をふたつ、4*2=8byte
            // 受け取り用の構造体を作る
            //
            
            char udpMessage[8];
            udpConnection1.Receive(udpMessage,8);// ここに構造体のポインタを渡す
            string message=udpMessage;
            
//            camera_pos *tmpPos = static_cast<camera_pos>(message);
            
            // 4バイトずつもらう
            
            // ofToBinaryでcharをbinaryにする
            string bm[8];
            bm[0] = ofToBinary(udpMessage[0]);
            bm[1] = ofToBinary(udpMessage[1]);
            bm[2] = ofToBinary(udpMessage[2]);
            bm[3] = ofToBinary(udpMessage[3]);
            bm[4] = ofToBinary(udpMessage[4]);
            bm[5] = ofToBinary(udpMessage[5]);
            bm[6] = ofToBinary(udpMessage[6]);
            bm[7] = ofToBinary(udpMessage[7]);
            // binaryになったcharを4byte分たす
            // たされた結果をofBinaryToFloatでfloatに戻す
            float x = ofBinaryToFloat(bm[0] + bm[1] + bm[2] + bm[3]);
            float y = ofBinaryToFloat(bm[4] + bm[5] + bm[6] + bm[7]);
            mPos[0].set(x, y);
//            if(message!=""){
//                float x,y;
//                vector<string> strPoints = ofSplitString(message,"[/p]");
//                for(unsigned int i=0;i<strPoints.size();i++){
//                    vector<string> point = ofSplitString(strPoints[i],"|");
//                    if( point.size() == 2 ){
//                        x=atof(point[0].c_str());
//                        y=atof(point[1].c_str());
//                        mPos[0].set(x, y);
//                    }
//                }
//            }
            
            // ２つ目のコントローラ
            udpConnection2.Receive(udpMessage,8);// ここに構造体のポインタを渡す
            
            // ofToBinaryでcharをbinaryにする
            bm[0] = ofToBinary(udpMessage[0]);
            bm[1] = ofToBinary(udpMessage[1]);
            bm[2] = ofToBinary(udpMessage[2]);
            bm[3] = ofToBinary(udpMessage[3]);
            bm[4] = ofToBinary(udpMessage[4]);
            bm[5] = ofToBinary(udpMessage[5]);
            bm[6] = ofToBinary(udpMessage[6]);
            bm[7] = ofToBinary(udpMessage[7]);
            // binaryになったcharを4byte分たす
            // たされた結果をofBinaryToFloatでfloatに戻す
            x = ofBinaryToFloat(bm[0] + bm[1] + bm[2] + bm[3]);
            y = ofBinaryToFloat(bm[4] + bm[5] + bm[6] + bm[7]);
            mPos[1].set(x, y);
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