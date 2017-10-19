#include "Kaguya.h"
#include "Shot.h"

#include "..\Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{



Kaguya::Kaguya(int _x, int _y, int cx, int cy) : 
EnemyChild(1000, _x, _y, 32, 64, false, true),
initial_pos(cx, cy)
{
	loadImage();
	
	initialize();
}

Kaguya::~Kaguya()
{
	for (int i = 0; i < 32; i++)
	{
		DeleteGraph(images[i]);
	}
}

void Kaguya::initialize()
{
	this->mTime = 0;
	this->init_attacks = false;

	this->mImage = images[0];
	

	this->isMakingEnemy = false;
	this->darkTime = 0;
	this->vanishTime = 0;

	this->attack_vanish = false;
	this->attack_reflect= false;
	this->attack_spread	= false;
	this->attack_dark	= false;
	this->attack_enemy	= false;
	this->mutekiByEne = false;
}

void Kaguya::initialize_attacks()
{
	reflects.reserve(maxReflectNum);
	for (auto i = 0; i < maxReflectNum; i++)
	{
		auto reflect_tmp = new Shot_reflect(player, this);
		reflect_tmp->addAttacks(attacks);

		reflects.push_back(reflect_tmp);
	}

	spreads.reserve(maxReflectNum);
	for (auto i = 0; i < maxReflectNum; i++)
	{
		auto spread_tmp = new Shot_spread(player, this);
		spread_tmp->addAttacks(attacks);

		spreads.push_back(spread_tmp);
	}

	init_attacks = true;
}

void Kaguya::update(const StageChild* _stage, const Vector2* _camera)
{
	if (!init_attacks)initialize_attacks();

	++this->mTime;
	this->mDirection = this->p->raw_x > player->raw_x;
	mImage = images[0];

	standardAction(_stage);

	//消える関係
	if (this->attack_vanish)
	{
		vanishTime = 180;
		this->attack_vanish = false;
	}
	
	//暗闇処理
	this->darkTime = max(0, darkTime - 1);

	//敵作成関連
	if (this->isMakingEnemy)this->isMakingEnemy = false;
	if (this->attack_enemy)this->isMakingEnemy = true;

	//vanishTimeが正の間は無敵
	vanishTime = max(0, vanishTime - 1);

	//敵がいるか消えているかで無敵化
	this->collision->noCollide = (mutekiByEne | (vanishTime > 0));


	//Shot_reflect
	for (auto& reflect : reflects)
	{
		if (reflect->isActive())
		{
			reflect->update(_camera);
			reflect->checkActive(_stage);
		}
	}
	
	//Shot_spread
	for (auto& spread : spreads)
	{
		if (spread->isActive())
		{
			spread->update();
			spread->checkActive(_stage);
		}
	}

	//*
	if (attack_reflect)
	{
		for (auto& reflect : reflects)
		{
			if (!reflect->isActive())
			{
				reflect->setStatus(p, player);
				reflect->setActive(true);
				break;
			}
		}
	}
	//*/

	//*
	if (attack_spread)
	{
		for (auto& spread : spreads)
		{
			if (!spread->isActive())
			{
				spread->setStatus(&Vector2(p->raw_x + GetRand(100000) - 50000, p->raw_y + GetRand(100000) - 50000, true));
				spread->setActive(true);
			}
		}
	}
	//*/
}

void Kaguya::draw(const Vector2* _camera) const
{
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//やられているとき
	if (!mIsAlive)
	{
		//やられアニメーションを描画
		if (deadTime < 30)
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, 100);
			DrawCircle(draw_x, draw_y, (15 - abs(15 - deadTime)) * 10 / 7,  GLAY, true);
			DrawCircle(draw_x, draw_y, (15 - abs(15 - deadTime)) *  8 / 7, WHITE, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
		}
		return;
	}

	//画面内にいなければreturn
	checkIsActive(_camera);
	if (!mIsActive)return;

	standardDraw(_camera, mDirection);

	//バリア表示
	if(vanishTime != 0)
	{
		DrawCircle(draw_x, draw_y, max(16, vanishTime / 3) + (int)(5 * cos(pi(vanishTime / 6.0f))), WHITE, false);
		DrawCircle(draw_x, draw_y, max(16, vanishTime / 3) + (int)(5 * sin(pi(vanishTime / 6.0f))), GREEN, false);
	}
	else if (mutekiByEne)
	{
		DrawCircle(draw_x, draw_y, 32 + (int)(2 * cos(pi(mTime / 4.0f))), WHITE, false);
		DrawCircle(draw_x, draw_y, 32 + (int)(2 * sin(pi(mTime / 4.0f))), RED, false);
	}

	draw_other(_camera);
}

void Kaguya::draw_other(const Vector2* _camera) const
{
	for (auto& reflect : reflects)
	{
		if (reflect->isActive())
			reflect->draw(_camera);
	}

	for (auto& spread : spreads)
	{
		if (spread->isActive())
			spread->draw(_camera);
	}

	//for Debug
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawString(draw_x - 16, draw_y - 32, "輝夜", BLUE);

	//for Debug
	DrawFormatString(draw_x - 16, draw_y - 64, GREEN, "%d", hpController.getHP());
}

