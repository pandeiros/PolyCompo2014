#ifndef _PLAYER_
#define _PLAYER_

#include "cocos2d.h"
#include "EnumIDs.h"
#include "BodyCreator.h"

class Player : public cocos2d::Sprite {
public:
    Player ();
    ~Player ();

    static Player* create (cocos2d::Vec2 position);

    void initOptions ();

    void move (unsigned int flags, float dt);

private:
	b2Body * body;
};

#endif
