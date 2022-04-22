#include "Enemy3.h"
#include "GameManager.h"
#include "GameAudio.h"
USING_NS_CC;

Enemy3* Enemy3::create() {
	Enemy3* enemy = new (std::nothrow)Enemy3();

	if (enemy && enemy->init()) {
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

Enemy3::Enemy3() :Enemy("image/enemy2.png", 3) {

}

Enemy3::~Enemy3() {

}

bool Enemy3::init() {
	if (!Enemy::init()) return false;

	this->setPosition(random(50, 380), 1000);

	return true;
}

void Enemy3::reuse() {

	_currentHP = _hp;
	this->setPosition(random(100, 300), 1000);
	auto animation = this->getAnimationNormal();
	this->_sprite->runAction(RepeatForever::create(Animate::create(animation)));
}

void Enemy3::destory() {
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

void Enemy3::hit() {
	this->_sprite->stopAllActions();

	auto animation = this->getAnimationHit();
	auto callback = CallFunc::create([this]() {
		auto animation = this->getAnimationNormal();
		this->_sprite->runAction(RepeatForever::create(Animate::create(animation)));
	});
	auto seq = Sequence::create(Animate::create(animation), callback, nullptr);
	this->_sprite->runAction(seq);
}

Animation* Enemy3::getAnimationNormal() {
	Animation* animation = AnimationCache::getInstance()->getAnimation("enemy2-normal");
	if (!animation) {
		Vector<SpriteFrame*> frames;
		auto sprite = Sprite::create("image/enemy2.png");
		frames.pushBack(sprite->getSpriteFrame());

		sprite = Sprite::create("image/enemy2_n2.png");
		frames.pushBack(sprite->getSpriteFrame());
		animation = Animation::createWithSpriteFrames(frames, 0.1);
		AnimationCache::getInstance()->addAnimation(animation, "enemy2-normal");
	}

	return animation;
}

Animation* Enemy3::getAnimationHit() {
	Animation* animation = AnimationCache::getInstance()->getAnimation("enemy2-hit");
	if (!animation) {
		Vector<SpriteFrame*> frames;

		auto sprite = Sprite::create("image/enemy2_hit.png");
		frames.pushBack(sprite->getSpriteFrame());

		sprite = Sprite::create("image/enemy2.png");
		frames.pushBack(sprite->getSpriteFrame());

		animation = Animation::createWithSpriteFrames(frames, 0.1);
		AnimationCache::getInstance()->addAnimation(animation, "enemy2-hit");
	}
	return animation;
}

Animation* Enemy3::getAnimationDestory() {
	Animation* animation = AnimationCache::getInstance()->getAnimation("enemy2-destory");
	if (!animation) {
		Vector<SpriteFrame*> frames;
		char file[100];
		for (int i = 1; i <= 6; ++i) {
			sprintf(file, "image/enemy2_down%d.png", i);
			auto sprite = Sprite::create(file);
			frames.pushBack(sprite->getSpriteFrame());
		}
		animation = Animation::createWithSpriteFrames(frames, 0.1);
		AnimationCache::getInstance()->addAnimation(animation, "enemy2-destory");
	}
	return animation;
}
