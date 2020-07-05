#ifndef __SPINNER_SCENE_H__
#define __SPINNER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include <time.h>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;
USING_NS_CC;
using namespace cocos2d::ui;

class SpinnerScene : public Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(SpinnerScene);

	//static members for keeping track of probability of sectors
	//set probabilities to default values
	int p_sector_1 = P_SECTOR_1_DEF;
	int p_sector_2 = P_SECTOR_2_DEF;
	int p_sector_3 = P_SECTOR_3_DEF;
	int p_sector_4 = P_SECTOR_4_DEF;
	int p_sector_5 = P_SECTOR_5_DEF;
	int p_sector_6 = P_SECTOR_6_DEF;
	int p_sector_7 = P_SECTOR_7_DEF;
	int p_sector_8 = P_SECTOR_8_DEF;
	int p_sector_sum = 100;

private:
	//sprites that need class scope
	cocos2d::Sprite* sectors;
	cocos2d::Sprite* arrow;
	cocos2d::Sprite* border;
	cocos2d::Sprite* sprite_1;
	cocos2d::Sprite* sprite_2;
	cocos2d::Sprite* sprite_3;
	cocos2d::Sprite* sprite_4;
	cocos2d::Sprite* sprite_5;
	cocos2d::Sprite* sprite_6;
	cocos2d::Sprite* sprite_7;
	cocos2d::Sprite* sprite_8;
	cocos2d::Sprite* rewards[8];

	//keep track of sector limits (for deciding reward)
	int sector_limit_1;
	int sector_limit_2;
	int sector_limit_3;
	int sector_limit_4;
	int sector_limit_5;
	int sector_limit_6;
	int sector_limit_7;
	int sector_limit_8;
	int last_reward = 0;

	//keep track of reward info 
	Sprite* reward_sprite;
	Vec2 reward_position;
	float reward_rotation;
	float reward_scale;

	//private methods
	void touchEvent(Ref* sender, Widget::TouchEventType type);
	Sprite* addSectorSprite(string image, int sector);
	void addLabelWithQuantity(Sprite* sprite, string label_text);
	void calculateSectorLimits();
	float getGoalAngle();

	void runSpinTest();
};

#endif // __SPINNER_SCENE_H__
