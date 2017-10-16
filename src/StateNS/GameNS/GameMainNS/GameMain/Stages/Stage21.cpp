#include "Stage21.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage21::Stage21() :
StageChild(3, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage21::~Stage21()
{

}

void Stage21::initialize()
{

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(21, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(21, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(21, 2, MapPos::POS_LEFT_FREE));


	flag = new ClearFlag(Vector2(3088, 400));
	maps[2]->addGimmick(flag);

	SwitchWithBlock* s = new SwitchWithBlock(23 * 32 + 16, 6 * 32 + 16, 1);
	for (int i = 0; i < 4; i++)s->push_block(new Block(59 * 32 + 16, (18 + i) * 32 + 16, 1.0,BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(s);


	torches.push_back(new Torch(9 * 32 + 16, 48 * 32 + 16));
	torches.push_back(new Torch(42 * 32 + 16, 24 * 32 + 16));
	torches.push_back(new Torch(84 * 32 + 16, 7 * 32 + 16));

	for (const auto& t : torches)maps[1]->addDynamicGimmick(t);


	torches2.push_back(new Torch(63 * 32 + 16, 21 * 32 + 16));
	for (const auto& t : torches2)maps[2]->addDynamicGimmick(t);


	startX = 2864, startY = 1536;
	converseFlag0;
	findRestartPoint();
}


void Stage21::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain, _player);
	standardUpdate(_player);

	gameMain->setFilter(FilterType::FILTER_DARK);
	if(now_stage_num==0)gameMain->setFilter(FilterType::FILTER_NONE);
	if(now_stage_num==1)for (const auto& t : torches)if (t->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);
	if(now_stage_num==2)for (const auto& t : torches2)if (t->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);

}

void Stage21::updateConverse(GameMain* gameMain,PlayerChild* _player)
{
	if (converseFlag0)
	{
		gameMain->startConverse(210);
		converseFlag0 = false;
	}
}


void Stage21::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage21::isClear() const
{
	return !flag->isActive;
}


}
}
}


