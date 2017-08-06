#include "Mokou.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

//もこたんいんしたお
Mokou::Mokou(int _x, int _y) : PlayerChild(5.0f, 20.0f, 2, 100)
{
	this->p = new Vector2(_x, _y);
	this->camera = new Vector2(_x, _y);
	initialize();
}

Mokou::~Mokou()
{
	SAFE_DELETE(p);
	SAFE_DELETE(camera);
}

void Mokou::initialize()
{
	this->moveSpeed = 5.0f;
	loadImage();
}

PlayerChild* Mokou::update(const Stage* _stage)
{
	PlayerChild* next = this;

	standardMove(_stage);
	
	return next;
}


//==============================================
//内部プライベート関数
//==============================================
void Mokou::attack()
{

}

void Mokou::draw_other() const
{

}


void Mokou::loadImage()
{
	img = LoadGraph("Data/Image/player.png");
	assert(img != -1 && "自機画像読み込みエラー");
}


}
}
}