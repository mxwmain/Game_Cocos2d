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

#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"
#include "MainScene.h"
#include "GameAudio.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    return StartScene::create();
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	GameAudio::preloadMusic();
	GameAudio::prelaodEffects();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//rootlayer
	auto rootlayer = CCLayerColor::create(Color4B(255, 0, 0, 255));
	rootlayer->setPosition(origin);
	this->addChild(rootlayer);
		
	//background
	auto bg = Sprite::create("image/background.png");
	bg->setPosition(visibleSize.width*0.5, visibleSize.height*0.5);
	rootlayer->addChild(bg);
	auto scale = visibleSize.height / bg->getContentSize().height;
	bg->setScale(scale);

	//title
	auto title = Sprite::create("image/name.png");
	title->setPosition(visibleSize.width*0.5, visibleSize.height*0.7);
	rootlayer->addChild(title);

	//button
	auto button = ui::Button::create("image/game_resume_nor.png", "image/game_resume_pressed.png", "image/game_resume_pressed.png");
	button->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
	button->setScale(2.0);
	rootlayer->addChild(button);

	button->addClickEventListener(CC_CALLBACK_1(StartScene::onClickStart, this));


    return true;
}

void StartScene::onClickStart(Ref* pSender) {
	CCLOG("click on start!");
	GameAudio::playButtonClick();
	auto scene = MainScene::createScene();
	Director::getInstance()->replaceScene(scene);
}