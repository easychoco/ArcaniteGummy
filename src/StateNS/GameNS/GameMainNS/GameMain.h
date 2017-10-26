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
enum PlayerCharacter{ CHARA_MOKOU, CHARA_SAKUYA, CHARA_NUE, CHARA_NONE };

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

	void setNextCharacter(PlayerCharacter);


private:
	StageChild* mStage = 0;
	PlayerChild* mPlayer = 0;
	System* mSystem = 0;
	EnemyController* mEController = 0;
	int stageID;

	int mTime;
	int converseNum;

	int icon_mokou;
	int icon_sakuya;
	int icon_nue;

	PlayerCharacter nextCharacter;
	bool ufoLoaded;

	int changeableCharacter;

	//~‚ß‚âƒLƒƒƒ‰•ÏX‚Ì‚ÉA“®‚¢‚Ä‚¢‚é‚à‚Ì‚ğ~‚ß‚é
	StopType stopDynamicObject;

	void updateDynamics(StageChild* stage);
	void updateStoppingDynamics(StageChild* stage);
	void processCollision(StageChild* stage);
	StageChild* getNextStage(int);
	void drawPlayerInfo() const;


};




}
}
}