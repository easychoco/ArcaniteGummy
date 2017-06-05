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
	bool canPass(const Vector2) const;

	enum ChipType
	{
		TYPE_BACK,				//すり抜けられる
		TYPE_RIGID,				//すり抜けられない
		TYPE_RIDE,				//下からはすり抜け、上からはすり抜けられない
		TYPE_SLANT_RIGHT,		//右上へ向けた斜めブロック, 下からすり抜けられる
		TYPE_SLANT_LEFT,		//左上へ向けた斜めブロック, 下からすり抜けられる
	};

private:
	int mBackImg;


	//ギミックの配列
	std::vector<GimmickChild*> mGimmicks;

	//mapChipの画像(32x32pixcels)
	int mapChip[3];

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
	array<Chip, 3> chip
	{
		Chip(ChipType::TYPE_BACK),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_SLANT_RIGHT),
	};


};




}
}
}