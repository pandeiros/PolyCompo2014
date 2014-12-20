#include "GameScene.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* GameScene::createScene () {
    // 'scene' is an autorelease object
    auto scene = Scene::create ();

    // 'layer' is an autorelease object
    auto layer = GameScene::create ();

    // add layer as a child to scene
    scene->addChild (layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init () {
    CCLOG ("GAME SCENE START");

    if (!MainScene::init ()) {
        return false;
    }

    // HERE STARTS THE MAGIC
    scheduleUpdate ();
    mState = MainScene::GAME;

    mPlayer = Player::create ();
    this->addChild (mPlayer, ENTITIES);

    return true;
}

// Update
void GameScene::update (float dt) {
}

void GameScene::onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
        Director::getInstance ()->replaceScene (TransitionFade::create (1, MenuScene::createScene (), Color3B (0, 0, 0)));
    }

}

void GameScene::onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

}

