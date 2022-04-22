#ifndef __ENEMY3_H__
#define __ENEMY3_H__

#include "cocos2d.h"
#include "Enemy.h"

using namespace cocos2d;

class Enemy3 : public Enemy {
public:
	static Enemy3* create();
	bool init() override;

	virtual void reuse();
	virtual void destory();
	virtual void hit();

	Animation* getAnimationNormal();
	Animation* getAnimationHit();
	Animation* getAnimationDestory();

protected:
	Enemy3();
	~Enemy3();

};



#endif // !__ENEMY3_H__

