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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//Back button to return to wheel scene
	auto back_button = Button::create("spin_button.png");
	back_button->setTitleText("Back");
	back_button->setTitleFontSize(20);
	back_button->getTitleLabel()->enableOutline(Color4B::BLACK, 1);
	back_button->getTitleLabel()->setPosition(Vec2(back_button->getBoundingBox().size.width / 2, back_button->getBoundingBox().size.height * 0.55));
	back_button->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 0.85 + origin.y));
	this->addChild(back_button, 0);
	back_button->addTouchEventListener(CC_CALLBACK_2(MenuScene::touchEvent, this));



	return true;
}

void MenuScene::touchEvent(Ref* sender, Widget::TouchEventType type)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//if the probabilities add to [0,100], enable the back button
	if (spinner_scene->p_sector_sum >= 0 && spinner_scene->p_sector_sum <= 100 && type == Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->popScene();
	}
	//if the P(reward) is not in [0,100], show a warning message
	else if (type == Widget::TouchEventType::ENDED)
	{
		auto warning = Label::createWithSystemFont("P(reward) not in [0,100]", "Arial", 20);
		warning->setColor(Color3B::RED);
		warning->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.30 + origin.y));
		this->addChild(warning);
		warning->runAction(FadeOut::create(TRANSITION_TIME_SLOW));
	}
}

//handles when text field is exited
void MenuScene::fieldEvent(Ref* sender, TextField::EventType type)
{
	//capture the sending field
	TextField* txt_field = (TextField*)sender;

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
			//depending on which textfield called, update
			switch (txt_field->getTag())
			{
			case TF_1_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[0];
				spinner_scene->chances[0] = input;
				break;
			case TF_2_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[1];
				spinner_scene->chances[1] = input;
				break;
			case TF_3_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[2];
				spinner_scene->chances[2] = input;
				break;
			case TF_4_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[3];
				spinner_scene->chances[3] = input;
				break;
			case TF_5_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[4];
				spinner_scene->chances[4] = input;
				break;
			case TF_6_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[5];
				spinner_scene->chances[5] = input;
				break;
			case TF_7_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[6];
				spinner_scene->chances[6] = input;
				break;
			case TF_8_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[7];
				spinner_scene->chances[7] = input;
				break;
			default:
				break;
			}
			//update p_sector_sum
			spinner_scene->p_sector_sum += input;
		}
		//if the input doesnt translate to an int,
		catch (...)
		{
			//log bad input and invalidate.

			log("Bad input");

			switch (txt_field->getTag())
			{
			case TF_1_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[0];
				spinner_scene->chances[0] = ERROR;
				break;
			case TF_2_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[1];
				spinner_scene->chances[1] = ERROR;
				break;
			case TF_3_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[2];
				spinner_scene->chances[2] = ERROR;
				break;
			case TF_4_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[3];
				spinner_scene->chances[3] = ERROR;
				break;
			case TF_5_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[4];
				spinner_scene->chances[4] = ERROR;
				break;
			case TF_6_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[5];
				spinner_scene->chances[5] = ERROR;
				break;
			case TF_7_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[6];
				spinner_scene->chances[6] = ERROR;
				break;
			case TF_8_TAG:
				spinner_scene->p_sector_sum -= spinner_scene->chances[7];
				spinner_scene->chances[7] = ERROR;
				break;
			default:
				break;
			}
			//update p_sector_sum
			spinner_scene->p_sector_sum += ERROR;
		}

	}
}

void MenuScene::populateTextFields()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//Textfields to edit the probabilities of sectors
	auto sector_1_field = LiveTextField::createWith("P(sector 1): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.75 + origin.y), spinner_scene->chances[0], TF_1_TAG);
	sector_1_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_2_field = LiveTextField::createWith("P(sector 2): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.70 + origin.y), spinner_scene->chances[1], TF_2_TAG);
	sector_2_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_3_field = LiveTextField::createWith("P(sector 3): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.65 + origin.y), spinner_scene->chances[2], TF_3_TAG);
	sector_3_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_4_field = LiveTextField::createWith("P(sector 4): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.60 + origin.y), spinner_scene->chances[3], TF_4_TAG);
	sector_4_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_5_field = LiveTextField::createWith("P(sector 5): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.55 + origin.y), spinner_scene->chances[4], TF_5_TAG);
	sector_5_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_6_field = LiveTextField::createWith("P(sector 6): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.50 + origin.y), spinner_scene->chances[5], TF_6_TAG);
	sector_6_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_7_field = LiveTextField::createWith("P(sector 7): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.45 + origin.y), spinner_scene->chances[6], TF_7_TAG);
	sector_7_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_8_field = LiveTextField::createWith("P(sector 8): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.40 + origin.y), spinner_scene->chances[7], TF_8_TAG);
	sector_8_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));
}