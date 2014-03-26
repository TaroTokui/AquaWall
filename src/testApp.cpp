#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    wiiInput.start();
    for (int i=0; i<NUM_WII; i++) {
        wiiPos[i].x = 0;
        wiiPos[i].y = 0;
    }
    
#if ENABLE_ARDUINO
    ardOutput.setup();
#endif
    
    // gui
	parameters.setName("settings");
    parameters.add(target_window.set( "target window", ofVec4f(ofGetWidth()/4, ofGetHeight()/4, ofGetWidth()/2, ofGetHeight()/2), ofVec4f(0, 0, 0, 0), ofVec4f(ofGetWidth()/4, ofGetHeight()/2, 1920, 1080) ));
    parameters.add(hibana_num.set( "hibana num", 10, 1, 50 ));
    parameters.add(hibana_size.set( "hibana size", 10, 1, 100 ));
    parameters.add(hibana_speed.set( "hibana speed", 5.0, 0.0, 20.0 ));
    
    parameters.add(stage1.parameters);
    parameters.add(stage2.parameters);
    parameters.add(game_title.parameters);
    parameters.add(gameover.parameters);
    
    gui.setup(parameters);
    
    gui.loadFromFile("settings.xml");
    
    bShowGui = true;
    
    scene = TITLE;
    game_title.init(target_window);

    current_scene = &game_title;
}

//--------------------------------------------------------------
void testApp::update(){
    
    // input
    for (int i=0; i<NUM_WII; i++) {
        wiiInput.getXY(wiiPos[i].x, wiiPos[i].y, i);
        
        wiiPos[i].y -= 0.2;
        
        string tmpMessage = wiiInput.getButton(i);
        
#if ENABLE_ARDUINO
        if(inTheScreen(wiiPos[i].x*ofGetWidth(), wiiPos[i].y*ofGetHeight()))
        {
            ardOutput.setState(true, i);
//            cout << "ID: "<< i << " on " << wiiPos[i].x << " " << wiiPos[i].y << endl;
        }else{
            ardOutput.setState(false, i);
        }
        
        // arduinoでonかoffかを受け取る
        if (ardOutput.getState(i)) {
            collider(wiiPos[i].x*ofGetWidth(), wiiPos[i].y*ofGetHeight());
        }
#endif
    }
    
#if ENABLE_ARDUINO
    ardOutput.update();
#endif
    
    current_scene->update();
    if( current_scene->isEnd() )
    {
        toggleScene();
    }
    
    if (scene == STAGE2) {
        if (stage2.isExplode())
        {
            hibana.setup(target_window->x + target_window->z/2, target_window->y + target_window->w/2, hibana_size, stage2.getHibanaAmount(), hibana_speed);
        }
    }
    
    hibana.update();
    hamon.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    
    current_scene->draw();
    
    hibana.draw();
    hamon.draw();
    
	if( bShowGui )
    {
        ofNoFill();
        ofSetColor(255);
        ofRect(target_window->x, target_window->y, target_window->z, target_window->w);
        
		gui.draw();
	}
    
#if SHOW_WIIMOTE
    for (int i=0; i<NUM_WII; i++)
    {
        ofFill();
        ofSetColor(255);
        ofEllipse(wiiPos[i].x*ofGetWidth(), wiiPos[i].y*ofGetHeight(), 50, 50);
    }
#endif
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
	if (key == 'c'){
        CGDisplayHideCursor(NULL);
    }
    if (key == 'C'){
        CGDisplayShowCursor(NULL);
    }
    
	if(key == 'f') {
        ofToggleFullscreen();
    }
    
	if(key == 'g') {
        bShowGui = !bShowGui;
    }
    
	if(key == 'r') {
		hamon.setup(mouseX, mouseY, 10.0);
	}
    
	if(key == 's') {
		gui.saveToFile("settings.xml");
	}
	if(key == 'l') {
		gui.loadFromFile("settings.xml");
	}
	if(key == 't') {
		toggleScene(true);
	}
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    collider(x, y); // デバッグ用
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void testApp::toggleScene(bool bIncrement){
    if (scene==GAMEOVER) {
        if (bIncrement) {
            scene = CONFIG;
        }else{
            scene = TITLE;
        }
    }else{
        scene = static_cast<My_sequence>(scene + 1);
    }
    
    // シーンの変更
    switch (scene) {
        case CONFIG:
            break;
            
        case CALIBRATION:
            current_scene = &calibration;
            break;
            
        case TITLE:
            current_scene = &game_title;
            break;
            
        case STAGE1:
            current_scene = &stage1;
            break;
            
        case STAGE2:
            current_scene = &stage2;
            break;
            
        case GAMEOVER:
            current_scene = &gameover;
            break;
            
        default:
            break;
    }
    
    // シーンの初期化
    current_scene->init(target_window);
    
}

//--------------------------------------------------------------
bool testApp::collider(int x, int y){
    
    bool isHit = false;
    
    // 枠内にあるか
    if (inTheScreen(x,y))
    {
        // 当たり判定
        if( current_scene->collider(x, y) ){
            hibana.setup(x, y, hibana_size, hibana_num, hibana_speed);
            isHit = true;
        }
        
        if (!isHit) {
            hamon.setup(x, y, 10.0);
        }
        
        return true;
    }else{
        return false;
    }
    
}

//--------------------------------------------------------------
bool testApp::inTheScreen(int x, int y){
    
    // 枠内にあるか
    if (target_window->x < x && x < target_window->x + target_window->z &&
        target_window->y < y && y < target_window->y + target_window->w)
    {
        return true;
    }else{
        return false;
    }
    
}
