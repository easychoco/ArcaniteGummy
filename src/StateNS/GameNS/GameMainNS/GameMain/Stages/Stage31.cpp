#include "Stage31.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage31::Stage31() :
StageChild(2, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage31::~Stage31()
{
	DeleteGraph(imageReisen);
	sound->deleteSound("bgm3");
}

void Stage31::initialize()
{
	sound->setSound("Data/Sound/Phantom_Ship.wav", "bgm3");
	sound->playSound("bgm3", LOOP, false);
	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(31, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(31, 1, MapPos::POS_LEFT_FREE));

	flag = new ClearFlag(Vector2(1936, 1552));
	maps[1]->addGimmick(flag);


	torches.push_back(new Torch(22 * 32 + 16, 48 * 32 + 16));
	torches.push_back(new Torch(23 * 32 + 16, 30 * 32 + 16));
	torches.push_back(new Torch(8 * 32 + 16, 16 * 32 + 16));
	torches.push_back(new Torch(58 * 32 + 16, 9 * 32 + 16));
	torches.push_back(new Torch(49 * 32 + 16, 48 * 32 + 16));
	for (const auto& t : torches)maps[0]->addDynamicGimmick(t);

	torches2.push_back(new Torch(8 * 32 + 16, 48 * 32 + 16));
	torches2.push_back(new Torch(26 * 32 + 16, 5 * 32 + 16));
	torches2.push_back(new Torch(68 * 32 + 16, 23 * 32 + 16));
	for (const auto& t : torches2)maps[1]->addDynamicGimmick(t);

	SwitchWithBlock* s = new SwitchWithBlock(78 * 32 + 16, 5 * 32 + 16);
	for (int i = 0; i < 3; i++)s->push_block(new Block(78 * 32 + 16, (11 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[1]->addSwitchWithBlock(s);


	startX = 144, startY = 1536;
	converseFlag0 = true;
	converseFlag0fin = false;
	converseFlag1 = true;
	converseFlag1fin = false;
	imageReisen = LoadGraph("Data/Image/Character/haribote_reisen.png");
	//復活
	bool restart = findRestartPoint();
	//復活したら会話フラグを折る
	if (restart)
	{
		converseFlag0 = false;
		converseFlag0fin = true;
	}
}


void Stage31::update(GameMain* gameMain, PlayerChild* _player)
{

	updateConverse(gameMain, _player);
	standardUpdate(_player);

	gameMain->setFilter(FilterType::FILTER_DARK);
	if(!converseFlag1fin)	gameMain->setFilter(FilterType::FILTER_NONE);
	if(now_stage_num==0)for (const auto& t : torches)if (t->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);
	if(now_stage_num==1)for (const auto& t : torches2)if (t->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);


	findRestartPoint();
}

void Stage31::updateConverse(GameMain* gameMain, PlayerChild* _player)
{
	if (!converseFlag1)converseFlag1fin = true;
	if (converseFlag1 && converseFlag0fin)
	{
		gameMain->startConverse(311);
		converseFlag1 = false;
	}

	if (!converseFlag0 && converseFlag1)
	{
		converseFlag0fin = true;
	}

	if (converseFlag0)
	{
		gameMain->startConverse(310);
		converseFlag0 = false;
	}

}

void Stage31::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
	if (!converseFlag0fin)DrawRotaGraph(360, 416, 1.0, 0.0, imageReisen, TRUE);
}

bool Stage31::isClear() const
{
	return !flag->isActive;
}


}
}
}


