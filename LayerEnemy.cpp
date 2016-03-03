#include "LayerEnemy.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool LayerEnemy::init()
{
	smallArray=CCArray::create();
	midArray=CCArray::create();
	bigArray=CCArray::create();
	smallArray->retain();
	midArray->retain();
	bigArray->retain();

	//¶¯»­ÌØÐ§
	CCAnimation *smallAnimation = CCAnimation::create();
	smallAnimation->setDelayPerUnit(0.1f);
	char nameBuf[100];
	for (int i = 0; i < 4; i++)
	{
		memset(nameBuf, 0, sizeof(nameBuf));
		sprintf(nameBuf, "enemy1_down%d.png", i + 1);
		smallAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(nameBuf));
	}

	//midEnemy Animate
	CCAnimation *midAnimation = CCAnimation::create();
	midAnimation->setDelayPerUnit(0.1f);
	//char nameBufmid[100];
	for (int i = 0; i < 4; i++)
	{
		memset(nameBuf, 0, sizeof(nameBuf));
		sprintf(nameBuf, "enemy2_down%d.png", i + 1);
		midAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(nameBuf));
	}

	CCAnimation *midHitAnimation=CCAnimation::create();
	midHitAnimation->setDelayPerUnit(0.02f);
	midHitAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_hit.png"));
	midHitAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png"));

	//bigEnemy Animate
	CCAnimation *bigAnimation = CCAnimation::create();
	bigAnimation->setDelayPerUnit(0.1f);
	//char nameBufmid[100];
	for (int i = 0; i < 6; i++)
	{
		memset(nameBuf, 0, sizeof(nameBuf));
		sprintf(nameBuf, "enemy3_down%d.png", i + 1);
		bigAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(nameBuf));
	}

	CCAnimation *bigHitAnimation=CCAnimation::create();
	bigHitAnimation->setDelayPerUnit(0.02f);
	bigHitAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_hit.png"));
	bigHitAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n2.png"));


	CCAnimationCache::sharedAnimationCache()->addAnimation(smallAnimation, "SmallBlowUp");
	CCAnimationCache::sharedAnimationCache()->addAnimation(midAnimation, "MidBlowUp");
	CCAnimationCache::sharedAnimationCache()->addAnimation(midHitAnimation, "MidHit");
	CCAnimationCache::sharedAnimationCache()->addAnimation(bigAnimation, "BigBlowUp");
	CCAnimationCache::sharedAnimationCache()->addAnimation(bigHitAnimation, "BigHit");

	schedule(schedule_selector(LayerEnemy::addSmallEnemy), 0.5f);
	schedule(schedule_selector(LayerEnemy::addMidEnemy), 3.0f);
	schedule(schedule_selector(LayerEnemy::addBigEnemy), 6.0f);
	return true;
}

void LayerEnemy::addSmallEnemy(float dt)
{
	Enemy * smallPlane = Enemy::create();
	smallPlane->bindEnemySprite(CCSprite::createWithSpriteFrameName("enemy1.png"), SMALL_MAXLIFE);
	smallArray->addObject(smallPlane);
	addChild(smallPlane);

	float x = CCRANDOM_0_1()*(winSize.width - smallPlane->getBoundingBox().size.width) + smallPlane->getBoundingBox().size.width / 2;
	float y = winSize.height + smallPlane->boundingBox().size.height / 2;

	CCPoint smallBirth = ccp(x, y);
	smallPlane->setPosition(smallBirth);
	CCMoveTo *to = CCMoveTo::create(3, ccp(smallBirth.x,
		smallBirth.y - winSize.height - smallPlane->getBoundingBox().size.height));
	CCCallFuncN * actionDone = CCCallFuncN::create(this, callfuncN_selector(LayerEnemy::smallEnemyMovefinished));
	CCSequence * sequence = CCSequence::create(to, actionDone, NULL);
	smallPlane->runAction(sequence);

}

void LayerEnemy::smallEnemyMovefinished(CCNode *node)
{
	CCSprite * smallEnemy = (CCSprite *)node;
	smallArray->removeObject(smallEnemy);
	smallEnemy->removeFromParentAndCleanup(true);
}

void LayerEnemy::smallEnemyBlowUp(Enemy * smallEnemy)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy1_down.wav");
	CCAnimate * smallAnimate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("SmallBlowUp"));
	CCCallFuncND  * actionDone = CCCallFuncND::create(this, callfuncND_selector(LayerEnemy::removeSmallEnemy), (void*)smallEnemy);
	CCSequence *sequence = CCSequence::create(smallAnimate, actionDone, NULL);
	smallEnemy->getSprite()->runAction(sequence);
}

void LayerEnemy::removeSmallEnemy(CCNode * target, void * data)
{
	Enemy * smallEnemy = (Enemy*)data;
	if (smallEnemy)
	{
		smallArray->removeObject(smallEnemy);
		smallEnemy->removeFromParentAndCleanup(true);
	}
}

void LayerEnemy::removeAllSmallEnemy()
{
	CCObject *et;
	CCARRAY_FOREACH(smallArray, et)
	{
		Enemy * enemy = (Enemy *)et;
		if (enemy->getLife() >= 1)
		{
			smallEnemyBlowUp(enemy);
		}
	}
}

