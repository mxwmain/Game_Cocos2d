#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "cocos2d.h"
USING_NS_CC;

class IColliderTest
{
public:
	virtual void collider() = 0;
	virtual void destory() = 0;
	virtual void hit() = 0;
};

class IRecycleInterface
{
public:
	virtual void recycle() = 0;
	virtual void reuse() = 0;
};

class IEnemyAniamtion {
public:
	virtual Animation* getAnimationNormal() = 0;
	virtual Animation* getAnimationHit() = 0;
	virtual Animation* getAnimationDestory() = 0;
};

#endif // !_bullet_H_
