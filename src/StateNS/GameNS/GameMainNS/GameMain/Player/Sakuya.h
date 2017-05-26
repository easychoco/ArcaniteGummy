#pragma once

#include "PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Sakuya : public PlayerChild
{
public:
	Sakuya();
	~Sakuya();
	PlayerChild* update();
	void draw() const;

};




}
}
}