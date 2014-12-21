#ifndef _ENEMY
#define _ENEMY

#include "cocos2d.h"
#include "EnumIDs.h"
#include <Box2D\Box2D.h>
#include "BodyCreator.h"
#include "Entity.h"

class Enemy : public Entity
{
public:
    Enemy();
    ~Enemy();

    // Update
    void update(float dt);

    // Methods
    static Enemy* create(cocos2d::Vec2 position, Enemies::Type type, Movement::Directions direction);

    void initOptions(cocos2d::Vec2 position);

    bool getIsValid();

    void damage (Damage::Type type);

    bool getIsDead () {
        return isDead;
    }

private:
    bool isValid; 
    b2Body * body;

    int hp = 50;
    bool isDead = false;
};

#endif

