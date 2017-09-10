#pragma once

#include "..\GameMain.h"


namespace StateNS {
namespace GameNS {

namespace GameMainNS{

class Child;

class System
{
public:
	System(int stagenum,int stageX,int stageY);
	~System();
	void initialize();
	void update(GameMain::HowStageMove);
	void draw() const;
	int getNowStage() const { return nowStage; }

private:
	int nowStage;
	int stage_x;
	int stage_y;
	int stage_num;
};




}
}
}