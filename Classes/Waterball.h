#ifndef WATERBALL
#define WATERBALL

#include "cocos2d.h"

class Waterball : public cocos2d::Sprite
{
public:

	// Constructor & Destructor
	Waterball();
	~Waterball();

	// Update
	void update(float dt);

	// Methods
	static Waterball* create(cocos2d::Vec2 *position);

	void initOptions(cocos2d::Vec2 *position);

};

#endif

