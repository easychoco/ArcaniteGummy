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
	sound->deleteSound("pause");

	if (resetGame)SAFE_DELETE(main);
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
	assert(img_showStage != -1 && "ShowStage.png�ǂݍ��݃G���[");
	assert(img_resetGame != -1 && "ResetGame.png�ǂݍ��݃G���[");

	sound->setSound("Data/Sound/Pause.mp3", "pause");
	sound->playSound("pause");
}

Child* Pause::update(GameParent* _parent)
{
	Child* next = this;

	update_state();
	
	if (!prePush && Input_A())exit = true;

	if (exit)next = main;

	if (!prePush && Input_OK())sound->playSound("ok", BACK, true);
	if (!prePush && Input_NO())sound->playSound("no", BACK, true);

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
//�����v���C�x�[�g�֐�
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

	if (Input_UP())cursorPos = ((cursorPos + 1) % 2); // + 1 �� 1 �́C��]���Ƃ� 2 - 1 �� 1
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
		saveData->resetCheckPoint();
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

	//�w�i�g�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(20, 380, 350, 480, BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	//�I�����`��
	DrawString(30, 390, "�����L�[: �J�����ړ�", WHITE);
	DrawString(30, 420, "����{�^��: �J���������Ƃɖ߂�", WHITE);
	DrawString(30, 450, "�߂�{�^��: �ЂƂ߂�", WHITE);
}

void Pause::draw_reset() const
{
	DrawGraph(0, 60, img_resetGame, true);

	//�w�i�g�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(150, 150, 490, 250, BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	//�I�����`��
	DrawString(160, 160, "�{���ɂ�蒼���H", WHITE);
	DrawString(160, 190, "����{�^��: �͂�", WHITE);
	DrawString(160, 220, "�߂�{�^��: ������", WHITE);
}



}
}
}

