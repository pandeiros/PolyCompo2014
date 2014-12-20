#include "Missile.h"

Missile::Missile () {
    this->isValid = true;
}


Missile::~Missile () {
}

Missile* Missile::create (cocos2d::Vec2 position, Missiles::Type type, Movement::Directions direction) {
    Missile* missile = new Missile ();
    missile->direction = direction;

    std::string filename = "";
    switch (type) {
        case Missiles::M_WATERBALL:
            filename = "WB_placeholder.png";
            break;
        case Missiles::M_ENEMYS_BALL:
            filename = "EnemyProjectile";
            break;
    }

    switch (direction) {
        case Movement::LEFT :
            missile->dx = -1; break;
        case Movement::DOWN :
            missile->dy = -1; break;
        case Movement::RIGHT :
            missile->dx = 1; break;
        case Movement::UP :
            missile->dy = 1; break;
    }

    if (missile->initWithFile (filename)) {
        missile->autorelease ();
        missile->initOptions (position);

        return missile;
    }

    CC_SAFE_DELETE (missile);
    return NULL;
}

void Missile::update (float dt) {
    
    this->setPosition (this->getPosition () + cocos2d::Vec2 (this->dx, this->dy));

    if (this->getPosition ().x > 3000 || this->getPosition ().x < -1000) {

        this->isValid = false;
    }
}

void Missile::initOptions (cocos2d::Vec2 position) {
    this->setPosition (position);
}

bool Missile::getIsValid () {
    return isValid;
}
