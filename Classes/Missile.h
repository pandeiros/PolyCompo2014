#ifndef MISSILE
#define MISSILE

#include "cocos2d.h"
#include "EnumIDs.h"

class Missile : public cocos2d::Sprite
{
public:

    // Constructor & Destructor
    Missile();
    ~Missile();

    // Update
    void update(float dt);

    // Methods
    static Missile* create(cocos2d::Vec2 position, Missiles::Type type, Movement::Directions direction);

    void initOptions(cocos2d::Vec2 position);

    bool getIsValid ();

private:
    bool isValid;
    Movement::Directions direction;
    int dx = 0;
    int dy = 0;

};

#endif

