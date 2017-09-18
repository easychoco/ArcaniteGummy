#include "Pikachi.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Pikachi::Pikachi(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32,1,1)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Pikachi画像読み込みエラー!");

	initialize();
};


Pikachi::~Pikachi()
{
	DeleteGraph(mImage);
}

void Pikachi::initialize()
{
	this->mDirection = false;
	this->moveSpeed = 0;
	this->mTime = 0;
}

void Pikachi::update(const StageChild* _stage,const Vector2* _camera)
{
	mTime++;
	mTime %= 211;
	standardAction(_stage);
	this->mDirection = player->raw_x > this->p->raw_x;

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

void Pikachi::move(const StageChild* _stage, int& _dx, int& _dy)
{

	if (150 <= mTime ) 
	{
		int tmp_dy = mTime < 180 ? getTopDiffer(_stage, -2 * vectorRate, true) : getBottomDiffer(_stage, 2 * vectorRate, true);
		_dy = tmp_dy;
	}
	
	if (mTime == 180)
	{
		attack(_stage);
	}


}


//==============================================
//内部プライベート関数
//==============================================

void Pikachi::hittedAction()
{

}

void Pikachi::attack(const StageChild* _stage)
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
	attacks.push_back(new Thunder(this, _stage, player->raw_x, player->raw_y, 5000));
}

void Pikachi::draw_other(const Vector2* _camera) const
{
	for (const auto& a : attacks)
	{
		if (a->isActive)a->draw(_camera);
	}
}

//==============================================
//Thunderクラス
//==============================================
Pikachi::Thunder::Thunder(const Character* _parent, const StageChild* _stage, int _x, int _y, int _speed) :
Attack(_parent, _parent->getVector2()->raw_x, _parent->getVector2()->raw_y, 32, 32, ObjectID::ID_NONE),
stage(_stage)
{
	this->setStatus(Vector2(_x, _y, true), _speed);

	//for Debug
	this->damageValue = 20;

	mImage = LoadGraph("Data/Image/PikachiAttack.png");
	assert(mImage != -1 && "PikachiAttack画像読み込みエラー");
}

Pikachi::Thunder::~Thunder()
{
	DeleteGraph(mImage);
}

void Pikachi::Thunder::update()
{
	mTime++;
	int dx_tmp = getHorizontalDiffer(stage, dx, false, false);
	int dy_tmp = getHorizontalDiffer(stage, dy, false, false);

	this->p->raw_x += dx_tmp;
	this->p->raw_y += dy_tmp;

	if (dx_tmp == 0 || dy_tmp == 0)this->isActive = false;
}

void Pikachi::Thunder::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(p->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, mTime * pi(1 / 15.0f), mImage, true, mDirection);
}

void Pikachi::Thunder::setStatus(Vector2 _player, int _speed)
{
	mTime = 0;
	this->isActive = true;
	this->mDirection = this->dx < 0;

	*(this->p) = *(parent->getVector2());

	float differ_x = (float)(this->p->raw_x - _player.raw_x);
	float differ_y = (float)(this->p->raw_y - _player.raw_y);

	float angle = atan2f(differ_y, differ_x) + Pi;
	this->dx = (int)(_speed * cosf(angle));
	this->dy = (int)(_speed * sinf(angle));
}

void Pikachi::Thunder::hittedAction()
{
	this->isActive = false;
}





}
}
}