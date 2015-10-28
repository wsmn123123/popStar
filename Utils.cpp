#include "Utils.h"
#include <support/CCPointExtension.h>
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <android/log.h>
#include "../../../cocos2dx/platform/android/jni/JniHelper.h"
#endif




#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define TAG_BG 1
#define TAG_FG 2

bool Utils::isUpdateNeeded = false;
bool Utils::isPreferenceChanged = false;
float Utils::xOffsetStep = 0.0f;
int Utils::xPiexlOffset = 0;
bool Utils::isPreview = false;

USING_NS_CC;

static const cocos2d::CCSize normalSize = CCSizeMake(320, 480);

extern "C"
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	
	void Java_liu_niu_wallpaper_WallpaperJNIUtils_offsetChanged(JNIEnv*  env, jobject thiz, jfloat xOffset, jfloat yOffset,
    			jfloat xOffsetStep, jfloat yOffsetStep, jint xPixelOffset,
    			jint yPixelOffset)
	{
	   CCLog("%f,%f,%f,%f,%d,%d",xOffset,yOffset,xOffsetStep,yOffsetStep,xPixelOffset,yPixelOffset);
	 //_xOffset = xOffset;
		Utils::xOffsetStep = xOffsetStep;
		Utils::xPiexlOffset = xPixelOffset;

		Utils::isUpdateNeeded = true;
	
	}

	void Java_liu_niu_wallpaper_WallpaperJNIUtils_setPreview(JNIEnv*  env, jobject thiz, jboolean isPreview)
	{
		Utils::isPreview = isPreview;
		Utils::isUpdateNeeded = true;
	}

	/*
	void Java_liu_niu_wallpaper_WallpaperJNIUtils_dateTimeChanged(JNIEnv*  env, jobject thiz,jint yy,jint mm,jint dd,jint hh,jint mi,jint ss)
	{
	   CCLog("dateTimeChanged %d,%d,%d,%d,%d,%d",yy,mm,dd,hh,mi,ss);
	   s_year = yy;
	   s_month = mm;
	   s_date = dd;
	   s_hour = hh;
	   s_minute = mi;
	   s_second = ss;
	   isUpdateNeeded = true;
	}*/

	void Java_liu_niu_wallpaper_WallpaperJNIUtils_onPreferenceChanged(JNIEnv*  env, jobject thiz)
	{
	   CCLog("Java_liu_niu_wallpaper_WallpaperJNIUtils_onPreferenceChanged");
		Utils::isUpdateNeeded = true;
		Utils::isPreferenceChanged = true;
	
	}


#endif
}

int Utils::getPreference(int keyId)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t, "liu/niu/wallpaper/WallpaperJNIUtils", "getPreference", "(I)I")) {
		
           int value = t.env->CallStaticIntMethod(t.classID, t.methodID,keyId);
            t.env->DeleteLocalRef(t.classID);
			CCLog("getPreference key: %d return : %d",keyId, value);
			return value;
        }else{
			CCLog("getPreference key: %d not found!", keyId);
		}
		#endif
		
		return -1;
}


float Utils::getDegree( cocos2d::CCPoint startPos, cocos2d::CCPoint endPos )
{
	float angle = ccpAngle(startPos,endPos);

	float dy = endPos.y - startPos.y;
	float dx = endPos.x - startPos.x;
	float dd = ccpDistance(endPos,startPos);
	angle = dx/dd;

	angle = acosf(angle);

	float degree = angle * 180.0f / 3.14f;
	if(dy < 0.0f)
	{
		degree = -degree;
	}
	return -degree;
}
cocos2d::CCPoint Utils::getWinPoint( cocos2d::CCPoint normalPoint )
{	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint winPoint;
	winPoint.x = winSize.width / normalSize.width * normalPoint.x;
	winPoint.y = winSize.height / normalSize.height * normalPoint.y;

	return winPoint;
}

cocos2d::CCPoint Utils::getWinPoint(int x,int y)
{	
	return Utils::getWinPoint(ccp(x,y));
}

void Utils::processSpritePosition(cocos2d::CCNode* sp, cocos2d::CCPoint pointInDesign)
{
	if(sp == 0) return;
	CCPoint winPoint = Utils::getWinPoint(pointInDesign);
	sp->setPosition(winPoint);
}

void Utils::processSpriteSize(cocos2d::CCNode* sp, cocos2d::CCSize sizeInDesign)
{
	if(sp == 0)return;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	float scaleWidth = winSize.width / normalSize.width;
	float scaleHeight = winSize.height / normalSize.height;
	
	CCSize sizeInWindow = CCSizeMake(scaleWidth * sizeInDesign.width, scaleHeight * sizeInDesign.height);

	sp->setScaleX(sizeInWindow.width / sp->getContentSize().width);
	sp->setScaleY(sizeInWindow.height / sp->getContentSize().height);

}

