#include "Enemy1.h"
#include "GameManager.h"
#include "GameAudio.h"
USING_NS_CC;

Enemy1* Enemy1::create() {
	Enemy1* enemy = new (std::nothrow)Enemy1();

	if (enemy && enemy->init()) {
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

Enemy1::Enemy1():Enemy("image/enemy0.png", 1) {

}

Enemy1::~Enemy1() {

}

bool Enemy1::init() {
	if (!Enemy::init()) return false;

	return true;
}

//void Enemy1::recycle() {
//	GameManager::instance()->recycleEnemy(this);
//	this->removeFromParent();
//}

void Enemy1::reuse() {
	_currentHP = _hp;
	this->setPosition(random(50, 300), 1000);
	auto animation = this->getAnimationNormal();
	this->_sprite->runAction(RepeatForever::create(Animate::create(animation)));
}

void Enemy1::destory() {
	this->_sprite->stopAllActions();

	auto animation = this->getAnimationDestory();
	auto callback = CallFunc::create([this]() {
		this->recycle();
		GameManager::instance()->addScore(this->_score);
	});
	auto seq = Sequence::create(Animate::create(animation), callback, nullptr);
	this->_sprite->runAction(seq);
	GameAudio::playEnemyDown();
}
void Enemy1::hit() {

}

Animation* Enemy1::getAnimationNormal() {
	Animation* animation = AnimationCache::getInstance()->getAnimation("enemy0-normal");
	if (!animation) {
		Vector<SpriteFrame*> frames;
		char file[100];
		for (int i = 1; i <= 1; ++i) {
			sprintf(file, "image/enemy0.png");
			auto sprite = Sprite::create(file);
			frames.pushBack(sprite->getSpriteFrame());
		}
		animation = Animation::createWithSpriteFrames(frames, 0.1);
		AnimationCache::getInstance()->addAnimation(animation, "enemy0-normal");
	}

	return animation;
}

Animation* Enemy1::getAnimationHit() {
	return nullptr;
}

Animation* Enemy1::getAnimationDestory() {
	Animation* animation = AnimationCache::getInstance()->getAnimation("enemy0-destory");
	if (!animation) {
		Vector<SpriteFrame*> frames;
		char file[100];
		for (int i = 1; i <= 4; ++i) {
			sprintf(file, "image/enemy0_down%d.png", i);
			auto sprite = Sprite::create(file);
			frames.pushBack(sprite->getSpriteFrame());
		}
		animation = Animation::createWithSpriteFrames(frames, 0.1);
		AnimationCache::getInstance()->addAnimation(animation, "enemy0-destory");
	}
	return animation;
}

