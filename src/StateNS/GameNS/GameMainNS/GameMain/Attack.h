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
	virtual void setStatus(Vector2, int status) = 0;
	virtual void update() = 0;
	void draw(const Vector2*) const;
	void checkActive(const Vector2* camera);
	int getDamageValue() { return damageValue; }

	bool isActive;
	Character* parent;

protected:
	int mImage;
	bool mDirection;
	int damageValue;
};




}
}
}