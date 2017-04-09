#pragma once

#include "PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Mokou : public PlayerChild
{
public:
	Mokou();
	~Mokou();
	PlayerChild* update();
	void draw() const;

};




}
}
}