#ifndef __SPINNER_SCENE_H__
#define __SPINNER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include <time.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>

using namespace std;
USING_NS_CC;
using namespace cocos2d::ui;

class SpinnerScene : public Scene
{
public:
	static Scene* createScene(vector<string> new_sprite_imgs, vector<string> new_labels, vector<int> new_chances);
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(SpinnerScene);

	//public members for keeping track of probability of sectors
	vector<int> chances;
	int p_sector_sum = 100;

private:
	//sprites that need class scope
	cocos2d::Sprite* sectors;
	cocos2d::Sprite* arrow;
	cocos2d::Sprite* border;
	vector<Sprite*> sprites;

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

	//spinner info
	vector<string> sprite_imgs;
	vector<string> labels;


	//private methods
	void touchEvent(Ref* sender, Widget::TouchEventType type);
	Sprite* addSectorSprite(string image, int sector);
	void addLabelWithQuantity(Sprite* sprite, string label_text);
	float getGoalAngle();
	void runSpinTest();
	void populateSectors();
	void showRewardFunc();
	void replaceRewardFunc();

	//private actions
	ScaleTo* hide, * show;
	CallFunc* removeWheel, * showWheel, * changeToClaim, * changeToSpin, * showReward, * replaceReward;

};

#endif // __SPINNER_SCENE_H__
