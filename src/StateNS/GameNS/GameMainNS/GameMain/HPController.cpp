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
	this->HP = max(this->HP - _val, 0);
}

void HPController::damageWithAction(int _val)
{
	this->HP = max(this->HP - _val, 0);
	if (parent)parent->damagedAction();
}

void HPController::recover(int _val)
{
	this->HP = min(this->HP + _val, this->maxHP);
}



}
}
}