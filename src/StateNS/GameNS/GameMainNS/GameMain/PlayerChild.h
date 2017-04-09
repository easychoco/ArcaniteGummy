#pragma once

#include <vector>


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class PlayerChild
{
public:
	virtual ~PlayerChild() {};
	virtual PlayerChild* update() = 0;
	virtual void draw() const = 0;
};




}
}
}