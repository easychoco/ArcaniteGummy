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

private:
	int mBackImg;


	//ギミックの配列
	std::vector<GimmickChild*> mGimmicks;

	//mapChip(32x32pixcels)
	int mapChip[2];

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
		Chip(bool _canPass, bool _canRide) : canPass(_canPass), canRide(_canRide) {};
		~Chip() {};
		const bool canPass;//通ることができるか
		const bool canRide;//上に乗れるかどうか
	};

	array<Chip, 2> chip
	{
		Chip(false, false),
		Chip(true, false),
	};


};




}
}
}