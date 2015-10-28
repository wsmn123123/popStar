#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class PopStar;

enum GUI_EVENT_TYPE
{
	EVENT_UPDATE_SCORE,					// ˢ�·���
	EVENT_UPDATE_TARGET_SCORE,			// ˢ��Ŀ�����
	EVENT_UPDATE_LEVEL,					// ˢ�¹ؿ�
	EVENT_UPDATE_REDUCE_SCORE,			// ˢ����������
	EVENT_UPDATE_TOTAL_HISTORY_SCORE,	// ˢ����ʷ��߷�
	EVENT_UPDATE_LEVEL_HISTORY_SCORE,	// ˢ�±�����߷�
};

class PopStarLayer : public cocos2d::CCLayer
{
public:
	~PopStarLayer();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	virtual void onEnter();
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void update(float delta);

	void onGuiEvent(GUI_EVENT_TYPE event, int nValue, unsigned int uValue = 0);
    
    // implement the "static node()" method manually
    CREATE_FUNC(PopStarLayer);


public:
	cocos2d::CCLabelTTF* historyTotalScore;	// ��ʷ��߷�
	cocos2d::CCLabelTTF* historyLevelScore;	// ������߷�
	cocos2d::CCLabelTTF* gameLevel;			// �ؿ�
	cocos2d::CCLabelTTF* targetScore;		// Ŀ��
	cocos2d::CCLabelTTF* curScore;			// ����
	cocos2d::CCLabelTTF* reduceScore;

private:
	PopStar*	popStar;
};

#endif // __HELLOWORLD_SCENE_H__
