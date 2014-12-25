#include "Star.h"

Star::Star () {
}

Star::~Star () {
}

Star* Star::create (cocos2d::Vec2 position) {
    Star* star = new Star ();

    if (star->initWithFile ("sprites/star.png")) {
        star->autorelease ();

        star->initOptions (position);

        return star;
    }

    CC_SAFE_DELETE (star);
    return NULL;
}

void Star::update (float dt) {
    this->setPosition (this->getPosition () + cocos2d::Vec2 (-Movement::starSpeed * dt, 0));

    if (this->getPosition ().x > 3000 || this->getPosition ().x < -1000) {

        this->isValid = false;
    }
}

void Star::initOptions (cocos2d::Vec2 position) {
    this->setPosition (position);
}

bool Star::getIsValid () {
    return isValid;
}