void Kaguya::move(const StageChild* _stage, int& _dx, int& _dy)
{
	if (mTime > timeToNextMotion)
	{
		mTime = 0;
		move_type = GetRand(6);
	}

	//for Debug
	move_type = 4;

	switch (move_type)
	{
	case 0: 
		processReflect(_stage, _dx, _dy); break;
	case 1: case 2: case 3:
		processSpread(_stage, _dx, _dy); break;
	case 4: case 5:
		processEnemy(_stage, _dx, _dy); break;
	}

	//空中に飛び上がるか地上に降りている途中
	if (_dx != 0)
	{
		this->mDirection = _dx < 0;
		this->mImage = images[15];
	}
}


//==============================================
//内部プライベート関数
//==============================================
void Kaguya::loadImage()
{
	int tmp = LoadDivGraph("Data/Image/Character/chip_kaguya.png", 32, 8, 4, 32, 64, images);
	assert(tmp != -1 && "Kaguya画像読み込みエラー");
}

void Kaguya::hittedAction()
{
	this->attack_vanish = true;
}

void Kaguya::processReflect(const StageChild* _stage, int& _dx, int& _dy)
{
	timeToNextMotion = 810;

	attack_reflect = false;
	if (mTime < 30)
	{
		mImage = images[2];
	}
	else if (mTime == 30)
	{
		attack_reflect = true;
	}
	else if (mTime < 180);
	else if (mTime < 210)
	{
		mImage = images[2];
	}
	else if (mTime == 210)
	{
		attack_reflect = true;
	}
	else if (mTime < 420);
	else if (mTime < 450)
	{
		mImage = images[2];
	}
	else if (mTime == 450)
	{
		attack_reflect = true;
	}
	else if (mTime < 540);
	else if (mTime < 570)
	{
		mImage = images[2];
	}
	else if (mTime == 570)
	{
		attack_reflect = true;
	}
}

void Kaguya::processSpread(const StageChild* _stage, int& _dx, int& _dy)
{
	timeToNextMotion = 360;
	attack_spread = false;
	if (mTime < 60)
	{
		_dx = 0;
		_dy = -4000;
	}
	else if (mTime < 300)
	{
		attack_spread = true;
		//左右往復
		_dx = dx;
		if (p->raw_x + dx < initial_pos.raw_x - 200000 || initial_pos.raw_x + 200000 < p->raw_x + _dx)
		{
			dx = -dx;
			p->raw_x += dx;
		}
	}
	else if (mTime == 300)
	{
		attack_spread = false;
		for (auto& sp : spreads)
		{
			if (sp->isActive())
			{
				sp->setActive(false);
			}
		}
	}
	else
	{
		_dx = 0;
		_dy = getBottomDiffer(_stage, 5000, false);
	}
}

void Kaguya::processEnemy(const StageChild* _stage, int& _dx, int& _dy)
{
	timeToNextMotion = 450;
	attack_enemy = false;

	if (mTime > 300)return;
	if (mTime % 90 == 0)attack_enemy = true;
}



//==============================================
//Shot_reflectクラス
//==============================================
Kaguya::Shot_reflect::Shot_reflect(const Vector2* _player, EnemyChild* _parent)
{
	parent = _parent;
	player = _player;
	initialize();
}

Kaguya::Shot_reflect::~Shot_reflect()
{
	for (auto& s : shots)
	{
		SAFE_DELETE(s);
	}
	shots.clear();
	shots.shrink_to_fit();
}

void Kaguya::Shot_reflect::initialize()
{
	this->time = 0;
	this->mIsActive = false;

	//先にメモリを確保することで高速化
	shots.reserve(maxShotNum);

	for (int i = 0; i < maxShotNum; i++)
	{
		Shot* s_tmp = new Shot(parent, 0, 0, 0, 0, 50);
		s_tmp->isActive = false;

		//乱数で弾の色を設定
		//GetRand(3) + 1 は 1 ~ 4 の値を返す
		s_tmp->setImage(GetRand(3) + 1);

		shots.push_back(s_tmp);
	}
}

void Kaguya::Shot_reflect::update(const Vector2* _camera)
{
	++time;

	if (time > 240)this->setActive(false);
	
	for (auto& s : shots)
	{
		if (!s->isActive)continue;
		const Vector2* s_pos = s->getVector2();
		int draw_x = 320 + s_pos->x() - _camera->x();
		int draw_y = 240 + s_pos->y() - _camera->y();

		//左右の画面外なら
		if (draw_x < 0 || 640 < draw_x)s->dx = -s->dx;
	}

	for (auto& s : shots)if (s->isActive)s->update();
}

void Kaguya::Shot_reflect::draw(const Vector2* _camera) const
{
	for (auto& s : shots)
	{
		if(s->isActive)s->draw(_camera);
	}
}

