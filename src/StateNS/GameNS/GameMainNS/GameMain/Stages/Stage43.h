#pragma once
#include "..\..\..\..\..\Data.h"
#include "StageChild.h"
#include "..\Enemy\Fran.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Torch;

class Stage43 : public StageChild
{
public:
	Stage43();
	~Stage43();
	void update(GameMain*, PlayerChild*);
	void draw(const Vector2* player) const;
	bool isClear() const;
	
private:
	void initialize();
	void updateConverse(GameMain*, PlayerChild*);
	bool converseFlag0;
	bool converseFlag1,converseFlag1fin;
	bool converseFlag2, converseFlag2fin;
	int imageSakuya, imageNue;
	Fran* fran;
	vector<Torch*> torches;
	vector<Torch*> torches2;

};




}
}
}