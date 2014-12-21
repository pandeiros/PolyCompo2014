#ifndef _PLAYER_
#define _PLAYER_

#include "cocos2d.h"
#include "EnumIDs.h"
#include "BodyCreator.h"
#include "Entity.h"

class Player : public Entity {
public:
    Player ();
    ~Player ();

    static Player* create (cocos2d::Vec2 position, b2World * world);

    void initOptions ();

    void move (unsigned int flags, float dt);

    void damage (Damage::Type type);

    bool getIsDead () {
        return isDead;
    }

private:
    b2Body * body;

    int hp = 100;
    bool isDead = false;
};

#endif
