#include "PrevScene.h"
#include "SpinnerScene.h"


Scene* PrevScene::createScene()
{
	return PrevScene::create();
}

bool PrevScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	return true;
}

void PrevScene::onEnter()
{
	switchToSpinnerScene();
}

void PrevScene::switchToSpinnerScene()
{
	//set up data structures to create custom spinner
	vector<string> sprites = { "heart.png", "brush.png", "gem.png", "hammer.png", "coin.png", "brush.png", "gem.png", "hammer.png" };
	vector<string> labels = { "30 min", "x3", "x35", "x3", "x750", "x1", "x75", "x1" };
	vector<int> chances = { 20, 10, 10, 10, 5, 20, 5, 20 };
	// go to spinner scene with these prizes
	auto scene = SpinnerScene::createScene(sprites, labels, chances);
	Director::getInstance()->replaceScene(scene);
}