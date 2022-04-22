#include "Hero.h"
#include "2d/CCSprite.h"
#include "GameManager.h"


Hero::Hero(const std::string& filename) 
	: _hp(5)
	, _shootTime(0.1f)
	, _enhanceTime(0)
	, _wudiTime(0.2f)
{
	_sprite = Sprite::create(filename);//引用计数是1  -> 将sprite放入autoreleasepool中
	this->setContentSize(_sprite->getContentSize());
	this->addChild(_sprite);//应用计数2
	
}

Hero::~Hero() {
	
}


bool Hero::init() {
	this->scheduleUpdate();

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto pos = this->getParent()->convertTouchToNodeSpace(touch);
		this->setPosition(pos);
		return true;
	};
	listener->onTouchMoved = [this](Touch* touch, Event* event) {
		auto pos = this->getParent()->convertTouchToNodeSpace(touch);
		this->setPosition(pos);
	};
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		auto pos = this->getParent()->convertTouchToNodeSpace(touch);
		this->setPosition(pos);
	};
	listener->onTouchCancelled = [this](Touch* touch, Event* event) {
		auto pos = this->getParent()->convertTouchToNodeSpace(touch);
		this->setPosition(pos);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//EventListenerKeyboard::create();

	Animation* animation = this->getAnimationNormal();
	this->_sprite->runAction(RepeatForever::create(Animate::create(animation)));

	return true;
}

void Hero::update(float dt) {
	_shootTime -= dt;
	if (_shootTime <= 0) {
		_shootTime += 0.1f;
		
		GameManager::instance()->shooting(this);
	}
	if (_enhanceTime > 0) {
		_enhanceTime -= dt;
	}
	if (_wudiTime > 0) {
		_wudiTime -= dt;
	}
}

void Hero::collider() {
	this->_hp--;
	if (this->_hp == 0) {
		this->destory();
	}
	else {
		this->hit();
		_wudiTime = 0.5f;
	}
}
void Hero::destory() {

	this->_sprite->stopAllActions();


	auto animation = this->getAnimationDestory();
	auto action = DelayTime::create(0.5f);
	auto callback = CallFunc::create([this]() {
		GameManager::instance()->endGame();
	});
	auto seq = Sequence::create(Animate::create(animation), callback, nullptr);
	this->_sprite->runAction(seq);
}

void Hero::hit() {
	auto action1 = CallFunc::create([this]() {
		this->_sprite->setColor(Color3B(200, 0, 0));
	});
	auto action2 = DelayTime::create(0.1);
	auto action3 = CallFunc::create([this]() {
		this->_sprite->setColor(Color3B(255, 255, 255));
	});
	this->_sprite->runAction(Sequence::create(action1, action2, action3, nullptr));

}

Animation* Hero::getAnimationNormal() {
	Animation* animation = AnimationCache::getInstance()->getAnimation("hero-normal");
	if (!animation) {
		Vector<SpriteFrame*> frames;
		
		auto sprite = Sprite::create("image/hero1.png");
		frames.pushBack(sprite->getSpriteFrame());
		sprite = Sprite::create("image/hero2.png");
		frames.pushBack(sprite->getSpriteFrame());

		animation = Animation::createWithSpriteFrames(frames, 0.2);
		AnimationCache::getInstance()->addAnimation(animation, "hero-normal");
	}

	return animation;
}

Animation* Hero::getAnimationHit() {
	return nullptr;
}

Animation* Hero::getAnimationDestory() {
	Animation* animation = AnimationCache::getInstance()->getAnimation("hero-destory");
	if (!animation) {
		Vector<SpriteFrame*> frames;
		char file[100];
		for (int i = 1; i <= 4; ++i) {
			sprintf(file, "image/hero_blowup_n%d.png", i);
			auto sprite = Sprite::create(file);
			frames.pushBack(sprite->getSpriteFrame());
		}
		animation = Animation::createWithSpriteFrames(frames, 0.2);
		AnimationCache::getInstance()->addAnimation(animation, "hero-destory");
	}

	return animation;
}