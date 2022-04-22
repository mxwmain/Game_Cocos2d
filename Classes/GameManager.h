#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "Hero.h"
#include "ui/UIText.h"
#include <unordered_map>

using namespace cocos2d;
using namespace ui;

/*
{
	"target-score" : 100000,
		"enemy-score" : [1000, 6000, 30000],
		"enemy-interval" : [1, 5, 10],
		"enemy-hp" : [1, 5, 12],
		"enemy-speed" : [1, 1, 1],
		"enhance-interval" : [5, 10],
		"bomb-interval" : [5, 10]
}*/
struct LevelData {
	int targetScore;
	int enemyScore[3];
	int enemyHP[3];
	float enemyInterval[3];
	float enemySpeed[3];
	float enhanceInterval[2];
	float bombInterval[2];
};


class Enemy;
class Bullet;
class GameManager : public Node{
public:
	static GameManager* instance();

	bool init() override;
	void update(float dt) override;

public:
	void startGame(int level, Layer* layer, Text* score, Text* bomb);
	void levelUp();
	void restartGame();
	void pauseGame();
	void resumeGame();
	void endGame();
	
	void randomEnemy(int type);
	Enemy* reuseEnemy(int type);
	void recycleEnemy(Enemy* enemy);
	void recycleBullet(Bullet* bullet);

	void shooting(Hero* hero);

	Bullet* reuseBullet();

public:
	void colliderTest();
	void addScore(int score);

	int highestScore() { return _hightestScore; }
	int score() { return _score; }
	int level() { return _level; }
protected:
	GameManager();
	~GameManager();

private:
	static GameManager* _sGameManager;
	Vector<Enemy*> _enemys[3];
	Vector<Bullet*> _bullets;
	Hero* _hero;
	std::vector<LevelData*> _levelCfg;

	Layer* _gameLayer;
	Text* _scoreText;
	Text* _bombText;

	int _level;
	int _score;
	int _hightestScore;

	//collider test
	std::unordered_map<Bullet*, bool> _collideBullets;
	std::unordered_map<Enemy*, bool> _collideEnemys;
};

#endif // !__GAMEMANAGER_H__

