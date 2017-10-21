#include "Reisen.h"

#include "..\Collision.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS{

	
Reisen::Reisen(int x, int y) :
Reisen(x, y, true)
{ }

Reisen::Reisen(int _x, int _y, bool _isOriginal) :
EnemyChild(_isOriginal ? 500 : 25, _x, _y, 32, 64, _isOriginal, true),
maxHP(500),
isOriginal(_isOriginal)
{
	loadImage(); 
	mImage = images[0];
	
	initialize();
}

Reisen::~Reisen()
{
	SAFE_DELETE(replica);
	for (int i = 0; i < 32; i++)
	{
		DeleteGraph(images[i]);
	}
}

void Reisen::initialize()
{
	this->mTime = 0;
	this->nowMoving = false;
	this->makeReplica = false;

	if (isOriginal)
	{
		replica = new Reisen(p->raw_x / vectorRate, p->raw_y / vectorRate, false);
	}
	else
	{
		this->collision->noCollide = true;
		replica = 0;
	}
}

void Reisen::update(const StageChild* _stage, const Vector2* _camera)
{
	this->mDirection = this->p->raw_x > player->raw_x;

	++mTime;
	if (mTime % 90 == 0 && !nowMoving)attack();
	//if (!nowMoving && abs(player->raw_x - this->p->raw_x) < 64000)

	if (mTime % jump_interval == 0)
	{
		nowMoving = false;
	}

	//移動
	//360 はjump_intervalの偶数倍
	if(mTime == 360)
	{
		nowMoving = true;
	}
	//元に戻る
	//660 はjump_intervalの奇数倍
	if (mTime == 660)
	{
		nowMoving = true;
		mTime = jump_interval;
	}


	for (auto& a : attacks)
	{
		if (a->isActive)
		{
			a->update();
			a->checkActive(_camera);
		}
	}
	standardAction(_stage);


	//以下，分身関連の処理
	if (!isOriginal)return;

	//分身を作る
	//すでに作っていてやられていたら replica->isAlive() は false になる
	if (this->hpController.getHP() < maxHP / 3)
	{
		makeReplica = replica->isAlive();
		replica->collision->noCollide = false;
	}

	//分身をupdate
	if (makeReplica)
	{
		replica->update(_stage, _camera);
		makeReplica = replica->isAlive();
	}
	

}

vector<Attack*> Reisen::getAttacks() const
{
	//分身ならそのまま返す
	if (!isOriginal)return attacks;

	//本体なら分身の弾と一緒に返す
	vector<Attack*> ret = attacks;
	for (auto& a : replica->getAttacks())
	{
		ret.push_back(a);
	}

	return ret;
}

void Reisen::move(const StageChild* _stage, int& _dx, int& _dy)
{
	//何もなければ落下だけする
	_dy = getBottomDiffer(_stage, 4000, true);
	if (!nowMoving)return;

	//移動中
	float theta = pi(1 / (float)jump_interval) * (mTime % (jump_interval * 2));

	float sin1 = sinf(theta);
	float sin2 = sinf(theta * 2.0f);

	_dx = getHorizontalDiffer(_stage, (int)(-16000 * sin1), sin2 < 0.0f);
	_dy = ((sin2 < 0) ? getTopDiffer(_stage, (int)(-20000 * sin2), _dx < 0) : getBottomDiffer(_stage, (int)(-20000 * sin2), _dx < 0));
}

void Reisen::draw_other(const Vector2* _camera) const
{
	//分身をdraw
	if (makeReplica && isOriginal)
	{
		SetDrawBlendMode(DX_BLENDMODE_SUB, 130);
		replica->draw(_camera);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 20);
	}

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	draw_hp_bar(draw_x, draw_y - 32, maxHP, 50);


	for (const auto& a : attacks)
	{
		if (a->isActive)a->draw(_camera);
	}
}


//==============================================
//内部プライベート関数
//==============================================
void Reisen::loadImage()
{
	int tmp = LoadDivGraph("Data/Image/Character/chip_Reisen.png", 32, 8, 4, 32, 64, images);
	assert(tmp != -1 && "Reisen画像読み込みエラー");
}

void Reisen::hittedAction()
{

}

void Reisen::attack()
{
	//使っていないオブジェクトを再利用
	for (auto& a : attacks)
	{
		if (!a->isActive)
		{
			a->setStatus(*p, this->mDirection);
			a->isActive = true;
			return;
		}
	}

	//すべて使っていたらnewする
	attacks.push_back(new Shot(this, player, this->p->raw_x, this->p->raw_y));
}

//==============================================
//Shotクラス
//==============================================
Reisen::Shot::Shot(const EnemyChild* _parent, const Vector2* _player, int _x, int _y) :
Attack(_parent, _x, _y, 32, 32, ObjectID::ID_NONE),
player(_player)
{
	this->damageValue = 20;

	mImage = LoadGraph("Data/Image/shot0.png");
	assert(mImage != -1 && "鈴仙Shot画像読み込みエラー");

	initialize();
}

Reisen::Shot::~Shot()
{
	DeleteGraph(mImage);
}

void Reisen::Shot::initialize()
{
	mDirection = player->raw_x > this->p->raw_x;
	dx = (mDirection) ? fast_speed : -fast_speed;
	p->raw_x += ((mDirection) ? 16000 : -16000);
	time = 0;
	nowFast = true;
}

void Reisen::Shot::update()
{
	time++;
	if (time < 60)
	{
		//生成中
		return;
	}

	if (
		nowFast && ( //プレイヤーに近くなったら減速
		(mDirection  && this->player->raw_x < this->p->raw_x + fast_speed * 15) ||
		(!mDirection && this->player->raw_x > this->p->raw_x - fast_speed * 15)
		))
	{
		this->dx = ((this->dx < 0) ? -slow_speed : slow_speed);
		nowFast = false;
	}

	this->p->raw_x += dx;

	//自機から離れると消滅
	if (abs(this->p->raw_x - player->raw_x) > 640000)this->isActive = false;
}

void Reisen::Shot::draw(const Vector2* _camera) const
{
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();


	//生成中なら
	if (time < 60)
	{
		unsigned ring_color = GetColor(255, min(time * 6, 255), 255);
		DrawCircle(draw_x, draw_y, (60 - time), ring_color, 0);
	}
	else
	{
		DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, mDirection);
	}
}

void Reisen::Shot::setStatus(Vector2 _pos, int direction)
{
	*(this->p) = _pos;
	initialize();
}

void Reisen::Shot::hittedAction()
{

}


}
}
}