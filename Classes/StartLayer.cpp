#include "GameScene.h"
#include "GameLevel.h"

#include "StartLayer.h"
#include "Utils.h"

USING_NS_CC;


CCScene* StartLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	StartLayer *layer = StartLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StartLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	float scale = visibleSize.width/320.f;

	CCSprite* popStarBg = CCSprite::create("popstar_start.png");
	Utils::processSpritePosition(popStarBg, ccp(160, 240));
	Utils::processSpriteSize(popStarBg, CCSizeMake(320, 480));
	/*popStarBg->setPosition(ccp(160*scale, 240*scale));
	popStarBg->setScale(scale);*/
	this->addChild(popStarBg, 0);



	CCMenuItemImage* item = CCMenuItemImage::create("buttons/default/00010.png",
		"buttons/default/00010.png",
		"buttons/default/00010.png",
		this,
		menu_selector(StartLayer::onClickMenu));

	/*item->setPosition(ccp(visibleSize.width/2, visibleSize.height/3));
	item->setScale(1.0, 1.0);*/
	Utils::processSpritePosition(item, ccp(160, 160));
	Utils::processSpriteSize(item, CCSizeMake(256, 256));

	CCMenu* menu = CCMenu::create(item, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	return true;
}

void StartLayer::onClickMenu(CCObject* obj)
{
	changeLayer( this, GameLevel::create() );
}
