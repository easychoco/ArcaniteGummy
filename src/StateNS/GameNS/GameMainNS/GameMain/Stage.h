#pragma once
#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class PlayerChild;
class GimmickChild;

class Stage
{
public:
	Stage(int stageID);
	~Stage();
	void initialize();
	void update(PlayerChild*);
	void draw(const Vector2* player) const;

	enum ChipType
	{
		TYPE_BACK				= 0b0000001, //すり抜けられる
		TYPE_RIGID				= 0b0000010, //すり抜けられない
		TYPE_RIDE				= 0b0000100, //下からはすり抜け、上からはすり抜けられない
		TYPE_DOWN_SLANT_RIGHT	= 0b0001000, //右上へ向けた斜めブロック, 上がブロックなし
		TYPE_DOWN_SLANT_LEFT	= 0b0010000, //左上へ向けた斜めブロック, 上がブロックなし
		TYPE_UP_SLANT_RIGHT		= 0b0100000, //右上へ向けた斜めブロック, 下がブロックなし
		TYPE_UP_SLANT_LEFT		= 0b1000000, //左上へ向けた斜めブロック, 下がブロックなし
	};
	ChipType getChipType(const Vector2) const;
	ChipType getChipType(const RawVector2) const;

	bool isRigid_down(ChipType _ct) const { return (_ct & 0b1110110) != 0; }
	bool isRigid_up(ChipType _ct)   const { return (_ct & 0b0011010) != 0; }
	bool isSlant(ChipType _ct)		const { return (_ct & 0b1111000) != 0; }

private:
	int mBackImg;

	//ギミックの配列
	std::vector< GimmickChild* > mGimmicks;

	//mapChipの画像(32x32pixcels)
	int mapChip[7];

	//map(y:20 x:30 :: 320chips)
	//mapData[y][x]でアクセスできる
	//mapData[~19][~29]
	std::array< std::array<int, 30>, 20> mapData;

	//マップ描画

	//前景描画
	template<typename Arr>
	void drawMap(Arr, const Vector2*) const;

	void loadMap(int stageID);

	class Chip
	{
	public:
		Chip(ChipType _chipType) : chipType(_chipType) {};
		~Chip() {};
		ChipType getChipType() const { return chipType; }
		void setChipType(ChipType _chipType) { chipType = _chipType; }
	private:
		ChipType chipType;
	};

	//マップチップ
	array<Chip, 7> chip
	{
		Chip(ChipType::TYPE_BACK),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIDE),
		Chip(ChipType::TYPE_DOWN_SLANT_RIGHT),
		Chip(ChipType::TYPE_DOWN_SLANT_LEFT),
		Chip(ChipType::TYPE_UP_SLANT_RIGHT),
		Chip(ChipType::TYPE_UP_SLANT_LEFT)
	};


};




}
}
}