void Utils::processSpriteSize(cocos2d::CCNode* sp, cocos2d::CCSize sizeInDesign, bool scaleToMax)
{
	if(sp == 0)return;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		
	float scaleHeight = winSize.height / normalSize.width;
	float scaleWidth = winSize.width / normalSize.height;
	CCSize sizeInWindow = CCSizeMake(scaleWidth * sizeInDesign.width, scaleHeight * sizeInDesign.height);
	CCSize spSize = CCSizeMake(sp->getContentSize().width, sp->getContentSize().height);
	
	if(scaleToMax)
	{
		sp->setScale(scaleWidth>scaleHeight?scaleWidth:scaleHeight);
	}else{
		sp->setScale(scaleWidth<scaleHeight?scaleWidth:scaleHeight);
	}

}

cocos2d::CCPoint Utils::getNormalPoint( cocos2d::CCPoint winPoint )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint normalPoint;
	normalPoint.x = winPoint.x / winSize.width * normalSize.width; ///winSize.width / 480 * normalPoint.x;
	normalPoint.y = winPoint.y / winSize.height * normalSize.height; ///winSize.height / 800 * normalPoint.y;

	return normalPoint;
}


float Utils::getMinScale()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float scaleX = winSize.width / normalSize.width;
	float scaleY = winSize.height / normalSize.height;

	return MIN(scaleY,scaleX);
}

float Utils::getMaxScale()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float scaleX = winSize.width / normalSize.width;
	float scaleY = winSize.height / normalSize.height;

	return MAX(scaleY,scaleX);
}

float Utils::getScale()
{
	return Utils::getMaxScale();
}

unsigned char Utils::toHex( const unsigned char &x )
{
	return x > 9 ? x -10 + 'A': x + '0';
};

unsigned char Utils::fromHex( const unsigned char &x )
{
	return isdigit(x) ? x-'0' : x-'A'+10;
};

std::string Utils::URLEncode( const std::string &sIn )
{
	std::string sOut;
	for( size_t ix = 0; ix < sIn.size(); ix++ )
	{      
		unsigned char buf[4];
		memset( buf, 0, 4 );
		if( isalnum( (unsigned char)sIn[ix] ) )
		{      
			buf[0] = sIn[ix];
		}
		//else if ( isspace( (BYTE)sIn[ix] ) ) //貌似把空格编码成%20或者+都可以
		//{
		//    buf[0] = '+';
		//}
		else
		{
			buf[0] = '%';
			buf[1] = toHex( (unsigned char)sIn[ix] >> 4 );
			buf[2] = toHex( (unsigned char)sIn[ix] % 16);
		}
		sOut += (char *)buf;
	}
	return sOut;
}

std::string Utils::URLDecode( const std::string &sIn )
{
	std::string sOut;
	for( size_t ix = 0; ix < sIn.size(); ix++ )
	{
		unsigned char ch = 0;
		if(sIn[ix]=='%')
		{
			ch = (fromHex(sIn[ix+1])<<4);
			ch |= fromHex(sIn[ix+2]);
			ix += 2;
		}
		else if(sIn[ix] == '+')
		{
			ch = ' ';
		}
		else
		{
			ch = sIn[ix];
		}
		sOut += (char)ch;
	}
	return sOut;
}

int Utils::calLen( const char* pszText )
{
	int n = 0;
	char ch = 0;
	while ((ch = *pszText))
	{
		CC_BREAK_IF(! ch);

		if (0x80 != (0xC0 & ch))
		{
			++n;
		}
		++pszText;
	}
	return n;
}

bool Utils::checkInputCh( const char* pszText )
{
	int n = 0;
	char ch = 0;
	bool flag = true;
	while ((ch = *pszText))
	{
		if (ch == '_' || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
		{
			++n;
		}
		else
		{
			flag = false;
			break;
		}
		++pszText;
	}
	return flag;
}

int Utils::checkInputString( const char* pszStr )
{
	int len = calLen(pszStr);
	if(len < 6)
	{
		return 1;
	}
	if(len > 20)
	{
		return 2;
	}
	return 0;
}

bool Utils::isEmail( const char* pszStr )
{
	if(pszStr == 0)
	{
		return false;
	}
	std::string str(pszStr);
	if(str.find(' ') != -1)
	{
		return false;
	}
	int indexAt = str.find('@');
	if(indexAt > 0 && str.find('.') >0)
	{
		return true;
	}
	return false;
}

bool Utils::isPhone( const char* pszStr )
{
	if(pszStr == 0)
	{
		return false;
	}
	std::string str(pszStr);
	if(str.length() < 11)
	{
		return false;
	}
	if(str.find('1') == 0)
	{
		return true;
	}
	return false;
}




