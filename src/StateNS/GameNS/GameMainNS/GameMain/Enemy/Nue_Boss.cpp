#include "Nue_Boss.h"
#include "Shot.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS{

	
bool Nue_Boss::imgLoad = false;
int Nue_Boss::images[32];


	
Nue_Boss::Nue_Boss(int _x, int _y) : 
EnemyChild(1000, _x, _y, 32, 32, false, true)
{
	loadImage();
	
	initialize();
}

Nue_Boss::~Nue_Boss()
{
	//DeleteGraph(mImage2);
}

void Nue_Boss::initialize()
{
	this->mTime = 0;
	this->init_attacks = false;
	this->mImage = images[0];
}

void Nue_Boss::initialize_attacks()
{
	shot3.reserve(maxShot3Num);

	for (int i = 0; i < maxShot3Num; i++)
	{
		Shot_3way* s3_tmp = new Shot_3way(player, this);
		s3_tmp->addAttacks(attacks);

		shot3.push_back(s3_tmp);
	}

	init_attacks = true;
}

void Nue_Boss::update(const StageChild* _stage, const Vector2* _camera)
{
	if (!init_attacks)initialize_attacks();

	++mTime;
	this->mDirection = this->p->raw_x > player->raw_x;
	standardAction(_stage);

	processAttack(_stage);
}

//==============================================
//内部プライベート関数
//==============================================
void Nue_Boss::move(const StageChild* _stage, int& _dx, int& _dy)
{

}

void Nue_Boss::processAttack(const StageChild* _stage)
{
	//udpate
	for (auto& s3 : shot3)
	{
		if (s3->isActive())
		{
			s3->update();
			s3->checkActive(_stage);
		}
	}

	//*
	//if(LockOnなら)
	if(mTime % 20 == 0)
	for (auto& s3 : shot3)
	{
		if (!s3->isActive())
		{
			s3->setStatus(p, mDirection);
			s3->setActive(true);
			break;
		}
	}
	//*
}

void Nue_Boss::draw_other(const Vector2* _camera) const
{
	if (init_attacks)
	{
		for (const auto& s3 : shot3)if (s3->isActive())s3->draw(_camera);
	}

	//for Debug
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawString(draw_x - 16, draw_y - 32, "鵺", BLUE);

	//for Debug
	DrawFormatString(draw_x - 16, draw_y - 64, GREEN, "%d", hpController.getHP());

	//for Debug
	DrawFormatString(0, 50, BLACK, "time: %d", this->mDirection);
}


void Nue_Boss::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Character/chip_nue.png", 8, 8, 1, 64, 64, images);
		assert(tmp != -1 && "Nue_Boss画像読み込みエラー");
	}
	imgLoad = true;
}


void Nue_Boss::hittedAction()
{

}


//==============================================
//Shot_3wayクラス
//==============================================
Nue_Boss::Shot_3way::Shot_3way(const Vector2* _pos, EnemyChild* _parent)
{
	parent = _parent;
	initialize(_pos);
}

Nue_Boss::Shot_3way::~Shot_3way()
{

	for (auto& s : shots)
	{
		SAFE_DELETE(s);
	}
	shots.clear();
	shots.shrink_to_fit();
}

void Nue_Boss::Shot_3way::initialize(const Vector2* _pos)
{
	time = 0;
	this->mIsActive = false;

	//先にメモリを確保することで高速化
	shots.reserve(3);

	for (int i = 0; i < 3; i++)
	{
		Shot* s_tmp = new Shot(parent, 0, 0, 0, 0, 50);
		s_tmp->isActive = false;

		//乱数で弾の色を設定
		//GetRand(3) + 1 は 1 ~ 4 の値を返す
		s_tmp->setImage(5);

		shots.push_back(s_tmp);
	}
}

void Nue_Boss::Shot_3way::update()
{
	++time;
	for (auto& s : shots)if (s->isActive)s->update();
	if (time > 120)this->setActive(false);
}

void Nue_Boss::Shot_3way::draw(const Vector2* _camera) const
{
	for (auto& s : shots)
	{
		s->draw(_camera);
	}

	//for Debug
	DrawFormatString(0, 80, BLACK, "time: %d", shots[0]->direction);
}

void Nue_Boss::Shot_3way::addAttacks(vector<Attack*>& _attacks)
{
	//先にメモリを確保することで高速化
	_attacks.reserve(_attacks.size() + 3);

	for (auto& s : shots)
	{
		_attacks.push_back(s);
	}
}

void Nue_Boss::Shot_3way::setStatus(const Vector2* _pos, bool _direction)
{
	time = 0;
	for (int i = 0; i < 3; i++)
	{
		shots[i]->setStatus_2args(Vector2(_pos->raw_x, _pos->raw_y, true), -30 + 30 * i, ((_direction) ? -1 : 1) * 3000);
		shots[i]->direction = _direction;
	}
}

void Nue_Boss::Shot_3way::setActive(bool _isActive)
{
	this->mIsActive = _isActive;

	for (auto& s : shots)
	{
		s->isActive = _isActive;
	}
}

void Nue_Boss::Shot_3way::checkActive(const StageChild* _stage)
{
	this->mIsActive = false;
	for (auto& s : shots)
	{
		StageChild::ChipType chipType = _stage->getChipType(*s->getVector2(), true);
		s->isActive &= !_stage->isRigid_down(chipType);

		mIsActive |= s->isActive;
	}
}



}
}
}