#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Karon : public EnemyChild
{
public:
	Karon(int x, int y);
	~Karon();

	void update(const StageChild* _stage, const Vector2* _camera);


private:
	//Character‚ÌŠÖ”
	void hittedAction();

	//Enemychild‚ÌŠÖ”
	void move(const StageChild*, int& dx, int& dy);
	int images[8];
	void loadImage()
	{
		if (!imgLoad)LoadDivGraph("Data/Image/Karon.png", 8, 8, 1, 32, 32, images);
		for (int i = 0; i < 8; i++)mImage[i] = images[i];
		imgLoad = true;
	}

	void initialize();


	bool imgLoad = false;
	
	int mTime;
	bool isAlive;
	int moveSpeed;
	bool preOnGround;
};




}
}
}