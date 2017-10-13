#include "Stage33.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include "..\Gimmick\DynamicGimmickChild.h"

#include <fstream>

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
	//torchesはMapのDynamickGimmicksと一緒にdeleteされるから，ここではdeleteしない
	/*
	for (auto& t : torches)
	{
			SAFE_DELETE(t);
	}
	torches.clear();
	torches.shrink_to_fit();
	*/
}

void Stage33::initialize()
{

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

	SwitchWithBlock* s = new SwitchWithBlock(8 * 32 + 16, 15 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)s->push_block(new Block((49 + i) * 32 + 16, 34 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[4]->addSwitchWithBlock(s);

	SwitchWithBlock* s1 = new SwitchWithBlock(94 * 32 + 16, 32 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)s1->push_block(new Block((49 + i) * 32 + 16, 36 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[4]->addSwitchWithBlock(s1);

	SwitchWithBlock* s2 = new SwitchWithBlock(8 * 32 + 16, 38 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)s2->push_block(new Block((49 + i) * 32 + 16, 38 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[4]->addSwitchWithBlock(s2);

	SwitchWithBlock* s3 = new SwitchWithBlock(94 * 32 + 16, 38 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)s3->push_block(new Block((49 + i) * 32 + 16, 40 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[4]->addSwitchWithBlock(s3);

	now_stage_num = 4;
	startX = 1616, startY = 704;

	//this->torches.push_back(new Torch(304, 1488));
	//this->maps[0]->addGimmick(torches[0]);


}


void Stage33::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//gameMain->setFilter(FilterType::FILTER_DARK);
	//if (torches[0]->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);
}

void Stage33::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage33::isClear() const
{
	return !flag->isActive;
}


}
}
}


