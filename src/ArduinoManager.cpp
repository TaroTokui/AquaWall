//
//  ArduinoManager.cpp
//  Laval2014_02
//
//  Created by Taro Tokui on 2014/01/26.
//
//

#include "ArduinoManager.h"

//--------------------------
ArduinoManager::ArduinoManager(){}
ArduinoManager::~ArduinoManager(){}

void ArduinoManager::setup()
{
    // arduinoの初期化
	ard.connect("/dev/tty.usbmodem1421", 57600);
	ofAddListener(ard.EInitialized, this, &ArduinoManager::setupArduino);
	bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
    enable[0] = false;
    enable[1] = false;
    shot_start_flag[0] = false;
    shot_start_flag[1] = false;
    pin_out[0] = GUN_OUTPUT_1;
    pin_out[1] = GUN_OUTPUT_2;
    pin_in[0] = GUN_INPUT_1;
    pin_in[1] = GUN_INPUT_2;
}

void ArduinoManager::update()
{
	updateArduino();
    
    // 空気砲
    for (int i=0; i<NUM_CONTROLLER; i++)
    {
        if (shot_flag[i])
        {
            if( ofGetElapsedTimeMillis() - shot_start_time[i] > SHOT_DURATION )
            {
                ard.sendDigital(pin_out[i], ARD_LOW);
                shot_flag[i] = false;
            }
        }
    }
    
    // なにか
    if (shot_flag3)
    {
        if( ofGetElapsedTimeMillis() - start_time_boss > SHOT_DURATION )
        {
            ard.sendDigital(SHOT_3, ARD_LOW);
            shot_flag3 = false;
        }
    }
}

//--------------------------
void ArduinoManager::shot_start(int ID)
{
    
    shot_start_time[ID] = ofGetElapsedTimeMillis();
    ard.sendDigital(pin_out[ID], ARD_HIGH);
    shot_flag[ID] = true;
    shot_start_flag[ID] = true;
    
//    if (ID == 0) {
//        start_time_shot1 = ofGetElapsedTimeMillis();
//        ard.sendDigital(GUN_OUTPUT_1, ARD_HIGH);
//        shot_flag1 = true;
//        shot_start_flag[ID] = true;
//    }else if(ID==1){
//        start_time_shot2 = ofGetElapsedTimeMillis();
//        ard.sendDigital(GUN_OUTPUT_2, ARD_HIGH);
//        shot_flag2 = true;
//        shot_start_flag[ID] = true;
//    }
}

//--------------------------
void ArduinoManager::boss_start()
{
    start_time_boss = ofGetElapsedTimeMillis();
    ard.sendDigital(SHOT_3, ARD_HIGH);
    shot_flag3 = true;
}

void ArduinoManager::setState(bool flag, int ID){
    enable[ID] = flag;
}

bool ArduinoManager::getState(int ID){
    bool tmpFlag = shot_start_flag[ID];
    shot_start_flag[ID] = false;
    return tmpFlag;
}

void ArduinoManager::setupArduino(const int & version){
	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &ArduinoManager::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    // If using Arduino 0022 or older, then use 16 - 21.
    // Firmata pin numbering changed in version 2.3 (which is included in Arduino 1.0)
    
    // set pins D2 and A5 to digital input
    ard.sendDigitalPinMode(GUN_INPUT_1, ARD_INPUT);
    ard.sendDigitalPinMode(GUN_INPUT_2, ARD_INPUT);
    
    // set pin A0 to analog input
//    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    
    // set pin D13 as digital output
	ard.sendDigitalPinMode(GUN_OUTPUT_1, ARD_OUTPUT);
    // set pin A4 as digital output
    ard.sendDigitalPinMode(GUN_OUTPUT_2, ARD_OUTPUT);
    
    // set pin D11 as PWM (analog output)
//	ard.sendDigitalPinMode(11, ARD_PWM);
    
    // attach a servo to pin D9
    // servo motors can only be attached to pin D3, D5, D6, D9, D10, or D11
//    ard.sendServoAttach(9);
	
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &ArduinoManager::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &ArduinoManager::analogPinChanged);
}

void ArduinoManager::digitalPinChanged(const int & pinNum){
    // do something with the digital input. here we're simply going to print the pin number and
    // value to the screen each time it changes
//    buttonState = "digital pin: " + ofToString(pinNum) + " = " + ofToString(ard.getDigital(pinNum));
    
    cout << "----------" << endl;
    cout << pinNum << ": " << ard.getDigital(pinNum) << endl;
    
#if DEMO_MODE
    for (int i=0; i<NUM_CONTROLLER; i++)
    {
        if ( pinNum == pin_in[i] && ard.getDigital(pin_in[i])) {
            shot_start(i);
            cout << i << endl;
        }
    }
#else
    for (int i=0; i<NUM_CONTROLLER; i++)
    {
        if (ard.getDigital(pin_in[i]) && enable[i] ) {
            shot_start(i);
        }
    }
#endif
    
//    if ( pinNum == GUN_INPUT_1 && ard.getDigital(GUN_INPUT_1) && enable[0]) {
//        shot_start(0);
//    }
//    if ( pinNum == GUN_INPUT_2 && ard.getDigital(GUN_INPUT_2) && enable[1]) {
//        shot_start(1);
//    }
    
    
}

void ArduinoManager::analogPinChanged(const int & pinNum){
    // do something with the analog input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    potValue = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum));
}

void ArduinoManager::updateArduino(){
    
	// update the arduino, get any data or messages.
    // the call to ard.update() is required
	ard.update();
	
	// do not send anything until the arduino has been set up
	if (bSetupArduino) {
        // fade the led connected to pin D11
		ard.sendPwm(11, (int)(128 + 128 * sin(ofGetElapsedTimef())));   // pwm...
	}
    
}

