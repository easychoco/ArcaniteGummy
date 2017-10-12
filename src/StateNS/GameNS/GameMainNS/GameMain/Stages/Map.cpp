#include "Map.h"

#include "..\Player\PlayerChild.h"
#include "..\Gimmick\GimmickChild.h"
#include "..\Gimmick\DynamicGimmickChild.h"
#include "..\Gimmick\AllGimmicks.h"
#include "..\Enemy\EnemyController.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Map::Map(int _stageID, int _mapID, MapPos _mapPos)
{
	loadMap(_stageID, _mapID);
	this->mapPos = _mapPos;
	
	initialize();
}

Map::~Map()
{
	for (auto& gimmick : mGimmicks)
	{
		SAFE_DELETE(gimmick);
	}
	mGimmicks.clear();
	mGimmicks.shrink_to_fit();

	for (auto& gimmick : mDynamicGimmicks)
	{
		if(gimmick != nullptr)SAFE_DELETE(gimmick);
	}
	mDynamicGimmicks.clear();
	mDynamicGimmicks.shrink_to_fit();
}

void Map::initialize()
{
	this->mEController = new EnemyController();

	for (unsigned y = 0; y < gimmickData.size(); y++)
	{
		for (unsigned x = 0; x < gimmickData[y].size(); x++)
		{
			loadGimmick(x, y, gimmickData[y][x]);
			loadEnemy(x, y, gimmickData[y][x]);
		}
	}
}

void Map::update(PlayerChild* _player, const StageChild* _stage)
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

	updateDynamicGimmick(mDynamicGimmicks, _player, _stage);
	updateDynamicGimmick(mSwitchWithBlocks, _player, _stage);

	//スイッチのブロックをupdate
	for (auto& s_b : mSwitchWithBlocks)
	{
		updateDynamicGimmick(s_b->getBlocks(), _player, _stage);
	}
}

void Map::draw(const Vector2* _camera) const
{
	drawMap(_camera);

	//ギミックの描画
	for (const auto& gimmick : mGimmicks)
	{
		if (gimmick->isActive)gimmick->draw(_camera);
	}

	//ダイナミックギミックの描画
	for (const auto& d_gimmick : mDynamicGimmicks)
	{
		if (d_gimmick->isActive)d_gimmick->draw(_camera);
	}

	//スイッチ関連の描画
	for (const auto& s_b : mSwitchWithBlocks)
	{
		if (s_b->isActive)s_b->draw(_camera);

		//SwitchによるBlockの描画
		for (auto& b : s_b->getBlocks())
		{
			b->draw(_camera);
		}
	}
}

void Map::draw_front(const Vector2* _camera) const
{
	//ギミックの描画
	for (const auto& gimmick : mGimmicks)
	{
		if (gimmick->isActive)gimmick->draw_front(_camera);
	}

	//ダイナミックギミックの描画
	for (const auto& d_gimmick : mDynamicGimmicks)
	{
		if (d_gimmick->isActive)d_gimmick->draw_front(_camera);
	}

	//スイッチ関連の描画
	for (const auto& s_b : mSwitchWithBlocks)
	{
		if (s_b->isActive)s_b->draw_front(_camera);

		//SwitchによるBlockの描画
		for (auto& b : s_b->getBlocks())
		{
			b->draw(_camera);
		}
	}
}

