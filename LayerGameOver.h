#ifndef __LayerGameOver_H__
#define __LayerGameOver_H__
#include "cocos2d.h"
USING_NS_CC;


class LayerGameOver :public CCLayer
{
public:
	static CCScene * scene();
	CREATE_FUNC(LayerGameOver);
	bool init();

	void addGameOverPicture();
	void addScoreLabel();
	void addMenu();
	void returnGame(CCObject *obj);
	void exitGame(CCObject *obj);
};


#endif