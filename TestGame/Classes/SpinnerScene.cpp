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

#include "SpinnerScene.h"

Scene* SpinnerScene::createScene()
{
    return SpinnerScene::create();
}

bool SpinnerScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //TTF config for all labels
    TTFConfig fontConfig;
    fontConfig.fontFilePath = "fonts/arial.ttf";
    fontConfig.fontSize = 20;
    fontConfig.outlineSize = 1;

    // add spinner border sprite
    auto border = Sprite::create("wheel_border.png");
    
    border->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(border, 1);

    // add spinner arrow sprite
    auto arrow = Sprite::create("wheel_arrow.png");
    
    border->addChild(arrow);
    arrow->setScale(1.25);
    arrow->setPosition(Vec2(border->getBoundingBox().size.width/2, border->getBoundingBox().size.height - (arrow->getBoundingBox().size.height/3)));

    //add spinner sectors sprite (the part that will rotate) which is declared in the header file.
    sectors = Sprite::create("wheel_sections_8.png");

    sectors->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sectors,0);

    //add reward sprites with labels to the spinner sectors
    auto hammer_1 = Sprite::create("hammer.png");
    sectors->addChild(hammer_1,1);
    hammer_1->setPosition(Vec2(sectors->getBoundingBox().size.width*0.366, sectors->getBoundingBox().size.height*0.823));
    hammer_1->setRotation(-ANGLE_SECTOR_1);
    auto hammer_1_label = Label::createWithTTF(fontConfig, "x1");
    hammer_1->addChild(hammer_1_label);
    hammer_1_label->setAnchorPoint(Vec2(0.5,1));
    hammer_1_label->setPosition(Vec2(hammer_1->getBoundingBox().size.width*0.4,hammer_1->getBoundingBox().size.height*0.2));

    auto gem_75 = Sprite::create("gem.png");
    sectors->addChild(gem_75, 1);
    gem_75->setPosition(Vec2(sectors->getBoundingBox().size.width*0.177, sectors->getBoundingBox().size.height*0.634));
    gem_75->setRotation(-ANGLE_SECTOR_2);
    auto gem_75_label = Label::createWithTTF(fontConfig, "x75");
    gem_75->addChild(gem_75_label);
    gem_75_label->setAnchorPoint(Vec2(0.5,1));
    gem_75_label->setPosition(Vec2(gem_75->getBoundingBox().size.width*0.4,gem_75->getBoundingBox().size.height*0.2));

    auto brush_1 = Sprite::create("brush.png");
    sectors->addChild(brush_1, 1);
    brush_1->setPosition(Vec2(sectors->getBoundingBox().size.width*0.177, sectors->getBoundingBox().size.height*0.366));
    brush_1->setRotation(-ANGLE_SECTOR_3);
    brush_1->setScale(0.8f);
    auto brush_1_label = Label::createWithTTF(fontConfig, "x1");
    brush_1->addChild(brush_1_label);
    brush_1_label->setAnchorPoint(Vec2(0.5,1));
    brush_1_label->setPosition(Vec2(brush_1->getBoundingBox().size.width*0.4,brush_1->getBoundingBox().size.height*0.2));

    auto coins_750 = Sprite::create("coin.png");
    sectors->addChild(coins_750, 1);
    coins_750->setPosition(Vec2(sectors->getBoundingBox().size.width*0.366, sectors->getBoundingBox().size.height*0.177));
    coins_750->setRotation(-ANGLE_SECTOR_4);
    auto coins_750_label = Label::createWithTTF(fontConfig, "x750");
    coins_750->addChild(coins_750_label);
    coins_750_label->setAnchorPoint(Vec2(0.5,1));
    coins_750_label->setPosition(Vec2(coins_750->getBoundingBox().size.width*0.4,coins_750->getBoundingBox().size.height*0.2));

    auto hammer_3 = Sprite::create("hammer.png");
    sectors->addChild(hammer_3, 1);
    hammer_3->setPosition(Vec2(sectors->getBoundingBox().size.width*0.634, sectors->getBoundingBox().size.height*0.177));
    hammer_3->setRotation(-ANGLE_SECTOR_5);
    auto hammer_3_label = Label::createWithTTF(fontConfig, "x3");
    hammer_3->addChild(hammer_3_label);
    hammer_3_label->setAnchorPoint(Vec2(0.5,1));
    hammer_3_label->setPosition(Vec2(hammer_3->getBoundingBox().size.width*0.4,hammer_3->getBoundingBox().size.height*0.2));

    auto gem_35 = Sprite::create("gem.png");
    sectors->addChild(gem_35, 1);
    gem_35->setPosition(Vec2(sectors->getBoundingBox().size.width*0.824, sectors->getBoundingBox().size.height*0.366));
    gem_35->setRotation(-ANGLE_SECTOR_6);
    auto gem_35_label = Label::createWithTTF(fontConfig, "x35");
    gem_35->addChild(gem_35_label);
    gem_35_label->setAnchorPoint(Vec2(0.5,1));
    gem_35_label->setPosition(Vec2(gem_35->getBoundingBox().size.width*0.4,gem_35->getBoundingBox().size.height*0.2));

    auto brush_3 = Sprite::create("brush.png");
    sectors->addChild(brush_3, 1);
    brush_3->setPosition(Vec2(sectors->getBoundingBox().size.width*0.824, sectors->getBoundingBox().size.height*0.634));
    brush_3->setRotation(-ANGLE_SECTOR_7);
    brush_3->setScale(0.8f);
    auto brush_3_label = Label::createWithTTF(fontConfig, "x3");
    brush_3->addChild(brush_3_label);
    brush_3_label->setAnchorPoint(Vec2(0.5,1));
    brush_3_label->setPosition(Vec2(brush_3->getBoundingBox().size.width*0.4,brush_3->getBoundingBox().size.height*0.2));

    auto life_30 = Sprite::create("heart.png");
    sectors->addChild(life_30, 1);
    life_30->setPosition(Vec2(sectors->getBoundingBox().size.width*0.634, sectors->getBoundingBox().size.height*0.824));
    life_30->setRotation(-ANGLE_SECTOR_8);
    auto life_30_label = Label::createWithTTF(fontConfig, "x30");
    life_30->addChild(life_30_label);
    life_30_label->setAnchorPoint(Vec2(0.5,1));
    life_30_label->setPosition(Vec2(life_30->getBoundingBox().size.width*0.4,life_30->getBoundingBox().size.height*0.2));

    
    //add "spin on" button
    auto spin_button = Button::create("spin_button.png");

    spin_button->setTitleText("Play On");
    spin_button->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/5 + origin.y));
    this->addChild(spin_button,1);

    //add the touch event handler to the button
    spin_button->addTouchEventListener(CC_CALLBACK_2(SpinnerScene::touchEvent, this));
    return true;
}

