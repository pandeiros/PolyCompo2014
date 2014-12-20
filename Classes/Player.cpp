#include "Player.h"

Player::Player () {
}

Player::~Player () {
}

Player* Player::create(cocos2d::Vec2 position) {
    Player* pSprite = new Player ();
	pSprite->body = BodyCreator::createBody(Entities::PLAYER, b2Vec2(position.x / BodyCreator::PixelPerMeter, position.y / BodyCreator::PixelPerMeter));

    if (pSprite->initWithFile ("aquarius.png")) {
        pSprite->autorelease ();
		pSprite->setPosition(position);

        pSprite->initOptions ();

        return pSprite;
    }

    CC_SAFE_DELETE (pSprite);
    return NULL;
}

void Player::initOptions () {
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
	newVec *= Movement::playerSpeed * dt;

	body->SetTransform(body->GetPosition() + BodyCreator::convertToBoxVec(newVec), 0.f);
    this->setPosition (this->getPosition() + newVec);
}
