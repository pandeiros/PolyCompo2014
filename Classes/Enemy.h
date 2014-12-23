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
    static Enemy* create (cocos2d::Vec2 position, Enemies::Type type, Movement::Directions direction, b2World * world);

    void initOptions(cocos2d::Vec2 position);

    bool getIsValid();

    void damage (Damage::Type type);

    bool getIsDead () {
        return isDead;
    }

    void setInvalid () {
        isValid = false;
    }

    void die () {
        isValid = false;
        isDead = true;
        this->setOpacity (0);
        /*if (this->getParent () != nullptr)
            this->getParent ()->removeChild (this);*/
    }

private:
    bool isValid = true; 
    b2Body * body;

    int hp = 50;
    bool isDead = false;
};

#endif

