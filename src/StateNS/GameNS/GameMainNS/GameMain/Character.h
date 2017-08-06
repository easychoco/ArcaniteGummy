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
	Character(int _hp) : hpController(HPController(this, _hp)){}
	virtual ~Character() { SAFE_DELETE(p); }
	virtual void damagedAction() = 0;
	const Vector2* getVector2() { return p; }
	void moveCharacter(int _dx, int _dy)
	{
		this->p->pos_x += _dx * MyData::vectorRate;
		this->p->pos_y += _dy * MyData::vectorRate;
	}

	HPController hpController;

protected:
	Vector2* p;
};



}
}
}