#ifndef WATERBALL
#define WATERBALL

#include "cocos2d.h"

class Waterball : public cocos2d::Sprite
{
public:
	// Cechy
	int damage;
	float missile_speed;

	// Constructor & Destructor
	Waterball();
	~Waterball();

	// Update
	//virtual void update();

	// Methods
	static Waterball* create(cocos2d::Vec2 *position);

	void initOptions(cocos2d::Vec2 *position);

};

#endif

