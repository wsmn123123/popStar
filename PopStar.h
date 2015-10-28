#ifndef __POPSTAR_H__
#define __POPSTAR_H__

#include "cocos2d.h"

class PopStarLayer;
class Star;

struct SelectStar
{
	int		row;
	int		col;
	Star*	star;
};

class PopStarState;

class PopStar : public cocos2d::CCNode
{
	enum
	{
		ROW_NUM = 10, // ����
		COL_NUM = 10, // ����

		REVERSE_NUM = 100, // Ԥ�����������
	};

	typedef std::list<SelectStar>	StarList;
	typedef StarList::iterator		StarListIter;

public:
	PopStar(PopStarLayer* layer);
	virtual ~PopStar();

	static PopStar* create(PopStarLayer* layer);
	bool init();

	void onClick(const cocos2d::CCPoint& pos);
	void onUpdate(float delta);

	void setScore(int score); // ���õ�ǰ����
	void setLevel(int level);
	void setHistoryScore(int score);
	void setHistoryLevelScore(int score);
	void setTargetScore(int score);

	bool isLevelEnd();			// �����Ƿ����
	bool isGameOver();			// ��Ϸ�Ƿ����

	void changeState(PopStarState* newState);
	bool isInitFinish();		// �Ƿ��ʼ�����

	int  getLeftStarNum();		// ��ȡʣ���������
	void clearStarsOneByOne();
	void gotoNextLevel();		// ������һ��
	void gotoStartLayer();		// ���ص���ʼ

private:
	void onReduce();
	void onSelect(const SelectStar& selectStar);
	void clearSelectStars();
	bool isNeedHoriAdjust();	// �Ƿ���Ҫˮƽ����
	int  getCheckEndCol();		// ��ȡ��Ҫˮƽ�������������

private:
	PopStarLayer*	gameLayer;
	Star*			stars[ROW_NUM][COL_NUM];
	StarList		selectStars;

	PopStarState*	currentState;
	float			elapsedTime;
};

#endif // __POPSTAR_H__
