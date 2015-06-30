#ifndef _ENTITY_
#define _ENTITY_

#define _MAX(a,b) (((a) > (b)) ? (a) : (b))
#define _MIN(a,b) (((a) < (b)) ? (a) : (b))

#include "cocos2d.h"
#include "EnumIDs.h"
#include "BodyCreator.h"

class Entity : public cocos2d::Sprite
{
public:
    Entities::Type type;

    Entity();
    ~Entity();
};

#endif