int Map::getTopPosition(const Vector2* _pos, const int& _dy) const
{
	//もらった座標に他のObjectがあったら、そのObjectの上のy座標を返す
	int ret = fixToVectorHeight(_pos->raw_y + _dy);

	//*
	//メモリリークこわ
	Vector2* tmp = new Vector2(_pos->raw_x, _pos->raw_y + _dy, true);

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

int Map::getBottomPosition(const Vector2* _pos, const int& _dy) const
{
	//もらった座標に他のObjectがあったら、そのObjectの底のy座標を返す

	int ret = fixToVectorHeight(_pos->raw_y + _dy) +CHIP_HEIGHT_RATE();

	//*
	//メモリリークこわ
	Vector2* tmp = new Vector2(_pos->raw_x, _pos->raw_y + _dy, true);

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

ChipType Map::getChipType(const Vector2& _other, bool colliWithGimmick) const
{
	int sub_x = _other.raw_x / CHIP_WIDTH_RATE();
	if (_other.raw_x < 0)--sub_x;

	int sub_y = _other.raw_y / CHIP_HEIGHT_RATE();
	if (_other.raw_y < 0)--sub_y;

	//Mapの範囲外(右の端)なら
	if (MyData::MAP_WIDTH_NUM <= sub_x)
	{
		if (isRight(mapPos))
			return ChipType::TYPE_RIGID;

		//else
		return ChipType::TYPE_BACK;
	}

	//Mapの範囲外(左の端)なら
	if (sub_x < 0)
	{
		if (isLeft(mapPos))
			return ChipType::TYPE_RIGID;

		//else
		return ChipType::TYPE_BACK;
	}

	//Mapの範囲外(上の端)なら
	if (sub_y < 0)
	{
		if (isUp(mapPos))
			return ChipType::TYPE_RIGID;

		//else
		return ChipType::TYPE_BACK;
	}
	//Mapの範囲外(下の端)なら
	if (MyData::MAP_HEIGHT_NUM <= sub_y)
	{
		if (isDown(mapPos))
			return ChipType::TYPE_RIGID;

		//else
		return ChipType::TYPE_BACK;
	}

	
	ChipType ret = ChipType::TYPE_BACK;
	if(sub_y < MyData::MAP_HEIGHT_NUM && sub_x < MyData::MAP_WIDTH_NUM)
		ret = chip[mapData[sub_y][sub_x]].getChipType();

	//Playerなら以下を読む
	if (!colliWithGimmick) return ret;

	//TODO
	//今のままだと、Gimmickのほうを優先しちゃう
	//つまり、RIGIDなDynamicGimmickとBACKなGimmickが重なると透過しちゃう
	for (const auto& d_gimmick : mDynamicGimmicks)
	{
		if (d_gimmick->isActive)
		{
			if (d_gimmick->isOverlap(&_other))
			{
				ChipType tmp = d_gimmick->getChipType();
				if (tmp != ChipType::TYPE_BACK)
					ret = tmp;
			}
		}
	}

	for (const auto& s_b : mSwitchWithBlocks)
	{
		for (auto& b : s_b->getBlocks())
		{
			if (b->isOverlap(&_other))
			{
				ChipType tmp = b->getChipType();
				if (tmp != ChipType::TYPE_BACK)
					ret = tmp;
			}
		}
	}
	
	for (const auto& gimmick : mGimmicks)
	{
		if (gimmick->isActive)
		{
			//if (gimmick->isOverlap(sub_x, sub_y))
			if (gimmick->isOverlap(&_other))
			{
				ChipType tmp = gimmick->getChipType();
				if (tmp != ChipType::TYPE_BACK)
					ret = tmp;
			}
		}
	}

	return ret;
}

//ポリモーフィズム
ChipType Map::getChipType(const Vector2& _other) const
{
	return getChipType(_other, true);
}

ChipType Map::getChipType(const RawVector2& _other, bool _isPlayer) const
{
	return getChipType(Vector2(_other.pos_x, _other.pos_y), _isPlayer);
}

void Map::addEnemy(EnemyChild* _enemy)
{
	this->mEController->addEnemy(_enemy);
}

void Map::addEnemy(AllEnemies _enemy, int _x, int _y)
{
	this->mEController->addEnemy(_enemy, &Vector2::ZERO, _x, _y);
}

void Map::addEnemy(AllEnemies _enemy, const Vector2* _player, int _x, int _y)
{
	this->mEController->addEnemy(_enemy, _player, _x, _y);
}


void Map::processDynamicCollision(PlayerChild* _player)
{
	processDynamicCollision(mDynamicGimmicks, _player);
	processDynamicCollision(mSwitchWithBlocks, _player);

	//スイッチのブロックをupdate
	for (auto& s_b : mSwitchWithBlocks)
	{
		processDynamicCollision(s_b->getBlocks(), _player);
	}
}

//========================================================================
// 内部private関数
//========================================================================
template<typename D_Gmk>
void Map::updateDynamicGimmick(D_Gmk d_gmk, PlayerChild* _player, const StageChild* _stage)
{
	for (auto& d_gimmick : d_gmk)
	{
		if (d_gimmick->isActive)
		{
			d_gimmick->update(_stage);
		}
	}
}

template<typename D_Gmk>
void Map::processDynamicCollision(D_Gmk d_gmk, PlayerChild* _player)
{
	for (auto& d_gimmick : d_gmk)
	{
		if (d_gimmick->isActive)
		{
			//ここはコリジョン関係だから，別の関数で実装する
			if (d_gimmick->onActiveArea(_player->getVector2()))
				d_gimmick->apply(_player);

			if (d_gimmick->rideOnGimmick(_player->getVector2()))
				_player->moveCharacter(d_gimmick->getDX(), d_gimmick->getDY());
		}
	}
}

//template<typename Arr>
void Map::drawMap(const Vector2* _camera) const
{
	//マップ描画をする際に，カメラの位置依存で描画位置の座標が変わる
	int draw_x = _camera->x() - MyData::CX;
	int draw_y = _camera->y() - MyData::CY;


	//マップ描画
	for (unsigned y = 0; y < mapData.size(); y++)
	{
		for (unsigned x = 0; x < mapData[0].size(); x++)
		{
			int gomi = DrawGraph(x * 32 - draw_x, y * 32 - draw_y, MyData::MapChip[mapData[y][x]], true);
			assert(gomi != -1);
		}
	}
}

void Map::loadMap(int _stageID, int _mapID)
{
	string textFile = "Data/Text/stage";
	textFile += std::to_string(_stageID);
	textFile += "/stage";
	textFile += std::to_string(_mapID);
	textFile += ".txt";

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

void Map::loadGimmick(int _x, int _y, int _n)
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
		//燃えるブロック
	case 116:mDynamicGimmicks.push_back(new Block(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0, BlockType::TYPE_WOOD)); break;
		//壊れるブロック
	case 117:mDynamicGimmicks.push_back(new Block(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0, BlockType::TYPE_FRAGILE)); break;
		//大きいドッスン
	case 118:mDynamicGimmicks.push_back(new Dossunn(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 3.0)); break;
		//小さいドッスン
	case 119:mDynamicGimmicks.push_back(new Dossunn(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0)); break;
		//上向きトゲ
	case 120:mGimmicks.push_back(new Needle(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 0.0f)); break;
		//下向きトゲ
	case 121:mGimmicks.push_back(new Needle(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, Pi)); break;
		//右向きトゲ
	case 122:mGimmicks.push_back(new Needle(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, Pi/2)); break;
		//左向きトゲ
	case 123:mGimmicks.push_back(new Needle(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, -Pi/2)); break;
		//反時計回りファイアバー
	case 124:mDynamicGimmicks.push_back(new FireBar(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, false)); break;
		//時計回りファイアバー
	case 125:mDynamicGimmicks.push_back(new FireBar(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, true)); break;
		//乗ると落ちる床
	case 126:mDynamicGimmicks.push_back(new FallFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, true)); break;
		//乗ると上がる床
	case 127:mDynamicGimmicks.push_back(new FallFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, false)); break;
		//動く床：上下：小
	case 128:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT - CHIP_HEIGHT * 5 / 2, 1.0f, 0)); break;
		//動く床：上下：大
	case 129:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT - CHIP_HEIGHT * 15 / 2, 1.0f, 0)); break;
		//動く床：左右：小
	case 130:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 5 / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 0)); break;
		//動く床：左右：大
	case 131:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 15 / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 0)); break;
		//動く床：右上斜め：小
	case 132:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 9 / 2, _y * CHIP_HEIGHT - CHIP_HEIGHT * 7 / 2, 1.0f, 0)); break;
		//動く床：右上斜め：大
	case 133:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 17 / 2, _y * CHIP_HEIGHT - CHIP_HEIGHT * 15 / 2, 1.0f, 0)); break;
		//動く床：右下斜め：小
	case 134:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 9 / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT * 9 / 2, 1.0f, 0)); break;
		//動く床：右下斜め：大
	case 135:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 17 / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT * 17 / 2, 1.0f, 0)); break;
		//動く床：円：小：時計回り
	case 136:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 5 / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 3)); break;
		//動く床：円：大：時計回り
	case 137:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 7 / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 3)); break;
		//動く床：円：小：反時計回り
	case 138:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 5 / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 4)); break;
		//動く床：円：大：反時計回り
	case 139:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 7 / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 4)); break;
		//動く床：上に凸な放物線：小
	case 140:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 5 / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 1)); break;
		//動く床：上に凸な放物線：大
	case 141:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 15 / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 3.0f, 1)); break;
		//動く床：下に凸な放物線：小
	case 142:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 5 / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 2)); break;
		//動く床：下に凸な放物線：大
	case 143:mDynamicGimmicks.push_back(new MovingFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, _x * CHIP_WIDTH + CHIP_WIDTH * 15 / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 3.0f, 2)); break;
		//松明
	case 144:break;
		//上向きバーナー１
	case 145:mDynamicGimmicks.push_back(new Burner(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, -Pi / 2, 0)); break;
		//上向きバーナー２
	case 146:mDynamicGimmicks.push_back(new Burner(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, -Pi / 2, 1)); break;
		//下向きバーナー１
	case 147:mDynamicGimmicks.push_back(new Burner(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, Pi / 2, 0)); break;
		//下向きバーナー２
	case 148:mDynamicGimmicks.push_back(new Burner(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, Pi / 2, 1)); break;
		//右向きバーナー１
	case 149:mDynamicGimmicks.push_back(new Burner(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 0.0f, 0)); break;
		//右向きバーナー２
	case 150:mDynamicGimmicks.push_back(new Burner(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 0.0f, 1)); break;
		//左向きバーナー１
	case 151:mDynamicGimmicks.push_back(new Burner(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, Pi, 0)); break;
		//左向きバーナー２
	case 152:mDynamicGimmicks.push_back(new Burner(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, Pi, 1)); break;
		//時間差で現れる足場１
	case 153:mDynamicGimmicks.push_back(new OrderEmergeFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 1));break;
		//時間差で現れる足場２
	case 154:mDynamicGimmicks.push_back(new OrderEmergeFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 2)); break;
		//時間差で現れる足場３
	case 155:mDynamicGimmicks.push_back(new OrderEmergeFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 3)); break;
		//時間差で現れる足場４
	case 156:mDynamicGimmicks.push_back(new OrderEmergeFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 4)); break;
		//時間差で現れる足場５
	case 157:mDynamicGimmicks.push_back(new OrderEmergeFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 5)); break;
		//時間差で現れる足場６
	case 158:mDynamicGimmicks.push_back(new OrderEmergeFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 6)); break;
		//時間差で現れる足場７
	case 159:mDynamicGimmicks.push_back(new OrderEmergeFloor(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2, 1.0f, 7)); break;
	

	}
	


}

void Map::loadEnemy(int _x, int _y, int _n)
{
	//TODO 変更途中
	AllEnemies eneID = ENE_NONE;
	switch (_n) {
	case 240:eneID = ENE_USA; break;
	case 241:eneID = ENE_BALL; break;
	case 242:eneID = ENE_POPPY; break;
	case 243:eneID = ENE_RARA; break;
	case 244:eneID = ENE_PIKA; break;
	case 245:eneID = ENE_BROTH; break;
	case 246:eneID = ENE_YACH; break;
	case 247:eneID = ENE_KARON; break;
	case 248:eneID = ENE_AIRMZ; break;
	case 249:eneID = ENE_TERESA; break;
	case 250:eneID = ENE_ICE; break;
	case 251:eneID = ENE_MARI; break;
	}
	//TODO Flyweightチックに書き換える
	if (eneID != ENE_NONE)addEnemy(eneID, _x*CHIP_WIDTH + CHIP_WIDTH / 2, _y*CHIP_HEIGHT + CHIP_HEIGHT / 2);

}






}
}
}


