#include "Enemy.h"


Enemy::Enemy () {
}


Enemy::~Enemy () {
}

Enemy* Enemy::create (cocos2d::Vec2 position, Enemies::Type type, Movement::Directions direction) {
    Enemy* wbSprite = new Enemy ();

    std::string filename;

    switch (type) {
        case 0:
            filename = "TieFighter.png";
            break;
        default:
            filename = "TieFighter.png";
            break;
    }

    if (wbSprite->initWithFile (filename)) {
        wbSprite->autorelease ();

        wbSprite->initOptions (position);

        return wbSprite;
    }

    CC_SAFE_DELETE (wbSprite);
    return NULL;
}

void Enemy::update (float dt) {
    this->setPosition (this->getPosition () - cocos2d::Vec2 (Movement::enemySpeed *dt, 0));

    if (this->getPosition ().x > 3000 || this->getPosition ().x < -1000) {
        this->isValid = false;
    }
}

void Enemy::initOptions (cocos2d::Vec2 position) {
    this->setPosition (position);
}

bool Enemy::getIsValid () {
    return isValid;
}
