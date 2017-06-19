#pragma once
#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class GimmickChild;

class Stage
{
public:
	Stage(int stageID);
	~Stage();
	void initialize();
	void update();
	void draw(const Vector2* player) const;

	enum ChipType
	{
		TYPE_RIGID				= 0b0000001, //すり抜けられない
		TYPE_RIGID_SLANT_RIGHT	= 0b0000010, //右上へ向けた斜めブロック, 下からすり抜けられない
		TYPE_RIGID_SLANT_LEFT	= 0b0000100, //左上へ向けた斜めブロック, 下からすり抜けられない
		TYPE_BACK				= 0b0001000, //すり抜けられる
		TYPE_RIDE				= 0b0010000, //下からはすり抜け、上からはすり抜けられない
		TYPE_SLANT_RIGHT		= 0b0100000, //右上へ向けた斜めブロック, 下からすり抜けられる
		TYPE_SLANT_LEFT			= 0b1000000, //左上へ向けた斜めブロック, 下からすり抜けられる
	};
	ChipType getChipType(const Vector2) const;
	bool isRigid(ChipType _ct) const { return (_ct & 0b0000111) != 0; }
	bool isSlant(ChipType _ct) const { return (_ct & 0b1100110) != 0; }
	bool  isRide(ChipType _ct) const { return (_ct & 0b1110111) != 0; }

private:
	int mBackImg;

	//ギミックの配列
	std::vector< GimmickChild* > mGimmicks;

	//mapChipの画像(32x32pixcels)
	int mapChip[4];

	//map(y:15 x:20 :: 320chips)
	//mapData[y][x]でアクセスできる
	//mapData[~14][~19]
	std::array< std::array<int, 30>, 30> mapData;

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
	array<Chip, 4> chip
	{
		Chip(ChipType::TYPE_BACK),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_SLANT_RIGHT),
		Chip(ChipType::TYPE_SLANT_LEFT),
	};


};




}
}
}