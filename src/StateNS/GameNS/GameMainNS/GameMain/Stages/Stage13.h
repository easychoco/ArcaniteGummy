#pragma once
#include "..\..\..\..\..\Data.h"
#include "StageChild.h"
#include "..\Enemy\Reisen.h"
namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Torch;

class Stage13 : public StageChild
{
public:
	Stage13();
	~Stage13();
	void update(GameMain*, PlayerChild*);
	void draw(const Vector2* player) const;
	bool isClear() const;
	
private:
	void initialize();
	void updateConverse(GameMain*,PlayerChild*);
	void draw_front(const Vector2* _camera) const override;
	bool converseFlag0;
	bool converseFlag1;
	bool converseFlag2;
	int cTime;
	Reisen* reisen;

};




}
}
}