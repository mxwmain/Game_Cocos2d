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

#include "EndScene.h"
#include "SimpleAudioEngine.h"
#include "2d/CCSprite.h"
#include "ui/UIButton.h"
#include "HelloWorldScene.h"
#include "MainScene.h"
#include "ui/UIText.h"
#include "GameManager.h"

USING_NS_CC;

Scene* EndScene::createScene()
{
    return EndScene::create();
}

// on "init" you need to initialize your instance
bool EndScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//rootlayer
	auto rootLayer = CCLayerColor::create(Color4B(255, 0, 0, 255));
	rootLayer->setPosition(origin);
	this->addChild(rootLayer);

	//background
	auto bg = Sprite::create("image/gameover.png");
	bg->setPosition(visibleSize.width*0.5, visibleSize.height*0.5);
	rootLayer->addChild(bg);

	//title
	_highestScore = ui::Text::create("123456", "fonts/Marker Felt.ttf", 45);
	_highestScore->setTextColor(Color4B(100, 100, 100, 255));
	_highestScore->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.6));
	rootLayer->addChild(_highestScore);
	_highestScore->setString(std::to_string(GameManager::instance()->highestScore()));

	_score = ui::Text::create("123456", "fonts/Marker Felt.ttf", 45);
	_score->setTextColor(Color4B(100, 100, 100, 255));
	_score->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.25));
	rootLayer->addChild(_score);
	_score->setString(std::to_string(GameManager::instance()->score()));

	//button
	auto button = ui::Button::create("image/restart_nor.png", "image/restart_sel.png", "image/restart_sel.png");
	button->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
	rootLayer->addChild(button);
	button->setScale(2.0);
	button->setName("restart");
	button->addClickEventListener(CC_CALLBACK_1(EndScene::onClick, this));


	button = ui::Button::create("image/quit_nor.png", "image/quit_sel.png", "image/quit_sel.png");
	button->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.1));
	rootLayer->addChild(button);
	button->setScale(2.0);
	button->setName("quit");
	button->addClickEventListener(CC_CALLBACK_1(EndScene::onClick, this));


    return true;
}

void EndScene::onClick(Ref* pSender) {
	CCLOG("click on start!");
	auto name = ((Node*)pSender)->getName();
	if (name == "restart") {
		GameManager::instance()->restartGame();
	}
	else if (name == "quit") {
		Director::getInstance()->end();
	}
	
}
