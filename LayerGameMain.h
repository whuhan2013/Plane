#ifndef __LayerGameMain_H__
#define __LayerGameMain_H__
#include "cocos2d.h"
#include "Plane.h"
#include "LayerGameStart.h"
#include "LayerBullet.h"
#include "LayerEnemy.h"
#include "LayerControl.h"
#include "LayerFood.h"
#include "LayerGameOver.h"
USING_NS_CC;

const int  SMALL_SCORE = 1000;
const int  MID_SCORE = 6000;
const int  BIG_SCORE = 30000;

const int MAX_BIGBOOM_COUNT = 100000;
const int TAG_BIGBOOM = 1000;
const int TAG_BIGBOOMCOUNT = 2000;
class LayerGameMain :public CCLayer
{
public:
	static CCScene * scene();
	CREATE_FUNC(LayerGameMain);
	bool init();
	//加载主场景背景
	void addBackGround();
	//背景动起来
	void movingBackGround(float dt);
	void addHero();
	void addBulletLayer();
	void addEnemyLayer();
	void addCtrlLayer();
	void addFoodLayer();

	void updateBigBoomCount(int bigBoomCount);

	void boomMenuCallBack(CCObject * obj);
	enum BACKGROUND
	{
		BACK1, BACK2
	};
	void update(float dt);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	LayerBullet  * _bulletLayer;
	LayerEnemy   * _enemyLayer;
	LayerControl * _ctrlLayer;
	LayerFood    * _foodLayer;
	static int score;
	static void setScore(int num);
	int bigBoomCount;
	
};


#endif