void Kaguya::Shot_reflect::addAttacks(vector<Attack*>& _attacks)
{
	//先にメモリを確保することで高速化
	_attacks.reserve(_attacks.size() + maxShotNum);

	for (auto& s : shots)
	{
		_attacks.push_back(s);
	}
}

void Kaguya::Shot_reflect::setStatus(const Vector2* _pos, const Vector2* _player)
{
	time = 0;
	this->player = _player;
	int differ = ((_pos->raw_x < _player->raw_x) ? 400 : -4000);

	for (int i = 0; i < maxShotNum; i++)
	{
		Vector2 pos = Vector2(
			_pos->raw_x + differ * i * i,
			_pos->raw_y - 60000 * i,
			true
		);
		//shots[i]->isActive = true;
		shots[i]->setStatus_2args(pos, 	getAngleToPlayer(pos), 3000);

	}
}

void Kaguya::Shot_reflect::setActive(bool _isActive)
{
	this->mIsActive = _isActive;

	for (auto& s : shots)
	{
		s->isActive = _isActive;
	}
}

void Kaguya::Shot_reflect::checkActive(const StageChild* _stage)
{
	if (!this->mIsActive)return;


	this->mIsActive = false;
	for (auto& s : shots)
	{
		StageChild::ChipType chipType = _stage->getChipType(*s->getVector2(), true);
		if (_stage->isRigid_down(chipType))s->dy = -s->dy;
		this->mIsActive |= s->isActive;
	}
}

double Kaguya::Shot_reflect::getAngleToPlayer(const Vector2& _pos)
{
	int differ_x = player->raw_x - _pos.raw_x;
	int differ_y = player->raw_y - _pos.raw_y;

	return atan2(differ_y, differ_x);
}

//==============================================
//Shot_spreadクラス
//==============================================
Kaguya::Shot_spread::Shot_spread(const Vector2* _pos, EnemyChild* _parent)
{
	parent = _parent;
	initialize(_pos);
}

Kaguya::Shot_spread::~Shot_spread()
{
	for (auto& s : shots)
	{
		SAFE_DELETE(s);
	}
	shots.clear();
	shots.shrink_to_fit();
}

void Kaguya::Shot_spread::initialize(const Vector2* _pos)
{
	this->time = 0;
	this->center_pos = (*_pos / vectorRate);
	this->mIsActive = false;

	//先にメモリを確保することで高速化
	shots.reserve(maxShotNum);

	for (int i = 0; i < maxShotNum; i++)
	{
		Shot* s_tmp = new Shot(parent, 0, 0, 0, 0, 50);
		s_tmp->isActive = false;

		//乱数で弾の色を設定
		//GetRand(3) + 1 は 1 ~ 4 の値を返す
		s_tmp->setImage(GetRand(3) + 1);

		shots.push_back(s_tmp);
	}
}

void Kaguya::Shot_spread::update()
{
	++time;
	if (time < 10)return;
	if (time > 90)this->setActive(false);


	for (auto& s : shots)if (s->isActive)s->update();

}

void Kaguya::Shot_spread::draw(const Vector2* _camera) const
{
	if (time > 10)
	{
		for (auto& s : shots)
		{
			s->draw(_camera);
		}
	}
	else
	{
		int draw_x = 320 + center_pos.raw_x - _camera->x();
		int draw_y = 240 + center_pos.raw_y - _camera->y();

		for (int i = 0; i < 6; i++)
		{
			DrawCircle(draw_x, draw_y, (10 - time) * 5, PURPLE, false);
		}
	}
}

void Kaguya::Shot_spread::addAttacks(vector<Attack*>& _attacks)
{
	//先にメモリを確保することで高速化
	_attacks.reserve(_attacks.size() + maxShotNum);

	for (auto& s : shots)
	{
		_attacks.push_back(s);
	}
}

void Kaguya::Shot_spread::setStatus(const Vector2* _pos)
{
	time = 0;
	this->center_pos = (*_pos / vectorRate);

	int initial_phase = GetRand(1);
	for (int i = 0; i < maxShotNum; i++)
	{
		int angle = 60 * i + initial_phase * 30;
		shots[i]->setStatus_2args(
			Vector2(
				_pos->raw_x + (int)(radius * cosf_degree(angle)),
				_pos->raw_y + (int)(radius * sinf_degree(angle)),
				true
			),
			(angle), 3000
		);
	}
}

void Kaguya::Shot_spread::setActive(bool _isActive)
{
	this->mIsActive = _isActive;

	for (auto& s : shots)
	{
		s->isActive = _isActive;
	}
}

void Kaguya::Shot_spread::checkActive(const StageChild* _stage)
{
	if (!this->mIsActive)return;


	this->mIsActive = false;
	for (auto& s : shots)
	{
		StageChild::ChipType chipType = _stage->getChipType(*s->getVector2(), true);
		s->isActive = !_stage->isRigid_down(chipType);

		mIsActive |= s->isActive;
	}
}




}
}
}