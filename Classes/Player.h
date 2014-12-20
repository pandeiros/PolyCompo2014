#ifndef _PLAYER_
#define _PLAYER_

#include "cocos2d.h"
#include "EnumIDs.h"

class Player : public cocos2d::Sprite {
public:
    Player ();
    ~Player ();

    static Player* create ();

    void initOptions ();

    void move (unsigned int flags, float dt);


};

#endif