void SpinnerScene::touchEvent(Ref* sender, Widget::TouchEventType type)
{
    Button *button = (Button*)sender;
    switch(type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
            {
                //make the button disappear while wheel is spinning
                button->runAction(Sequence::create(ScaleTo::create(BUTTON_TRANSITION_TIME,0), DelayTime::create(ROTATION_TIME), ScaleTo::create(BUTTON_TRANSITION_TIME,1), nullptr));
                //make the wheel spin
                //SpinnerScene::sectors->runAction(Sequence::create(RotateBy::create(ROTATION_TIME,ROTATION_ANGLE), RotateTo::create(1.0f, 50.0f),nullptr));
                SpinnerScene::sectors->runAction(EaseInOut::create(RotateTo::create(ROTATION_TIME,ROTATION_ANGLE+getGoalAngle()),EASING_RATE)->clone());
                //SpinnerScene::sectors->runAction(RotateBy::create(ROTATION_TIME, ROTATION_ANGLE));
                break;
            }
            default:
                break;
        }
    return;
}

float SpinnerScene::getGoalAngle()
{
    srand(time(NULL));
    int r_num = rand() % 100 + 1;
    if(r_num < 20)
        return ANGLE_SECTOR_1;
    if(r_num < 25)
        return ANGLE_SECTOR_2;
    if(r_num < 45)
        return ANGLE_SECTOR_3;
    if(r_num < 50)
        return ANGLE_SECTOR_4;
    if(r_num < 60)
        return ANGLE_SECTOR_5;
    if(r_num < 70)
        return ANGLE_SECTOR_6;
    if(r_num < 80)
        return ANGLE_SECTOR_7;
    if(r_num < 100)
        return ANGLE_SECTOR_8;
    return 0;
}