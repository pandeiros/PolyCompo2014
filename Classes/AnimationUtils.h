#ifndef ANIMATION_UTILS
#define ANIMATION_UTILS

#include "cocos2d.h"
#define TAG_ANIMATION 6969

class AnimationUtils
{
public:
    static cocos2d::Action* getAnimationRunningForever(std::string name, int tag = TAG_ANIMATION);
    static cocos2d::Action* getAnimationWithCallback(std::string name, std::function<void()> callback, int tag = TAG_ANIMATION);
};

#endif // ANIMATION_UTILS