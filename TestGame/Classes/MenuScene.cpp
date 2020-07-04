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
	back_button->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height*0.85 + origin.y));
	this->addChild(back_button,0);
	back_button->addTouchEventListener(CC_CALLBACK_2(MenuScene::touchEvent, this));

	return true;
}

void MenuScene::touchEvent(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->popScene();
	}
}