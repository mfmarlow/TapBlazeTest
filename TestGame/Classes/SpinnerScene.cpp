#include "SpinnerScene.h"
#include "MenuScene.h"

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

	//add spinner sectors sprite (the part that will rotate)
	sectors = Sprite::create("wheel_sections_8.png");
	sectors->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sectors, 0);

	//add reward sprites with labels to the spinner sectors

	//Sector 1 Sprite - LIFEx30
	sprite_1 = addSectorSprite(SPRITE_SECTOR_1, 1);
	addLabelWithQuantity(sprite_1, QTY_SECTOR_1);

	//Sector 2 Sprite - BRUSHx3
	sprite_2 = addSectorSprite(SPRITE_SECTOR_2, 2);
	addLabelWithQuantity(sprite_2, QTY_SECTOR_2);

	//Sector 3 Sprite - GEMSx35
	sprite_3 = addSectorSprite(SPRITE_SECTOR_3, 3);
	sprite_3->setScale(0.8f);
	addLabelWithQuantity(sprite_3, QTY_SECTOR_3);

	//Sector 4 Sprite - HAMMERx3
	sprite_4 = addSectorSprite(SPRITE_SECTOR_4, 4);
	addLabelWithQuantity(sprite_4, QTY_SECTOR_4);

	//Sector 5 Sprite - COINSx750
	sprite_5 = addSectorSprite(SPRITE_SECTOR_5, 5);
	addLabelWithQuantity(sprite_5, QTY_SECTOR_5);

	//Sector 6 Sprite - BRUSHx1
	sprite_6 = addSectorSprite(SPRITE_SECTOR_6, 6);
	addLabelWithQuantity(sprite_6, QTY_SECTOR_6);

	//Sector 7 Sprite - GEMSx75
	sprite_7 = addSectorSprite(SPRITE_SECTOR_7, 7);
	sprite_7->setScale(0.8f);
	addLabelWithQuantity(sprite_7, QTY_SECTOR_7);

	//Sector 8 Sprite - HAMMERx1
	sprite_8 = addSectorSprite(SPRITE_SECTOR_8, 8);
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

	//unit-testing
	//runSpinTest();

	return true;
}

//handle touch events for buttons
void SpinnerScene::touchEvent(Ref* sender, Widget::TouchEventType type)
{
	//recover button object from sender reference
	Button* button = (Button*)sender;

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
			Scene* menu_scene = MenuScene::createScene(this);
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
	}

	ofstream file;
	file.open("../../1000spins.txt");
	if (file)
	{
		file << "Sector 1: " << sector_1_count << endl;
		file << "Sector 2: " << sector_2_count << endl;
		file << "Sector 3: " << sector_3_count << endl;
		file << "Sector 4: " << sector_4_count << endl;
		file << "Sector 5: " << sector_5_count << endl;
		file << "Sector 6: " << sector_6_count << endl;
		file << "Sector 7: " << sector_7_count << endl;
		file << "Sector 8: " << sector_8_count << endl;
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

//add passed sprite to passed sector
Sprite* SpinnerScene::addSectorSprite(string image, int sector)
{
	float wheel_width = sectors->getBoundingBox().size.width;
	float wheel_height = sectors->getBoundingBox().size.height;

	auto sprite = Sprite::create(image);
	rewards[sector - 1] = sprite;
	sectors->addChild(sprite, 1);

	//depending on desired sector, set position and rotation as necessary.
	switch (sector)
	{
	case 1:
		sprite->setPosition(Vec2(wheel_width * CIRCLE_COORDS_3, wheel_height * CIRCLE_COORDS_4));
		sprite->setRotation(-ANGLE_SECTOR_1);
		break;
	case 2:
		sprite->setPosition(Vec2(wheel_width * CIRCLE_COORDS_4, wheel_height * CIRCLE_COORDS_3));
		sprite->setRotation(-ANGLE_SECTOR_2);
		break;
	case 3:
		sprite->setPosition(Vec2(wheel_width * CIRCLE_COORDS_4, wheel_height * CIRCLE_COORDS_2));
		sprite->setRotation(-ANGLE_SECTOR_3);
		break;
	case 4:
		sprite->setPosition(Vec2(wheel_width * CIRCLE_COORDS_3, wheel_height * CIRCLE_COORDS_1));
		sprite->setRotation(-ANGLE_SECTOR_4);
		break;
	case 5:
		sprite->setPosition(Vec2(wheel_width * CIRCLE_COORDS_2, wheel_height * CIRCLE_COORDS_1));
		sprite->setRotation(-ANGLE_SECTOR_5);
		break;
	case 6:
		sprite->setPosition(Vec2(wheel_width * CIRCLE_COORDS_1, wheel_height * CIRCLE_COORDS_2));
		sprite->setRotation(-ANGLE_SECTOR_6);
		break;
	case 7:
		sprite->setPosition(Vec2(wheel_width * CIRCLE_COORDS_1, wheel_height * CIRCLE_COORDS_3));
		sprite->setRotation(-ANGLE_SECTOR_7);
		break;
	case 8:
		sprite->setPosition(Vec2(wheel_width * CIRCLE_COORDS_2, wheel_height * CIRCLE_COORDS_4));
		sprite->setRotation(-ANGLE_SECTOR_8);
		break;
	default:
		break;
	}

	return sprite;
}