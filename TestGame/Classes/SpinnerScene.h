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

	//getters and setters
	int getChancesOf(int sector_num);
	int getTotalProb();
	void setChancesOf(int sector_num, int new_chances);

private:
	//sprites
	cocos2d::Sprite* sectors, *arrow, *border;
	vector<Sprite*> sprites;

	//keep track of reward sprite info 
	int last_reward = ERROR;
	Sprite* reward_sprite;
	Vec2 reward_position;
	float reward_rotation, reward_scale;

	//reward info for display
	vector<string> sprite_imgs, labels;

	//probabilities
	vector<int> chances;
	int total_prob = 100;

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
