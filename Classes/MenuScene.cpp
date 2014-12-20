#include "MenuScene.h"
#include "GameScene.h"

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
    mState = MainScene::MENU;

    // Bakcround
    mBackground = Sprite::create ("Background.png");
    mBackground->setPosition (Vec2 (origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild (mBackground, Layers::BACKGROUND);

    // Button
    mStartButton = MenuItemImage::create ("ButtonEmpty.png", "ButtonFull.png", CC_CALLBACK_0 (MenuScene::startGame, this));
    mStartButton->setPosition (visibleSize.width / 2, visibleSize.height / 2 + mStartButton->getBoundingBox ().size.height / 2);
   
    // "Wars" sprite
    mWars = Sprite::create ("Wars.png");
    mWars->setPosition (visibleSize.width / 2, visibleSize.height / 2 - mWars->getBoundingBox().size.height / 2 - 15);
    this->addChild (mWars, Layers::GUI);

    mMenu = Menu::create (mStartButton, NULL);
    mMenu->setPosition (Vec2::ZERO);
    this->addChild (mMenu, Layers::GUI);

    return true;
}

// Update
void MenuScene::update (float dt) {
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
    Director::getInstance ()->replaceScene (TransitionFade::create (1, GameScene::createScene (), Color3B (0, 0, 0)));
}