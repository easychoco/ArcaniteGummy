#pragma once

#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class HPController
{
public:
	HPController();
	HPController(int HP);
	~HPController();
	void damage(int val);
	void damageWithAction(int val);
	void recover(int val);
	int getHP() const { return HP; }
	bool isAlive() const { return HP > 0; }

private:
	const int MAX_HP;
	int HP;
};


}
}
}