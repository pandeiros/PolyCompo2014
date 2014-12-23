#include "Player.h"

Player::Player () {
}

Player::~Player () {
}

Player* Player::create (cocos2d::Vec2 position, b2World * world) {
    Player* pSprite = new Player ();
    pSprite->body = BodyCreator::createBody<Player>(Entities::PLAYER, BodyCreator::convertToBoxVec(position), pSprite, world);
    pSprite->type = Entities::PLAYER;

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

    body->SetLinearVelocity (BodyCreator::convertToBoxVec (newVec)); 
}

void Player::damage (Damage::Type type) {
    hp -= type;
    if (hp <= 0) {
        isDead = true;
    }
}

void Player::setIsRage(const bool & rage){
	if (isRage != rage){
		if (rage)
			setTexture("aquariusRage.png");
		else{
			setTexture("aquarius.png");
			resetRage();
		}
	}
	isRage = rage;
}

bool Player::getIsRage(){
	return isRage;
}

int Player::getHp () {
    return hp;
}

void Player::rageIncrease(){
	if (!isRage){		
		++rage;
		if (rage >= Entities::rageCharging)
		{
			resetRage();
			setIsRage(true);
		}
	}
}

void Player::resetRage(){
	rage = 0;
}





