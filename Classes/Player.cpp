#include "Player.h"

Player::Player () {
}

Player::~Player () {
}

Player* Player::create () {
    Player* pSprite = new Player ();

    if (pSprite->initWithFile ("aquarius.png")) {
        pSprite->autorelease ();

        pSprite->initOptions ();

        return pSprite;
    }

    CC_SAFE_DELETE (pSprite);
    return NULL;
}

void Player::initOptions () {
    this->setPosition (400.f, 400.f);
    this->setScale (0.15);
}

void Player::move (unsigned int flags, float dt) {
    bool xOpposite = false, yOpposite = false;

    cocos2d::Vec2 newVec (((flags & Movement::RIGHT) != 0) -
                          ((flags & Movement::LEFT) != 0),
                          ((flags & Movement::UP) != 0) -
                          ((flags & Movement::DOWN) != 0));

    if ((flags & Movement::UP) && (flags & Movement::DOWN))
        yOpposite = true;

    if ((flags & Movement::LEFT) && (flags & Movement::RIGHT))
        xOpposite = true;

    if (!(xOpposite && yOpposite)) {
        if (((flags & Movement::UP) || (flags & Movement::DOWN)) &&
            ((flags & Movement::LEFT) || (flags & Movement::RIGHT)))
            newVec.normalize ();
    }

    this->setPosition (this->getPosition () + newVec * Movement::playerSpeed * dt);
    
}
