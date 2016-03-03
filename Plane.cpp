#include "Plane.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Plane *Plane::_splane=NULL;
Plane* Plane::getInstance()
{
	if(!_splane)
	{
		_splane=new Plane;
		if (_splane&&_splane->init())
		{

		}
	}

	return _splane;

}


bool Plane::init()
{
	CCSprite::init();
	// 用帧动画的帧来创建精灵
	this->initWithSpriteFrameName("hero1.png");
	CCBlink *blink = CCBlink::create(1, 3);
	
	//闪三次以后，开始执行动画
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Plane::animatePlane));
	CCSequence *sequence = CCSequence::create(blink, callFunc, NULL);  // 
	//CCsequence 不能打包ccrepeatforever的动作
	runAction(sequence);

	//暴炸动画缓存

	CCAnimation * animation = CCAnimation::create();
	animation->setDelayPerUnit(0.2f);
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n1.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n2.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n3.png"));

	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "PlaneBlowUp");

	return true;
}


void  Plane::animatePlane()
{
	CCAnimation *Animation = CCAnimation::create();
	Animation->setDelayPerUnit(0.2f);
	Animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
	Animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));
	CCAnimate *animate = CCAnimate::create(Animation);
	this->runAction(CCRepeatForever::create(animate));

}

void Plane::blowUp()
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/game_over.wav");
	CCAnimate *animate=CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("PlaneBlowUp"));
	CCCallFunc * actionDone = CCCallFunc::create(this, callfunc_selector(Plane::removePlane));
	CCSequence *sequence = CCSequence::create(animate, actionDone, NULL);

	this->runAction(sequence);
}

void Plane::removePlane()
{
	removeFromParent();
	CCScene * scene = LayerGameOver::scene();
	CCDirector::sharedDirector()->replaceScene(scene);
}
