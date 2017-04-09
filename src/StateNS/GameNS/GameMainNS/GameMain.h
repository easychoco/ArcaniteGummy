#pragma once

#include "GameMainChild.h"

#include <string>
#include <vector>



namespace StateNS {
namespace GameNS {

class Play;
using GameParent = Play;

namespace GameMainNS{

class GimmickChild;
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
	GimmickChild* mGimmick;
	PlayerChild* mPlayer;
	System* mSystem;
};




}
}
}