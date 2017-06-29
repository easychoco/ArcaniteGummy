#include "HPController.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS{


HPController::HPController() : HPController(100)
{
	
}

HPController::HPController(int _hp) : MAX_HP(_hp)
{
	this->HP = this->MAX_HP;
}

HPController::~HPController()
{

}

void HPController::damage(int _val)
{
	this->HP = max(this->HP - _val, 0);
}

void HPController::damageWithAction(int _val)
{
	this->HP = max(this->HP - _val, 0);
}

void HPController::recover(int _val)
{
	this->HP = min(this->HP + _val, this->MAX_HP);
}



}
}
}