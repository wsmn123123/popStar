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
	//����(startPos,endPos)��������x����ļн�,�Ƕ�
	static float getDegree(cocos2d::CCPoint startPos, cocos2d::CCPoint endPos);
/***
	*������480*800 ��Ӧ��λ��
	*������Ļ�ϵ�λ��.
	*/
	static cocos2d::CCPoint getWinPoint(cocos2d::CCPoint normalPoint);
	static cocos2d::CCPoint getWinPoint(int x,int y);

	static void processSpritePosition(cocos2d::CCNode* sp, cocos2d::CCPoint pointInDesign);
	static void processSpriteSize(cocos2d::CCNode* sp, cocos2d::CCSize sizeInDesign);
	static void processSpriteSize(cocos2d::CCNode* sp, cocos2d::CCSize sizeInDesign, bool scaleToMax);

	/**
	*����win�ϵ�λ��,
	*������480*800��Ӧ��λ��
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
	//���� ��ĸ �»���
	static bool checkInputCh(const char* pszText);

	//������������0,�������ض�Ӧ������
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