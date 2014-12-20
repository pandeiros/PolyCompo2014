#include "Missile.h"

const int SPEED = 1000;

Missile::Missile()
{
    this->isValid = true;
}


Missile::~Missile()
{
}

Missile* Missile::create(cocos2d::Vec2 position, Missiles::Type type, Movement::Directions direction) {
    Missile* missile = new Missile();

    if (missile->initWithFile ("WB_placeholder.png")) {
        missile->autorelease ();

        missile->initOptions (position);

        return missile;
    }

    CC_SAFE_DELETE (missile);
    return NULL;
}

void Missile::update (float dt) {
    this->setPosition (this->getPosition () + cocos2d::Vec2 (SPEED*dt, 0));

    if (this->getPosition ().x > 3000 || this->getPosition ().x < -1000) {
        
        this->isValid = false;
    }
}

void Missile::initOptions(cocos2d::Vec2 position){
    this->setPosition(position);
}

bool Missile::getIsValid () {
    return isValid;
}
