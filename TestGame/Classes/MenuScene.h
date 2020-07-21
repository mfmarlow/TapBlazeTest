#pragma once

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "SpinnerScene.h"
#include "LiveTextField.h"

using namespace std;
USING_NS_CC;
using namespace ui;

class MenuScene : public Scene
{
public:
	static Scene* createScene(SpinnerScene* prev_scene);
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene);
private:
	void touchEvent(Ref* sender, Widget::TouchEventType type);
	void fieldEvent(Ref* sender, TextField::EventType type);
	SpinnerScene* spinner_scene;
};

#endif // __MENU_SCENE_H__
