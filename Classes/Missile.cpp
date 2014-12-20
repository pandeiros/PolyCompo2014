#include "Missile.h"

const int SPEED = 1000;

Missile::Missile()
{
}


Missile::~Missile()
{
}

Missile* Missile::create(cocos2d::Vec2 position, Missiles::Type type, Movement::Directions direction) {
	Missile* wbSprite = new Missile();

	if (wbSprite->initWithFile("WB_placeholder.png")) {
		wbSprite->autorelease();

		wbSprite->initOptions(position);

		return wbSprite;
	}

	CC_SAFE_DELETE(wbSprite);
	return NULL;
}

void Missile::update(float dt){
	this->setPosition(this->getPosition() + cocos2d::Vec2(SPEED*dt, 0));
}

void Missile::initOptions(cocos2d::Vec2 position){
	this->setPosition(position);
}
