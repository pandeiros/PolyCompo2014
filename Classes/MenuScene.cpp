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

    // HERE STARTS THE MAGIC
    scheduleUpdate ();
    mState = MainScene::MENU;

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
        case EventKeyboard::KeyCode::KEY_KP_ENTER: case EventKeyboard::KeyCode::KEY_ENTER : {
            
            Director::getInstance ()->replaceScene (GameScene::createScene ()); break;
        }
    }
}

void MenuScene::onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

}

