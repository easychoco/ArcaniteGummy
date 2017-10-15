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
	void updateConverse(GameMain*, PlayerChild*);
	vector<Torch*> torches;
	vector<Torch*> torches2;
	bool converseFlag0;

};




}
}
}