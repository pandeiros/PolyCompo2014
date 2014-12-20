#include "MenuScene.h"
#include "IntroScene.h"

USING_NS_CC;

Scene* MenuScene::createScene () {
    // 'scene' is an autorelease object
    auto scene = Scene::create ();

    // 'layer' is an autorelease object
    auto layer = MenuScene::create ();

    // add layer as a child to scene
    scene->addChild (layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init () {
    CCLOG ("MENU SCENE START");

    if (!MainScene::init ()) {
        return false;
    }

    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    Size visibleSize = Director::getInstance ()->getVisibleSize ();

    // Config
    scheduleUpdate ();
    mState = States::S_MENU;

    // Bakcround
    mBackground = Sprite::create ("Background.png");
    mBackground->setPosition (Vec2 (origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild (mBackground, Layers::BACKGROUND);

    // Button
    mStartButton = MenuItemImage::create ("ButtonEmpty.png", "ButtonFull.png", CC_CALLBACK_0 (MenuScene::startGame, this));
    mStartButton->setPosition (visibleSize.width / 2.f, visibleSize.height / 2.f + mStartButton->getBoundingBox ().size.height / 2 - 140);
    mStartButton->setScale (0.5f);
   
    // "Wars" sprite
    mWars = Sprite::create ("Wars.png");
    mWars->setScale (0.5f);
    mWars->setPosition (visibleSize.width / 2.f, visibleSize.height / 2.f - mWars->getBoundingBox().size.height / 2 - 115);
    this->addChild (mWars, Layers::GUI);

    mMenu = Menu::create (mStartButton, NULL);
    mMenu->setPosition (Vec2::ZERO);
    this->addChild (mMenu, Layers::GUI);
    
    // Title
    mTitle = Sprite::create ("placeholder.png");
    mTitle->setPosition (visibleSize.width / 2.f, visibleSize.height - 150.f);
    this->addChild (mTitle, Layers::GUI);

    return true;
}

// Update
void MenuScene::update (float dt) {
    time += dt;
   
    // Flashing start button
    if (time > 0.6f) {
        time = 0.f;
        if (isStartActive) {
            mStartButton->setNormalImage (Sprite::create ("ButtonEmpty.png"));
        }
        else {
            mStartButton->setNormalImage (Sprite::create ("ButtonFull.png"));
        }
        isStartActive = !isStartActive;
    }
}

void MenuScene::onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ESCAPE: {
            Director::getInstance ()->end (); break;
        }
    }
}

void MenuScene::onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

}

void MenuScene::startGame () {
    Director::getInstance ()->replaceScene (TransitionFade::create (1, IntroScene::createScene (), Color3B (0, 0, 0)));
}