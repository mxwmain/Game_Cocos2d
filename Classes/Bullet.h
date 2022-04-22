#ifndef _bullet_H_
#define _bullet_H_

#include "cocos2d.h"
#include "Interface.h"
using namespace cocos2d;

class Bullet : public Node , public IRecycleInterface{
public:
	CREATE_FUNC(Bullet);

	bool init() override;
	void onEnter() override;
	void onExit() override;
	void update(float dt) override;

	virtual void recycle();
	virtual void reuse();
	virtual void collider();

protected:
	Bullet(const std::string& filename = "image/bullet1.png");
	~Bullet();

protected:
	Sprite* _sprite;
	Vec2 _speed;
};

#endif // !_bullet_H_
