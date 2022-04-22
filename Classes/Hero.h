/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Interface.h"

USING_NS_CC;

class GameManager;
class Hero : public Node, public IColliderTest, public IEnemyAniamtion
{
	friend class GameManager;
public:
	CREATE_FUNC(Hero);

	bool init() override;
	void update(float dt) override;

	virtual void collider();
	virtual void destory();
	virtual void hit();

	virtual Animation* getAnimationNormal();
	virtual Animation* getAnimationHit();
	virtual Animation* getAnimationDestory();

protected:
	Hero(const std::string& filename = "image/hero1.png");
	~Hero();

public:
	bool isEnhance() { return _enhanceTime > 0;  }
	inline int hp() { return _hp; }
	inline bool isWuDi() { return _wudiTime > 0;  }

private:
	Sprite* _sprite;
	int _hp;
	float _shootTime;
	float _enhanceTime;
	float _wudiTime;
};


#endif
