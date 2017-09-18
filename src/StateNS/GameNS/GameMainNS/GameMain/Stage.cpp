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


Stage::Stage(int _stageID, int _stage_num,int _stage_max_x,int _stage_max_y)
{
	loadMap(_stageID, _stage_num);
	this->stage_num = _stage_num;

	stage_max_x = _stage_max_x;
	stage_max_y = _stage_max_y;

	initialize();
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
	stage_num_x = stage_num % (stage_max_x + 1);
	stage_num_y = stage_num / (stage_max_x + 1);

	//mGimmicksの0番目はclearFlag
	this->clearFlag = new ClearFlag(Vector2(400, 1552));
	mGimmicks.push_back(clearFlag);

	for (unsigned y = 0; y < gimmickData.size(); y++)
	{
		for (unsigned x = 0; x < gimmickData[0].size(); x++)
		{
			loadGimmick(x, y,gimmickData[y][x]);
			//DrawGraph(x * 32 - draw_x, y * 32 - draw_y, mapChip[_mapData[y][x]], true);
		}
	}

	// for Debug
	//mDynamicGimmicks.push_back(new MovingFloor(300, 1400, 360, 1200, 3.0));
	mDynamicGimmicks.push_back(new FireBar(304, 1488,true));
	mDynamicGimmicks.push_back(new Block(656, 1488, 1.0));
	mDynamicGimmicks.push_back(new Block(688, 1488, 1.0, false));
	mSwitchWithBlocks.push_back(new SwitchWithBlock(208, 1488));
	
	mSwitchWithBlocks[0]->push_block(new Block(208, 1296, 1.0));
	mSwitchWithBlocks[0]->push_block(new Block(256, 1312, 2.0));

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

	updateDynamicGimmick(mDynamicGimmicks, _player);
	updateDynamicGimmick(mSwitchWithBlocks, _player);

	//スイッチのブロックをupdate
	for (auto& s_b : mSwitchWithBlocks)
	{
		updateDynamicGimmick(s_b->getBlocks(), _player);
	}


	/*
	for (auto& d_gimmick : mDynamicGimmicks)
	{
		if (d_gimmick->isActive)
		{
			d_gimmick->update(this);

			if (d_gimmick->onActiveArea(_player->getVector2()))
				d_gimmick->apply(_player);

			if (d_gimmick->rideOnGimmick(_player->getVector2()))
				_player->moveCharacter(d_gimmick->getDX(), d_gimmick->getDY());
		}
	}

	for (auto& s_b : mSwitchWithBlocks)
	{
		if (s_b->isActive)s_b->update(this);

		if (s_b->onActiveArea(_player->getVector2()))
			s_b->apply(_player);

		if (s_b->rideOnGimmick(_player->getVector2()))
			_player->moveCharacter(s_b->getDX(), s_b->getDY());
	}
	*/
}

void Stage::draw(const Vector2* _camera) const
{
	DrawGraph(0, 0, mBackImg, true);
	drawMap(mapData, _camera);

	//スイッチ関連の描画
	for (const auto& s_b : mSwitchWithBlocks)
	{
		if (s_b->isActive)s_b->draw(_camera);
	}

	//ギミックの描画
	for (const auto& gimmick : mGimmicks)
	{
		if(gimmick->isActive)gimmick->draw(_camera);
	}

	//ダイナミックギミックの描画
	for (const auto& d_gimmick : mDynamicGimmicks)
	{
		if(d_gimmick->isActive)d_gimmick->draw(_camera);
	}

	//スイッチのブロックをupdate
	for (auto& s_b : mSwitchWithBlocks)
	{
		for (auto& b : s_b->getBlocks())
		{
			b->draw(_camera);
		}
	}

}

int Stage::getTopPosition(const Vector2* _pos, const int& _dy) const
{
	//もらった座標に他のObjectがあったら、そのObjectの上のy座標を返す

	int ret = fixToVectorHeight(_pos->pos_y() + _dy);

	//*
	//メモリリークこわ
	Vector2* tmp = new Vector2(_pos->pos_x(), _pos->pos_y() + _dy, true);

	for (const auto& d_gimmick : mDynamicGimmicks)
	{
		//足元にRIGIDのd_gimmickがあるなら
		if (d_gimmick->isActive)
		{
			if (d_gimmick->isOverlap(tmp) && isRigid_down(d_gimmick->getChipType()))
			{
				ret = d_gimmick->getTopPosition();
			}
		}
	}

	//メモリリークこわ
	SAFE_DELETE(tmp);
	//*/


	return ret;
}

