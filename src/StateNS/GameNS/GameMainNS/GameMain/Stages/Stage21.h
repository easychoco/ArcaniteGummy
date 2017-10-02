#pragma once
#include "..\..\..\..\..\Data.h"
#include "StageChild.h"
#include "..\Gimmick\Torch.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Stage21 : public StageChild
{
public:
	Stage21();
	~Stage21();
	void update(GameMain*, PlayerChild*);
	void draw(const Vector2* player) const;
	bool isClear() const;
	
private:
	void initialize();

	vector<Torch*> torches;
	vector<Torch*> torches2;

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
	};


};




}
}
}