
#ifndef  _GAMEAUDIO_H_
#define  _GAMEAUDIO_H_

#include "cocos2d.h"

class GameAudio {
public :
	static void preloadMusic();
	static void prelaodEffects();
	
	static void playBgMusic();
	static void playBullet();
	static void playEnemyDown();
	static void playButtonClick();

	static float musicVolumn;
	static float effectVolumn;

};


#endif // _GAMEAUDIO_H_

