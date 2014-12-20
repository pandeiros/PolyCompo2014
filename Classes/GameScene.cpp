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
    mState = States::S_GAME;

    mPlayer = Player::create ();
    this->addChild (mPlayer, Layers::ENTITIES);

    mapKeysPressed[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
    mapKeysPressed[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
    mapKeysPressed[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
    mapKeysPressed[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;

    return true;
}

// Update
void GameScene::update (float dt) {
    mPlayer->move (mapKeysPressed[EventKeyboard::KeyCode::KEY_UP_ARROW] * Movement::UP |
                   mapKeysPressed[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] * Movement::RIGHT |
                   mapKeysPressed[EventKeyboard::KeyCode::KEY_DOWN_ARROW] * Movement::DOWN |
                   mapKeysPressed[EventKeyboard::KeyCode::KEY_LEFT_ARROW] * Movement::LEFT);

    for (Missile * missile : vecMissiles) {
        missile->update (dt);
    }
}


void GameScene::onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ESCAPE : {
            Director::getInstance ()->replaceScene (TransitionFade::create (1, MenuScene::createScene (), Color3B (0, 0, 0))); 
            break;
        }
        case EventKeyboard::KeyCode::KEY_SPACE: {
            vecMissiles.push_back (Missile::create(mPlayer->getPosition(),Missiles::M_WATERBALL));
            break;
        }
    }
    
    mapKeysPressed[keyCode] = true;
}

void GameScene::onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    mapKeysPressed[keyCode] = false;
}

