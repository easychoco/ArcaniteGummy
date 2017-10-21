#include "Stage41.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"
#include "..\Player\PlayerChild.h"
#include "..\Gimmick\Guide.h"
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
	sound->deleteSound("bgm4");
	DeleteGraph(imageFlan);
}

void Stage41::initialize()
{
	sound->setSound("Data/Sound/hyakunen.wav", "bgm4");
	sound->playSound("bgm4", LOOP, false);

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;
	this->changeableCharacter |= CHARA_NUE;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(41, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(41, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(41, 2, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(41, 3, MapPos::POS_LEFT_FREE));

	vector<string> message
	{
		"ぬえはUFOに乗って",
		"遠くに飛ぶことが",
		"できるぞ"
	};
	Guide* guide = new Guide(5 * 32 + 16, 48 * 32 + 16, message);
	maps[1]->addGimmick(guide);

	vector<string> message2
	{
		"しゃがむことで",
		"変化して",
		"敵の攻撃を",
		"防げるぞ"
	};
	Guide* guide2 = new Guide(31 * 32 + 16, 21 * 32 + 16, message2);
	maps[1]->addGimmick(guide2);


	flag = new ClearFlag(Vector2(97 * 32 + 16, 16 * 32 + 16));
	maps[3]->addGimmick(flag);

	startX = 77*32, startY = 48*32;
	converseFlag0 = true;

	converseFlag1 = true;
	cTime = 0;

	imageFlan = LoadGraph("Data/Image/haribote_flan.png");
	//復活
	bool restart = findRestartPoint();
	//復活したら会話フラグを折る
	if (restart)
	{
		converseFlag0 = false;
		converseFlag1 = false;
	}
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
		gameMain->setNextCharacter(PlayerCharacter::CHARA_NUE);
		this->changeableCharacter ^= CHARA_MOKOU;
		this->changeableCharacter ^= CHARA_SAKUYA;
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
	//爆発を表現
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (int)(0.03*(cTime-90)*(cTime - 90)));
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


