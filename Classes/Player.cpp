#include "Player.h"

Player::Player () {
}

Player::~Player () {
}

Player* Player::create () {
    Player* pSprite = new Player ();

    if (pSprite->initWithFile ("DeafStar.png")) {
        pSprite->autorelease ();

        pSprite->initOptions ();

        return pSprite;
    }

    CC_SAFE_DELETE (pSprite);
    return NULL;
}

void Player::initOptions () {
    this->setPosition (400.f, 400.f);
}
