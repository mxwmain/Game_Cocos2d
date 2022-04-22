#include "GameAudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

float GameAudio::musicVolumn = 1.0f;
float GameAudio::effectVolumn = 1.0f;

void GameAudio::preloadMusic() {
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/game_music.mp3");
	return ;
}

void GameAudio::prelaodEffects() {
	SimpleAudioEngine::getInstance()->preloadEffect("sound/bullet.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/button.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/get_boom.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/use_boom.mp3");
	return;
}

void GameAudio::playBgMusic() {
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_music.mp3");
	return;
}

void GameAudio::playBullet() {
	SimpleAudioEngine::getInstance()->playEffect("sound/bullet.mp3");
	return;
}

void GameAudio::playEnemyDown() {
	SimpleAudioEngine::getInstance()->playEffect("sound/use_boom.mp3");
	return;
}

void GameAudio::playButtonClick() {
	SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3");
	return;
}

