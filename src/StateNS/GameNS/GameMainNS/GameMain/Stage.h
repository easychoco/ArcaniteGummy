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
	Stage(int mapID, int stageID);
	~Stage();
	void initialize();
	void update(PlayerChild*);
	void draw(const Vector2* player) const;
	void setStageSize(int _x, int _y)
	{
		stage_max_x = _x;
		stage_max_y = _y;
	}

	enum ChipType
	{
		TYPE_BACK				= 0b00000001, //すり抜けられる
		TYPE_RIGID				= 0b00000010, //すり抜けられない
		TYPE_RIDE				= 0b00000100, //下からはすり抜け、上からはすり抜けられない
		TYPE_DOWN_SLANT_RIGHT	= 0b00001000, //右上へ向けた斜めブロック, 上がブロックなし
		TYPE_DOWN_SLANT_LEFT	= 0b00010000, //左上へ向けた斜めブロック, 上がブロックなし
		TYPE_UP_SLANT_RIGHT		= 0b00100000, //右上へ向けた斜めブロック, 下がブロックなし
		TYPE_UP_SLANT_LEFT		= 0b01000000, //左上へ向けた斜めブロック, 下がブロックなし
		TYPE_LADDER				= 0b10000000, //はしご
	};
	ChipType getChipType(const Vector2&) const;
	ChipType getChipType(const RawVector2&) const;

	bool isRigid_down(ChipType _ct) const { return (_ct & 0b1100110) != 0; }//下にすり抜けられないブロック，床になる
	bool isRigid_up(ChipType _ct)   const { return (_ct & 0b0011010) != 0; }//上にすり抜けられないブロック，天井になる
	bool isSlant(ChipType _ct)		const { return (_ct & 0b1111000) != 0; }//斜めブロック
	
	std::vector< DynamicGimmickChild* > getDynamicGimmicks() { return mDynamicGimmicks; }

private:
	int mBackImg;
	int stage_max_x;
	int stage_max_y;

	//ギミックの配列
	std::vector< GimmickChild* > mGimmicks;
	std::vector< DynamicGimmickChild* > mDynamicGimmicks;


	//以下マップ関連

	//mapChipの画像(32x32pixcels)
	int mapChip[8];

	//map(y:20 x:30 :: 320chips)
	//mapData[y][x]でアクセスできる
	//mapData[~19][~29]
//	std::array< std::array<int, 30>, 20> mapData;
	std::array< std::array<int, MAP_WIDTH_NUM>, MAP_HEIGHT_NUM> mapData;

	//前景描画
	template<typename Arr>
	void drawMap(Arr, const Vector2*) const;

	void loadMap(int stageID, int mapID);
	//void loadGimmick();

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
	array<Chip, 8> chip
	{
		Chip(ChipType::TYPE_BACK),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIDE),
		Chip(ChipType::TYPE_DOWN_SLANT_RIGHT),
		Chip(ChipType::TYPE_DOWN_SLANT_LEFT),
		Chip(ChipType::TYPE_UP_SLANT_RIGHT),
		Chip(ChipType::TYPE_UP_SLANT_LEFT),
		Chip(ChipType::TYPE_LADDER)
	};


};




}
}
}