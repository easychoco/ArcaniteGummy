#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Balloon : public EnemyChild
{
public:
	Balloon(int x, int y);
	~Balloon();

	void update(const StageChild* _stage, const Vector2* _camera);


private:
	int images;
	bool imgLoad = false;
	int mTime;

	//Character‚ÌŠÖ”
	void hittedAction();

	//Enemychild‚ÌŠÖ”
	void move(const StageChild*, int& dx, int& dy);
	void loadImage() { images = LoadGraph("Data/Image/balloon.png"); mImage = images; imgLoad = true; }


	void initialize();

};




}
}
}