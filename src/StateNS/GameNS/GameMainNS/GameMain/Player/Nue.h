#pragma once

#include "PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Nue : public PlayerChild
{
public:
	Nue();
	~Nue();
	PlayerChild* update();
	void draw() const;

};




}
}
}