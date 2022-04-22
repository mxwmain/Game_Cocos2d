#include "Enemy2.h"
#include "GameManager.h"
#include "GameAudio.h"

USING_NS_CC;

Enemy2* Enemy2::create() {
	Enemy2* enemy = new (std::nothrow)Enemy2();

	if (enemy && enemy->init()) {
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

Enemy2::Enemy2() :Enemy("image/enemy1.png", 2) {

}

Enemy2::~Enemy2() {

}

bool Enemy2::init() {
	if (!Enemy::init()) return false;

	return true;
}

void Enemy2::reuse() {

	_currentHP = _hp;
	this->setPosition(random(50, 300), 1000);
	auto animation = this->getAnimationNormal();
	this->_sprite->runAction(RepeatForever::create(Animate::create(animation)));

}

void Enemy2::destory() {
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

void Enemy2::hit() {
	this->_sprite->stopAllActions();

	auto animation = this->getAnimationHit();
	auto callback = CallFunc::create([this]() {
		auto animation = this->getAnimationNormal();
		this->_sprite->runAction(RepeatForever::create(Animate::create(animation)));
	});
	auto seq = Sequence::create(Animate::create(animation), callback, nullptr);
	this->_sprite->runAction(seq);
}

Animation* Enemy2::getAnimationNormal() {
	Animation* animation = AnimationCache::getInstance()->getAnimation("enemy1-normal");
	if (!animation) {
		Vector<SpriteFrame*> frames;
		char file[100];
		for (int i = 1; i <= 1; ++i) {
			sprintf(file, "image/enemy1.png");
			auto sprite = Sprite::create(file);
			frames.pushBack(sprite->getSpriteFrame());
		}
		animation = Animation::createWithSpriteFrames(frames, 0.1);
		AnimationCache::getInstance()->addAnimation(animation, "enemy1-normal");
	}

	return animation;
}

Animation* Enemy2::getAnimationHit() {
	Animation* animation = AnimationCache::getInstance()->getAnimation("enemy1-hit");
	if (!animation) {
		Vector<SpriteFrame*> frames;
			
		auto sprite = Sprite::create("image/enemy1_hit.png");
		frames.pushBack(sprite->getSpriteFrame());

		sprite = Sprite::create("image/enemy1.png");
		frames.pushBack(sprite->getSpriteFrame());

		animation = Animation::createWithSpriteFrames(frames, 0.1);
		AnimationCache::getInstance()->addAnimation(animation, "enemy1-hit");
	}
	return animation;
}

Animation* Enemy2::getAnimationDestory() {
	Animation* animation = AnimationCache::getInstance()->getAnimation("enemy1-destory");
	if (!animation) {
		Vector<SpriteFrame*> frames;
		char file[100];
		for (int i = 1; i <= 4; ++i) {
			sprintf(file, "image/enemy1_down%d.png", i);
			auto sprite = Sprite::create(file);
			frames.pushBack(sprite->getSpriteFrame());
		}
		animation = Animation::createWithSpriteFrames(frames, 0.1);
		AnimationCache::getInstance()->addAnimation(animation, "enemy1-destory");
	}
	return animation;
}
