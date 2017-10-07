#pragma once

#include "GameMainChild.h"
#include "..\..\..\Data.h"


namespace StateNS {
namespace GameNS {

class Play;
using GameParent = Play;

namespace GameMainNS{

class StageChild;
class PlayerChild;
class System;
class EnemyController;

enum StopType { TYPE_SAKUYA, TYPE_CHANGE, TYPE_NONE };

enum FilterType{ FILTER_DARK, FILTER_NONE, };

class GameMain : public Child
{
public:
	GameMain(int stageID);
	~GameMain();
	void initialize();
	Child* update(GameParent*);
	void draw() const;

	void startConverse(int _convNum) { this->converseNum = _convNum; }
	void setFilter(FilterType _f);
	const Vector2* getCameraPos() const;
	void moveCamera(int dx, int dy);
	void setCamera(const Vector2&);

private:
	StageChild* mStage;
	PlayerChild* mPlayer;
	System* mSystem;
	EnemyController* mEController;
	int stageID;

	int mTime;
	int converseNum;

	//~‚ß‚âƒLƒƒƒ‰•ÏX‚Ì‚ÉA“®‚¢‚Ä‚¢‚é‚à‚Ì‚ğ~‚ß‚é
	StopType stopDynamicObject;

	void updateDynamics(StageChild* stage);
	void processCollision(StageChild* stage);
	StageChild* getNextStage(int);
};




}
}
}