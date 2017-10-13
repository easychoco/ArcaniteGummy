#pragma once

#include "..\..\..\..\..\Data.h"
#include "StageChild.h"
#include "..\Gimmick\Switches\SwitchWithBlock.h"
#include "..\Gimmick\Block.h"
namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class PlayerChild;
class GimmickChild;
class EnemyChild;
class DynamicGimmickChild;
class SwitchWithBlock;
class EnemyController;


//マップでの位置
//下の図中の番号はMapPosのコメントにある数字と対応
/*
+---+---+---+
| 0 | 1 | 2 |
+---+---+---+
| 3 | 4 | 5 |
+---+---+---+
| 6 | 7 | 8 |
+---+---+---+

+---+ +---+ +   + +---+
  9 | | 10  | 11| | 12|
+---+ +---+ +---+ +   +
+---+ +   + +---+
  13  | 14| | 15|
+---+ +   + +---+
*/
enum MapPos
{
	//番号は上の図での位置
	POS_LEFT_UP		= 0x0001,//0
	POS_UP			= 0x0002,//1
	POS_RIGHT_UP	= 0x0004,//2
	POS_LEFT		= 0x0008,//3
	POS_CENTER		= 0x0010,//4
	POS_RIGHT		= 0x0020,//5
	POS_LEFT_DOWN	= 0x0040,//6
	POS_DOWN		= 0x0080,//7
	POS_RIGHT_DOWN	= 0x0100,//8
	POS_LEFT_FREE	= 0x0200,//9
	POS_RIGHT_FREE	= 0x0400,//10
	POS_UP_FREE		= 0x0800,//11
	POS_DOWN_FREE	= 0x1000,//12
	POS_UP_DOWN		= 0x2000,//13
	POS_RIGHT_LEFT	= 0x4000,//14
	POS_SINGLE		= 0x8000,//15

	POS_NONE		= 0, //なんかわからんやつ
};

using ChipType = StageChild::ChipType;



class Map
{
public:
	Map(int stageID, int mapID, MapPos);
	~Map();
	void update(PlayerChild*, const StageChild*);
	void draw(const Vector2* camera) const;
	void draw_front(const Vector2* camera) const;

	bool isRigid_down(ChipType _ct) const { return (_ct & 0b101100110) != 0; }//下にすり抜けられないブロック，床になる
	bool isRigid_up(ChipType _ct)   const { return (_ct & 0b000011010) != 0; }//上にすり抜けられないブロック，天井になる
	bool isSlant(ChipType _ct)		const { return (_ct & 0b001111000) != 0; }//斜めブロック

	ChipType getChipType(const Vector2&, bool isPlayer) const;
	ChipType getChipType(const Vector2&) const;
	ChipType getChipType(const RawVector2&, bool isPlayer) const;

	int getTopPosition(const Vector2*, const int& dy) const;//引数は今いる地点の座標にvectorRrateをかけたもの
	int getBottomPosition(const Vector2*, const int& dy) const;//引数は今いる地点の座標にvectorRrateをかけたもの

	void processDynamicCollision(PlayerChild*);

	vector< GimmickChild* > getGimmicks() { return mGimmicks; }
	vector< DynamicGimmickChild* > getDynamicGimmicks() { return mDynamicGimmicks; }
	vector< SwitchWithBlock* > getSwitchWithBlocks() { return mSwitchWithBlocks; }
	EnemyController* getEController() { return this->mEController; }

	//bool isClear() const;

	void addGimmick(GimmickChild* _gmk) { mGimmicks.push_back(_gmk); }
	void addDynamicGimmick(DynamicGimmickChild* _d_gmk) { mDynamicGimmicks.push_back(_d_gmk); mDynamicGimmicks.shrink_to_fit(); }
	void addGimmick(int x, int y, int ID) { loadGimmick(x, y, ID); }
	void addEnemy(EnemyChild*);
	void addEnemy(AllEnemies, int x, int y);
	void addEnemy(AllEnemies, const Vector2*, int x, int y);
	void addSwitchWithBlock(SwitchWithBlock* s) {
		mDynamicGimmicks.push_back(s);
		mSwitchWithBlocks.push_back(s);
	}
	
	std::array< std::array<int, MAP_WIDTH_NUM>, MAP_HEIGHT_NUM> getMapData() { return mapData; }

private:
	void initialize();

	MapPos mapPos;

	//ギミックの配列
	std::vector< GimmickChild* > mGimmicks;
	std::vector< DynamicGimmickChild* > mDynamicGimmicks;
	std::vector< SwitchWithBlock* > mSwitchWithBlocks;

	//敵
	EnemyController* mEController;

	//テンプレートたち
	template<typename D_Gmk>
	void updateDynamicGimmick(D_Gmk, PlayerChild*, const StageChild*);

	template<typename D_Gmk>
	void processDynamicCollision(D_Gmk d_gmk, PlayerChild* _player);
	
	bool isLeft(MapPos _mp)		const { return _mp & 0xDC49; }
	bool isRight(MapPos _mp)	const { return _mp & 0xDB24; }
	bool isUp(MapPos _mp)		const { return _mp & 0xB607; }
	bool isDown(MapPos _mp)		const { return _mp & 0xAFC0; }
	bool isCenter(MapPos _mp)	const { return _mp & 0x0010; }


	//以下マップ関連

	//mapChipの画像(32x32pixcels)

	//map(y:20 x:30 :: 320chips)
	//mapData[y][x]でアクセスできる
	//mapData[~19][~29]
	std::array< std::array<int, MAP_WIDTH_NUM>, MAP_HEIGHT_NUM> mapData;
	std::array< std::array<int, MAP_WIDTH_NUM>, MAP_HEIGHT_NUM> gimmickData;



	void loadMap(int stageID, int mapID);
	void loadGimmick(int x,int y,int ID);
	void loadEnemy(int x, int y, int ID);

	
	//前景描画
	//template<typename Arr>
	void drawMap(const Vector2*) const;

	class Chip
	{
	public:
		Chip(ChipType _chipType) : mChipType(_chipType) {};
		~Chip() {};
		ChipType getChipType() const { return mChipType; }
		void setChipType(ChipType _chipType) { mChipType = _chipType; }
	private:
		ChipType mChipType;
	};

	//マップチップ
	array<Chip, 37> chip
	{
		Chip(ChipType::TYPE_BACK),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIDE),
		Chip(ChipType::TYPE_DOWN_SLANT_RIGHT),
		Chip(ChipType::TYPE_DOWN_SLANT_LEFT),
		Chip(ChipType::TYPE_UP_SLANT_RIGHT),
		Chip(ChipType::TYPE_UP_SLANT_LEFT),
		Chip(ChipType::TYPE_LADDER),
		Chip(ChipType::TYPE_LADDER_TOP),
		Chip(ChipType::TYPE_LESAL),
		Chip(ChipType::TYPE_LESAL),
		Chip(ChipType::TYPE_LESAL),
		Chip(ChipType::TYPE_LESAL),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),

		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIDE),
		Chip(ChipType::TYPE_DOWN_SLANT_RIGHT),
		Chip(ChipType::TYPE_DOWN_SLANT_LEFT),
		Chip(ChipType::TYPE_UP_SLANT_RIGHT),
		Chip(ChipType::TYPE_UP_SLANT_LEFT),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),

		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_DOWN_SLANT_RIGHT),
		Chip(ChipType::TYPE_DOWN_SLANT_LEFT),
		Chip(ChipType::TYPE_UP_SLANT_RIGHT),
		Chip(ChipType::TYPE_UP_SLANT_LEFT),
	};

};




}
}
}