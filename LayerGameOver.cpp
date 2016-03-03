#include "LayerGameOver.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "LayerGameMain.h"
#include "LayerGameStart.h"
using namespace CocosDenshion;


#define  loadMusic() CocosDenshion::SimpleAudioEngine::sharedEngine()

CCScene * LayerGameOver::scene()
{
	CCScene * scene = CCScene::create();
	LayerGameOver * layer = LayerGameOver::create();
	scene->addChild(layer);

	return scene;
}
bool LayerGameOver::init()
{
	CCLayer::init();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	addGameOverPicture();
	addScoreLabel();
	addMenu();
    return true;
}

void LayerGameOver::addGameOverPicture()
{
	CCSprite * background = CCSprite::createWithSpriteFrameName("gameover.png");
	background->setAnchorPoint(ccp(0, 0));
	background->setPosition(ccp(0, -30));
	addChild(background);
}

void LayerGameOver::addScoreLabel()
{
	CCLabelBMFont * scoreItem=CCLabelBMFont::create("0", "font/font.fnt");
	scoreItem->setColor(ccc3(143, 146, 147));
	scoreItem->setAnchorPoint(ccp(0.5, 0.5));
	scoreItem->setPosition(ccp(winSize.width/2, winSize.height/2));
	int score=LayerGameMain::score;
	CCLOG("the score is%d",score);
	CCString *strScore = CCString::createWithFormat("%d", score);
	scoreItem->setCString(strScore->getCString());
	addChild(scoreItem);
}

void LayerGameOver::addMenu()
{
	//CCSprite * returnGame1 = CCSprite::createWithSpriteFrameName("btn_finish.png");
	//CCSprite * returnGame2 = CCSprite::createWithSpriteFrameName("shoot_copyright.png");
	//CCMenuItemSprite * returnItem = CCMenuItemSprite::create(returnGame1, returnGame2, this, menu_selector(LayerGameOver::returnGame));
	//CCMenuItemSprite * exitItem = CCMenuItemSprite::create(returnGame2, returnGame1, this, menu_selector(LayerGameOver::exitGame));
	////boomItem->setPosition();
	//CCMenu * Menu = CCMenu::create();
	//Menu->addChild(returnItem);
	////Menu->addChild(exitItem);
	//Menu->setPosition(ccp(winSize.width/2, winSize.height/2-30));
	//Menu->alignItemsVerticallyWithPadding(30);
	//addChild(Menu);

	CCMenuItem *returnItem=CCMenuItemFont::create("Redo",this,menu_selector(LayerGameOver::returnGame));
	CCMenuItem *exitItem=CCMenuItemFont::create("Exit",this,menu_selector(LayerGameOver::exitGame));
	
	
	CCMenu *menu=CCMenu::create(returnItem,exitItem,NULL);
	menu->setPosition(ccp(winSize.width/2, winSize.height/2-80));
	menu->alignItemsVerticallyWithPadding(30);
	addChild(menu);
}

void LayerGameOver::returnGame(CCObject *obj)
{
	LayerGameMain::setScore(0);
	CCScene * scene = LayerGameMain::scene();
	CCDirector::sharedDirector()->replaceScene(scene);
}

void LayerGameOver::exitGame(CCObject *obj)
{
	exit(1);
}
