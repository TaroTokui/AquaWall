//
//  ArduinoManager.h
//  Laval2014_02
//
//  Created by Taro Tokui on 2014/01/26.
//
//

#pragma once

#include "ofMain.h"
#include "ofEvents.h"

#include <iostream>

#define GUN_INPUT_1 12
#define GUN_INPUT_2 13
#define GUN_OUTPUT_1 10
#define GUN_OUTPUT_2 11

#define SHOT_3 9
#define AHIRU 8

#define DEMO_MODE 1

static const int NUM_CONTROLLER = 2;

class ArduinoManager{
    
public:
    
    //--------------------------
    ArduinoManager();
    ~ArduinoManager();
    
    void setup();
    void update();
    
    //--------------------------
    void shot_start(int ID);
    void boss_start();
    void ahiru_start();
    void setState(bool flag, int ID);
    bool getState(int ID);
    
    ofParameterGroup parameters;
private:
    
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
	void updateArduino();
    
    // 出力(arduino)
	ofArduino	ard;
	bool		bSetupArduino;			// flag variable for setting up arduino once
    string buttonState;
    string potValue;
    
    unsigned long long shot_start_time[NUM_CONTROLLER], start_time_boss, start_time_ahiru;
    bool shot_flag[NUM_CONTROLLER], shot_flag3, ahiru_flag;
    bool enable[NUM_CONTROLLER], shot_start_flag[NUM_CONTROLLER];
    int pin_out[NUM_CONTROLLER];
    int pin_in[NUM_CONTROLLER];
    
	ofParameter<int> shot_duration;
	ofParameter<int> boss_duration;
	ofParameter<int> ahiru_duration;
};
