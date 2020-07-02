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

Scene *SpinnerScene::createScene()
{
    return SpinnerScene::create();
}

bool SpinnerScene::init()
{
    if (!Scene::init())
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
    border = Sprite::create("wheel_border.png");

    border->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(border, 1);

    // add spinner arrow sprite
    arrow = Sprite::create("wheel_arrow.png");

    border->addChild(arrow);
    arrow->setScale(1.25);
    arrow->setPosition(Vec2(border->getBoundingBox().size.width / 2, border->getBoundingBox().size.height * 0.95));

    //add spinner sectors sprite (the part that will rotate) which is declared in the header file.
    sectors = Sprite::create("wheel_sections_8.png");

    sectors->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(sectors, 0);

    //add reward sprites with labels to the spinner sectors

    float wheel_width = sectors->getBoundingBox().size.width;
    float wheel_height = sectors->getBoundingBox().size.height;

    //HAMMERx1
    auto hammer_1 = Sprite::create("hammer.png");
    sectors->addChild(hammer_1, 1);
    hammer_1->setPosition(Vec2(wheel_width * CIRCLE_COORDS_2, wheel_height * CIRCLE_COORDS_4));
    hammer_1->setRotation(-ANGLE_SECTOR_1);
    auto hammer_1_label = Label::createWithTTF(fontConfig, "x1");
    hammer_1->addChild(hammer_1_label);
    hammer_1_label->setAnchorPoint(Vec2(0.5, 1));
    hammer_1_label->setPosition(Vec2(hammer_1->getBoundingBox().size.width * 0.4, hammer_1->getBoundingBox().size.height * SPRITE_LABEL_HEIGHT));

    //GEMx75
    auto gem_75 = Sprite::create("gem.png");
    sectors->addChild(gem_75, 1);
    gem_75->setPosition(Vec2(wheel_width * CIRCLE_COORDS_1, wheel_height * CIRCLE_COORDS_3));
    gem_75->setRotation(-ANGLE_SECTOR_2);
    auto gem_75_label = Label::createWithTTF(fontConfig, "x75");
    gem_75->addChild(gem_75_label);
    gem_75_label->setAnchorPoint(Vec2(0.5, 1));
    gem_75_label->setPosition(Vec2(gem_75->getBoundingBox().size.width * 0.4, gem_75->getBoundingBox().size.height * SPRITE_LABEL_HEIGHT));

    //BRUSHx1
    auto brush_1 = Sprite::create("brush.png");
    sectors->addChild(brush_1, 1);
    brush_1->setPosition(Vec2(wheel_width * CIRCLE_COORDS_1, wheel_height * CIRCLE_COORDS_2));
    brush_1->setRotation(-ANGLE_SECTOR_3);
    brush_1->setScale(0.8f);
    auto brush_1_label = Label::createWithTTF(fontConfig, "x1");
    brush_1->addChild(brush_1_label);
    brush_1_label->setAnchorPoint(Vec2(0.5, 1));
    brush_1_label->setPosition(Vec2(brush_1->getBoundingBox().size.width * 0.4, brush_1->getBoundingBox().size.height * SPRITE_LABEL_HEIGHT));
    brush_1_label->setScale(1.25f);

    //COINSx750
    auto coins_750 = Sprite::create("coin.png");
    sectors->addChild(coins_750, 1);
    coins_750->setPosition(Vec2(wheel_width * CIRCLE_COORDS_2, wheel_height * CIRCLE_COORDS_1));
    coins_750->setRotation(-ANGLE_SECTOR_4);
    auto coins_750_label = Label::createWithTTF(fontConfig, "x750");
    coins_750->addChild(coins_750_label);
    coins_750_label->setAnchorPoint(Vec2(0.5, 1));
    coins_750_label->setPosition(Vec2(coins_750->getBoundingBox().size.width * 0.4, coins_750->getBoundingBox().size.height * SPRITE_LABEL_HEIGHT));

    //HAMMERx3
    auto hammer_3 = Sprite::create("hammer.png");
    sectors->addChild(hammer_3, 1);
    hammer_3->setPosition(Vec2(wheel_width * CIRCLE_COORDS_3, wheel_height * CIRCLE_COORDS_1));
    hammer_3->setRotation(-ANGLE_SECTOR_5);
    auto hammer_3_label = Label::createWithTTF(fontConfig, "x3");
    hammer_3->addChild(hammer_3_label);
    hammer_3_label->setAnchorPoint(Vec2(0.5, 1));
    hammer_3_label->setPosition(Vec2(hammer_3->getBoundingBox().size.width * 0.4, hammer_3->getBoundingBox().size.height * SPRITE_LABEL_HEIGHT));

    //GEMx35
    auto gem_35 = Sprite::create("gem.png");
    sectors->addChild(gem_35, 1);
    gem_35->setPosition(Vec2(wheel_width * CIRCLE_COORDS_4, wheel_height * CIRCLE_COORDS_2));
    gem_35->setRotation(-ANGLE_SECTOR_6);
    auto gem_35_label = Label::createWithTTF(fontConfig, "x35");
    gem_35->addChild(gem_35_label);
    gem_35_label->setAnchorPoint(Vec2(0.5, 1));
    gem_35_label->setPosition(Vec2(gem_35->getBoundingBox().size.width * 0.4, gem_35->getBoundingBox().size.height * SPRITE_LABEL_HEIGHT));

    //BRUSHx3
    auto brush_3 = Sprite::create("brush.png");
    sectors->addChild(brush_3, 1);
    brush_3->setPosition(Vec2(wheel_width * CIRCLE_COORDS_4, wheel_height * CIRCLE_COORDS_3));
    brush_3->setRotation(-ANGLE_SECTOR_7);
    brush_3->setScale(0.8f);
    auto brush_3_label = Label::createWithTTF(fontConfig, "x3");
    brush_3->addChild(brush_3_label);
    brush_3_label->setAnchorPoint(Vec2(0.5, 1));
    brush_3_label->setPosition(Vec2(brush_3->getBoundingBox().size.width * 0.4, brush_3->getBoundingBox().size.height * SPRITE_LABEL_HEIGHT));
    brush_3_label->setScale(1.25f);

    //LIFEx30
    auto life_30 = Sprite::create("heart.png");
    sectors->addChild(life_30, 1);
    life_30->setPosition(Vec2(wheel_width * CIRCLE_COORDS_3, wheel_height * CIRCLE_COORDS_4));
    life_30->setRotation(-ANGLE_SECTOR_8);
    auto life_30_label = Label::createWithTTF(fontConfig, "30");
    life_30->addChild(life_30_label);
    life_30_label->setAnchorPoint(Vec2(0.5, 1));
    life_30_label->setPosition(Vec2(life_30->getBoundingBox().size.width * 0.4, life_30->getBoundingBox().size.height * SPRITE_LABEL_HEIGHT));
    auto life_30_sublabel = Label::createWithTTF("min", "fonts/arial.ttf", 10);
    life_30_sublabel->enableOutline(Color4B::BLACK, 1);
    life_30_label->addChild(life_30_sublabel);
    life_30_sublabel->setPosition(Vec2(life_30_label->getBoundingBox().size.width, 0));

    //"play on" button
    auto spin_button = Button::create("spin_button.png");
    spin_button->setTitleText("Play On");
    spin_button->setTitleFontSize(26);
    spin_button->getTitleLabel()->enableOutline(Color4B::BLACK, 1);
    spin_button->getTitleLabel()->setPosition(Vec2(spin_button->getBoundingBox().size.width / 2, spin_button->getBoundingBox().size.height * 0.55));
    spin_button->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 5 + origin.y));
    this->addChild(spin_button, 1);
    spin_button->setTag(SPIN_TAG);

    //add the touch event handler to the button
    spin_button->addTouchEventListener(CC_CALLBACK_2(SpinnerScene::touchEvent, this));
    return true;
}

