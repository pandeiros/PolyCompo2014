#ifndef PLAYER
#define PLAYER

#include "cocos2d.h"

class Player : public cocos2d::Sprite {
public:
    Player ();
    ~Player ();

    static Player* create ();

    void initOptions ();

};

#endif
