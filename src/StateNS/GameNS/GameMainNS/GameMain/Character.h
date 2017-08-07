#pragma once

#include "..\..\..\..\Data.h"
#include "HPController.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


//Ž©‹@‚Æ“G‚Å‹¤’Ê‚·‚és“®
class Character
{
public:
	Character(int _hp) : hpController(HPController(this, _hp)) { p = 0; next_dx = next_dy = 0; }
	virtual ~Character() { SAFE_DELETE(p); }
	virtual void damagedAction() = 0;
	const Vector2* getVector2() { return p; }
	void moveCharacter(float _dx, float _dy)
	{
		this->next_dx += (int)(_dx * MyData::vectorRate);
		this->next_dy += (int)(_dy * MyData::vectorRate);
	}

	HPController hpController;

protected:
	Vector2* p;
	int next_dx;
	int next_dy;
};



}
}
}