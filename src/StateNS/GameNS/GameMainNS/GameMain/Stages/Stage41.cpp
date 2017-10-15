#include "Stage41.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"
#include "..\Player\PlayerChild.h"
#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage41::Stage41() :
StageChild(4, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage41::~Stage41()
{

}

void Stage41::initialize()
{

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;
	this->changeableCharacter |= CHARA_NUE;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(41, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(41, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(41, 2, MapPos::POS_LEFT_FREE));

	flag = new ClearFlag(Vector2(97 * 32 + 16, 16 * 32 + 16));
	maps[2]->addGimmick(flag);

	startX = 77*32, startY = 48*32;
	converseFlag0 = true;

	converseFlag1 = true;
	cTime = 0;

	imageFlan = LoadGraph("Data/Image/Character/haribote_flan.png");
	findRestartPoint();
}


void Stage41::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain,_player);
	standardUpdate(_player);
}

void Stage41::updateConverse(GameMain* gameMain, PlayerChild* _player)
{
	cTime = min(cTime, 180);
	if (converseFlag1 && cTime == 180)
	{
		gameMain->startConverse(411);
		converseFlag1 = false;
	}

	if (cTime == 90)
	{
		this->changeableCharacter ^= CHARA_MOKOU;
		this->changeableCharacter ^= CHARA_SAKUYA;
		//////////////////強制的にぬえに変更する関数をここに/////////////////
		DeleteGraph(imageFlan);
	}
	if (cTime < 180)_player->lock = true;

	if (converseFlag0)
	{
		gameMain->startConverse(410);
		converseFlag0 = false;
	}
	cTime++;
}


void Stage41::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
	if (cTime<=90)DrawRotaGraph(420, 416, 1.0, 0.0, imageFlan, TRUE);
}

void Stage41::draw_front(const Vector2* _camera) const
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 -   0.03*(cTime-90)*(cTime - 90));
	DrawCircle(320, 240, cTime * 12, YELLOW, TRUE, 1);
	DrawCircle(320, 240, cTime * 12, RED, FALSE,5);
	DrawBox(0, 0, 640, 480, WHITE, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool Stage41::isClear() const
{
	return !flag->isActive;
}



}
}
}


