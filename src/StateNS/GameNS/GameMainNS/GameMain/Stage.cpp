#include "Stage.h"
#include "Player\PlayerChild.h"
#include "Gimmick\GimmickChild.h"
#include "Gimmick\DynamicGimmickChild.h"
#include "Gimmick\AllGimmicks.h"

#include "..\..\..\..\KeyInput.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Stage::Stage(int _stageID, int _mapID)
{
	initialize();

	//for Debug
	loadMap(_stageID, 0);
	//loadMap(_stageID, _mapID);
	mBackImg = LoadGraph("Data/Image/back.jpg");
	assert(mBackImg != -1 && "背景画像読み込みエラー");
}

Stage::~Stage()
{
	for (auto& gimmick : mGimmicks)
	{
		SAFE_DELETE(gimmick);
	}
	mGimmicks.clear();
	mGimmicks.shrink_to_fit();

	for (auto& gimmick : mDynamicGimmicks)
	{
		SAFE_DELETE(gimmick);
	}
	mDynamicGimmicks.clear();
	mDynamicGimmicks.shrink_to_fit();
}

void Stage::initialize()
{
	//loadGimmick()
	//とかいう関数で外部のテキストデータから読み込み

	/*
	//for Debug
	mGimmicks.push_back(new BeltConveyor(0.5, Vector2(80, 176)));
	mGimmicks.push_back(new BeltConveyor(0.5, Vector2(112, 176)));
	mGimmicks.push_back(new BeltConveyor(0.5, Vector2(112, 208)));
	mGimmicks.push_back(new BeltConveyor(2.0, Vector2(144, 208)));
	mGimmicks.push_back(new BeltConveyor(0.5, Vector2(176, 208)));
	mGimmicks.push_back(new BeltConveyor(2.0, Vector2(208, 208)));

	mGimmicks.push_back(new Spring(2.0, Vector2(240, 384)));
	mDynamicGimmicks.push_back(new Block(80, 176, 32, 32));
	*/
}

void Stage::update(PlayerChild* _player)
{
	for (auto& gimmick : mGimmicks)
	{
		if (gimmick->isActive)
		{
			gimmick->update();

			if (gimmick->onActiveArea(_player->getVector2()))
				gimmick->apply(_player);
		}
	}

	for (auto& d_gimmick : mDynamicGimmicks)
	{
		d_gimmick->update(_player);
	}

}

void Stage::draw(const Vector2* _camera) const
{
	DrawGraph(0, 0, mBackImg, true);
	drawMap(mapData, _camera);

	//ギミックの描画
	for (const auto& gimmick : mGimmicks)
	{
		if(gimmick->isActive)gimmick->draw(_camera);
	}

	//ダイナミックギミックの描画
	for (const auto& gimmick : mDynamicGimmicks)
	{
		if(gimmick->isActive)gimmick->draw(_camera);
	}

}

Stage::ChipType Stage::getChipType(const Vector2& _player) const
{

	int sub_x = _player.raw_x / MyData::vectorRate / MyData::CHIP_WIDTH;
	int sub_y = _player.raw_y / MyData::vectorRate / MyData::CHIP_HEIGHT;

	//Stageの範囲外(左か上の端)ならTYPE_RIGIDを返す
	if (sub_y < 0 || sub_x < 0)
		return ChipType::TYPE_RIGID;


	//Stageの範囲外(右か下の端)ならTYPE_RIGIDを返す
	if (MyData::MAP_HEIGHT_NUM * stage_max_y <= sub_y || 
		MyData::MAP_WIDTH_NUM  * stage_max_x <= sub_x)
		return ChipType::TYPE_RIGID;

	
	ChipType ret = TYPE_BACK;
	if(sub_y < MyData::MAP_HEIGHT_NUM && sub_x < MyData::MAP_WIDTH_NUM)
		ret = chip[mapData[sub_y][sub_x]].getChipType();

	//TODO
	//今のままだと、Gimmickのほうを優先しちゃう
	//つまり、RIGIDなDynamicGimmickとBACKなGimmickが重なると透過しちゃう
	for (const auto& d_gimmick : mDynamicGimmicks)
	{
		if (d_gimmick->isActive)
		{
			if (d_gimmick->isOverlap(sub_x, sub_y))
			{
				ret = d_gimmick->getChipType();
			}
		}
	}

	for (const auto& gimmick : mGimmicks)
	{
		if (gimmick->isActive)
		{
			if (gimmick->isOverlap(sub_x, sub_y))
			{
				ret = gimmick->getChipType();
			}
		}
	}
	return ret;
}

//ポリモーフィズム
Stage::ChipType Stage::getChipType(const RawVector2& _player) const
{
	return getChipType(Vector2(_player.pos_x, _player.pos_y));
}



//========================================================================
// 内部private関数
//========================================================================
void Stage::loadMap(int _stageID, int _mapID)
{
	//string imgFile = "Data/Image/block";
	//imgFile += std::to_string(_stageID);
	//imgFile += ".png";
	string imgFile = "Data/Image/block0.png";

	//int tmp = LoadDivGraph(imgFile.c_str(), 7, 7, 1, 32, 32, mapChip);
	int tmp = LoadDivGraph(imgFile.c_str(), 9, 9, 1, 32, 32, mapChip);
	assert(tmp != -1 && "マップチップ読み込みエラー");

	string textFile = "Data/Text/stage";
	textFile += std::to_string(_mapID);
	textFile += ".txt";

	std::ifstream fin(textFile);
	assert(fin && "マップデータ読み込みエラー");

	for (auto& mapY : mapData)
	{
		for (auto& mapX : mapY)
		{
			fin >> mapX;
		}
	}

}



//マップチップが変わっても対応可能
//第一引数にマップチップへのポインタを持ってくるためにtemplateを使用
template<typename Arr>
void Stage::drawMap(Arr _mapData, const Vector2* _camera) const
{
	//マップ描画をする際に，カメラの位置依存で描画位置の座標が変わる
	int draw_x = _camera->x() - MyData::CX;
	int draw_y = _camera->y() - MyData::CY;


	//マップ描画
	for (unsigned y = 0; y < mapData.size(); y++)
	{
		for (unsigned x = 0; x < mapData[0].size(); x++)
		{
			DrawGraph(x * 32 - draw_x, y * 32 - draw_y, mapChip[_mapData[y][x]], true);
		}
	}
}





}
}
}


