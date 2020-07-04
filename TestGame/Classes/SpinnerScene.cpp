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
#include "MenuScene.h"

 //set probabilities to default values
int SpinnerScene::p_sector_1 = P_SECTOR_1_DEF;
int SpinnerScene::p_sector_2 = P_SECTOR_2_DEF;
int SpinnerScene::p_sector_3 = P_SECTOR_3_DEF;
int SpinnerScene::p_sector_4 = P_SECTOR_4_DEF;
int SpinnerScene::p_sector_5 = P_SECTOR_5_DEF;
int SpinnerScene::p_sector_6 = P_SECTOR_6_DEF;
int SpinnerScene::p_sector_7 = P_SECTOR_7_DEF;
int SpinnerScene::p_sector_8 = P_SECTOR_8_DEF;
int SpinnerScene::p_sector_sum = 100;

Scene* SpinnerScene::createScene()
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
	srand(time(NULL));

	//add settings button for QA testing
	auto settings = Button::create("spin_button.png");
	settings->setTitleText("Settings");
	settings->setTitleFontSize(20);
	settings->getTitleLabel()->enableOutline(Color4B::BLACK, 1);
	settings->getTitleLabel()->setPosition(Vec2(settings->getBoundingBox().size.width / 2, settings->getBoundingBox().size.height * 0.55));
	settings->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 0.85 + origin.y));
	this->addChild(settings, 1);
	settings->setTag(SETTINGS_TAG);
	settings->addTouchEventListener(CC_CALLBACK_2(SpinnerScene::touchEvent, this));

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

	//Sector 1 Sprite - LIFEx30
	sprite_1 = Sprite::create(SPRITE_SECTOR_1);
	rewards[0] = sprite_1;
	sectors->addChild(sprite_1, 1);
	sprite_1->setPosition(Vec2(wheel_width * CIRCLE_COORDS_3, wheel_height * CIRCLE_COORDS_4));
	sprite_1->setRotation(-ANGLE_SECTOR_1);
	addLabelWithQuantity(sprite_1, QTY_SECTOR_1);

	//Sector 2 Sprite - BRUSHx3
	sprite_2 = Sprite::create(SPRITE_SECTOR_2);
	rewards[1] = sprite_2;
	sectors->addChild(sprite_2, 1);
	sprite_2->setPosition(Vec2(wheel_width * CIRCLE_COORDS_4, wheel_height * CIRCLE_COORDS_3));
	sprite_2->setRotation(-ANGLE_SECTOR_2);
	addLabelWithQuantity(sprite_2, QTY_SECTOR_2);

	//Sector 3 Sprite - GEMSx35
	sprite_3 = Sprite::create(SPRITE_SECTOR_3);
	rewards[2] = sprite_3;
	sectors->addChild(sprite_3, 1);
	sprite_3->setPosition(Vec2(wheel_width * CIRCLE_COORDS_4, wheel_height * CIRCLE_COORDS_2));
	sprite_3->setRotation(-ANGLE_SECTOR_3);
	sprite_3->setScale(0.8f);
	addLabelWithQuantity(sprite_3, QTY_SECTOR_3);

	//Sector 4 Sprite - HAMMERx3
	sprite_4 = Sprite::create(SPRITE_SECTOR_4);
	rewards[3] = sprite_4;
	sectors->addChild(sprite_4, 1);
	sprite_4->setPosition(Vec2(wheel_width * CIRCLE_COORDS_3, wheel_height * CIRCLE_COORDS_1));
	sprite_4->setRotation(-ANGLE_SECTOR_4);
	addLabelWithQuantity(sprite_4, QTY_SECTOR_4);

	//Sector 5 Sprite - COINSx750
	sprite_5 = Sprite::create(SPRITE_SECTOR_5);
	rewards[4] = sprite_5;
	sectors->addChild(sprite_5, 1);
	sprite_5->setPosition(Vec2(wheel_width * CIRCLE_COORDS_2, wheel_height * CIRCLE_COORDS_1));
	sprite_5->setRotation(-ANGLE_SECTOR_5);
	addLabelWithQuantity(sprite_5, QTY_SECTOR_5);

	//Sector 6 Sprite - BRUSHx1
	sprite_6 = Sprite::create(SPRITE_SECTOR_6);
	rewards[5] = sprite_6;
	sectors->addChild(sprite_6, 1);
	sprite_6->setPosition(Vec2(wheel_width * CIRCLE_COORDS_1, wheel_height * CIRCLE_COORDS_2));
	sprite_6->setRotation(-ANGLE_SECTOR_6);
	addLabelWithQuantity(sprite_6, QTY_SECTOR_6);

	//Sector 7 Sprite - GEMSx75
	sprite_7 = Sprite::create(SPRITE_SECTOR_7);
	rewards[6] = sprite_7;
	sectors->addChild(sprite_7, 1);
	sprite_7->setPosition(Vec2(wheel_width * CIRCLE_COORDS_1, wheel_height * CIRCLE_COORDS_3));
	sprite_7->setRotation(-ANGLE_SECTOR_7);
	sprite_7->setScale(0.8f);
	addLabelWithQuantity(sprite_7, QTY_SECTOR_7);

	//Sector 8 Sprite - HAMMERx1
	sprite_8 = Sprite::create(SPRITE_SECTOR_8);
	rewards[7] = sprite_8;
	sectors->addChild(sprite_8, 1);
	sprite_8->setPosition(Vec2(wheel_width * CIRCLE_COORDS_2, wheel_height * CIRCLE_COORDS_4));
	sprite_8->setRotation(-ANGLE_SECTOR_8);
	addLabelWithQuantity(sprite_8, QTY_SECTOR_8);

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

	//runSpinTest();

	return true;
}

