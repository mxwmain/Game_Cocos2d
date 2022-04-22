#ifndef __ENEMY2_H__
#define __ENEMY1_H__

#include "cocos2d.h"
#include "Enemy.h"

using namespace cocos2d;

class Enemy2 : public Enemy {
public:
	static Enemy2* create();
	bool init() override;

	virtual void reuse();
	virtual void destory();
	virtual void hit();

	Animation* getAnimationNormal();
	Animation* getAnimationHit();
	Animation* getAnimationDestory();

protected:
	Enemy2();
	~Enemy2();

};



#endif // !__ENEMY2_H__

