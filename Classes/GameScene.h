#ifndef GAME_SCENE
#define GAME_SCENE

#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "MainScene.h"
#include "Player.h"
#include "Missile.h"
#include "Enemy.h"
#include "EnumIDs.h"
#include "Star.h";

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
    void missilesUpdate (float dt);
    void enemiesUpdate (float dt);
    void starsUpdate (float dt);

    Player * mPlayer;
    std::vector <Missile*> vecMissiles;
    std::vector <Enemy*> vecEnemies;
    std::vector <Star*> vecStars;

    b2World * world;
};

#endif // GAME_SCENE
