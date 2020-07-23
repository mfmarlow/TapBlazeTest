#include "MenuScene.h"

Scene* MenuScene::createScene(SpinnerScene* new_spinner_scene)
{
	auto scene = MenuScene::create();
	scene->spinner_scene = new_spinner_scene;
	scene->populateTextFields();
	return scene;
}

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visible_size = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	tags = { TF_1_TAG, TF_2_TAG, TF_3_TAG, TF_4_TAG, TF_5_TAG, TF_6_TAG, TF_7_TAG, TF_8_TAG };

	//Back button to return to wheel scene
	back_button = Button::create("spin_button.png");
	back_button->setTitleText("Back");
	back_button->setTitleFontSize(20);
	back_button->getTitleLabel()->enableOutline(Color4B::BLACK, 1);
	back_button->getTitleLabel()->setPosition(Vec2(back_button->getBoundingBox().size.width / 2, back_button->getBoundingBox().size.height * 0.55));
	back_button->setPosition(Vec2(visible_size.width / 2 + origin.x, visible_size.height * 0.85 + origin.y));
	this->addChild(back_button, 0);
	back_button->addTouchEventListener(CC_CALLBACK_2(MenuScene::touchEvent, this));

	//warning text to appear if total_prob is not in [0,100]
	warning = Label::createWithSystemFont("Total probability not in [0,100]", "Arial", 15);
	warning->setColor(Color3B::RED);
	warning->setPosition(Vec2(visible_size.width * 0.5 + origin.x, visible_size.height * 0.10 + origin.y));
	warning->setOpacity(0);
	this->addChild(warning, 0);

	return true;
}

void MenuScene::touchEvent(Ref* sender, Widget::TouchEventType type)
{
	//if the total_prob is in [0,100], enable the back button
	if (spinner_scene->getTotalProb() >= 0 && spinner_scene->getTotalProb() <= 100 && type == Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->popScene();
	}
	//if the total_prob is not in [0,100], show a warning message
	else if (type == Widget::TouchEventType::ENDED)
	{
		warning->setOpacity(255);
		warning->runAction(FadeOut::create(TRANSITION_TIME_SLOW));
	}
}

//handles when text field is exited
void MenuScene::fieldEvent(Ref* sender, TextField::EventType type)
{
	//capture the sending field and tag
	TextField* txt_field = (TextField*)sender;
	int field_tag = txt_field->getTag();

	//get the sector number from the field tag

	vector<int>::iterator itr = find(tags.begin(), tags.end(), field_tag);
	int sector_num = distance(tags.begin(), itr);

	//if done entering
	if (type == TextField::EventType::DETACH_WITH_IME)
	{
		//get the user's input
		string input_string = txt_field->getString();
		//if the user doesnt enter anything, simply return
		if (input_string == "")
		{
			return;
		}
		//try converting string to int
		try
		{
			int input = stoi(input_string);

			//update prob for appropriate sector
			spinner_scene->setChancesOf(sector_num, input);
		}
		//if the input doesnt translate to an int,
		catch (...)
		{
			//log bad input
			log("Bad input");

			//invalidate the probability for that field
			spinner_scene->setChancesOf(sector_num, ERROR);
		}

	}
}

void MenuScene::populateTextFields()
{
	for (int x = 0; x < SECTOR_COUNT; x++)
	{
		auto sector_field = LiveTextField::createWith("P(sector" + to_string(x + 1) + "): ", this, Vec2(visible_size.width * 0.33 + origin.x, visible_size.height * (FIELD_STARTING_HEIGHT - x * FIELD_SEPARATION) + origin.y), spinner_scene->getChancesOf(x), tags.at(x));
		sector_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));
	}
}