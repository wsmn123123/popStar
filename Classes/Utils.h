#ifndef __UTILS_H__
#define __UTILS_H__
#include <cocoa/CCGeometry.h>
#include <string>
#include <iostream>
#include <sstream>

NS_CC_BEGIN
	class CCSprite;

	
NS_CC_END

class Utils
{
public:
	//两点(startPos,endPos)的向量和x正向的夹角,角度
	static float getDegree(cocos2d::CCPoint startPos, cocos2d::CCPoint endPos);
/***
	*传入与480*800 对应的位置
	*返回屏幕上的位置.
	*/
	static cocos2d::CCPoint getWinPoint(cocos2d::CCPoint normalPoint);
	static cocos2d::CCPoint getWinPoint(int x,int y);

	static void processSpritePosition(cocos2d::CCNode* sp, cocos2d::CCPoint pointInDesign);
	static void processSpriteSize(cocos2d::CCNode* sp, cocos2d::CCSize sizeInDesign);
	static void processSpriteSize(cocos2d::CCNode* sp, cocos2d::CCSize sizeInDesign, bool scaleToMax);

	/**
	*传入win上的位置,
	*返回与480*800对应的位置
	*
	*/
	static cocos2d::CCPoint getNormalPoint(cocos2d::CCPoint winPoint);

	static float getMinScale();
	static float getMaxScale();
	static float getScale();

	static unsigned char toHex(const unsigned char &x);

	static unsigned char fromHex(const unsigned char &x);

	static  std::string URLEncode(const std::string &sIn);

	static std::string URLDecode(const std::string &sIn);

	static int calLen(const char* pszText);
	//数字 字母 下划线
	static bool checkInputCh(const char* pszText);

	//满足条件返回0,其他返回对应的数字
	static int checkInputString(const char* pszStr);
	static bool isEmail(const char* pszStr);
	static bool isPhone(const char* pszStr);


	static int getPreference(int keyId);

public:
	static bool isUpdateNeeded;
	static bool isPreferenceChanged;
	static float xOffsetStep;
	static int xPiexlOffset;
	static bool isPreview;
protected:
	
private:
	Utils();
};




#endif