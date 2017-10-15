#pragma once
#include "..\..\..\..\..\Data.h"
#include "StageChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Stage41 : public StageChild
{
public:
	Stage41();
	~Stage41();
	void update(GameMain*, PlayerChild*);
	void draw(const Vector2* player) const;
	bool isClear() const;
	void draw_front(const Vector2* _camera) const override;
private:
	void initialize();
	void updateConverse(GameMain*,PlayerChild*);
	bool converseFlag0;
	bool converseFlag1;
	int cTime;
	int imageFlan;

};




}
}
}