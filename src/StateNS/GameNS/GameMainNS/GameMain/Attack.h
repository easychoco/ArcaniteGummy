#pragma once

#include "..\..\..\..\Data.h"
#include "DynamicObject.h"


namespace StateNS {
namespace GameNS {

namespace GameMainNS{

class Collision;
class Character;

class Attack : public DynamicObject
{
public:
	Attack(int x, int y, int w, int h);
	virtual ~Attack();
	virtual void update() = 0;
	virtual void draw(const Vector2*) const = 0;
	int getDamageValue() { return damageValue; }

	bool isActive;
	Character* parent;

private:
	int damageValue;
};




}
}
}