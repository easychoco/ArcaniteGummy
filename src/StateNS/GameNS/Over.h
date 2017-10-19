#pragma once

#include "GameChild.h"

namespace StateNS {

class Parent;

namespace GameNS {


class Over : public Child
{
public:
	Over();
	~Over();
	Child* update(StateNS::Parent*);
	void draw() const;

private:
	void initialize();
	int backImg;
	bool prePushZ;
	bool prePushUD;
	int cursorPos;

};




}
}