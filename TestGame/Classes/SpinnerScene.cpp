#include "SpinnerScene.h"
#include "MenuScene.h"

Scene* SpinnerScene::createScene(vector<string> new_sprite_imgs, vector<string> new_labels, vector<int> new_chances)
{
	auto scene = SpinnerScene::create();
	scene->sprite_imgs = new_sprite_imgs;
	scene->labels = new_labels;
	scene->chances = new_chances;
	scene->calcTotalProb();
	scene->populateSectors();
	//scene->runSpinTest();
	return scene;
}

bool SpinnerScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visible_size = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	srand(time(NULL));

	//add settings button for QA testing
	auto settings = Button::create("spin_button.png");
	settings->setTitleText("Settings");
	settings->setTitleFontSize(20);
	settings->getTitleLabel()->enableOutline(Color4B::BLACK, 1);
	settings->getTitleLabel()->setPosition(Vec2(settings->getBoundingBox().size.width / 2, settings->getBoundingBox().size.height * 0.55));
	settings->setPosition(Vec2(visible_size.width / 2 + origin.x, visible_size.height * 0.85 + origin.y));
	this->addChild(settings, 1);
	settings->setTag(SETTINGS_TAG);
	settings->addTouchEventListener(CC_CALLBACK_2(SpinnerScene::touchEvent, this));

	// add spinner border sprite
	border = Sprite::create("wheel_border.png");
	border->setPosition(Vec2(visible_size.width / 2 + origin.x, visible_size.height / 2 + origin.y));
	this->addChild(border, 1);

	// add spinner arrow sprite
	arrow = Sprite::create("wheel_arrow.png");
	border->addChild(arrow);
	arrow->setScale(1.25);
	arrow->setPosition(Vec2(border->getBoundingBox().size.width / 2, border->getBoundingBox().size.height * 0.95));

	//add spinner sectors sprite (the part that will rotate)
	sectors = Sprite::create("wheel_sections_8.png");
	sectors->setPosition(Vec2(visible_size.width / 2 + origin.x, visible_size.height / 2 + origin.y));
	this->addChild(sectors, 0);

	//"play on" button
	auto spin_button = Button::create("spin_button.png");
	spin_button->setTitleText("Play On");
	spin_button->setTitleFontSize(26);
	spin_button->getTitleLabel()->enableOutline(Color4B::BLACK, 1);
	spin_button->getTitleLabel()->setPosition(Vec2(spin_button->getBoundingBox().size.width / 2, spin_button->getBoundingBox().size.height * 0.55));
	spin_button->setPosition(Vec2(visible_size.width / 2 + origin.x, visible_size.height / 5 + origin.y));
	this->addChild(spin_button, 1);
	spin_button->setTag(SPIN_TAG);

	float wheel_width = sectors->getBoundingBox().size.width;
	float wheel_height = sectors->getBoundingBox().size.height;

	sector_angles = { ANGLE_SECTOR_1, ANGLE_SECTOR_2, ANGLE_SECTOR_3, ANGLE_SECTOR_4,
					  ANGLE_SECTOR_5, ANGLE_SECTOR_6, ANGLE_SECTOR_7, ANGLE_SECTOR_8 };

	sector_positions = { Vec2(wheel_width * CIRCLE_COORDS_3, wheel_height * CIRCLE_COORDS_4) ,
						 Vec2(wheel_width * CIRCLE_COORDS_4, wheel_height * CIRCLE_COORDS_3) ,
						 Vec2(wheel_width * CIRCLE_COORDS_4, wheel_height * CIRCLE_COORDS_2) ,
						 Vec2(wheel_width * CIRCLE_COORDS_3, wheel_height * CIRCLE_COORDS_1) ,
						 Vec2(wheel_width * CIRCLE_COORDS_2, wheel_height * CIRCLE_COORDS_1) ,
						 Vec2(wheel_width * CIRCLE_COORDS_1, wheel_height * CIRCLE_COORDS_2) ,
						 Vec2(wheel_width * CIRCLE_COORDS_1, wheel_height * CIRCLE_COORDS_3) ,
						 Vec2(wheel_width * CIRCLE_COORDS_2, wheel_height * CIRCLE_COORDS_4) };

	sector_rotations = { -ANGLE_SECTOR_1, -ANGLE_SECTOR_2, -ANGLE_SECTOR_3, -ANGLE_SECTOR_4,
						 -ANGLE_SECTOR_5, -ANGLE_SECTOR_6, -ANGLE_SECTOR_7, -ANGLE_SECTOR_8 };

	//add the touch event handler to the button
	spin_button->addTouchEventListener(CC_CALLBACK_2(SpinnerScene::touchEvent, this));

	//set up actions
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

	//retain these actions for use later
	hide->retain();
	show->retain();
	removeWheel->retain();
	showWheel->retain();
	changeToClaim->retain();
	changeToSpin->retain();
	showReward->retain();
	replaceReward->retain();

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
	//generate random int in [1,100]
	int r_num = ((rand() / static_cast<float>(RAND_MAX)) * 100) + 1;

	//deduct p(each reward) from r_num until reward is reached
	int reward = 0;
	while (reward < SECTOR_COUNT && (r_num -= chances[reward]) > 0)
		++reward;

	//if no reward is selected (possible if total_prob < 100)
	if (reward >= SECTOR_COUNT)
	{
		last_reward = ERROR;
		return 0;
	}

	last_reward = reward;
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
	vector<int> sim_results = { 0,0,0,0,0,0,0,0,0 };

	for (int x = 0; x < 1000; x++)
	{
		getGoalAngle();
		if (last_reward != ERROR)
		{
			sim_results.at(last_reward)++;
			continue;
		}
		sim_results.at(8)++;
	}

	ofstream file;
	file.open("../../1000spins.txt");
	if (file)
	{
		file << "Sector 1: " << sim_results.at(0) << endl;
		file << "Sector 2: " << sim_results.at(1) << endl;
		file << "Sector 3: " << sim_results.at(2) << endl;
		file << "Sector 4: " << sim_results.at(3) << endl;
		file << "Sector 5: " << sim_results.at(4) << endl;
		file << "Sector 6: " << sim_results.at(5) << endl;
		file << "Sector 7: " << sim_results.at(6) << endl;
		file << "Sector 8: " << sim_results.at(7) << endl;
		file << "No sector: " << sim_results.at(8) << endl;
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
		sprites.push_back(addSectorSprite(sprite_imgs[x], x));
		addLabelWithQuantity(sprites[x], labels[x]);
	}
}

//function for show reward animation
void SpinnerScene::showRewardFunc()
{
	//record members of reward sprite (for replacement later)
	if (last_reward != ERROR)
	{
		reward_sprite = sprites.at(last_reward);
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
		reward_sprite->runAction(MoveTo::create(TRANSITION_TIME_FAST, Vec2(visible_size.width / 2 + origin.x, visible_size.height / 2 + origin.y)));
	}
}

//fuction for replace reward animation
void SpinnerScene::replaceRewardFunc()
{
	if (last_reward != ERROR)
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

int SpinnerScene::getChancesOf(int sector_num)
{
	return chances.at(sector_num);
}

int SpinnerScene::getTotalProb()
{
	return total_prob;
}

//sets probability of sector and updates total_prob
void SpinnerScene::setChancesOf(int sector_num, int new_chances)
{
	total_prob -= chances.at(sector_num);
	chances.at(sector_num) = new_chances;
	total_prob += new_chances;
}

void SpinnerScene::calcTotalProb()
{
	total_prob = accumulate(chances.begin(), chances.end(), 0);
}