#ifndef ENEMY
#define ENEMY

#include "cocos2d.h"
#include "EnumIDs.h"

class Enemy : public cocos2d::Sprite
{
public:
	Enemy();
	~Enemy();

	// Update
	void update(float dt);

	// Methods
	static Enemy* create(cocos2d::Vec2 position, Enemies::Type type, Movement::Directions direction);

	void initOptions(cocos2d::Vec2 position);

	bool getIsValid();

private:
	bool isValid;

};

#endif

