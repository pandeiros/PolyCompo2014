#include "Missile.h"

Missile::Missile () {
    this->isValid = true;
}


Missile::~Missile () {
}

Missile* Missile::create (cocos2d::Vec2 position, Missiles::Type type, Movement::Directions direction, b2World * world) {
    Missile* missile = new Missile ();
    missile->direction = direction;

    std::string filename = "";
    switch (type) {
        case Missiles::M_WATERBALL:
            filename = "waterball.png";
            missile->type = Entities::WATERBALL;
            missile->setScale (1.5f);
            missile->speed = Movement::playerMissileSpeed;
            break;
        case Missiles::M_FIREBALL:
            filename = "fireball.png";
            missile->type = Entities::FIREBALL;
            missile->setScale (1.25f);
            missile->speed = Movement::playerMissileSpeed * 0.75;
            break;
        case Missiles::M_ENEMYS_BALL:
            filename = "enemyLaser.png";
            missile->type = Entities::LASER;
            missile->setScale (0.6f);
            missile->speed = Movement::enemyMissileSpeed;
            break;
    }

    switch (direction) {
        case Movement::LEFT:
            missile->dx = -1; break;
        case Movement::DOWN:
            missile->dy = -1; break;
        case Movement::RIGHT:
            missile->dx = 1; break;
        case Movement::UP:
            missile->dy = 1; break;
    }

    missile->body = BodyCreator::createBody<Missile> (missile->type, BodyCreator::convertToBoxVec (position), missile, world);

    if (missile->initWithFile (filename)) {
        missile->autorelease ();
        missile->initOptions (position);

        return missile;
    }

    CC_SAFE_DELETE (missile);
    return NULL;
}

void Missile::update (float dt) {

    //this->setPosition (this->getPosition () + cocos2d::Vec2 (this->dx * Movement::missileSpeed * dt, this->dy * Movement::missileSpeed * dt));
    body->SetLinearVelocity (BodyCreator::convertToBoxVec (cocos2d::Vec2 (this->dx * speed * dt, this->dy * speed * dt)));
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
