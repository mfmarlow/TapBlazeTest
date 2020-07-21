#include "SpinnerScene.h"
#include "MenuScene.h"

Scene* SpinnerScene::createScene(vector<string> new_sprite_imgs, vector<string> new_labels, vector<int> new_chances)
{
	auto scene = SpinnerScene::create();
	scene->sprite_imgs = new_sprite_imgs;
	scene->labels = new_labels;
	scene->chances = new_chances;
	scene->populateSectors();
	scene->runSpinTest();
	return scene;
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

	//set up actions TODO - FIX 
	hide = ScaleTo::create(TRANSITION_TIME_FAST, 0);
	show = ScaleTo::create(TRANSITION_TIME_FAST, 1);

	removeWheel = CallFunc::create([=]() {
		border->runAction(EaseBackIn::create(hide->clone()));
		sectors->runAction(EaseBackIn::create(hide->clone()));
		});

	showWheel = CallFunc::create([=]() {
		border->runAction(EaseBackOut::create(show->clone()));
		sectors->runAction(EaseBackOut::create(show->clone()));
		});

	changeToClaim = CallFunc::create([=]() {
		spin_button->setTitleText("Claim");
		spin_button->setTag(CLAIM_TAG);
		});

	changeToSpin = CallFunc::create([=]() {
		spin_button->setTitleText("Play On");
		spin_button->setTag(SPIN_TAG);
		});

	showReward = CallFunc::create([&]() {SpinnerScene::showRewardFunc(); });

	replaceReward = CallFunc::create([&]() {SpinnerScene::replaceRewardFunc(); });

	return true;
}

//handle touch events for buttons
void SpinnerScene::touchEvent(Ref* sender, Widget::TouchEventType type)
{
	//recover button object from sender reference
	Button* button = (Button*)sender;

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
	float sector_angles[SECTOR_COUNT] = { ANGLE_SECTOR_1, ANGLE_SECTOR_2, ANGLE_SECTOR_3, ANGLE_SECTOR_4,
										  ANGLE_SECTOR_5, ANGLE_SECTOR_6, ANGLE_SECTOR_7, ANGLE_SECTOR_8 };
	//generate random int in [0,total_prob]
	int total_prob = accumulate(chances.begin(), chances.end(), 0);
	int r_num = (rand() / static_cast<float>(RAND_MAX)) * total_prob;

	int reward = 0;
	while ((r_num -= chances[reward]) > 0)
		++reward;

	last_reward = reward + 1;
	return sector_angles[reward];
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
	int no_sector_count = 0;

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
			no_sector_count++;
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
		file << "No sector: " << no_sector_count << endl;
		file.close();
		log("unit test complete");
	}
	else
	{
		log("Unable to open output file");
	}

}

//add passed sprite to passed sector
Sprite* SpinnerScene::addSectorSprite(string image, int sector)
{
	float wheel_width = sectors->getBoundingBox().size.width;
	float wheel_height = sectors->getBoundingBox().size.height;

	static Vec2 sector_positions[8] = { Vec2(wheel_width * CIRCLE_COORDS_3, wheel_height * CIRCLE_COORDS_4) ,
										Vec2(wheel_width * CIRCLE_COORDS_4, wheel_height * CIRCLE_COORDS_3) ,
										Vec2(wheel_width * CIRCLE_COORDS_4, wheel_height * CIRCLE_COORDS_2) ,
										Vec2(wheel_width * CIRCLE_COORDS_3, wheel_height * CIRCLE_COORDS_1) ,
										Vec2(wheel_width * CIRCLE_COORDS_2, wheel_height * CIRCLE_COORDS_1) ,
										Vec2(wheel_width * CIRCLE_COORDS_1, wheel_height * CIRCLE_COORDS_2) ,
										Vec2(wheel_width * CIRCLE_COORDS_1, wheel_height * CIRCLE_COORDS_3) ,
										Vec2(wheel_width * CIRCLE_COORDS_2, wheel_height * CIRCLE_COORDS_4) };

	static float sector_rotations[8] = { -ANGLE_SECTOR_1, -ANGLE_SECTOR_2, -ANGLE_SECTOR_3, -ANGLE_SECTOR_4,
										 -ANGLE_SECTOR_5, -ANGLE_SECTOR_6, -ANGLE_SECTOR_7, -ANGLE_SECTOR_8 };

	//create new sprite using image
	auto new_sprite = Sprite::create(image);

	//set sprite position and rotation
	new_sprite->setPosition(sector_positions[sector]);
	new_sprite->setRotation(sector_rotations[sector]);

	//add sprite as a child of sectors sprite
	sectors->addChild(new_sprite, 1);

	return new_sprite;
}

//create sprites and labels for every sector
void SpinnerScene::populateSectors()
{
	for (int x = 0; x < SECTOR_COUNT; x++)
	{
		this->sprites.push_back(addSectorSprite(this->sprite_imgs[x], x));
		addLabelWithQuantity(this->sprites[x], this->labels[x]);
	}
}

void SpinnerScene::showRewardFunc()
{
	//record members of reward sprite (for replacement later)
	if (last_reward != 0)
	{
		reward_sprite = sprites.at(last_reward-1);
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
}

void SpinnerScene::replaceRewardFunc()
{
	if (last_reward != 0)
	{
		reward_sprite->retain();
		reward_sprite->removeFromParent();
		sectors->addChild(reward_sprite, 1);
		reward_sprite->setPosition(reward_position);
		reward_sprite->setRotation(reward_rotation);
		reward_sprite->setScale(reward_scale);
		reward_sprite->release();
	}
}