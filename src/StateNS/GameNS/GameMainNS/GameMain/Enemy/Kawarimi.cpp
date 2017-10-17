#include "Kawarimi.h"

#include "..\Collision.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{
	
bool Kawarimi::imgLoad = false;
int Kawarimi::images[8];


Kawarimi::Kawarimi(int _x, int _y) : EnemyChild(100000, _x, _y, 32, 64)
{
	loadImage();
	

	initialize();
};


Kawarimi::~Kawarimi()
{
	//DeleteGraphはしない
}

void Kawarimi::initialize()
{
	this->mDirection = true;
	this->moveSpeed = 1000;
	this->isAlive = true;
	mImage = images[GetRand(5)];
}

void Kawarimi::update(const StageChild* _stage,const Vector2* _camera)
{

	if (!isAlive)mTime++;
	//ダメージを受けたら
	if (damaged && isAlive) 
	{
		hpController.recover(1);
		isAlive = false;
		hpController.isMuteki = true;
		this->collision->noCollide = true;
		mImage = images[actState * 2];
		mTime = 0;
		attack(_stage);
	}
	standardAction(_stage);
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

void Kawarimi::move(const StageChild* _stage, int& _dx, int& _dy)
{
	_dy = getBottomDiffer(_stage, 4000, _dx < 0);
	if (mTime < 60)return;
	if (!isAlive)return;

	//_dyが0でなかったら空中にいる
/*	if (_dy != 0)
	{
		_dx = 0;
		return;
	}*/
	_dx = getHorizontalDiffer(_stage, moveSpeed, _dy < 0);
	this->mDirection = _dx > 0;
	
}


//==============================================
//内部プライベート関数
//==============================================
void Kawarimi::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Kawarimi.png", 8, 8, 1, 32, 64, images);
		assert(tmp != -1 && "Kawarimi画像読み込みエラー");
	}
	imgLoad = true;
}

void Kawarimi::hittedAction()
{
	actState = ENE_ACT_DEAD;
	this->width = 32;
}

void Kawarimi::attack(const StageChild* _stage)
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

void Kawarimi::draw_other(const Vector2* _camera) const
{
	for (const auto& a : attacks)
	{
		if (a->isActive)a->draw(_camera);
	}
}


//==============================================
//Thunderクラス
//==============================================
Kawarimi::Thunder::Thunder(const Character* _parent, const StageChild* _stage, int _x, int _y, int _speed) :
	Attack(_parent, _parent->getVector2()->raw_x, _parent->getVector2()->raw_y, 32, 32, ObjectID::ID_NONE),
	stage(_stage)
{
	this->setStatus(Vector2(_x, _y, true), _speed);

	//for Debug
	this->damageValue = 20;

	mImage = LoadGraph("Data/Image/PikachiAttack.png");
	assert(mImage != -1 && "KawarimiAttack画像読み込みエラー");
}

Kawarimi::Thunder::~Thunder()
{
	DeleteGraph(mImage);
}

void Kawarimi::Thunder::update()
{
	mTime++;
	//	int dx_tmp = getHorizontalDiffer(stage, dx, false, false);
	//	int dy_tmp = dy < 0 ? getTopDiffer(stage, dy, dx < 0, false) : getBottomDiffer(stage, dy, dx < 0, false);

	if (mTime < 60)return;
	this->p->raw_x += dx;
	this->p->raw_y += dy;

	StageChild::ChipType chipType = stage->getChipType(*(this->p), true);
	//床についたら
	if (stage->isRigid_down(chipType))this->isActive = false;
}

void Kawarimi::Thunder::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(p->raw_x - _camera->raw_x) > 480000 || abs(p->raw_y - _camera->raw_y) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, mTime * pi(1 / 15.0f), mImage, true, mDirection);
}

void Kawarimi::Thunder::setStatus(Vector2 _player, int _speed)
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

void Kawarimi::Thunder::hittedAction()
{
	this->isActive = false;
}








}
}
}