#include "Stage23.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Player\PlayerChild.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage23::Stage23() :
StageChild(3, 3) //エリアの数: よこ，たて
{
	initialize();
}

Stage23::~Stage23()
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

void Stage23::initialize()
{

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;


	time = 0;
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(23, 0, MapPos::POS_DOWN_FREE));
	this->maps.push_back(new Map(23, 1, MapPos::POS_LEFT_UP));
	this->maps.push_back(new Map(23, 2, MapPos::POS_LEFT_FREE));
	this->maps.push_back(new Map(23, 3, MapPos::POS_RIGHT_LEFT));
	this->maps.push_back(new Map(23, 4, MapPos::POS_RIGHT_LEFT));
	this->maps.push_back(new Map(23, 5, MapPos::POS_SINGLE));
	this->maps.push_back(new Map(23, 6, MapPos::POS_LEFT_DOWN));
	this->maps.push_back(new Map(23, 7, MapPos::POS_RIGHT_DOWN));
	this->maps.push_back(new Map(23, 8, MapPos::POS_LEFT_UP));

	SwitchWithBlock* s = new SwitchWithBlock(44 * 32 + 16, 14 * 32 + 16, 99);
	for (int i = 0; i < 3; i++)s->push_block(new Block((46 + i) * 32 + 16, 46 * 32 + 16, 1.0), false);
	maps[3]->addSwitchWithBlock(s);
	SwitchWithBlock* s2 = new SwitchWithBlock(50 * 32 + 16, 24 * 32 + 16, 99);
	for (int i = 0; i < 3; i++)s2->push_block(new Block((46 + i) * 32 + 16, 47 * 32 + 16, 1.0), false);
	maps[3]->addSwitchWithBlock(s2);
	SwitchWithBlock* s3 = new SwitchWithBlock(44 * 32 + 16, 35 * 32 + 16, 99);
	for (int i = 0; i < 3; i++)s3->push_block(new Block((46 + i) * 32 + 16, 48 * 32 + 16, 1.0), false);
	maps[3]->addSwitchWithBlock(s3);

	startX = 144, startY = 1536;

	//this->torches.push_back(new Torch(304, 1488));
	//this->maps[0]->addGimmick(torches[0]);


}


void Stage23::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);
	time++;
	if (time % 360 == 0)maps[0]->addEnemy(ENE_TERESA, _player->getVector2(), (1 + GetRand(1) * 30) * 32, 31 * 32);

	//gameMain->setFilter(FilterType::FILTER_DARK);
	//if (torches[0]->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);
}

void Stage23::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage23::isClear() const
{
	return !flag->isActive;
}



}
}
}