//handle touch events for button
void SpinnerScene::touchEvent(Ref* sender, Widget::TouchEventType type)
{
	//recover button object from sender reference
	Button* button = (Button*)sender;
	static Sprite* reward_sprite;
	static Vec2 reward_position;
	static float reward_rotation;
	static float reward_scale;

	//actions to be used
	auto hide = ScaleTo::create(TRANSITION_TIME_FAST, 0);
	auto show = ScaleTo::create(TRANSITION_TIME_FAST, 1);

	auto removeWheel = CallFunc::create([=]() {
		border->runAction(EaseBackIn::create(hide->clone()));
		sectors->runAction(EaseBackIn::create(hide->clone()));
		});

	auto showWheel = CallFunc::create([=]() {
		border->runAction(EaseBackOut::create(show->clone()));
		sectors->runAction(EaseBackOut::create(show->clone()));
		});

	//function for changing button to claim button
	auto changeToClaim = CallFunc::create([=]() {
		button->setTitleText("Claim");
		button->setTag(CLAIM_TAG);
		});

	//function for changing button back to spin button
	auto changeToSpin = CallFunc::create([=]() {
		button->setTitleText("Play On");
		button->setTag(SPIN_TAG);
		});

	//move reward to center of screen
	auto showReward = CallFunc::create([&]() {
		//record members of reward sprite (for replacement later)
		if (last_reward != 0)
		{
			reward_sprite = rewards[last_reward - 1];
			reward_position = reward_sprite->getPosition();
			Vec2 location = reward_sprite->getParent()->convertToWorldSpace(reward_position);
			reward_rotation = reward_sprite->getRotation();
			reward_scale = reward_sprite->getScale();

			//bring reward sprite to front and center screen
			reward_sprite->retain();
			reward_sprite->removeFromParent();
			this->addChild(reward_sprite, 2);
			reward_sprite->setPosition(location);
			reward_sprite->setRotation(0);
			reward_sprite->setScale(1);
			reward_sprite->release();

			//actions to bring reward sprite to front and center
			reward_sprite->runAction(ScaleTo::create(TRANSITION_TIME_FAST, 2));
			reward_sprite->runAction(MoveTo::create(TRANSITION_TIME_FAST, Vec2(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x, Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y)));
		}
		});

	//move reward back onto wheel
	auto replaceReward = CallFunc::create([&]() {
		if (last_reward != 0)
		{
			reward_sprite->retain();
			reward_sprite->removeFromParent();
			sectors->addChild(reward_sprite, 1);
			reward_sprite->setPosition(reward_position); // SIDE EFFECTS PREVENTING?
			reward_sprite->setRotation(reward_rotation);
			reward_sprite->setScale(reward_scale);
			reward_sprite->release();
		}
		});

	if (type == Widget::TouchEventType::ENDED)
	{
		//When clicking button to spin
		if (button->getTag() == SPIN_TAG)
		{
			//make the button disappear while wheel is spinning, then change to claim button and reappear
			button->runAction(Sequence::create(hide, DelayTime::create(ROTATION_TIME), changeToClaim, show, nullptr));
			//make the wheel spin to the reward, then disappear, revealing reward
			sectors->runAction(Sequence::create(EaseInOut::create(RotateTo::create(ROTATION_TIME, ROTATION_ANGLE + getGoalAngle()), EASING_RATE), removeWheel, showReward, nullptr));
		}
		//When clicking button to claim
		else if (button->getTag() == CLAIM_TAG)
		{
			//return back to wheel with spin button and put reward sprite back on wheel
			button->runAction(Sequence::create(hide, changeToSpin, DelayTime::create(TRANSITION_TIME_FAST), showWheel, replaceReward, show, nullptr));
		}
		//When clicking the settings button
		else if (button->getTag() == SETTINGS_TAG)
		{
			Scene* menu_scene = MenuScene::createScene();
			Director::getInstance()->pushScene(menu_scene);
		}
	}
	return;
}

