#include "GameManager.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Bullet.h"
#include "Hero.h"
#include "json/rapidjson.h"
#include "json\document-wrapper.h"
#include "EndScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "GameAudio.h"

GameManager* GameManager::_sGameManager = nullptr;

GameManager* GameManager::instance() {
	if (_sGameManager == nullptr) {
		_sGameManager = new GameManager();
		if (_sGameManager && _sGameManager->init()) {
			return _sGameManager;
		}
		CC_SAFE_DELETE(_sGameManager);
		_sGameManager = nullptr;
	}

	return _sGameManager;
}

GameManager::GameManager()
	:_gameLayer(nullptr)
	,_scoreText(nullptr)
	,_bombText(nullptr)
	,_hero(nullptr)
	,_level(0)
	,_score(0)
	,_hightestScore(0)
{

}
GameManager::~GameManager() {

}
bool GameManager::init() {

	ssize_t size = 0;
	unsigned char* pBytes = FileUtils::getInstance()->getFileData("res/level.json", "r", &size);
	std::string load_str((const char*)pBytes, size);
	rapidjson::Document doc;
	doc.Parse(load_str.c_str());
	if (doc.HasParseError()) return false;

	if (doc.IsObject()) {
		if (doc.HasMember("level")) {
			const rapidjson::Value& pArray = doc["level"];
			if (pArray.IsArray()) {
				for (rapidjson::SizeType i = 0; i < pArray.Size(); ++i) {
					const rapidjson::Value& p = pArray[i];
					LevelData* pLevel = new LevelData();
					_levelCfg.push_back(pLevel);
					pLevel->targetScore = p["target-score"].GetInt();
					for (int i = 0; i < 3; i++) {
						pLevel->enemyScore[i] = p["enemy-score"][i].GetInt();
						pLevel->enemyInterval[i] = p["enemy-interval"][i].GetFloat();
						pLevel->enemyHP[i] = p["enemy-hp"][i].GetInt();
						pLevel->enemySpeed[i] = p["enemy-speed"][i].GetFloat();
					}
					for (int i = 0; i < 2; i++) {
						pLevel->enhanceInterval[i] = p["enhance-interval"][i].GetFloat();
						pLevel->bombInterval[i] = p["bomb-interval"][i].GetFloat();
					}
				}
			}
		}
	}
	this->scheduleUpdate();
	this->resume();

	return true;
}

void GameManager::update(float dt) {
	//CCLOG("GameManager::update!!!!");
	this->colliderTest();


}

void GameManager::colliderTest() {
	//子弹和敌机
	for (auto it1 = _collideBullets.begin(); it1 != _collideBullets.end(); ++it1) {
		for(auto it2 = _collideEnemys.begin(); it2 != _collideEnemys.end() && it1->second; ++it2) {
			if (!it2->second || it2->first->_currentHP <= 0) continue;

			auto bullet = it1->first;
			auto enemy = it2->first;
			auto pos1 = bullet->getPosition();
			auto pos2 = enemy->getPosition();
			int sizeW = 0, sizeH = 0;
			
			if (enemy->_type == 1) {
				sizeW = 25;
				sizeH = 20;
			}
			else if (enemy->_type == 2) {
				sizeW = 35;
				sizeH = 45;
			}
			else if (enemy->_type == 3) {
				sizeW = 82;
				sizeH = 123;
			}

			if (abs(pos1.x - pos2.x) < sizeW && abs(pos1.y - pos2.y) < sizeH) {
				bullet->collider();
				enemy->collider();
				//it1->second = false;//子弹会调用reclycleBullet进行状态设置
				//it2->second = false;//这行代码不需要，否则hp>1的情况下无法再次检测碰撞
			}
		}
	}

	//敌机和英雄
	if (_hero && _hero->_hp > 0 && !_hero->isWuDi()) {
		for (auto it = _collideEnemys.begin(); it != _collideEnemys.end(); ++it) {
			auto enemy = it->first;
			auto pos1 = _hero->getPosition();
			auto pos2 = enemy->getPosition();
			int sizeW = 0, sizeH = 0;
			if (enemy->_type == 1) {
				sizeW = 25 + 50;
				sizeH = 20 + 60;
			}
			else if (enemy->_type == 2) {
				sizeW = 35 + 50;
				sizeH = 45 + 60;
			}
			else if (enemy->_type == 3) {
				sizeW = 82 + 50;
				sizeH = 123 + 60;
			}
			if (abs(pos1.x - pos2.x) < sizeW && abs(pos1.y - pos2.y) < sizeH) {
				_hero->collider();
			}
		}
	}
}

void GameManager::startGame(int level,  Layer* layer, Text* score, Text* bomb) {
	_gameLayer = layer;
	_scoreText = score;
	_bombText = bomb;
	_level = level - 1;

	auto levelCfg = _levelCfg[_level];
	if (levelCfg) {
		auto scheduler = Director::getInstance()->getScheduler();
		scheduler->schedule([this](float dt) {
			this->randomEnemy(1);
		}, this, levelCfg->enemyInterval[0], false, "random-enmey-1");

		scheduler->schedule([this](float dt) {
			this->randomEnemy(2);
		}, this, levelCfg->enemyInterval[1], false, "random-enmey-2");

		scheduler->schedule([this](float dt) {
			this->randomEnemy(3);
		}, this, levelCfg->enemyInterval[2], false, "random-enmey-3");
	}
}

