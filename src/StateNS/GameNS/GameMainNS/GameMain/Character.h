#pragma once

#include "..\..\..\..\Data.h"
#include "HPController.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


//自機と敵で共通する行動
class Character
{
public:
	Character(int _hp) : hpController(HPController(this, _hp)){}
	virtual ~Character(){}
	virtual void damagedAction() = 0;
	HPController hpController;
};



}
}
}