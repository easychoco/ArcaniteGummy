#include "Kaguya.h"
#include "Shot.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS{

	
bool Kaguya::imgLoad = false;
int Kaguya::images[32];



Kaguya::Kaguya(int _x, int _y) : 
EnemyChild(1000, _x, _y, 32, 32, false, true)
{
	loadImage();
	
	initialize();
}

Kaguya::~Kaguya()
{
	//DeleteGraph(mImage2);
}

void Kaguya::initialize()
{
	this->mTime = 0;
	this->init_attacks = false;

	this->mImage = images[0];

	this->isMakingEnemy = false;
	this->makeItDark = false;
	this->isVanish = false;
	
}

void Kaguya::update(const StageChild* _stage, const Vector2* _camera)
{
	this->mDirection = this->p->raw_x > player->raw_x;

	standardAction(_stage);
}

void Kaguya::move(const StageChild* _stage, int& _dx, int& _dy)
{

}

void Kaguya::draw_other(const Vector2* _camera) const
{
	//for Debug
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawString(draw_x - 16, draw_y - 32, "輝夜", BLUE);

	//for Debug
	DrawFormatString(draw_x - 16, draw_y - 64, GREEN, "%d", hpController.getHP());
}


//==============================================
//内部プライベート関数
//==============================================
void Kaguya::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Character/chip_kaguya.png", 32, 8, 4, 32, 64, images);
		assert(tmp != -1 && "Kaguya画像読み込みエラー");
	}
	imgLoad = true;
}

void Kaguya::hittedAction()
{

}

//==============================================
//Shot_aroundクラス
//==============================================




}
}
}