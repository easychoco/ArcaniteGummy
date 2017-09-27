#include "Reisen.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Reisen::Reisen(int _x, int _y) : EnemyChild(1000, _x, _y, 32, 32,1,1)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Reisen画像読み込みエラー!");

	initialize();
}

Reisen::~Reisen()
{
	for (auto& s : shots)
	{
		SAFE_DELETE(s);
	}
	shots.clear();
	shots.shrink_to_fit();
}

void Reisen::initialize()
{
	this->mTime = 0;
	this->nowMoving = false;
}

void Reisen::update(const StageChild* _stage, const Vector2* _camera)
{
	this->mDirection = player->raw_x > this->p->raw_x;

	++mTime;
	if (mTime % 90 == 0 && !nowMoving)attack(_stage);
	//if (!nowMoving && abs(player->raw_x - this->p->raw_x) < 64000)

	if (mTime % 60 == 0)
	{
		nowMoving = false;
	}
	//5秒で移動
	//360 は120の倍数
	if(mTime == 360)
	{
		nowMoving = true;
	}
	//5秒で元に戻る
	//660 は120の倍数 + 60
	if (mTime == 660)
	{
		nowMoving = true;
		mTime = 60;
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

}

void Reisen::move(const StageChild* _stage, int& _dx, int& _dy)
{
	//何もなければ落下だけする
	_dy = getBottomDiffer(_stage, 4000, true);
	if (!nowMoving)return;

	//移動中
	float theta = pi(1 / 60.0f) * (mTime % 120);

	float sin1 = sinf(theta);
	float sin2 = sinf(theta * 2.0f);

	_dx = getHorizontalDiffer(_stage, -16000 * sin1, sin2 < 0.0f);
	_dy = sin2 < 0 ? getTopDiffer(_stage, -20000 * sin2, _dx < 0) : getBottomDiffer(_stage, -20000 * sin2, _dx < 0);
}

void Reisen::draw_other(const Vector2* _camera) const
{

	for (const auto& a : attacks)
	{
		if (a->isActive)a->draw(_camera);
	}

	//for Debug
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawString(draw_x - 16, draw_y - 32, "鈴仙", BLUE);

	//for Debug
	DrawFormatString(draw_x - 16, draw_y - 64, GREEN, "%d", hpController.getHP());
}


//==============================================
//内部プライベート関数
//==============================================
void Reisen::hittedAction()
{

}

void Reisen::attack(const StageChild* _stage)
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
	attacks.push_back(new Shot(this, _stage, player, this->p->raw_x, this->p->raw_y));
}

//==============================================
//Shotクラス
//==============================================
Reisen::Shot::Shot(const EnemyChild* _parent, const StageChild* _stage, const Vector2* _player, int _x, int _y) :
Attack(_parent, _x, _y, 32, 32, ObjectID::ID_NONE),
stage(_stage),
player(_player)
{
	//for Debug
	this->damageValue = 20;

	mImage = LoadGraph("Data/Image/Reisen_shot.png");
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

	//for Debug
	if (CheckHitKey(KEY_INPUT_Q))
	{
		int gomi = 0;
	}
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


	int dx_tmp = getHorizontalDiffer(stage, dx, false, false);
	this->p->raw_x += dx_tmp;

	//壁に当たると消滅
	if (dx_tmp == 0)this->isActive = false;
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
	this->isActive = false;
}


}
}
}