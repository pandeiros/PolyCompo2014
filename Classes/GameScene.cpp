#include <cstdlib>
#include <ctime>
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

    srand ((int) std::time(NULL));

    if (!MainScene::init ()) {
        return false;
    }

    // HERE STARTS THE MAGIC
    scheduleUpdate ();
    mState = States::S_GAME;

    mPlayer = Player::create ();
    this->addChild (mPlayer, Layers::PLAYER);

    mapKeysPressed[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
    mapKeysPressed[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
    mapKeysPressed[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
    mapKeysPressed[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;

    return true;
}

// Update
void GameScene::update (float dt) {
    // Player update
    mPlayer->move (mapKeysPressed[EventKeyboard::KeyCode::KEY_UP_ARROW] * Movement::UP |
                   mapKeysPressed[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] * Movement::RIGHT |
                   mapKeysPressed[EventKeyboard::KeyCode::KEY_DOWN_ARROW] * Movement::DOWN |
                   mapKeysPressed[EventKeyboard::KeyCode::KEY_LEFT_ARROW] * Movement::LEFT);

    // Missile update
    missilesUpdate (dt);

    // Enemy update
    enemiesUpdate (dt);
}


void GameScene::onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ESCAPE: {
            Director::getInstance ()->replaceScene (TransitionFade::create (1, MenuScene::createScene (), Color3B (0, 0, 0)));
            break;
        }
        case EventKeyboard::KeyCode::KEY_SPACE: {
            Missile * missile = Missile::create (mPlayer->getPosition (), Missiles::M_WATERBALL, Movement::RIGHT);
            vecMissiles.push_back (missile);
            this->addChild (missile, Layers::MISSILES);
            break;
        }
    }

    mapKeysPressed[keyCode] = true;
}

void GameScene::onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    mapKeysPressed[keyCode] = false;
}

void GameScene::missilesUpdate (float dt) {
    for (unsigned int iMissile = 0; iMissile < vecMissiles.size (); ++iMissile) {
        if (vecMissiles[iMissile] != nullptr) {
            if (vecMissiles[iMissile]->getIsValid ()) {

                vecMissiles[iMissile]->update (dt);
            }
            else {
                if (vecMissiles[iMissile]->getParent () != nullptr)
                    vecMissiles[iMissile]->getParent ()->removeChild (this);
            }
        }
        else {
            std::swap (vecMissiles[iMissile], vecMissiles[vecMissiles.size () - 1]);
            vecMissiles.pop_back ();
        }
    }
}

void GameScene::enemiesUpdate (float dt) {
    int chance = rand () % Enemies::HARD;
    Size visibleSize = Director::getInstance ()->getVisibleSize ();

    if (chance == 0) {
        Enemy * enemy = Enemy::create (cocos2d::Vec2(visibleSize.width * 1.5, 100 + rand() % (int)(visibleSize.height * 0.8)), Enemies::E_TIEFIGHTER, Movement::LEFT);
        this->addChild (enemy, Layers::ENTITIES);
        vecEnemies.push_back (enemy);
    }
    for (unsigned int iEnemy = 0; iEnemy < vecEnemies.size (); ++iEnemy) {
        if (vecEnemies[iEnemy] != nullptr) {
            if (vecEnemies[iEnemy]->getIsValid ()) {

                vecEnemies[iEnemy]->update (dt);
            }
            else {
                if (vecEnemies[iEnemy]->getParent () != nullptr)
                    vecEnemies[iEnemy]->getParent ()->removeChild (this);
            }
        }
        else {
            std::swap (vecEnemies[iEnemy], vecEnemies[vecEnemies.size () - 1]);
            vecEnemies.pop_back ();
        }
    }
}

