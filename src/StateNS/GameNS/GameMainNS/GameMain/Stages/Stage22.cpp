#include "Stage22.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage22::Stage22() :
StageChild(2, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage22::~Stage22()
{
	DeleteGraph(imageSakuya);
	sound->deleteSound("bgm2");
}

void Stage22::initialize()
{
	sound->setSound("Data/Sound/Ousa-sama3.wav", "bgm2");
	sound->playSound("bgm2", LOOP, false);

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(22, 0, MapPos::POS_LEFT_UP));
	this->maps.push_back(new Map(22, 1, MapPos::POS_LEFT_FREE));


	flag = new ClearFlag(Vector2(2608, 1040));
	maps[1]->addGimmick(flag);

	SwitchWithBlock* s = new SwitchWithBlock(73 * 32 + 16, 32 * 32 + 16, 90);
	for (int i = 0; i < 6; i++)s->push_block(new Block(95 * 32 + 16, (27 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[0]->addSwitchWithBlock(s);
	
	SwitchWithBlock* s2 = new SwitchWithBlock(34 * 32 + 16, 3 * 32 + 16, 1);
	for (int i = 0; i < 4; i++)s2->push_block(new Block((27 + i) * 32 + 16, 5 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[1]->addSwitchWithBlock(s2);

	SwitchWithBlock* s3 = new SwitchWithBlock(61 * 32 + 16, 9 * 32 + 16 ,1);
	for (int i = 0; i < 6; i++)s3->push_block(new Block(73 * 32 + 16, (27 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[1]->addSwitchWithBlock(s3);

	SwitchWithBlock* s4 = new SwitchWithBlock(60 * 32 + 16, 43 * 32 + 16, 1);
	for (int i = 0; i < 6; i++)s4->push_block(new Block(75 * 32 + 16, (27 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[1]->addSwitchWithBlock(s4);

	SwitchWithBlock* s5 = new SwitchWithBlock(38 * 32 + 16, 39 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)s5->push_block(new Block(36 * 32 + 16, (41 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[1]->addSwitchWithBlock(s5);
	imageSakuya = LoadGraph("Data/Image/Character/haribote_sakuya.png");
	converseFlag0 = true;
	converseFlag0fin = false;
	startX = 144, startY = 704;

	//復活
	bool restart = findRestartPoint();
	//復活したら会話フラグを折る
	if (restart)
	{
		converseFlag0 = false;
		converseFlag0fin = true;
	}
}


void Stage22::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain, _player);
	standardUpdate(_player);
}

void Stage22::updateConverse(GameMain* gameMain, PlayerChild* _player)
{
	if (!converseFlag0 && !converseFlag0fin)
	{
		converseFlag0fin = true;
		this->changeableCharacter |= CHARA_SAKUYA;
	}
	if (converseFlag0)
	{
		gameMain->startConverse(220);
		converseFlag0 = false;
	}
}

void Stage22::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
	if (!converseFlag0fin)DrawRotaGraph(320, 240, 1.0, 0.0, imageSakuya, TRUE);
}

bool Stage22::isClear() const
{
	return !flag->isActive;
}


}
}
}


