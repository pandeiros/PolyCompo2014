#ifndef GAME_SCENE
#define GAME_SCENE

#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "Enemy.h"
#include "MainScene.h"
#include "Player.h"
#include "Missile.h"
#include "EnumIDs.h"
#include "Star.h"
#include "BodyCreator.h"
#include "ContactListener.h"


class GameScene : public MainScene {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene ();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init ();

    // Update
    virtual void update (float dt);

    // implement the "static create()" method manually
    CREATE_FUNC (GameScene);

    virtual void onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:
    void playerUpdate (float dt);
    void missilesUpdate (float dt);
    void enemiesUpdate (float dt);
    void starsUpdate (float dt);
    void guiUpdate (float dt);
    void updatePhysics (float dt);

    Player * mPlayer;
    std::vector <Missile*> vecMissiles;
    std::vector <Enemy *> vecEnemies;
    std::vector <Star *> vecStars;

	cocos2d::Label * pointsLabel;
    Enemies::Difficulty currentDifficulty = Enemies::EASY;
	int points = 0;
    float rageTime = 0,f;

    b2World * world;
    ContactListener * CL;
};

#endif
