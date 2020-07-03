/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __SPINNER_SCENE_H__
#define __SPINNER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include <time.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
USING_NS_CC;
using namespace cocos2d::ui;

class SpinnerScene : public Scene
{
public:
    static Scene *createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(SpinnerScene);

private:
    cocos2d::Sprite *sectors;
    cocos2d::Sprite *arrow;
    cocos2d::Sprite *border;
    cocos2d::Sprite *sprite_1;
    cocos2d::Sprite *sprite_2;
    cocos2d::Sprite *sprite_3;
    cocos2d::Sprite *sprite_4;
    cocos2d::Sprite *sprite_5;
    cocos2d::Sprite *sprite_6;
    cocos2d::Sprite *sprite_7;
    cocos2d::Sprite *sprite_8;
    cocos2d::Sprite *rewards[8];
    void touchEvent(Ref *sender, Widget::TouchEventType type);
    void addLabelWithQuantity(Sprite* sprite, string label_text);
    void runSpinTest();
    float getGoalAngle();
    int lastReward = 0;
};

#endif // __SPINNER_SCENE_H__
