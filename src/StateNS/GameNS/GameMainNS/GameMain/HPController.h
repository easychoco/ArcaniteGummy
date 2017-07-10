#pragma once

#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Character;

class HPController
{
public:
	HPController(Character* _parent, int _hp);
	~HPController();
	void damage(int val);
	void damageWithAction(int val);
	void recover(int val);
	int getHP() const { return HP; }
	bool isAlive() const { return HP > 0; }

private:
	Character* parent;
	const int maxHP;
	int HP;
};



}
}
}