int Stage::getBottomPosition(const Vector2* _pos, const int& _dy) const
{
	//もらった座標に他のObjectがあったら、そのObjectの底のy座標を返す

	int ret = fixToVectorHeight(_pos->pos_y() + _dy) +CHIP_HEIGHT_RATE();

	//*
	//メモリリークこわ
	Vector2* tmp = new Vector2(_pos->pos_x(), _pos->pos_y() + _dy, true);

	for (const auto& d_gimmick : mDynamicGimmicks)
	{
		//頭上にRIGIDのd_gimmickがあるなら
		if (d_gimmick->isActive)
		{
			if (d_gimmick->isOverlap(tmp) && isRigid_up(d_gimmick->getChipType()))
			{
				ret = d_gimmick->getBottomPosition();
			}
		}
	}

	//メモリリークこわ
	SAFE_DELETE(tmp);
	//*/


	return ret;
}


Stage::ChipType Stage::getChipType(const Vector2& _other, bool isPlayer) const
{
	int sub_x = _other.raw_x / CHIP_WIDTH_RATE();
	if (_other.raw_x < 0)--sub_x;

	int sub_y = _other.raw_y / CHIP_HEIGHT_RATE();
	if (_other.raw_y < 0)--sub_y;

	//Stageの範囲外(右の端)なら
	if (MyData::MAP_WIDTH_NUM <= sub_x)
	{
		if (stage_num_x == stage_max_x)
			return ChipType::TYPE_RIGID;

		//else
		return ChipType::TYPE_BACK;
	}

	//Stageの範囲外(左の端)なら
	if (sub_x < 0)
	{
		if (stage_num_x == 0)
			return ChipType::TYPE_RIGID;

		//else
		return ChipType::TYPE_BACK;
	}

	//Stageの範囲外(上の端)なら
	if (sub_y < 0)
	{
		if (stage_num_y == 0)
			return ChipType::TYPE_RIGID;

		//else
		return ChipType::TYPE_BACK;
	}
	//Stageの範囲外(下の端)なら
	if (MyData::MAP_HEIGHT_NUM <= sub_y)
	{
		if (stage_num_y == stage_max_y)
			return ChipType::TYPE_RIGID;

		//else
		//return ChipType::TYPE_LESAL;
		return ChipType::TYPE_BACK;
	}

	
	ChipType ret = ChipType::TYPE_BACK;
	if(sub_y < MyData::MAP_HEIGHT_NUM && sub_x < MyData::MAP_WIDTH_NUM)
		ret = chip[mapData[sub_y][sub_x]].getChipType();

	if (!isPlayer)return ret;

	//Playerなら以下を読む

	//TODO
	//今のままだと、Gimmickのほうを優先しちゃう
	//つまり、RIGIDなDynamicGimmickとBACKなGimmickが重なると透過しちゃう
	for (const auto& d_gimmick : mDynamicGimmicks)
	{
		if (d_gimmick->isActive)
		{
			if (d_gimmick->isOverlap(&_other))
			{
				ret = d_gimmick->getChipType();
			}
		}
	}

	for (const auto& s_b : mSwitchWithBlocks)
	{
		for (auto& b : s_b->getBlocks())
		{
			if (b->isOverlap(&_other))
			{
				ret = b->getChipType();
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
Stage::ChipType Stage::getChipType(const Vector2& _other) const
{
	return getChipType(_other, true);
}

Stage::ChipType Stage::getChipType(const RawVector2& _other, bool _isPlayer) const
{
	return getChipType(Vector2(_other.pos_x, _other.pos_y), _isPlayer);
}

bool Stage::isClear() const
{
	return !clearFlag->isActive;
}

//========================================================================
// 内部private関数
//========================================================================
template<typename D_Gmk>
void Stage::updateDynamicGimmick(D_Gmk d_gmk, PlayerChild* _player)
{
	for (auto& d_gimmick : d_gmk)
	{
		if (d_gimmick->isActive)
		{
			d_gimmick->update(this);

			if (d_gimmick->onActiveArea(_player->getVector2()))
				d_gimmick->apply(_player);

			if (d_gimmick->rideOnGimmick(_player->getVector2()))
				_player->moveCharacter(d_gimmick->getDX(), d_gimmick->getDY());
		}
	}
}



void Stage::loadMap(int _stageID, int _mapID)
{
	//string imgFile = "Data/Image/block";
	//imgFile += std::to_string(_stageID);
	//imgFile += ".png";
	string imgFile = "Data/Image/block0.png";

	//256*480
	int tmp = LoadDivGraph(imgFile.c_str(), 256, 8, 15, 32, 32, mapChip);
	assert(tmp != -1 && "マップチップ読み込みエラー");

	string textFile = "Data/Text/stage";
	textFile += std::to_string(_stageID);
	textFile += "/stage";
	textFile += std::to_string(_mapID);

	string textFile2 = textFile + "a";
	textFile += ".txt";
	textFile2 += ".txt";


	std::ifstream fin(textFile);
	std::ifstream fin2(textFile);

	assert(fin && "マップデータ読み込みエラー");
	assert(fin2 && "ギミック読み込みエラー");

	for (auto& mapY : mapData)
	{
		for (auto& mapX : mapY)
		{
			fin >> mapX;
		}
	}

	//ギミックや敵配置の後ろは背景とする。
	for (unsigned y = 0; y < mapData.size(); y++)
	{
		for (unsigned x = 0; x < mapData[0].size(); x++)
		{
			if (mapData[y][x] > 111)mapData[y][x] = 0;
		}
	}


	for (auto& gimmickY : gimmickData)
	{
		for (auto& gimmickX : gimmickY)
		{
			fin2 >> gimmickX;
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


void Stage::loadGimmick(int _x, int _y, int _n)
{
	//TODO 変更途中

	//Dynamicじゃないものはy座標を+16
	switch (_n) {
		//ばね
	case 113:mGimmicks.push_back(new Spring(Vector2(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2))); break;
		//左ベルトコンベア
	case 114:mGimmicks.push_back(new BeltConveyor(-2.0, Vector2(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2))); break;
		//右ベルトコンベア
	case 115:mGimmicks.push_back(new BeltConveyor(2.0, Vector2(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2))); break;
		//燃えるブロック？たぶん違う
	case 116:mDynamicGimmicks.push_back(new Block(_x * CHIP_WIDTH, _y * CHIP_HEIGHT, 1.0)); break;
		//壊れるブロック
	case 117:mDynamicGimmicks.push_back(new Block(_x * CHIP_WIDTH, _y * CHIP_HEIGHT, 1.0)); break;
		//大きいドッスン
	case 118:mDynamicGimmicks.push_back(new Dossunn(_x * CHIP_WIDTH, _y * CHIP_HEIGHT, 3.0)); break;
		//小さいドッスン
	case 119:mDynamicGimmicks.push_back(new Dossunn(_x * CHIP_WIDTH, _y * CHIP_HEIGHT, 1.0)); break;
		//上向きトゲ
	case 120:break;
		//下向きトゲ
	case 121:break;
		//右向きトゲ
	case 122:break;
		//左向きトゲ
	case 123:break;
		//反時計回りファイアバー
	case 124:mDynamicGimmicks.push_back(new FireBar(_x * CHIP_WIDTH, _y * CHIP_HEIGHT, false)); break;
		//時計回りファイアバー
	case 125:mDynamicGimmicks.push_back(new FireBar(_x * CHIP_WIDTH, _y * CHIP_HEIGHT, true)); break;
		//乗ると落ちる床
	case 126:break;
		//乗ると上がる床
	case 127:break;
		//動く床：上下：小
	case 128:break;
		//動く床：上下：大
	case 129:break;
		//動く床：左右：小
	case 130:break;
		//動く床：左右：大
	case 131:break;
		//動く床：右上斜め：小
	case 132:break;
		//動く床：右上斜め：大
	case 133:break;
		//動く床：右下斜め：小
	case 134:break;
		//動く床：右下斜め：大
	case 135:break;
		//動く床：円：小
	case 136:break;
		//動く床：円：大
	case 137:break;
		//動く床：アステロイド：小
	case 138:break;
		//動く床：アステロイド：大
	case 139:break;
		//動く床：上に凸な放物線：小
	case 140:break;
		//動く床：上に凸な放物線：大
	case 141:break;
		//動く床：下に凸な放物線：小
	case 142:break;
		//動く床：下に凸な放物線：大
	case 143:break;
		//松明
	case 144:break;

	

	}

}





}
}
}


