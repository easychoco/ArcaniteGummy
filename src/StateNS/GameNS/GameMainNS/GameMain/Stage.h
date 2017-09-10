#pragma once
#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class PlayerChild;
class GimmickChild;
class DynamicGimmickChild;

class Stage
{
public:
	Stage(int mapID, int stageID,int stage_max_x,int stage_max_y);
	~Stage();
	void initialize();
	void update(PlayerChild*);
	void draw(const Vector2* player) const;

	enum ChipType
	{
		TYPE_BACK				= 0b000000001, //すり抜けられる
		TYPE_RIGID				= 0b000000010, //すり抜けられない
		TYPE_RIDE				= 0b000000100, //下からはすり抜け、上からはすり抜けられない
		TYPE_DOWN_SLANT_RIGHT	= 0b000001000, //右上へ向けた斜めブロック, 上がブロックなし
		TYPE_DOWN_SLANT_LEFT	= 0b000010000, //左上へ向けた斜めブロック, 上がブロックなし
		TYPE_UP_SLANT_RIGHT		= 0b000100000, //右上へ向けた斜めブロック, 下がブロックなし
		TYPE_UP_SLANT_LEFT		= 0b001000000, //左上へ向けた斜めブロック, 下がブロックなし
		TYPE_LADDER				= 0b010000000, //はしご
		TYPE_LADDER_TOP			= 0b100000000, //はしごの上
	};

	bool isRigid_down(ChipType _ct) const { return (_ct & 0b101100110) != 0; }//下にすり抜けられないブロック，床になる
	bool isRigid_up(ChipType _ct)   const { return (_ct & 0b000011010) != 0; }//上にすり抜けられないブロック，天井になる
	bool isSlant(ChipType _ct)		const { return (_ct & 0b001111000) != 0; }//斜めブロック

	ChipType getChipType(const Vector2&, bool isPlayer) const;
	ChipType getChipType(const Vector2&) const;
	ChipType getChipType(const RawVector2&, bool isPlayer) const;

	int getTopPosition(const Vector2*, const int& dy) const;//引数は今いる地点の座標にvectorRrateをかけたもの
	int getBottomPosition(const Vector2*, const int& dy) const;//引数は今いる地点の座標にvectorRrateをかけたもの
	std::vector< DynamicGimmickChild* > getDynamicGimmicks() { return mDynamicGimmicks; }

	bool isClear() const;

private:
	int mBackImg;
	int stage_num;
	int stage_max_x;
	int stage_max_y;
	int stage_num_x;
	int stage_num_y;

	//ギミックの配列
	std::vector< GimmickChild* > mGimmicks;
	std::vector< DynamicGimmickChild* > mDynamicGimmicks;

	GimmickChild* clearFlag;


	//以下マップ関連

	//mapChipの画像(32x32pixcels)
	int mapChip[120];

	//map(y:20 x:30 :: 320chips)
	//mapData[y][x]でアクセスできる
	//mapData[~19][~29]
	std::array< std::array<int, MAP_WIDTH_NUM>, MAP_HEIGHT_NUM> mapData;
	std::array< std::array<int, MAP_WIDTH_NUM>, MAP_HEIGHT_NUM> gimmickData;

	//前景描画
	template<typename Arr>
	void drawMap(Arr, const Vector2*) const;

	void loadMap(int stageID, int mapID);
	void loadGimmick(int x,int y);

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
		Chip(ChipType::TYPE_LADDER),
		Chip(ChipType::TYPE_LADDER_TOP),

	};


};




}
}
}