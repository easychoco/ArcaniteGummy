#pragma once

//#include "..\Play.h"
#include <vector>


namespace StateNS {
namespace GameNS {

class Play;
using GameParent = Play;

namespace GameMainNS{


class Child
{
public:
	virtual ~Child() {};
	virtual Child* update(GameParent*) = 0;
	virtual void draw() const = 0;
};




}
}
}