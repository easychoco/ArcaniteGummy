#pragma once

#include "..\..\..\..\Data.h"
#include "DynamicObject.h"


namespace StateNS {
namespace GameNS {

namespace GameMainNS{

class Collision;
class PlayerChild;

class Attack : public DynamicObject
{
public:
	Attack(const PlayerChild*, int x, int y, int w, int h);
	Attack(const PlayerChild*, int x, int y, int w, int h, ObjectID);
	virtual ~Attack();
	virtual void setStatus(Vector2, int status) = 0;
	virtual void update() = 0;
	void draw(const Vector2*) const;
	void burnedAction(){ /*do nothing*/ }
	void checkActive(const Vector2* camera);
	int getDamageValue() { return damageValue; }

	bool isActive;
	const PlayerChild* parent;

	const ObjectID id;

protected:
	int mImage;
	bool mDirection;
	int damageValue;

};




}
}
}