#ifndef _ENTITY_
#define _ENTITY_

#include "cocos2d.h"
#include "EnumIDs.h"
#include "BodyCreator.h"

class Entity : public cocos2d::Sprite {
public:
    Entities::Type type;

    Entity ();
    ~Entity ();
};

#endif
