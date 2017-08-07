#include "Usagi.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Usagi::Usagi(int _x, int _y) : EnemyChild(100)
{
	this->point = new Vector2(_x, _y);

	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Usagi画像読み込みエラー!");

	initialize();
};


Usagi::~Usagi()
{

}

void Usagi::initialize()
{
	mTime = 0;
	mDirection = false;
}

void Usagi::update()
{
	mTime++;


}

void Usagi::draw(const Vector2* _camera) const
{
	//compositeはここに書く


	//画面内にいなければreturn
	if (abs(point->pos_x() - _camera->pos_x()) > 350000 || abs(point->pos_y() - _camera->pos_y()) > 270000)return;



	int draw_x = 320 + (point->pos_x() - _camera->pos_x()) / MyData::vectorRate;
	int draw_y = 240 + (point->pos_y() - _camera->pos_y()) / MyData::vectorRate;

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, mDirection);


	//DrawFormatString(0, 0, MyData::BLACK, "%d", draw_x);
	//DrawFormatString(0, 20, MyData::BLACK, "%d", draw_y);
}


//==============================================
//内部プライベート関数
//==============================================

void Usagi::damagedAction()
{

}

}
}
}