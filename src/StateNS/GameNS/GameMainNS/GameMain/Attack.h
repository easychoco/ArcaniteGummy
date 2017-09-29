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
	Attack(const Character*, int x, int y, int w, int h);
	Attack(const Character*, int x, int y, int w, int h, ObjectID);
	virtual ~Attack();
	virtual void setStatus(Vector2, int status) = 0;
	virtual void setStatus_2args(Vector2, int status1, int status2) {};
	virtual void update() = 0;
	virtual void draw(const Vector2* camera) const;
	void burnedAction(){ /*do nothing*/ }
	void checkActive(const Vector2* camera);
	int getDamageValue() { return damageValue; }

	bool isActive;
	const Character* parent;
	const ObjectID id;

protected:
	int mImage;
	bool mDirection;
	int damageValue;

};




}
}
}