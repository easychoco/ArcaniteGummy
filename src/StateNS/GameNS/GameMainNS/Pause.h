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
	virtual bool reset() { return resetGame; };

private:
	GameMain* main;
	bool exit;
	bool prePush;
	bool resetGame;
	Vector2 originalCameraPos;

	int cursorPos;
	int img_showStage;
	int img_resetGame;

	enum PauseState
	{
		STATE_HOME, //初めの画面
		STATE_SHOW, //ステージ見回し中
		STATE_RESET,//最初からやり直し中

		STATE_NONE,
	};
	PauseState nowState;

	//Visitor風
	void update_state();

	void update_home();
	void update_show();
	void update_reset();

	void draw_state() const;

	void draw_home() const;
	void draw_show() const;
	void draw_reset() const;


};



}
}
}