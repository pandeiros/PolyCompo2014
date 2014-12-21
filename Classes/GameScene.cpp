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

    srand ((int) std::time(NULL));

    if (!MainScene::init ()) {
        return false;
    }

    world = new b2World (b2Vec2 (0.f, 0.f));

    this->addChild (new B2DebugDrawLayer (world, BodyCreator::PixelPerMeter), 9999999);

    // HERE STARTS THE MAGIC
    scheduleUpdate ();
    mState = States::S_GAME;
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    Size visibleSize = Director::getInstance ()->getVisibleSize ();

    // Background
    mBackground = Sprite::create ("gameBackground.png");
    mBackground->setPosition (Vec2 (origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild (mBackground, Layers::BACKGROUND);

    mPlayer = Player::create (Vec2(400.f,400.f), world);
    this->addChild (mPlayer, Layers::PLAYER);

    mapKeysPressed[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
    mapKeysPressed[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
    mapKeysPressed[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
    mapKeysPressed[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;

    for (unsigned int i = 0; i < 100; ++i) {
        Star * star = Star::create (cocos2d::Vec2 (50.f + rand () % (int)(visibleSize.width), 50.f + rand () % (int)(visibleSize.height * 0.9f)));
        star->setScale (0.2f + (rand () % 6) / 10.f);
        star->setOpacity (50 + (rand () % 200));
        this->addChild (star, Layers::SECOND_PLAN);
		vecStars.push_back (star);
    }

    CL = new ContactListener;
    world->SetContactListener (CL);

	// Points
	pointsLabel = LabelTTF::create();
	points = 0;
	std::string boom, boom2;
	boom = "Points: ";
	boom2 = std::to_string(points);
	boom += boom2;
	pointsLabel->setString(boom);
	pointsLabel->setAnchorPoint(ccp(0, 0.f));
	pointsLabel->setPosition(Vec2(0.f, 0.f));
	this->addChild(pointsLabel, Layers::GUI);

    return true;
}

// Update
void GameScene::update (float dt) {
    this->updatePhysics (dt);

    // Player update
    mPlayer->move (mapKeysPressed[EventKeyboard::KeyCode::KEY_UP_ARROW] * Movement::UP |
                   mapKeysPressed[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] * Movement::RIGHT |
                   mapKeysPressed[EventKeyboard::KeyCode::KEY_DOWN_ARROW] * Movement::DOWN |
                   mapKeysPressed[EventKeyboard::KeyCode::KEY_LEFT_ARROW] * Movement::LEFT,
                   dt);

    // Missile update
    missilesUpdate (dt);

    // Enemy update
    enemiesUpdate (dt);

    // Star update
    starsUpdate (dt);

    if (mPlayer->getIsDead ()) {
        if (mPlayer->getParent () != nullptr)
            mPlayer->getParent ()->removeChild (this);

	// Obsluga punktow i enrage
		/* boom = "Points: ";
			boom2 = std::to_string(++points);
			boom += boom2;
			pointsLabel->setString(boom);
			mPlayer->setTexture("aquariusRage.png");
			Missile * missile = Missile::create(mPlayer->getPosition(), Missiles::M_FIREBALL, Movement::RIGHT, world);
			Missile * missile = Missile::create(Vec2(mPlayer->getPosition().x+30, mPlayer->getPosition().y+45), Missiles::M_WATERBALL, Movement::RIGHT, world);
			*/
    }
}


void GameScene::onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ESCAPE: {
            Director::getInstance ()->replaceScene (TransitionFade::create (1, MenuScene::createScene (), Color3B (0, 0, 0)));
            break;
        }
        case EventKeyboard::KeyCode::KEY_SPACE: {
			Missile * missile = Missile::create(Vec2(mPlayer->getPosition().x+30, mPlayer->getPosition().y+45), Missiles::M_WATERBALL, Movement::RIGHT, world);
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
        Enemy * enemy = Enemy::create (cocos2d::Vec2(visibleSize.width * 1.5, 100 + rand() % (int)(visibleSize.height * 0.8)), Enemies::E_TIEFIGHTER, Movement::LEFT, world);
        this->addChild (enemy, Layers::ENTITIES);
        vecEnemies.push_back (enemy);
    }
    for (unsigned int iEnemy = 0; iEnemy < vecEnemies.size (); ++iEnemy) {
        if (vecEnemies[iEnemy] != nullptr) {
            if (vecEnemies[iEnemy]->getIsValid () && !vecEnemies[iEnemy]->getIsDead()) {

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
        star->setScale (0.2f + (rand() % 8) / 10.f);
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

