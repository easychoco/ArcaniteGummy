#include "Stage33.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include "..\Gimmick\DynamicGimmickChild.h"
#include "..\Gimmick\Torch.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage33::Stage33() :
StageChild(3, 3) //�G���A�̐�: �悱�C����
{
	initialize();
}

Stage33::~Stage33()
{
	//torches��Map��DynamickGimmicks�ƈꏏ��delete����邩��C�����ł�delete���Ȃ�
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
	//���ォ��E��push���Ă���
	//StageID, 0���珸��, �G���A�̌`
	this->maps.push_back(new Map(23, 0, MapPos::POS_LEFT_UP));
	this->maps.push_back(new Map(23, 1, MapPos::POS_SINGLE));
	this->maps.push_back(new Map(23, 2, MapPos::POS_RIGHT_UP));
	this->maps.push_back(new Map(23, 3, MapPos::POS_LEFT));
	this->maps.push_back(new Map(23, 4, MapPos::POS_UP));
	this->maps.push_back(new Map(23, 5, MapPos::POS_RIGHT));
	this->maps.push_back(new Map(23, 6, MapPos::POS_UP_FREE));
	this->maps.push_back(new Map(23, 7, MapPos::POS_UP_FREE));
	this->maps.push_back(new Map(23, 8, MapPos::POS_UP_FREE));

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
	return false;
}


}
}
}

