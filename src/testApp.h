#pragma once

#include "ofMain.h"
#include "ofEvents.h"

#include "ofxGui.h"
#include "Hibana.h"
#include "Hamon.h"

//#include "WiimoteManager.h"
#include "ArduinoManager.h"
#include "SoundManager.h"
#include "UdpReceiver.h"

#include "SceneBase.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Title.h"
#include "Start.h"
#include "GameOver.h"
#include "Calibration.h"

#define ENABLE_ARDUINO 0
#define SHOW_WIIMOTE 0

#define IN_PORT_1 11999
#define IN_PORT_2 11998

//static const int NUM_WII = 2;

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // falseのときは余計なシーンは飛ばす
    void toggleScene(bool bIncrement = false);
    
    bool collider(int x, int y);
    bool inTheScreen(int x, int y);
    
    // 入力
//    wiimoteManager wiiInput;
//    ofVec2f wiiPos[NUM_WII];
    UdpReceiver cameraInput;
    ofPoint camPos[NUM_INPUT_CAMERAS];
    
    // 出力(arduino)
    ArduinoManager ardOutput;
    
    // GUI
	ofxPanel gui_general, gui_stage;
	ofParameter<ofVec4f> target_window;
	ofParameter<int> hibana_num;
	ofParameter<int> hibana_size;
	ofParameter<float> hibana_speed;
    
    ofParameterGroup general_params, stage_params;
    
    bool bShowGui;
    
    // シーン
    My_sequence scene;
    SceneBase *current_scene;
    Stage1 stage1;
    Stage2 stage2;
    Title game_title;
    CStart game_start;
    GameOver gameover;
    Calibration calibration;
    
    // エフェクト
    Hibana hibana;
    Hamon hamon;
    
};
