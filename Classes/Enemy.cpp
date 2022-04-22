#include "Enemy.h"
#include "GameManager.h"
USING_NS_CC;

Enemy::Enemy(const std::string& filename, int type) 
	: _hp(5)
	, _currentHP(5)
	, _type(type)
	, _speed(0, -1)
	, _score(1)
{
	_sprite = Sprite::create(filename);
	this->setContentSize(_sprite->getContentSize());
	this->addChild(_sprite);
}

Enemy::~Enemy() {

}

bool Enemy::init() {

	return true;
}
void Enemy::setConfig(int hp, Vec2 speed, int score) {
	this->_currentHP = hp;
	this->_hp = hp;
	this->_speed = speed;
	this->_score = score;
}

void Enemy::onEnter() {
	Node::onEnter();
	this->scheduleUpdate();
}

void Enemy::onExit() {
	Node::onExit();
	this->unscheduleUpdate();
}

void Enemy::update(float dt) {
	auto pos = this->getPosition();
	this->setPosition(pos + this->_speed);

	if (this->_position.y < -150) {
		this->recycle();
		CCLOG("enemy is out of view, need to recycle!");
	}
}

void Enemy::recycle() {
	GameManager::instance()->recycleEnemy(this);
	this->removeFromParent();
}

void Enemy::reuse() {

}

void Enemy::destory() {
	this->recycle();
}

void Enemy::hit() {

}

void Enemy::collider() {
	this->_currentHP--;

	if (this->_currentHP <= 0) {
		this->destory();
	}
	else {
		this->hit();
	}
}