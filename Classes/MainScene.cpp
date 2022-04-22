/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"
#include "ui/UIImageView.h"
#include "Hero.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "GameManager.h"
#include "GameAudio.h"
USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	GameAudio::playBgMusic(); 
	// CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_music.mp3");

    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//rootlayer
	auto rootlayer = CCLayerColor::create(Color4B(0, 255, 0, 255));
	rootlayer->setPosition(origin);
	this->addChild(rootlayer);
	_gameLayer = rootlayer;

	//background
	auto bg = Sprite::create("image/background.png");
	bg->setPosition(visibleSize.width*0.5, visibleSize.height*0.5);
	rootlayer->addChild(bg);
	auto scale = visibleSize.height / bg->getContentSize().height;
	bg->setScale(scale);

	//button
	auto btnPause = ui::Button::create("image/game_pause_nor.png", "image/game_pause_pressed.png", "image/game_pause_pressed.png");
	btnPause->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.95));
	rootlayer->addChild(btnPause, 10);
	btnPause->addClickEventListener(CC_CALLBACK_1(MainScene::onClick, this));
	btnPause->setName("btnPause");
	btnPause->setSwallowTouches(true);

	//score
	auto score = ui::Text::create("0", "fonts/Marker Felt.ttf", 45);
	score->setAnchorPoint(Vec2(0, 0.5));
	score->setPosition(Vec2(visibleSize.width * 0.1 + 50, visibleSize.height * 0.95));
	score->setTextColor(Color4B(100, 100, 100, 255));
	rootlayer->addChild(score);

	//button boom
	auto btnBoom = ui::Button::create("image/bomb.png", "image/bomb.png", "image/bomb.png");
	btnBoom->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.05));
	rootlayer->addChild(btnBoom, 10);
	btnBoom->addClickEventListener(CC_CALLBACK_1(MainScene::onClick, this));
	btnBoom->setName("btnBoom");
	btnBoom->setSwallowTouches(true);
	btnBoom->setPressedActionEnabled(true);

	//boom count
	auto boom = ui::Text::create("0", "fonts/Marker Felt.ttf", 45);
	boom->setAnchorPoint(Vec2(0, 0.5));
	boom->setPosition(Vec2(visibleSize.width * 0.1 + 50, visibleSize.height * 0.05));
	boom->setTextColor(Color4B(100, 100, 100, 255));
	rootlayer->addChild(boom);

	//pause layer
	auto pauseLayer = LayerColor::create();
	this->addChild(pauseLayer, 100);
	pauseLayer->setVisible(false);
	_pauseLayer = pauseLayer;


	auto image = ui::ImageView::create("image/bg.png");
	image->setOpacity(150);
	image->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height * 0.5));
	image->setScaleX(visibleSize.width / image->getContentSize().width);
	image->setScaleY(visibleSize.height / image->getContentSize().height);
	image->setTouchEnabled(true);
	image->setSwallowTouches(true);
	pauseLayer->addChild(image);

	auto btnResume = ui::Button::create("image/game_resume_nor.png", "image/game_resume_pressed.png", "image/game_resume_pressed.png");
	btnResume->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
	pauseLayer->addChild(btnResume);
	btnResume->addClickEventListener(CC_CALLBACK_1(MainScene::onClick, this));
	btnResume->setName("btnResume");
	btnResume->setScale(2);

	btnResume = ui::Button::create("image/resume_nor.png", "image/resume_sel.png", "image/resume_sel.png");
	btnResume->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5 - 100));
	pauseLayer->addChild(btnResume);
	btnResume->addClickEventListener(CC_CALLBACK_1(MainScene::onClick, this));
	btnResume->setName("btnResume");
	btnResume->setScale(2);


	//hero
	auto hero = Hero::create();
	hero->setPosition(visibleSize.width*0.5, visibleSize.height * 0.3);
	_gameLayer->addChild(hero);

	//auto enemy1 = Enemy1::create();
	//auto enemy2 = Enemy2::create();
	//auto enemy3 = Enemy3::create();
	//_gameLayer->addChild(enemy1);
	//_gameLayer->addChild(enemy2);
	//_gameLayer->addChild(enemy3);

	GameManager::instance()->startGame(GameManager::instance()->level()+1, _gameLayer, score, boom);


    return true;
}

void MainScene::onClick(Ref* pSender) {
	CCLOG("click on main");

	auto name = ((Node*)pSender)->getName();
	if (name == "btnPause") {
		GameAudio::playButtonClick();

		_pauseLayer->setVisible(true);
		GameManager::instance()->pauseGame();
		
		// CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3");
	}
	else if (name == "btnResume") {
		GameAudio::playButtonClick();

		_pauseLayer->setVisible(false);
		GameManager::instance()->resumeGame();
		
		// CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3");
	}


}
