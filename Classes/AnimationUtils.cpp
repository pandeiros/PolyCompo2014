#include "AnimationUtils.h"

#include <cstdlib>

USING_NS_CC;

Action* AnimationUtils::getAnimationRunningForever(std::string name, int tag)
{
    auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->animationByName(name)));
    action->setTag(tag);
    return action;
}

Action* AnimationUtils::getAnimationWithCallback(std::string name, std::function<void()> callback, int tag)
{
    auto action = Sequence::create(Animate::create(AnimationCache::getInstance()->animationByName(name)), CallFunc::create(callback), NULL);
    action->setTag(tag);
    return action;
}