#ifndef __POPSTAR_STATE_H__
#define __POPSTAR_STATE_H__

#include "cocos2d.h"

enum POPSTAR_STATE
{
	POPSTAR_STATE_INIT,		// ��ʼ��״̬
	POPSTAR_STATE_NORMAL,	// ����״̬
	POPSTAR_STATE_PASS,		// ����״̬
	POPSTAR_STATE_OVER,		// δ����״̬
};

class PopStar;

// PopStar״̬����
class PopStarState
{
public:
	PopStarState(PopStar* ps);
	virtual ~PopStarState();

	virtual void enter() = 0;				// ��״̬������ʱִ�����
	virtual void execute(float delta) = 0;	// ״̬��������
	virtual void exit() = 0;				// ��״̬�˳�ʱִ�����

protected:
	POPSTAR_STATE	state;
	PopStar*		popStar;
	float			elapsedTime;
};

// ��Ϸ��ʼ��״̬
class GameInitState : public PopStarState
{
public:
	GameInitState(PopStar* ps);

	virtual void enter();
	virtual void execute(float delta);
	virtual void exit();
};

// ������Ϸ״̬
class GameRunningState : public PopStarState
{
public:
	GameRunningState(PopStar* ps);

	virtual void enter();
	virtual void execute(float delta);
	virtual void exit();
};

class GamePassLevelState : public PopStarState
{
public:
	GamePassLevelState(PopStar* ps);

	virtual void enter();
	virtual void execute(float delta);
	virtual void exit();
};

class GameOverState : public PopStarState
{
public:
	GameOverState(PopStar* ps);

	virtual void enter();
	virtual void execute(float delta);
	virtual void exit();
};

#endif // __POPSTAR_STATE_H__
