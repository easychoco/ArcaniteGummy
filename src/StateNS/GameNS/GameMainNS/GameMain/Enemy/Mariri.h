#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"
#include "..\Attack.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Mariri : public EnemyChild
{
public:
	Mariri(int x, int y);
	~Mariri();

	void update(const StageChild* _stage,const Vector2* _camera);

private:
	int mTime;

	static bool imgLoad;
	static int images[8];
	void loadImage();

	//Character‚ÌŠÖ”
	void hittedAction();

	//Enemychild‚ÌŠÖ”
	void move(const StageChild*, int& dx, int& dy);
	
	void initialize();

	bool attackDirection;
	int moveSpeed;
	bool preOnGround;


};


}
}
}