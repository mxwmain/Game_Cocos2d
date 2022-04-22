#ifndef __ENEMY1_H__
#define __ENEMY1_H__

#include "cocos2d.h"
#include "Enemy.h"

using namespace cocos2d;

class Enemy1 : public Enemy {
public:
	static Enemy1* create();
	bool init() override;

	//virtual void recycle();
	virtual void reuse();

	virtual void destory();
	virtual void hit();

	Animation* getAnimationNormal();
	Animation* getAnimationHit();
	Animation* getAnimationDestory();

protected:
	Enemy1();
	~Enemy1();

};



#endif // !__ENEMY1_H__

