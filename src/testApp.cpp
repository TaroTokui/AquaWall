#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // カメラからUDPで座標を受け取る
    // 複数ポートでデータを受け取る
    cameraInput.setup(IN_PORT_1, IN_PORT_2);
    cameraInput.start();
    for (int i=0; i<NUM_INPUT_CAMERAS; i++) {
        camPos[i].x = 0;
        camPos[i].y = 0;
    }
    
#if ENABLE_ARDUINO
    ardOutput.setup();
#endif
    
    // gui
	general_params.setName("general settings");
    general_params.add(target_window.set( "target window", ofVec4f(ofGetWidth()/4, ofGetHeight()/4, ofGetWidth()/2, ofGetHeight()/2), ofVec4f(0, 0, 0, 0), ofVec4f(ofGetWidth()/4, ofGetHeight()/2, 1920, 1080) ));
    
    general_params.add(hibana.parameters);
    general_params.add(hamon.parameters);
    general_params.add(ardOutput.parameters);
    general_params.add(cameraInput.parameters);
    
    gui_general.setup(general_params);
    gui_general.loadFromFile("general_settings.xml");
    gui_general.setPosition(ofGetWidth()-300, 0);
    
	stage_params.setName("stage settings");
    stage_params.add(game_title.parameters);
    stage_params.add(game_start.parameters);
    stage_params.add(stage1.parameters);
    stage_params.add(stage2.parameters);
    stage_params.add(gameover.parameters);
    
    gui_stage.setup(stage_params);
    gui_stage.loadFromFile("stage_settings.xml");
    
    bShowGui = true;
    
    // soundの初期化
    sounds.setup();
    
    scene = TITLE;
    game_title.init(target_window);

    current_scene = &game_title;
}

//--------------------------------------------------------------
void testApp::update(){
    
    // input
    for (int i=0; i<NUM_INPUT_CAMERAS; i++) {
        cameraInput.getXY(camPos[i], i);
        
#if ENABLE_ARDUINO
        if(inTheScreen(camPos[i].x, camPos[i].y))
        {
            ardOutput.setState(true, i);
        }else{
            ardOutput.setState(false, i);
        }
        
        // arduinoでonかoffかを受け取る
        if (ardOutput.getState(i)) {
            collider(camPos[i].x, camPos[i].y);
        }
#endif
    }
    
    current_scene->update();
    if( current_scene->isEnd() )
    {
        toggleScene();
    }
    
    if (scene == START) {
        if (game_start.enableAhiru())
        {
#if ENABLE_ARDUINO
            ardOutput.ahiru_start();
#endif
            game_start.startAhiru();
        }
    }
    
    if (scene == STAGE2) {
        if (stage2.isExplode())
        {
            hibana.add(target_window->x + target_window->z/2, target_window->y + target_window->w/2, stage2.getHibanaAmount());
        }
    }
    
#if ENABLE_ARDUINO
    ardOutput.update();
#endif
    
    // エフェクトの更新
    hibana.update();
    hamon.update();
    
    // 効果音の更新
    sounds.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    
    current_scene->draw();
    
    hibana.draw();
    hamon.draw();
    cameraInput.draw();
	if( bShowGui )
    {
        ofNoFill();
        ofSetColor(255);
        ofRect(target_window->x, target_window->y, target_window->z, target_window->w);
        
		gui_general.draw();
		gui_stage.draw();
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
    
	if(key == 's' || key == OF_KEY_RETURN) {
        // ゲームスタート
        game_title.end();
	}
    
	if(key == 'S') {
		gui_general.saveToFile("general_settings.xml");
		gui_stage.saveToFile("stage_settings.xml");
	}
    
	if(key == 'L') {
		gui_general.loadFromFile("general_settings.xml");
		gui_stage.loadFromFile("stage_settings.xml");
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
            
        case START:
            current_scene = &game_start;
            break;
            
        case STAGE1:
            current_scene = &stage1;
            break;
            
        case STAGE2:
            current_scene = &stage2;
            break;
            
        case GAMEOVER:
            current_scene = &gameover;
#if ENABLE_ARDUINO
            // アヒルが出てくる
            ardOutput.ahiru_start();
            // ボスの後ろの空気砲を作動させる
            ardOutput.boss_start();
#endif
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
            hibana.add(x, y);
            isHit = true;
            // 火花の効果音を鳴らす
            sounds.play(0);
        }
        
        if (!isHit) {
            hamon.setup(x, y, 10.0);
            // 波紋の効果音を鳴らす
            sounds.play(1);
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
