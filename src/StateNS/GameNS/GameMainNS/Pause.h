#pragma once

#include "GameMainChild.h"
#include "..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class GameMain;

class Pause : public Child
{
public:
	Pause(GameMain*);
	~Pause();
	void initialize();
	Child* update(GameParent*);
	void draw() const;

private:
	GameMain* main;
	bool prePush;
	const Vector2* originalCameraPos;


};



}
}
}