void LayerEnemy::addMidEnemy(float dt)
{
	Enemy * midPlane = Enemy::create();
	midPlane->bindEnemySprite(CCSprite::createWithSpriteFrameName("enemy2.png"), MID_MAXLIFE);
	midArray->addObject(midPlane);
	addChild(midPlane);

	float x = CCRANDOM_0_1()*(winSize.width - midPlane->getBoundingBox().size.width) + midPlane->getBoundingBox().size.width / 2;
	float y = winSize.height + midPlane->boundingBox().size.height / 2;

	CCPoint midBirth = ccp(x, y);
	midPlane->setPosition(midBirth);
	CCMoveTo *to = CCMoveTo::create(3, ccp(midBirth.x,
		midBirth.y - winSize.height - midPlane->getBoundingBox().size.height));
	CCCallFuncN * actionDone = CCCallFuncN::create(this, callfuncN_selector(LayerEnemy::midEnemyMovefinished));
	CCSequence * sequence = CCSequence::create(to, actionDone, NULL);
	midPlane->runAction(sequence);
}

void LayerEnemy::midHitAnimate(Enemy *midEnemy)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy2_down.wav");
	CCAnimate * midHit = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("MidHit"));
	//CCCallFuncND  * actionDone = CCCallFuncND::create(this, callfuncND_selector(LayerEnemy::removeMidEnemy), (void*)midEnemy);
	//CCSequence *sequence = CCSequence::create(midAnimate, actionDone, NULL);
	//midEnemy->loseLife();
	midEnemy->getSprite()->runAction(midHit);
}

void LayerEnemy::midEnemyMovefinished(CCNode *node)
{
	CCSprite * midEnemy = (CCSprite *)node;
	midArray->removeObject(midEnemy);
	midEnemy->removeFromParentAndCleanup(true);
}

void LayerEnemy::midEnemyBlowUp(Enemy * midEnemy)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy2_down.wav");
	CCAnimate * midAnimate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("MidBlowUp"));
	CCCallFuncND  * actionDone = CCCallFuncND::create(this, callfuncND_selector(LayerEnemy::removeMidEnemy), (void*)midEnemy);
	CCSequence *sequence = CCSequence::create(midAnimate, actionDone, NULL);
	midEnemy->getSprite()->runAction(sequence);
}

void LayerEnemy::removeMidEnemy(CCNode * target, void * data)
{
	Enemy * midEnemy = (Enemy*)data;
	if (midEnemy)
	{
		midArray->removeObject(midEnemy);
		midEnemy->removeFromParentAndCleanup(true);
	}
}

void LayerEnemy::removeAllMidEnemy()
{
	CCObject *et;
	CCARRAY_FOREACH(midArray, et)
	{
		Enemy * enemy = (Enemy *)et;
		if (enemy->getLife() >= 1)
		{
			midEnemyBlowUp(enemy);
		}
	}
}


void LayerEnemy::addBigEnemy(float dt)
{
	Enemy * bigPlane = Enemy::create();
	bigPlane->bindEnemySprite(CCSprite::createWithSpriteFrameName("enemy3_n2.png"), BIG_MAXLIFE);
	bigArray->addObject(bigPlane);
	addChild(bigPlane);

	float x = CCRANDOM_0_1()*(winSize.width - bigPlane->getBoundingBox().size.width) + bigPlane->getBoundingBox().size.width / 2;
	float y = winSize.height + bigPlane->boundingBox().size.height / 2;

	CCPoint bigBirth = ccp(x, y);
	bigPlane->setPosition(bigBirth);
	CCMoveTo *to = CCMoveTo::create(3, ccp(bigBirth.x,
		bigBirth.y - winSize.height - bigPlane->getBoundingBox().size.height));
	CCCallFuncN * actionDone = CCCallFuncN::create(this, callfuncN_selector(LayerEnemy::bigEnemyMovefinished));
	CCSequence * sequence = CCSequence::create(to, actionDone, NULL);
	bigPlane->runAction(sequence);
}

void LayerEnemy::bigHitAnimate(Enemy *midEnemy)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy3_down.wav");
	CCAnimate * bigHit = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("BigHit"));
	//CCCallFuncND  * actionDone = CCCallFuncND::create(this, callfuncND_selector(LayerEnemy::removeMidEnemy), (void*)midEnemy);
	//CCSequence *sequence = CCSequence::create(midAnimate, actionDone, NULL);
	//midEnemy->loseLife();
	midEnemy->getSprite()->runAction(bigHit);
}

void LayerEnemy::bigEnemyMovefinished(CCNode *node)
{
	CCSprite * bigEnemy = (CCSprite *)node;
	bigArray->removeObject(bigEnemy);
	bigEnemy->removeFromParentAndCleanup(true);
}

void LayerEnemy::bigEnemyBlowUp(Enemy * bigEnemy)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy3_down.wav");
	CCAnimate * bigAnimate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("BigBlowUp"));
	CCCallFuncND  * actionDone = CCCallFuncND::create(this, callfuncND_selector(LayerEnemy::removeBigEnemy), (void*)bigEnemy);
	CCSequence *sequence = CCSequence::create(bigAnimate, actionDone, NULL);
	bigEnemy->getSprite()->runAction(sequence);
}

void LayerEnemy::removeBigEnemy(CCNode * target, void * data)
{
	Enemy * bigEnemy = (Enemy*)data;
	if (bigEnemy)
	{
		bigArray->removeObject(bigEnemy);
		bigEnemy->removeFromParentAndCleanup(true);
	}
}

void LayerEnemy::removeAllBigEnemy()
{
	CCObject *et;
	CCARRAY_FOREACH(bigArray, et)
	{
		Enemy * enemy = (Enemy *)et;
		if (enemy->getLife() >= 1)
		{
			bigEnemyBlowUp(enemy);
		}
	}
}



void LayerEnemy::removeAllEnemy()
{
	removeAllSmallEnemy();
	removeAllMidEnemy();
	removeAllBigEnemy();
}
