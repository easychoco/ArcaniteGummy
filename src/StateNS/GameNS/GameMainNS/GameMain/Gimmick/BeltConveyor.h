#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class BeltConveyor : public GimmickChild
{
public:
	BeltConveyor();
	~BeltConveyor();
	void initialize();
	void update(PlayerChild*);
	void draw() const;

private:
};




}
}
}