void GameManager::levelUp() {
	this->unschedule("random-enmey-1");
	this->unschedule("random-enmey-2");
	this->unschedule("random-enmey-3");

	auto levelCfg = _levelCfg[_level];
	if (levelCfg) {
		auto scheduler = Director::getInstance()->getScheduler();
		scheduler->schedule([this](float dt) {
			this->randomEnemy(1);
		}, this, levelCfg->enemyInterval[0], false, "random-enmey-1");

		scheduler->schedule([this](float dt) {
			this->randomEnemy(2);
		}, this, levelCfg->enemyInterval[1], false, "random-enmey-2");

		scheduler->schedule([this](float dt) {
			this->randomEnemy(3);
		}, this, levelCfg->enemyInterval[2], false, "random-enmey-3");
	}
}

void GameManager::restartGame() {
	_hero = nullptr;
	_enemys[0].clear();
	_enemys[1].clear();
	_enemys[2].clear();
	_bullets.clear();
	_collideBullets.clear();
	_collideEnemys.clear();

	auto scene = MainScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameManager::pauseGame() {
	Director::getInstance()->pause();
}

void GameManager::resumeGame() {
	Director::getInstance()->resume();
}

void GameManager::endGame() {
	this->unschedule("random-enmey-1");
	this->unschedule("random-enmey-2");
	this->unschedule("random-enmey-3");

	auto scene = EndScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameManager::randomEnemy(int type) {
	Enemy* enemy = this->reuseEnemy(type);
	auto levelCfg = _levelCfg[_level];
	if (enemy && levelCfg) {
		_gameLayer->addChild(enemy);

		enemy->setConfig(levelCfg->enemyHP[type - 1], Vec2(0, -levelCfg->enemySpeed[type - 1]), levelCfg->enemyScore[type - 1]);
		enemy->reuse();


		this->_collideEnemys[enemy] = true;
	}
}

Enemy* GameManager::reuseEnemy(int type) {
	Enemy* enemy = nullptr;
	if (!this->_enemys[type - 1].empty()) {
		enemy = this->_enemys[type - 1].back();
		enemy->retain();
		enemy->autorelease();//ref=2
		this->_enemys[type - 1].popBack();//ref=1
	}
	else {
		switch (type)
		{
		case 1:
			return Enemy1::create();
		case 2:
			return Enemy2::create();
		case 3:
			return Enemy3::create();
		default:
			break;
		}
	}

	return enemy;
}

void GameManager::recycleEnemy(Enemy* enemy) {
	this->_enemys[enemy->_type - 1].pushBack(enemy);
	this->_collideEnemys[enemy] = false;
}
void GameManager::recycleBullet(Bullet* bullet) {
	this->_bullets.pushBack(bullet);
	this->_collideBullets[bullet] = false;
}

void GameManager::shooting(Hero* hero) {

	GameAudio::playBullet();
	// CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/bullet.mp3");

	_hero = hero;

	if (hero->isEnhance()) {
		Bullet* bullet1 = this->reuseBullet();
		auto pos = hero->getPosition();
		bullet1->setPosition(pos.x - 30, pos.y + 20);
		_gameLayer->addChild(bullet1);
		this->_collideBullets[bullet1] = true;

		Bullet* bullet2 = this->reuseBullet();
		bullet2->setPosition(pos.x + 30, pos.y + 20);
		_gameLayer->addChild(bullet2);
		this->_collideBullets[bullet2] = true;
	}
	else {
		Bullet* bullet = this->reuseBullet();
		
		if (this->_collideBullets[bullet]) {
			CCLOG("=============bullet is in game layer! %p", bullet);
		}

		auto pos = hero->getPosition();
		bullet->setPosition(pos.x, pos.y + 70);
		_gameLayer->addChild(bullet);

		this->_collideBullets[bullet] = true;
		
		CCLOG("buffer bullts size = %d ;  collide bullts size = %d\n", _bullets.size(), _collideBullets.size());
	}
}
Bullet* GameManager::reuseBullet() {
	if (this->_bullets.empty()) {
		return Bullet::create();
	}
	Bullet* bullet = nullptr;
	bullet = this->_bullets.back();
	bullet->retain();
	bullet->autorelease();
	this->_bullets.popBack();
	CCLOG("address = %p , ref = %d",bullet, bullet->getReferenceCount());
	
	return bullet;
}
void GameManager::addScore(int score) {
	_score += score;
	_scoreText->setString(std::to_string(_score));

	if (_score > _hightestScore) {
		_hightestScore = _score;
	}

	if (_score >= _levelCfg[_level]->targetScore) {
		_level++;
		this->restartGame();
	}
}