//handle touch events for button
void SpinnerScene::touchEvent(Ref *sender, Widget::TouchEventType type)
{
    //recover button object from sender reference
    Button *button = (Button *)sender;

    auto removeWheel = CallFunc::create([=]() {
        border->runAction(EaseBackIn::create(ScaleTo::create(BUTTON_TRANSITION_TIME, 0)));
        sectors->runAction(EaseBackIn::create(ScaleTo::create(BUTTON_TRANSITION_TIME, 0)));
    });

    auto showWheel = CallFunc::create([=]() {
        border->runAction(EaseBackIn::create(ScaleTo::create(BUTTON_TRANSITION_TIME, 1)));
        sectors->runAction(EaseBackIn::create(ScaleTo::create(BUTTON_TRANSITION_TIME, 1)));
    });

    if (type == Widget::TouchEventType::ENDED)
    {
        //When clicking button to spin
        if (button->getTag() == SPIN_TAG)
        {
            //function for changing button to claim
            auto changeText = CallFunc::create([=]() {
                button->setTitleText("Claim");
                button->setTag(CLAIM_TAG);
            });

            //make the button disappear while wheel is spinning
            button->runAction(Sequence::create(ScaleTo::create(BUTTON_TRANSITION_TIME, 0), DelayTime::create(ROTATION_TIME), changeText, ScaleTo::create(BUTTON_TRANSITION_TIME, 1), nullptr));
            //make the wheel spin to the reward
            SpinnerScene::sectors->runAction(Sequence::create(EaseInOut::create(RotateTo::create(ROTATION_TIME, ROTATION_ANGLE + getGoalAngle()), EASING_RATE), removeWheel, nullptr));
        }
        //When clicking button to claim
        else if (button->getTag() == CLAIM_TAG)
        {
            //function for changing button back to spin
            auto changeText = CallFunc::create([=]() {
                button->setTitleText("Play On");
                button->setTag(SPIN_TAG);
            });
            //
            button->runAction(Sequence::create(ScaleTo::create(BUTTON_TRANSITION_TIME, 0), changeText, DelayTime::create(BUTTON_TRANSITION_TIME), showWheel, ScaleTo::create(BUTTON_TRANSITION_TIME, 1), nullptr));
        }
    }
    return;
}

//determine the reward and return the angle to spin to
float SpinnerScene::getGoalAngle()
{
    //generate random int in [1,100]
    srand(time(NULL));
    int r_num = rand() % 100 + 1;

    //depending on r_num, return angle of sector
    if (r_num <= SECTOR_LIMIT_1)
        return ANGLE_SECTOR_1;
    if (r_num <= SECTOR_LIMIT_2)
        return ANGLE_SECTOR_2;
    if (r_num <= SECTOR_LIMIT_3)
        return ANGLE_SECTOR_3;
    if (r_num <= SECTOR_LIMIT_4)
        return ANGLE_SECTOR_4;
    if (r_num <= SECTOR_LIMIT_5)
        return ANGLE_SECTOR_5;
    if (r_num <= SECTOR_LIMIT_6)
        return ANGLE_SECTOR_6;
    if (r_num <= SECTOR_LIMIT_7)
        return ANGLE_SECTOR_7;
    if (r_num <= SECTOR_LIMIT_8)
        return ANGLE_SECTOR_8;
    //this should never happen
    return 0;
}