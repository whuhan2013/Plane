#include "LayerBullet.h"
#include "Plane.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool LayerBullet::init()
{
	CCLayer::init();
	_bulletArray=CCArray::create();
	_bulletArray->retain();

	_bulletBatchNode=CCSpriteBatchNode::create("ui/shoot.png");
	addChild(_bulletBatchNode);

	startShoot();

	return true;
}

void LayerBullet::startShoot()
{
	schedule(schedule_selector(LayerBullet::addBulletCallback), 0.3f);
}
void LayerBullet::stopShoot()
{
	unschedule(schedule_selector(LayerBullet::addBulletCallback));
}

void LayerBullet::addBulletCallback(float dt)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.wav");
	//在另一个层中获得飞机的单例
	Plane *hero=Plane::getInstance();
	CCPoint birthPlace = hero->getPosition() + ccp(0, hero->getContentSize().height / 2 + 2);
	CCSprite * bullet = CCSprite::createWithSpriteFrameName("bullet1.png");
	bullet->setPosition(birthPlace);
	_bulletBatchNode->addChild(bullet);
	_bulletArray->addObject(bullet);

	float ditance = winSize.height - hero->getPositionY() - hero->getContentSize().height / 2;
	float velocity = 800 / 1;
	float movedt = ditance / velocity;

	CCMoveTo *to = CCMoveTo::create(movedt, ccp(birthPlace.x, winSize.height + bullet->getContentSize().height));
	CCCallFuncN * actionDone = CCCallFuncN::create(this, callfuncN_selector(LayerBullet::bulletMoveFinished));

	CCSequence * sequence = CCSequence::create(to, actionDone, NULL);

	bullet->runAction(sequence);
}


void LayerBullet::bulletMoveFinished(CCNode* node)
{
	CCSprite * bullet = (CCSprite*)node;
	_bulletBatchNode->removeChild(bullet, true);
	_bulletArray->removeObject(bullet);
}


void LayerBullet::removeBullet(CCSprite* bullet)
{
	_bulletBatchNode->removeChild(bullet, true);
	_bulletArray->removeObject(bullet);
}


