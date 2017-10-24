#pragma once
#include "..\..\..\..\..\Data.h"
#include "StageChild.h"
#include "..\Enemy\Junko.h"
namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Torch;

class Stage23 : public StageChild
{
public:
	Stage23();
	~Stage23();
	void update(GameMain*, PlayerChild*);
	void draw(const Vector2* player) const;
	bool isClear() const;
	
private:
	void initialize();
	void updateConverse(GameMain*, PlayerChild*);
	int time;
	bool converseFlag0,converseFlag0fin;
	bool converseFlag1,converseFlag1fin;
	bool converseFlag2,converseFlag2fin;
	int imageJunko;
	Junko* junko = 0;

};




}
}
}