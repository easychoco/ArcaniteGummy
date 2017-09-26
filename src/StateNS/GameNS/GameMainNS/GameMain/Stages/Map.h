#pragma once

#include "..\..\..\..\..\Data.h"
#include "StageChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class PlayerChild;
class GimmickChild;
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
+-----------+
*/
enum MapPos
{
	//番号は上の図での位置
	POS_LEFT_UP		= 0b000000001,//0
	POS_UP			= 0b000000010,//1
	POS_RIGHT_UP	= 0b000000100,//2
	POS_LEFT		= 0b000001000,//3
	POS_CENTER		= 0b000010000,//4
	POS_RIGHT		= 0b000100000,//5
	POS_LEFT_DOWN	= 0b001000000,//6
	POS_DOWN		= 0b010000000,//7
	POS_RIGHT_DOWN	= 0b100000000,//8

	POS_NONE,		//なんかわからんやつ
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


	vector< GimmickChild* > getGimmicks() { return mGimmicks; }
	vector< DynamicGimmickChild* > getDynamicGimmicks() { return mDynamicGimmicks; }
	vector< SwitchWithBlock* > getSwitchWithBlocks() { return mSwitchWithBlocks; }
	EnemyController* getEController() { return this->mEController; }

	//bool isClear() const;

	void addGimmick(DynamicGimmickChild* _d_gmk) { mDynamicGimmicks.push_back(_d_gmk); }
	void addGimmick(int x, int y, int ID) { loadGimmick(x, y, ID); }
	void addEnemy(AllEnemies);
	
	std::array< std::array<int, MAP_WIDTH_NUM>, MAP_HEIGHT_NUM> getMapData() { return mapData; }

	template<typename D_Gmk>
	void updateDynamicGimmick(D_Gmk, PlayerChild*, const StageChild*);

private:
	void initialize();

	MapPos mapPos;

	//ギミックの配列
	std::vector< GimmickChild* > mGimmicks;
	std::vector< DynamicGimmickChild* > mDynamicGimmicks;
	std::vector< SwitchWithBlock* > mSwitchWithBlocks;

	//敵
	EnemyController* mEController;

	//GimmickChild* clearFlag;
	
	bool isLeft(MapPos _mp)		const { return _mp & 0b001001001; }
	bool isRight(MapPos _mp)	const { return _mp & 0b100100100; }
	bool isUp(MapPos _mp)		const { return _mp & 0b000000111; }
	bool isDown(MapPos _mp)		const { return _mp & 0b111000000; }
	bool isCenter(MapPos _mp)	const { return _mp & 0b000010000; }
	

	//以下マップ関連

	//mapChipの画像(32x32pixcels)

	//map(y:20 x:30 :: 320chips)
	//mapData[y][x]でアクセスできる
	//mapData[~19][~29]
	std::array< std::array<int, MAP_WIDTH_NUM>, MAP_HEIGHT_NUM> mapData;
	std::array< std::array<int, MAP_WIDTH_NUM>, MAP_HEIGHT_NUM> gimmickData;



	void loadMap(int stageID, int mapID);
	void loadGimmick(int x,int y,int ID);

	
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
	array<Chip, 20> chip
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
	};

};




}
}
}