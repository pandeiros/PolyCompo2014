#ifndef MISSILE
#define MISSILE

#include "cocos2d.h"
#include "EnumIDs.h"
#include "BodyCreator.h"
#include "Entity.h"

class Missile : public Entity
{
public:
    // Constructor & Destructor
    Missile();
    ~Missile();

    // Update
    void update(float dt);

    // Methods
    static Missile* create (cocos2d::Vec2 position, Missiles::Type type, Movement::Directions direction, b2World * world);

    void initOptions(cocos2d::Vec2 position);

    bool getIsValid ();
    void setInvalid () {
        isValid = false;
        this->setOpacity (0);
        //if (this->getParent () != nullptr)
            //this->getParent ()->removeChild (this);
    }

private:
    bool isValid;
    Movement::Directions direction;
    int dx = 0;
    int dy = 0;
    float speed = 0.f;

    b2Body * body;

};

#endif

