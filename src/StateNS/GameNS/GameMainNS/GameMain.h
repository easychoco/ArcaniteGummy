#pragma once

#include "GameMainChild.h"

#include <string>
#include <vector>



namespace StateNS {
namespace GameNS {

class Play;
using GameParent = Play;

namespace GameMainNS{

class Stage;
class PlayerChild;
class System;

class GameMain : public Child
{
public:
	GameMain();
	~GameMain();
	void initialize();
	Child* update(GameParent*);
	void draw() const;


private:
	Stage* mStage;
	PlayerChild* mPlayer;
	System* mSystem;
};




}
}
}