#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Rarashi : public EnemyChild
{
public:
	Rarashi(int x, int y);
	~Rarashi();

	void update(const StageChild* _stage, const Vector2* _camera);


private:
	int images;
	bool imgLoad = false;
	
	int mTime;

	int moveSpeed;
	bool preOnGround;

	//Character‚ÌŠÖ”
	void hittedAction();

	//Enemychild‚ÌŠÖ”
	void move(const StageChild*, int& dx, int& dy);
	void loadImage() { images = LoadGraph("Data/Image/Rarashi.png"); mImage = images; imgLoad = true; }


	void initialize();
};




}
}
}