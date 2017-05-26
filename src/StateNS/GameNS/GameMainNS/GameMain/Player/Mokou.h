#pragma once

#include "PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Mokou : public PlayerChild
{
public:
	Mokou(int, int);
	~Mokou();
	PlayerChild* update();
	void draw() const;

private:
	void initialize();

};

using MyData::vectorRate;


}
}
}