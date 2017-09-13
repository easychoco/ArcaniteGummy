#pragma once

#include "GameMainChild.h"

//#include <string>
#include <vector>



namespace StateNS {
namespace GameNS {

class Play;
using GameParent = Play;

namespace GameMainNS{

class Stage;
class PlayerChild;
class System;
class EnemyController;

class GameMain : public Child
{
public:
	GameMain(int stageID,int width,int height);
	~GameMain();
	void initialize();
	Child* update(GameParent*);
	void draw() const;
	void setStopDynamicObject(bool _flag){ stopDynamicObject = _flag; }

	enum HowStageMove
	{
		MOVE_NONE,

		MOVE_UP,
		MOVE_RIGHT,
		MOVE_LEFT,
		MOVE_DOWN,
	};



private:
	std::vector<Stage*> mStages;
	PlayerChild* mPlayer;
	System* mSystem;
	EnemyController* mEController;
	int stageID;
	int xNum, yNum;

	int nowStageNum;

	//~‚ß‚âƒLƒƒƒ‰•ÏX‚Ì‚ÉA“®‚¢‚Ä‚¢‚é‚à‚Ì‚ğ~‚ß‚é
	bool stopDynamicObject;

	void updateDynamics(Stage* stage);
	void processCollision(Stage* stage);
};




}
}
}