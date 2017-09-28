#include "Airmz.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Airmz::Airmz(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32, 1, 1)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Airmz画像読み込みエラー!");

	initialize();
};

Airmz::~Airmz()
{
	DeleteGraph(images);
}

void Airmz::initialize()
{
	mTime = 0;
	this->mDirection = false;
}

void Airmz::update(const StageChild* _stage, const Vector2* _camera)
{
	if(mTime == 0)this->mDirection = player->raw_x > this->p->raw_x;

	//横に直進するだけ
	mTime++;
	mTime %= 90;
	standardAction(_stage);

	if (mTime == 0)attack(_stage);
	
	//攻撃
	for (auto& a : attacks)
	{
		if (a->isActive)
		{
			a->update();
			a->checkActive(_camera);
		}
	}


}

void Airmz::move(const StageChild* _stage, int& _dx, int& _dy)
{
	int x = this->mDirection ? vectorRate : -vectorRate;
	
	_dx = getHorizontalDiffer(_stage, x, _dy < 0);
}


//==============================================
//内部プライベート関数
//==============================================
void Airmz::hittedAction()
{

}


void Airmz::attack(const StageChild* _stage)
{
	int dx = mDirection ? 5 : -5;

	//使っていないオブジェクトを再利用
	for (auto& a : attacks)
	{
		if (!a->isActive)
		{
			a->setStatus(*player, 5000);
			return;
		}
	}

	//すべて使っていたらnewする
	attacks.push_back(new Bomb(this, _stage, player->raw_x, player->raw_y, 5000));
}

void Airmz::draw_other(const Vector2* _camera) const
{
	for (const auto& a : attacks)
	{
		if (a->isActive)a->draw(_camera);
	}
}

//==============================================
//Bombクラス
//==============================================
Airmz::Bomb::Bomb(const Character* _parent, const StageChild* _stage, int _x, int _y, int _speed) :
	Attack(_parent, _parent->getVector2()->raw_x, _parent->getVector2()->raw_y, 32, 32, ObjectID::ID_NONE),
	stage(_stage)
{
	this->setStatus(Vector2(_x, _y, true), _speed);


	//for Debug
	this->damageValue = 20;

	mImage = LoadGraph("Data/Image/AirmzAttack.png");
	assert(mImage != -1 && "AirmzAttack画像読み込みエラー");
}

Airmz::Bomb::~Bomb()
{
	DeleteGraph(mImage);
}

void Airmz::Bomb::update()
{
	mTime++;
	mTime %= 90;

	this->p->raw_x += -dx*vectorRate;
	float tmp = -sinf(Pi / 3)*mTime + mTime*mTime / 10.0f;
	this->p->raw_y = tmp*vectorRate + sy;

	//if (dx_tmp == 0 || dy_tmp == 0)this->isActive = false;
}

void Airmz::Bomb::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(p->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, mTime * pi(1 / 15.0f), mImage, true, mDirection);
}

void Airmz::Bomb::setStatus(Vector2 _player, int _speed)
{
	mTime = 0;
	this->isActive = true;
	this->mDirection = this->dx < 0;

	*(this->p) = *(parent->getVector2());

	float differ_x = (float)(this->p->raw_x - _player.raw_x);
	float differ_y = (float)(this->p->raw_y - _player.raw_y);

	sy = this->p->raw_y;

	float angle = atan2f(differ_y, differ_x) + Pi;
	this->dx = 2;
	//	this->dy = (int)(_speed * sinf(angle));
}

void Airmz::Bomb::hittedAction()
{
	this->isActive = false;
}







}
}
}