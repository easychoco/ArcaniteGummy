#pragma once

#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Character;

class HPController
{
public:
	HPController(Character* parent, int maxHP);
	HPController(Character* parent, int maxHP, int nowHP);
	~HPController();
	void damage(int val);
	void damage(int val, bool action);
	void recover(int val);
	int getHP() const { return HP; }
	bool isAlive() const { return HP > 0; }
	bool isMuteki;

private:
	Character* parent = 0;
	const int maxHP;
	int HP;
};



}
}
}