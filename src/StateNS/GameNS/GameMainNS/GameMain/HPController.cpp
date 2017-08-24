#include "HPController.h"
#include "Character.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


HPController::HPController(Character* _parent, int _hp) : maxHP(_hp)
{
	this->HP = this->maxHP;
	this->parent = _parent;
}

HPController::~HPController()
{
	this->parent = 0;
}

void HPController::damage(int _val)
{
	this->damage(_val, true);
}

void HPController::damage(int _val, bool action)
{
	if (parent->damaged)return;
	this->HP = max(this->HP - _val, 0);
	if (action)
	{
		parent->damaged = true;
	}
}

void HPController::recover(int _val)
{
	this->HP = min(this->HP + _val, this->maxHP);
}



}
}
}