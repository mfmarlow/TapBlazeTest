#pragma once

#ifndef __PREV_SCENE_H__
#define __PREV_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"

USING_NS_CC;

class PrevScene : public Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(PrevScene);
private:
	void switchToSpinnerScene();
	void onEnter();
};

#endif // __PREV_SCENE_H__
