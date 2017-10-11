#include "Nue_Boss.h"
#include "Shot.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS{

	
bool Nue_Boss::imgLoad = false;
int Nue_Boss::images[32];


	
Nue_Boss::Nue_Boss(int _x, int _y) : 
EnemyChild(1000, _x, _y, 32, 32, false, true),
initial_pos(Vector2(_x, _y))
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

	this->dx = 3000;
	this->dy = 0;
}

void Nue_Boss::initialize_attacks()
{
	shot3.reserve(maxShot3Num);

	for (int i = 0; i < maxShot3Num; i++)
	{
		Shot_3way* s3_tmp = new Shot_3way(p, this);
		s3_tmp->addAttacks(attacks);

		shot3.push_back(s3_tmp);
	}


	bombs.reserve(maxBombNum);
	attacks.reserve(attacks.size() + maxBombNum);

	for (int i = 0; i < maxBombNum; i++)
	{
		Bombing* b_tmp = new Bombing(p, this);
		bombs.push_back(b_tmp);
	}
	
	for (auto& b : bombs)
	{
		this->attacks.push_back(b);
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
	//*
	//左右往復
	_dx = dx;
	if (p->raw_x + dx < initial_pos.raw_x - 200000 || initial_pos.raw_x + 200000 < p->raw_x + dx)
	{
		dx = -dx;
		p->raw_x += dx;
	}
	//*/
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

	for (auto& b : bombs)
	{
		if (b->isActive)
		{
			b->update();
			b->checkOnGround(_stage);
		}
	}



	//インスタンス生成

	/*
	//if(Shot3wayなら)
	if (mTime % 20 == 0)
	{
		for (auto& s3 : shot3)
		{
			if (!s3->isActive())
			{
				s3->setStatus(p, mDirection);
				s3->setActive(true);
				break;
			}
		}
	}
	//*/

	//*
	//if(Bombingなら)
	if (mTime % 45 == 0)
	{
		for (auto& b : bombs)
		{
			if (!b->isActive)
			{
				b->setStatus(*p, mDirection);
				b->isActive = true;
				break;
			}
		}
	}
	//*/

}

void Nue_Boss::draw_other(const Vector2* _camera) const
{
	if (init_attacks)
	{
		for (const auto& s3 : shot3)if (s3->isActive())s3->draw(_camera);
		for (const auto& b : bombs)if (b->isActive)b->draw(_camera);
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
		s_tmp->setImage(6);

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

//==============================================
//Bombingクラス
//==============================================
Nue_Boss::Bombing::Bombing(const Vector2* _pos, EnemyChild* _parent):
Attack(_parent, _pos->raw_x, _pos->raw_y, 15, 15)
{
	parent = _parent;
	initialize(_pos);
}

Nue_Boss::Bombing::~Bombing()
{
	DeleteGraph(image);
	for (int i = 0; i < 3; i++)DeleteGraph(img_fire[i]);
}

void Nue_Boss::Bombing::initialize(const Vector2* _pos)
{
	time = 0;
	onGround = false;
	this->damageValue = 50;

	isActive = false;
	
	this->image = LoadGraph("Data/Image/AirmzAttack.png");
	assert(image != -1 && "Nue_Boss: Bombing画像読み込みエラー");

	int tmp = LoadDivGraph("Data/Image/Fire2.png", 3, 3, 1, 32, 96, img_fire);
	assert(tmp != -1 && "Nue_Boss: Bombing_Fire画像読み込みエラー");

	mImage = this->image;
}

void Nue_Boss::Bombing::update()
{
	++time;
	if (!onGround)
	{
		dy = 5 * time * time;

		p->raw_x += dx;
		p->raw_y += dy;
	}
	else
	{
		//画像設定
		if (time <= 60)this->mImage = img_fire[min(time / 30, 2)];
		if (time > 120)this->isActive = false;
	}
}

void Nue_Boss::Bombing::draw(const Vector2* _camera) const
{
	//画面外にあったら描画なし
	if (!isActive)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, false);
}

void Nue_Boss::Bombing::setStatus(Vector2 _pos, int _direction)
{
	time = 0;
	onGround = false;
	*this->p = _pos;

	dx = (_direction == 1) ? 1000 : -1000;
	dy = 0;

	this->height = 32;
	this->mImage = this->image;
}

void Nue_Boss::Bombing::checkOnGround(const StageChild* _stage)
{
	if (onGround)return;
	StageChild::ChipType chipType = _stage->getChipType(*p, true);

	//床についたら
	if (_stage->isRigid_down(chipType))
	{
		time = 0;
		dx = dy = 0;
		this->height = 96;
		onGround = true;

		p->raw_y -= (48 * vectorRate);
	}
}



}
}
}