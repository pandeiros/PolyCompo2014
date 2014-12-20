#include "Waterball.h"


Waterball::Waterball()
{
}


Waterball::~Waterball()
{
}

Waterball* Waterball::create(cocos2d::Vec2 *position) {
	Waterball* wbSprite = new Waterball();

	if (wbSprite->initWithFile("WB_placeholder.png")) {
		wbSprite->autorelease();

		wbSprite->initOptions(position);

		return wbSprite;
	}

	CC_SAFE_DELETE(wbSprite);
	return NULL;
}

void Waterball::initOptions(cocos2d::Vec2 *position){
	this->setPosition(*position);
}
