#pragma once
#include "..\..\..\..\..\Data.h"
#include "StageChild.h"
#include "..\Enemy\Nue_Boss.h"
namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Torch;

class Stage33 : public StageChild
{
public:
	Stage33();
	~Stage33();
	void update(GameMain*, PlayerChild*);
	void draw(const Vector2* player) const;
	bool isClear() const;
	void draw_front(const Vector2* _camera) const override;

private:
	void initialize();
	void updateConverse(GameMain*, PlayerChild*);
	bool converseFlag0, converseFlag0fin;
	bool converseFlag1, converseFlag1fin;
	bool converseFlag2, converseFlag2fin;
	bool converseFlag3, converseFlag3fin;
	int cTime;
	Nue_Boss* nue;
	int imageReisen;
	int imageNue;
	int imageMokou;
};




}
}
}