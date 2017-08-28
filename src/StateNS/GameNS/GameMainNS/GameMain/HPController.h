#pragma once

#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Character;

class HPController
{
public:
	HPController(Character* parent, int hp);
	~HPController();
	void damage(int val);
	void damage(int val, bool action);
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