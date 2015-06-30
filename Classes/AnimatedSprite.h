#ifndef ANIMATED_SPRITE
#define ANIMATED_SPRITE

#include "cocos2d.h"
#include "EnumIDs.h"
#include "AnimationUtils.h"
#include <string>

class AnimatedSprite : public cocos2d::Sprite
{
public:
    AnimatedSprite();
    ~AnimatedSprite();

    static AnimatedSprite* create(std::string filename);

    void initOptions();
};

#endif