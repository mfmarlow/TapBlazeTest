#include "MenuScene.h"

Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto back_button = Button::create("spin_button.png");
	back_button->setTitleText("back");
	back_button->setTitleFontSize(20);
	back_button->getTitleLabel()->enableOutline(Color4B::BLACK, 1);
	back_button->getTitleLabel()->setPosition(Vec2(back_button->getBoundingBox().size.width / 2, back_button->getBoundingBox().size.height * 0.55));
	back_button->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 0.85 + origin.y));
	this->addChild(back_button, 0);
	back_button->addTouchEventListener(CC_CALLBACK_2(MenuScene::touchEvent, this));

	//Textfields to edit the probabilities of sectors
	auto sector_1_field = LiveTextField::createWith("P(sector 1): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.75 + origin.y), SpinnerScene::p_sector_1, TF_1_TAG);
	sector_1_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_2_field = LiveTextField::createWith("P(sector 2): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.70 + origin.y), SpinnerScene::p_sector_2, TF_2_TAG);
	sector_2_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_3_field = LiveTextField::createWith("P(sector 3): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.65 + origin.y), SpinnerScene::p_sector_3, TF_3_TAG);
	sector_3_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_4_field = LiveTextField::createWith("P(sector 4): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.60 + origin.y), SpinnerScene::p_sector_4, TF_4_TAG);
	sector_4_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_5_field = LiveTextField::createWith("P(sector 5): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.55 + origin.y), SpinnerScene::p_sector_5, TF_5_TAG);
	sector_5_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_6_field = LiveTextField::createWith("P(sector 6): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.50 + origin.y), SpinnerScene::p_sector_6, TF_6_TAG);
	sector_6_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_7_field = LiveTextField::createWith("P(sector 7): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.45 + origin.y), SpinnerScene::p_sector_7, TF_7_TAG);
	sector_7_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	auto sector_8_field = LiveTextField::createWith("P(sector 8): ", this, Vec2(visibleSize.width * 0.33 + origin.x, visibleSize.height * 0.40 + origin.y), SpinnerScene::p_sector_8, TF_8_TAG);
	sector_8_field->getTextField()->addEventListener(CC_CALLBACK_2(MenuScene::fieldEvent, this));

	return true;
}

void MenuScene::touchEvent(Ref* sender, Widget::TouchEventType type)
{
	//if the probabilities add to [0,100], enable the back button
	if(SpinnerScene::p_sector_sum >= 0 && SpinnerScene::p_sector_sum <= 100 && type == Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->popScene();
	}
}

void MenuScene::fieldEvent(Ref* sender, TextField::EventType type)
{
	//capture the sending field
	TextField* txt_field = (TextField*)sender;

	//if done entering
	if (type == TextField::EventType::DETACH_WITH_IME)
	{
		//get the user's input
		string input_string = txt_field->getString();
		//try converting to int
		try
		{
			int input = stoi(input_string);
			switch (txt_field->getTag())
			{
			case TF_1_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_1;
				SpinnerScene::p_sector_1 = input;
				break;
			case TF_2_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_2;
				SpinnerScene::p_sector_2 = input;
				break;
			case TF_3_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_3;
				SpinnerScene::p_sector_3 = input;
				break;
			case TF_4_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_4;
				SpinnerScene::p_sector_4 = input;
				break;
			case TF_5_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_5;
				SpinnerScene::p_sector_5 = input;
				break;
			case TF_6_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_6;
				SpinnerScene::p_sector_6 = input;
				break;
			case TF_7_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_7;
				SpinnerScene::p_sector_7 = input;
				break;
			case TF_8_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_8;
				SpinnerScene::p_sector_8 = input;
				break;
			default:
				break;
			}
			//update p_sector_sum
			SpinnerScene::p_sector_sum += input;
		}
		//if the input doesnt translate to an int,
		catch (...)
		{
			//log bad input and invalidate.
			
			log("Bad input");

			switch (txt_field->getTag())
			{
			case TF_1_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_1;
				SpinnerScene::p_sector_1 = 999;
				break;
			case TF_2_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_2;
				SpinnerScene::p_sector_2 = 999;
				break;
			case TF_3_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_3;
				SpinnerScene::p_sector_3 = 999;
				break;
			case TF_4_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_4;
				SpinnerScene::p_sector_4 = 999;
				break;
			case TF_5_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_5;
				SpinnerScene::p_sector_5 = 999;
				break;
			case TF_6_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_6;
				SpinnerScene::p_sector_6 = 999;
				break;
			case TF_7_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_7;
				SpinnerScene::p_sector_7 = 999;
				break;
			case TF_8_TAG:
				SpinnerScene::p_sector_sum -= SpinnerScene::p_sector_8;
				SpinnerScene::p_sector_8 = 999;
				break;
			default:
				break;
			}
			//update p_sector_sum
			SpinnerScene::p_sector_sum += 999;
		}
		
	}
}