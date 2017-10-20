#include "Stage33.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include "..\Gimmick\Door.h"
#include "..\Gimmick\CheckPoint.h"
#include "..\Player\PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage33::Stage33() :
StageChild(3, 3) //エリアの数: よこ，たて
{
	initialize();
}

Stage33::~Stage33()
{
	DeleteGraph(imageReisen);
	DeleteGraph(imageNue);
	DeleteGraph(imageMokou);
	sound->deleteSound("bgm3");
	sound->deleteSound("boss3");
}

void Stage33::initialize()
{
	sound->setSound("Data/Sound/Phantom_Ship.wav", "bgm3");
	sound->setSound("Data/Sound/husi.wav", "boss3");
	sound->playSound("bgm3", LOOP, false);

	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(33, 0, MapPos::POS_DOWN_FREE));
	this->maps.push_back(new Map(33, 1, MapPos::POS_SINGLE));
	this->maps.push_back(new Map(33, 2, MapPos::POS_DOWN_FREE));
	this->maps.push_back(new Map(33, 3, MapPos::POS_LEFT));
	this->maps.push_back(new Map(33, 4, MapPos::POS_UP));
	this->maps.push_back(new Map(33, 5, MapPos::POS_RIGHT));
	this->maps.push_back(new Map(33, 6, MapPos::POS_UP_FREE));
	this->maps.push_back(new Map(33, 7, MapPos::POS_UP_FREE));
	this->maps.push_back(new Map(33, 8, MapPos::POS_UP_FREE));

	flag = new ClearFlag(Vector2(592, 1552));
	maps[1]->addGimmick(flag);

	Door* d = new Door(new Vector2(50 * 32 + 16, 8 * 32 + 16), new Vector2(83 * 32 + 16, 32 * 32 + 16));
	maps[7]->addGimmick(d);

	SwitchWithBlock* s = new SwitchWithBlock(8 * 32 + 16, 15 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)s->push_block(new Block((49 + i) * 32 + 16, 34 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[4]->addSwitchWithBlock(s);

	SwitchWithBlock* s1 = new SwitchWithBlock(94 * 32 + 16, 15 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)s1->push_block(new Block((49 + i) * 32 + 16, 36 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[4]->addSwitchWithBlock(s1);

	SwitchWithBlock* s2 = new SwitchWithBlock(8 * 32 + 16, 38 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)s2->push_block(new Block((49 + i) * 32 + 16, 38 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[4]->addSwitchWithBlock(s2);

	SwitchWithBlock* s3 = new SwitchWithBlock(94 * 32 + 16, 38 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)s3->push_block(new Block((49 + i) * 32 + 16, 40 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[4]->addSwitchWithBlock(s3);


	CheckPoint* cp = new CheckPoint(47 * 32 + 16, 8 * 32 + 16, 7);
	this->checkPoints.push_back(cp);
	maps[7]->addGimmick(cp);


	imageReisen = LoadGraph("Data/Image/Character/haribote_reisen.png");
	imageNue = LoadGraph("Data/Image/Character/haribote_nue.png");
	imageMokou = LoadGraph("Data/Image/Character/haribote_mokou.png");

	now_stage_num = 4;
	startX = 1616, startY = 704;
	nue = new Nue_Boss(95 * 32, 48 * 32, 90 * 32, 42 * 32 + 16);
	converseFlag0 = true;
	converseFlag1 = true;
	converseFlag2 = true;
	converseFlag3 = true;
	converseFlag0fin = false;
	converseFlag1fin = false;
	converseFlag2fin = false;
	converseFlag3fin = false;

	cTime = 0;

	//復活
	bool restart = findRestartPoint();

	//復活したら会話フラグを折る
	if (restart)
	{
		//converseFlag0 = false;
		//converseFlag0fin = true;
	}
}


void Stage33::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain, _player);
	standardUpdate(_player);

}

void Stage33::updateConverse(GameMain* gameMain, PlayerChild* _player)
{
	cTime = min(cTime, 180);
	if (!converseFlag3 && !converseFlag3fin)converseFlag3fin = true;
	if (converseFlag3 && !nue->isAlive())
	{
		gameMain->startConverse(333);
		converseFlag3 = false;
	}
	if (!converseFlag2 && !converseFlag2fin)
	{
		converseFlag2fin = true;
		gameMain->setNextCharacter(PlayerCharacter::CHARA_MOKOU);
		this->changeableCharacter ^= CHARA_SAKUYA;
		nue->setPlayer(_player->getVector2());
		maps[7]->addEnemy(nue);
		sound->stopSound("bgm3");
		sound->playSound("boss3");


	}
	if (converseFlag1fin && converseFlag2)
	{
		gameMain->startConverse(332);
		converseFlag2 = false;
	}
	if (cTime == 180)converseFlag1fin = true;
	if (!converseFlag1 && !converseFlag1fin)
	{
		cTime++;
		_player->lock = true;
	}
	if (converseFlag0fin && converseFlag1)
	{
		gameMain->startConverse(331);
		converseFlag1 = false;
	}
	if (cTime == 90)converseFlag0fin = true;
	if (!converseFlag0 && !converseFlag0fin)
	{
		cTime++;
		_player->lock = true;
	}
	if (now_stage_num == 7 && converseFlag0 &&_player->getVector2()->y() == 1536)
	{
		_player->lockCameraPos(new Vector2(90 * 32, 42 * 32 + 16));
		gameMain->startConverse(330);
		converseFlag0 = false;
	}


}

void Stage33::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
	if (!converseFlag0fin &&!converseFlag0&&cTime<=45)
		DrawRotaGraph(480, 416, 1.0, 0.0, imageReisen, TRUE);
	if (!converseFlag1fin && 45 < cTime&&cTime <= 135)
		DrawRotaGraph(480, 416, 1.0, 0.0, imageNue, TRUE);
	if (!converseFlag2fin && 135 < cTime)
		DrawRotaGraph(480, 416, 1.0, 0.0, imageMokou, TRUE);

}

void Stage33::draw_front(const Vector2* _camera) const
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (int)(0.126*(cTime % 90 - 45)*(cTime % 90 - 45)));
	DrawBox(0, 0, 640, 480, BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


bool Stage33::isClear() const
{
	return converseFlag3fin;
}


}
}
}


