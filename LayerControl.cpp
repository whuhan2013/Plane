#include "LayerControl.h"
#include "Plane.h"
#include "SimpleAudioEngine.h"

#define  winSize   CCDirector::sharedDirector()->getWinSize()
using namespace CocosDenshion;
bool LayerControl::init()
{
	CCSprite * nor = CCSprite::createWithSpriteFrameName("game_pause_nor.png");
	CCSprite * press = CCSprite::createWithSpriteFrameName("game_pause_pressed.png");
	pauseMenuItem = CCMenuItemSprite::create(nor, press, this, menu_selector(LayerControl::menuCallBack));
	CCPoint menuBirth = ccp(pauseMenuItem->getContentSize().width / 2 + 10, winSize.height - pauseMenuItem->getContentSize().height / 2 - 10);
	pauseMenuItem->setPosition(menuBirth);
	CCMenu *pauseMenu = CCMenu::create(pauseMenuItem, NULL);
	pauseMenu->setPosition(CCPointZero);
	addChild(pauseMenu);

	scoreItem = CCLabelBMFont::create("0", "font/font.fnt");
	scoreItem->setColor(ccc3(143, 146, 147));
	scoreItem->setAnchorPoint(ccp(0, 0.5));
	scoreItem->setPosition(ccp(pauseMenuItem->getPositionX() + nor->getContentSize().width / 2 + 5, pauseMenuItem->getPositionY()));

	addChild(scoreItem);

	return true;
}

void LayerControl::menuCallBack(CCObject *obj)
{
	if (!CCDirector::sharedDirector()->isPaused())
	{
		pauseMenuItem->setNormalImage(CCSprite::createWithSpriteFrameName("game_resume_nor.png"));
		pauseMenuItem->setSelectedImage(CCSprite::createWithSpriteFrameName("game_resume_pressed.png"));
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		CCDirector::sharedDirector()->pause();
		((CCLayer*)(Plane::getInstance()->getParent()))->setTouchEnabled(false);
	}
	else
	{
		pauseMenuItem->setNormalImage(CCSprite::createWithSpriteFrameName("game_pause_nor.png"));
		pauseMenuItem->setSelectedImage(CCSprite::createWithSpriteFrameName("game_pause_pressed.png"));
		CCDirector::sharedDirector()->resume();
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.wav");
		((CCLayer*)(Plane::getInstance()->getParent()))->setTouchEnabled(true);
	}
}


void LayerControl::updataScore(int score)
{
	CCString *strScore = CCString::createWithFormat("%d", score);
	scoreItem->setCString(strScore->getCString());
}