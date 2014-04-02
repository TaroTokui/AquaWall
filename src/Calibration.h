//
//  Calibration.h
//  AquaWall
//
//  Created by Taro Tokui on 2014/03/24.
//
//

#include "SceneBase.h"

class Calibration:public SceneBase{
public:
    Calibration();
    ~Calibration();
    void init(ofVec4f targetRect);
    void update();
    void draw();
    
    bool collider(int x, int y);
    bool isEnd();
private:
    bool bEnd;
    ofVec4f target_window;
    
    ofImage bgImage;
};