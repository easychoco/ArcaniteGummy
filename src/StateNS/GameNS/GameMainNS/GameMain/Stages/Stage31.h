#pragma once
#include "..\..\..\..\..\Data.h"
#include "StageChild.h"
#include "..\Gimmick\Torch.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Stage31 : public StageChild
{
public:
	Stage31();
	~Stage31();
	void update(GameMain*, PlayerChild*);
	void draw(const Vector2* player) const;
	bool isClear() const;
	
private:
	void initialize();
	void updateConverse(GameMain*, PlayerChild*);
	bool converseFlag0, converseFlag0fin;
	bool converseFlag1,converseFlag1fin;
	int imageReisen;

	vector<Torch*> torches{};
	vector<Torch*> torches2{};

};




}
}
}