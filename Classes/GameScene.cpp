#include <cstdlib>
#include <ctime>
#include "GameScene.h"
#include "MenuScene.h"
#include "GLES-Render.h"
#include <Box2D/Box2D.h>
#include "B2DebugDrawLayer.h"

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

    srand ((int)std::time (NULL));

    if (!MainScene::init ()) {
        return false;
    }

    world = new b2World (b2Vec2 (0.f, 0.f));

    // WARNING Following line temp to cause critical errors
    //this->addChild (new B2DebugDrawLayer (world, BodyCreator::PixelPerMeter), 9999999);

    // HERE STARTS THE MAGIC
    scheduleUpdate ();
    mState = States::S_GAME;
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    Size visibleSize = Director::getInstance ()->getVisibleSize ();

    // Background
    mBackground = Sprite::create ("gameBackground.png");
    mBackground->setPosition (Vec2 (origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild (mBackground, Layers::BACKGROUND);

    // Player
    mPlayer = Player::create (Vec2 (400.f, 400.f), world);
    this->addChild (mPlayer, Layers::PLAYER);

    mapKeysPressed[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
    mapKeysPressed[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
    mapKeysPressed[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
    mapKeysPressed[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;

    // Create starry background which moves
    for (unsigned int i = 0; i < 100; ++i) {
        Star * star = Star::create (cocos2d::Vec2 (50.f + rand () % (int)(visibleSize.width), 50.f + rand () % (int)(visibleSize.height * 0.9f)));
        star->setScale (0.2f + (rand () % 6) / 10.f);
        star->setOpacity (50 + (rand () % 200));
        this->addChild (star, Layers::SECOND_PLAN);
        vecStars.push_back (star);
    }

    // Assign Box2D contact listener to world
    CL = new ContactListener;
    world->SetContactListener (CL);

    // Points
    pointsLabel = Label::createWithTTF ("Score: " + std::to_string (points), "fonts/DKCoolCrayon.ttf", 25.f);
    pointsLabel->setPosition (10 + pointsLabel->getBoundingBox ().size.width / 2, 20);
    this->addChild (pointsLabel, Layers::GUI);

    // Bars
    mHpBarBorder = Sprite::create ("BarBorder.png");
    mRageBarBorder = Sprite::create ("BarBorder.png");
    mHpBarFill = Sprite::create ("HpBarFill.png");
    mRageBarFill = Sprite::create ("RageBarFill.png");

    mRageBarFill->setTextureRect (cocos2d::Rect (0.f, 0.f, 0.f, mRageBarFill->getBoundingBox ().size.height));
    mRageBarFill->setAnchorPoint (Vec2 (0.f, 0.5f));
    mRageBarBorder->setAnchorPoint (Vec2 (0.f, 0.5f));
    mHpBarBorder->setAnchorPoint (Vec2 (0.f, 0.5f));
    mHpBarFill->setAnchorPoint (Vec2 (0.f, 0.5f));

    mHpBarBorder->setPosition (100.f, visibleSize.height - 30.f);
    mRageBarBorder->setPosition (350.f, visibleSize.height - 30.f);
    mHpBarFill->setPosition (100.f, visibleSize.height - 30.f);
    mRageBarFill->setPosition (350.f, visibleSize.height - 30.f);

    this->addChild (mHpBarFill, Layers::GUI);
    this->addChild (mRageBarFill, Layers::GUI);
    this->addChild (mHpBarBorder, Layers::GUI);
    this->addChild (mRageBarBorder, Layers::GUI);

    return true;
}

// Update
void GameScene::update (float dt) {
    this->updatePhysics (dt);

    // Interpret collisions
    handleCollisions ();

    // Player update
    playerUpdate (dt);

    // Missile update
    missilesUpdate (dt);

    // Enemy update
    enemiesUpdate (dt);

    // Star update
    starsUpdate (dt);

    // GUI update
    guiUpdate (dt);
}


void GameScene::onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ESCAPE: {
            Director::getInstance ()->replaceScene (TransitionFade::create (1, MenuScene::createScene (), Color3B (0, 0, 0)));
            break;
        }
        case EventKeyboard::KeyCode::KEY_SPACE: {
            Missile * missile;
            if (mPlayer->getIsRage ())
                missile = Missile::create (mPlayer->getPosition (), Missiles::M_FIREBALL, Movement::RIGHT, world);
            else
                missile = Missile::create (Vec2 (mPlayer->getPosition ().x + 35, mPlayer->getPosition ().y + 40), Missiles::M_WATERBALL, Movement::RIGHT, world);

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

void GameScene::playerUpdate (float dt) {
    if (mPlayer == nullptr)
        return;

    // Player update
    mPlayer->move (mapKeysPressed[EventKeyboard::KeyCode::KEY_UP_ARROW] * Movement::UP |
                   mapKeysPressed[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] * Movement::RIGHT |
                   mapKeysPressed[EventKeyboard::KeyCode::KEY_DOWN_ARROW] * Movement::DOWN |
                   mapKeysPressed[EventKeyboard::KeyCode::KEY_LEFT_ARROW] * Movement::LEFT,
                   dt);

    // Rage behaviour
    if (mPlayer->getIsRage ()) {
        rageTime += dt;
        if (rageTime > Entities::rageDuration) {
            mPlayer->setIsRage (false);
            rageTime = 0.f;
        }

    }

    // Player destruction
    if (mPlayer->getIsDead ()) {
        if (mPlayer->getParent () != nullptr)
            mPlayer->getParent ()->removeChild (this);

    }
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
    int spawnChance = rand () % currentDifficulty;
    Size visibleSize = Director::getInstance ()->getVisibleSize ();

    if (spawnChance == 0) {
        Enemy * enemy = Enemy::create (cocos2d::Vec2 (visibleSize.width * 1.5, 100 + rand () % (int)(visibleSize.height * 0.8)), Enemies::E_TIEFIGHTER, Movement::LEFT, world);
        this->addChild (enemy, Layers::ENTITIES);
        vecEnemies.push_back (enemy);
    }
    for (unsigned int iEnemy = 0; iEnemy < vecEnemies.size (); ++iEnemy) {
        if (vecEnemies[iEnemy] != nullptr) {
            if (vecEnemies[iEnemy]->getIsValid () && !vecEnemies[iEnemy]->getIsDead ()) {

                int shootChance = rand () % Enemies::shootingFrequency;
                if (shootChance == 0) {
                    Missile * missile;
                    missile = Missile::create (vecEnemies[iEnemy]->getPosition (), Missiles::M_ENEMYS_BALL, Movement::LEFT, world);
                    vecMissiles.push_back (missile);
                    this->addChild (missile, Layers::MISSILES);
                }
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

void GameScene::starsUpdate (float dt) {
    int chance = rand () % Star::chance;
    Size visibleSize = Director::getInstance ()->getVisibleSize ();

    if (chance == 0) {
        Star * star = Star::create (cocos2d::Vec2 (visibleSize.width * 1.03, 100 + rand () % (int)(visibleSize.height * 0.8)));
        star->setScale (0.2f + (rand () % 8) / 10.f);
        star->setOpacity (50 + (rand () % 200));
        this->addChild (star, Layers::SECOND_PLAN);
        vecStars.push_back (star);
    }
    for (unsigned int iStar = 0; iStar < vecStars.size (); ++iStar) {
        if (vecStars[iStar] != nullptr) {
            if (vecStars[iStar]->getIsValid ()) {

                vecStars[iStar]->update (dt);
            }
            else {
                if (vecStars[iStar]->getParent () != nullptr)
                    vecStars[iStar]->getParent ()->removeChild (this);
            }
        }
        else {
            std::swap (vecStars[iStar], vecStars[vecStars.size () - 1]);
            vecEnemies.pop_back ();
        }
    }
}

void GameScene::guiUpdate (float dt) {
    // Points handling
    pointsLabel->setString ("Score: " + std::to_string (points));
    pointsLabel->setPosition (10 + pointsLabel->getBoundingBox ().size.width / 2, 20);

    // Bars update
    mHpBarFill->setTextureRect (cocos2d::Rect (0.f, 0.f,
        _MIN (mPlayer->getHp () / (float)Entities::maxHP * mHpBarBorder->getBoundingBox ().size.width,
        mHpBarBorder->getBoundingBox ().size.width),
        28.f));

    mRageBarFill->setTextureRect (cocos2d::Rect (0.f, 0.f,
        _MIN (mPlayer->getRage () / (float)Entities::rageCharging * mRageBarBorder->getBoundingBox ().size.width,
        mRageBarBorder->getBoundingBox ().size.width),
        28.f));
}

void GameScene::updatePhysics (float dt) {
    int velocityIterations = 8;
    int positionIterations = 3;

    world->Step (dt, velocityIterations, positionIterations);

    // Iterate over the bodies in the physics world
    for (b2Body* b = world->GetBodyList (); b; b = b->GetNext ()) {
        if (b->GetUserData () != NULL) {
            // Synchronize the sprites with bodies
            CCSprite* myActor = (CCSprite*)b->GetUserData ();
            myActor->setPosition (CCPointMake (b->GetPosition ().x * BodyCreator::PixelPerMeter, b->GetPosition ().y * BodyCreator::PixelPerMeter));
            myActor->setRotation (-1 * CC_RADIANS_TO_DEGREES (b->GetAngle ()));
        }
    }
}

void handleCollisions (float dt) {

}

