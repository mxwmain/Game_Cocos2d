#include "Bullet.h"
#include "2d\CCSprite.h"
#include "GameManager.h"
USING_NS_CC;


bool Bullet::init() {
	return true;
}

void Bullet::onEnter() {
	Node::onEnter();
	this->scheduleUpdate();
	
}

void Bullet::onExit() {
	this->unscheduleUpdate();
	Node::onExit();
}

void Bullet::update(float dt) {
	auto pos = this->getPosition();
	this->setPosition(pos + this->_speed);
	if (this->_position.y > 1000) {
		this->recycle();
	}
}

void Bullet::recycle() {
	GameManager::instance()->recycleBullet(this);
	this->removeFromParent();
}
void Bullet::reuse() {

}
void Bullet::collider() {
	this->recycle();
}


Bullet::Bullet(const std::string& filename): _speed(0, 5)
{
	_sprite = Sprite::create(filename);
	this->setContentSize(_sprite->getContentSize());
	this->addChild(_sprite);
}

Bullet::~Bullet() {
	_sprite->release();
}