//determine the reward and return the angle to spin to
float SpinnerScene::getGoalAngle()
{
	calculateSectorLimits();
	//generate random int in [1,100]
	int r_num = rand() % 100 + 1;

	//depending on r_num, return angle of sector
	if (r_num <= sector_limit_8)
	{
		last_reward = 8;
		return ANGLE_SECTOR_8;
	}
	if (r_num <= sector_limit_7)
	{
		last_reward = 7;
		return ANGLE_SECTOR_7;
	}
	if (r_num <= sector_limit_6)
	{
		last_reward = 6;
		return ANGLE_SECTOR_6;
	}
	if (r_num <= sector_limit_5)
	{
		last_reward = 5;
		return ANGLE_SECTOR_5;
	}
	if (r_num <= sector_limit_4)
	{
		last_reward = 4;
		return ANGLE_SECTOR_4;
	}
	if (r_num <= sector_limit_3)
	{
		last_reward = 3;
		return ANGLE_SECTOR_3;
	}
	if (r_num <= sector_limit_2)
	{
		last_reward = 2;
		return ANGLE_SECTOR_2;
	}
	if (r_num <= sector_limit_1)
	{
		last_reward = 1;
		return ANGLE_SECTOR_1;
	}
	//if probabilities dont add to 100, we could get here
	last_reward = 0;
	return 0;
}

//adds label to sprite for quantity.
void SpinnerScene::addLabelWithQuantity(Sprite* sprite, string label_text)
{
	//TTF config for all labels
	TTFConfig font_config;
	font_config.fontFilePath = "fonts/arial.ttf";
	font_config.fontSize = 20;
	font_config.outlineSize = 1;

	//parse label_text in case of subtext
	istringstream ss(label_text);
	ss >> label_text;

	//create quantity label for the passed sprite
	auto sprite_label = Label::createWithTTF(font_config, label_text);
	sprite->addChild(sprite_label);
	sprite_label->setAnchorPoint(Vec2(0.5, 1));
	sprite_label->setPosition(Vec2(sprite->getBoundingBox().size.width * 0.4, sprite->getBoundingBox().size.height * SPRITE_LABEL_HEIGHT));

	//if subtext is passed, also create subtext label
	if (ss)
	{
		string label_subtext;
		ss >> label_subtext;
		auto sprite_sublabel = Label::createWithTTF(label_subtext, "fonts/arial.ttf", 10);
		sprite_sublabel->enableOutline(Color4B::BLACK, 1);
		sprite_label->addChild(sprite_sublabel);
		sprite_sublabel->setPosition(Vec2(sprite_label->getBoundingBox().size.width, 0));
	}

	//if the sprite has been scaled, invert scale for the label
	if (sprite->getScale() != 1)
	{
		sprite_label->setScale(1 / sprite->getScale());
	}
}

//emulate 1000 spins and group results by prize - output to file "1000spins.txt"
void SpinnerScene::runSpinTest()
{
	int sector_1_count = 0;
	int sector_2_count = 0;
	int sector_3_count = 0;
	int sector_4_count = 0;
	int sector_5_count = 0;
	int sector_6_count = 0;
	int sector_7_count = 0;
	int sector_8_count = 0;

	for (int x = 0; x < 1000; x++)
	{
		getGoalAngle();
		switch (last_reward)
		{
		case 1:
			sector_1_count++;
			break;
		case 2:
			sector_2_count++;
			break;
		case 3:
			sector_3_count++;
			break;
		case 4:
			sector_4_count++;
			break;
		case 5:
			sector_5_count++;
			break;
		case 6:
			sector_6_count++;
			break;
		case 7:
			sector_7_count++;
			break;
		case 8:
			sector_8_count++;
			break;
		default:
			break;
		}

		//Sleep(10);
	}

	ofstream file;
	file.open("1000spins.txt");
	if (file)
	{
		file << "Hammerx1: " << sector_1_count << endl;
		file << "Gemsx75: " << sector_2_count << endl;
		file << "Brushx1: " << sector_3_count << endl;
		file << "Coinsx750: " << sector_4_count << endl;
		file << "Hammerx3: " << sector_5_count << endl;
		file << "Gemsx35: " << sector_6_count << endl;
		file << "Brushx3: " << sector_7_count << endl;
		file << "Lifex30: " << sector_8_count << endl;
		file.close();
		log("unit test complete");
	}
	else
	{
		log("Unable to open output file");
	}

}

//calculate/update the sector limits
void SpinnerScene::calculateSectorLimits()
{
	sector_limit_1 = p_sector_1 + p_sector_2 + p_sector_3 + p_sector_4 + p_sector_5 + p_sector_6 + p_sector_7 + p_sector_8;
	sector_limit_2 = p_sector_2 + p_sector_3 + p_sector_4 + p_sector_5 + p_sector_6 + p_sector_7 + p_sector_8;
	sector_limit_3 = p_sector_3 + p_sector_4 + p_sector_5 + p_sector_6 + p_sector_7 + p_sector_8;
	sector_limit_4 = p_sector_4 + p_sector_5 + p_sector_6 + p_sector_7 + p_sector_8;
	sector_limit_5 = p_sector_5 + p_sector_6 + p_sector_7 + p_sector_8;
	sector_limit_6 = p_sector_6 + p_sector_7 + p_sector_8;
	sector_limit_7 = p_sector_7 + p_sector_8;
	sector_limit_8 = p_sector_8;
	SpinnerScene::p_sector_sum = sector_limit_1;
}