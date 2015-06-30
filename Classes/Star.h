#ifndef STAR
#define STAR

#include "cocos2d.h"
#include "EnumIDs.h"

class Star : public cocos2d::Sprite
{
public:
    static const int chance = 100;

    // Constructor & Destructor
    Star();
    ~Star();

    // Update
    void update(float dt);

    // Methods
    static Star* create(cocos2d::Vec2 position);

    void initOptions(cocos2d::Vec2 position);

    bool getIsValid();

private:
    bool isValid;
};

#endif