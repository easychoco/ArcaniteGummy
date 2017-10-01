#include "stage43.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include "..\Gimmick\DynamicGimmickChild.h"
#include "..\Gimmick\Torch.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

stage43::stage43() :
StageChild(3, 1) //エリアの数: よこ，たて
{
	initialize();
}

stage43::~stage43()
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

void stage43::initialize()
{
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(13, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(13, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(13, 2, MapPos::POS_LEFT_FREE));

	startX = 144, startY = 1536;

	//this->torches.push_back(new Torch(304, 1488));
	//this->maps[0]->addGimmick(torches[0]);


}


void stage43::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//gameMain->setFilter(FilterType::FILTER_DARK);
	//if (torches[0]->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);
}

void stage43::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool stage43::isClear() const
{
	return false;
}


}
}
}


