#pragma once

#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Character;

class Collision
{
public:
	Collision(Character*, int, int);
	~Collision();
	bool isHit(const Collision* other) const;

	Character* parent;
	const Vector2* p;
	int width;
	int height;
};




}
}
}