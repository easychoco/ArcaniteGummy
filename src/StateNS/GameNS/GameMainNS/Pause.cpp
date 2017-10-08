#include "Pause.h"
#include "..\..\StateParent.h"


#include "GameMain.h"
#include "..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Pause::Pause(GameMain* _main)
{
	main = _main;
	initialize();
}

Pause::~Pause()
{
	DeleteGraph(img_showStage);
	DeleteGraph(img_resetGame);
}

void Pause::initialize()
{
	exit = false;
	prePush = true;
	resetGame = false;
	originalCameraPos = *(main->getCameraPos());

	cursorPos = 0;
	nowState = STATE_HOME;

	img_showStage = LoadGraph("Data/Image/ShowStage.png");
	img_resetGame = LoadGraph("Data/Image/ResetGame.png");
	assert(img_showStage != -1 && "ShowStage.png読み込みエラー");
	assert(img_resetGame != -1 && "ResetGame.png読み込みエラー");
}

Child* Pause::update(GameParent* _parent)
{
	Child* next = this;

	update_state();
	
	if (!prePush && Input_A())exit = true;

	if (exit)next = main;

	prePush = Input_A() || Input_OK() || Input_NO() || Input_UP() || Input_DOWN();
	return next;
}

void Pause::draw() const
{
	main->draw();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
	DrawBox(0, 0, 640, 480, BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	draw_state();
}


//==============================================
//内部プライベート関数
//==============================================
void Pause::update_state()
{
	switch (nowState)
	{
	case STATE_HOME: update_home(); break;
	case STATE_SHOW: update_show(); break;
	case STATE_RESET:update_reset(); break;
	}
}

void Pause::draw_state() const
{
	switch (nowState)
	{
	case STATE_HOME: draw_home(); break;
	case STATE_SHOW: draw_show(); break;
	case STATE_RESET:draw_reset(); break;
	}
}

void Pause::update_home()
{
	if (prePush)return;

	if (Input_UP())cursorPos = ((cursorPos + 1) % 2); // + 1 の 1 は，剰余をとる 2 - 1 の 1
	if (Input_DOWN())cursorPos = ((cursorPos + 1) % 2);

	if (Input_OK())
	{
		switch (cursorPos)
		{
		case 0: nowState = STATE_SHOW; break;
		case 1: nowState = STATE_RESET; break;
		}
	}
	if (Input_NO())exit = true;
}

void Pause::update_show()
{
	int dx = (Input_RIGHT() - Input_LEFT()) * 10;
	int dy = (Input_DOWN() - Input_UP()) * 10;

	main->moveCamera(dx, dy);

	if (Input_OK())main->setCamera(originalCameraPos);
	if (Input_NO())nowState = STATE_HOME;
}

void Pause::update_reset()
{
	if (prePush)return;

	if (Input_OK())
	{
		resetGame = true;
	}
	if (Input_NO())nowState = STATE_HOME;
}


void Pause::draw_home() const
{
	DrawGraph(0, 30, img_showStage, true);
	DrawGraph(0, 60, img_resetGame, true);

	DrawBox(0, 42 + 30 * cursorPos, 320, 68 + 30 * cursorPos, GREEN, false);
}

void Pause::draw_show() const
{
	DrawGraph(0, 30, img_showStage, true);

	//背景枠描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(20, 380, 350, 480, BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	//選択肢描画
	DrawString(30, 390, "方向キー: カメラ移動", WHITE);
	DrawString(30, 420, "決定ボタン: カメラをもとに戻す", WHITE);
	DrawString(30, 450, "戻るボタン: ひとつ戻る", WHITE);
}

void Pause::draw_reset() const
{
	DrawGraph(0, 60, img_resetGame, true);

	//背景枠描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(150, 150, 490, 250, BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	//選択肢描画
	DrawString(160, 160, "本当にやり直す？", WHITE);
	DrawString(160, 190, "決定ボタン: はい", WHITE);
	DrawString(160, 220, "戻るボタン: いいえ", WHITE);
}



}
}
}

