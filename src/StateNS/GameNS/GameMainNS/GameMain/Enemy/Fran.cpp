#include "Fran.h"
#include "Shot.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

	
bool Fran::imgLoad = false;
int Fran::images[32];


	
Fran::Fran(int _x, int _y) : 
EnemyChild(1000, _x, _y, 32, 64, false, true),
initial_pos(Vector2(_x, _y))
{
	loadImage();
	
	initialize();
}

Fran::~Fran()
{
	//DeleteGraph(mImage2);
}

void Fran::initialize()
{
	this->mImage = images[0];
	this->mTime = 0;
	this->init_attacks = false;
}

void Fran::initialize_attacks()
{

	stars.reserve(maxStarBowNum);
	waves.reserve(maxWave495Num);

	//*
	for (auto i = 0; i < maxStarBowNum; i++)
	{
		auto sb_tmp = new StarBow(player, this);
		sb_tmp->addAttacks(attacks);

		stars.push_back(sb_tmp);
	}
	//*/

	//*
	for (auto i = 0; i < maxWave495Num; i++)
	{
		auto wave_tmp = new Wave495(player, this);
		wave_tmp->addAttacks(attacks);

		waves.push_back(wave_tmp);
	}
	//*/

	//*
	kind4 = new Kind4(p, this);
	kind4->addAttacks(attacks);
	//*/

	//*/
	focus = new LockOn(this);
	focus->addAttacks(attacks);
	//*//

	attacks.shrink_to_fit();
	init_attacks = true;
}

void Fran::update(const StageChild* _stage, const Vector2* _camera)
{
	if (!init_attacks)initialize_attacks();


	
	++mTime;
	this->mDirection = this->p->raw_x > player->raw_x;
	standardAction(_stage);

	//弾のupdate
	if(mTime > 2)processAttack(_stage);

}

//==============================================
//内部プライベート関数
//==============================================
void Fran::move(const StageChild* _stage, int& _dx, int& _dy)
{
	/*
	_dx = dx;
	if (p->raw_x + dx < initial_pos.raw_x - 200000 || initial_pos.raw_x + 200000 < p->raw_x + dx)
	{
		dx = -dx;
		p->raw_x += dx;
	}
	//*/
}

void Fran::draw_other(const Vector2* _camera) const
{
	if (init_attacks && mTime > 2)
	{
		for (auto& sb : stars)
		{
			if (sb->isActive())
				sb->draw(_camera);
		}
		
		for (auto& wave : waves)
		{
			if (wave->isActive())
				wave->draw(_camera);
		}

		if(kind4->isActive())kind4->draw(_camera);

		if (focus->isActive())focus->draw(_camera);
	}

	//for Debug
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	//DrawString(draw_x - 16, draw_y - 32, "フラン", BLUE);

	//for Debug
	//DrawFormatString(draw_x - 16, draw_y - 64, GREEN, "%d", hpController.getHP());



}

void Fran::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Character/chip_fran.png", 32, 8, 4, 32, 64, images);
		assert(tmp != -1 && "Fran画像読み込みエラー");
	}
	imgLoad = true;
}


void Fran::hittedAction()
{

}

void Fran::processAttack(const StageChild* _stage)
{
	//udpate
	for (auto& sb : stars)
	{
		if (sb->isActive())
		{
			sb->update();
			sb->checkActive(_stage);
		}
	}

	for (auto& wave : waves)
	{
		if (wave->isActive())
		{	
			wave->update();
			wave->checkActive(_stage);
		}
	}

	if (kind4->isActive())kind4->update();

	if (focus->isActive())focus->update();

	//弾生成

	//for Debug

	/*
	//if(スターボウブレイク！なら)
	if (mTime % 17 == 0)
	{
		for (auto& sb : stars)
		{
			if (!sb->isActive())
			{
				sb->setStatus(this->p);
				sb->setActive(true);
				break;
			}
		}
	}
	//*/

	/*
	//if(Q.E.Dなら)
	if (mTime % 17 == 0)
	{
		for (auto& wave : waves)
		{
			if (!wave->isActive())
			{
				wave->setStatus(&Vector2(p->raw_x + GetRand(100000) - 50000, p->raw_y + GetRand(100000) - 50000, true));
				wave->setActive(true);
				break;
			}
		}
	}
	//*/

	/*
	//if(Kind4なら)
	if (!kind4->isActive())
	{
		kind4->setStatus(p);
		kind4->setActive(true);
	}
	//*/

	//*
	//if(LockOnなら)
	if (!focus->isActive())
	{
		focus->setStatus(player);
		focus->setActive(true);
	}
	//*/

	//for Debug
	//弾を消す
	if (CheckHitKey(KEY_INPUT_W))
	{
		for (auto& sb : stars)
		{
			sb->setActive(false);
		}
	}

}

//==============================================
//StarBowクラス
//==============================================
Fran::StarBow::StarBow(const Vector2* _pos, EnemyChild* _parent)
{
	parent = _parent;
	initialize(_pos);
}

Fran::StarBow::~StarBow()
{

	for (auto& s : shots)
	{
		SAFE_DELETE(s);
	}
	shots.clear();
	shots.shrink_to_fit();
}

void Fran::StarBow::initialize(const Vector2* _pos)
{
	time = 0;
	this->mIsActive = false;
	this->center_pos = (*_pos / vectorRate);

	//先にメモリを確保することで高速化
	shots.reserve(6);

	for (int i = 0; i < 6; i++)
	{
		Shot* s_tmp = new Shot(parent, 0, 0, 0, 0, 50);
		s_tmp->isActive = false;

		//乱数で弾の色を設定
		//GetRand(3) + 1 は 1 ~ 4 の値を返す
		s_tmp->setImage(GetRand(3) + 1);

		shots.push_back(s_tmp);
	}
}

void Fran::StarBow::update()
{
	++time;
	if (time < 10)return;

	if(time > 30)
	for (auto& s : shots)if (s->isActive)s->update();
}

void Fran::StarBow::draw(const Vector2* _camera) const
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
			DrawCircle(draw_x + differ_x[i], draw_y, (10 - time) * 5, PURPLE, false);
		}
	}

}

void Fran::StarBow::addAttacks(vector<Attack*>& _attacks)
{
	//先にメモリを確保することで高速化
	_attacks.reserve(_attacks.size() + 6);

	for (auto& s : shots)
	{
		_attacks.push_back(s);
	}
}

void Fran::StarBow::setStatus(const Vector2* _pos)
{
	time = 0;
	for (int i = 0; i < 6; i++)
	{
		shots[i]->setStatus_2args(Vector2(_pos->raw_x + differ_x[i] * vectorRate, _pos->raw_y, true), 90, 3000);
		shots[i]->setImage(GetRand(3) + 1);
	}
	this->center_pos = *_pos / vectorRate;
}

void Fran::StarBow::setActive(bool _isActive)
{
	this->mIsActive = _isActive;

	for (auto& s : shots)
	{
		s->isActive = _isActive;
	}
}

void Fran::StarBow::checkActive(const StageChild* _stage)
{
	this->mIsActive = false;
	for (auto& s : shots)
	{
		StageChild::ChipType chipType = _stage->getChipType(*s->getVector2(), true);
		s->isActive = !_stage->isRigid_down(chipType);

		mIsActive |= s->isActive;
	}
}

//==============================================
//Wave495クラス
//==============================================
Fran::Wave495::Wave495(const Vector2* _pos, EnemyChild* _parent)
{
	parent = _parent;
	initialize(_pos);
}

Fran::Wave495::~Wave495()
{
	for (auto& s : shots)
	{
		SAFE_DELETE(s);
	}
	shots.clear();
	shots.shrink_to_fit();
}

void Fran::Wave495::initialize(const Vector2* _pos)
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

void Fran::Wave495::update()
{
	++time;
	if (time < 10)return;
	if (time > 90)this->setActive(false);


	for (auto& s : shots)if (s->isActive)s->update();

}

void Fran::Wave495::draw(const Vector2* _camera) const
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

void Fran::Wave495::addAttacks(vector<Attack*>& _attacks)
{
	//先にメモリを確保することで高速化
	_attacks.reserve(_attacks.size() + maxShotNum);

	for (auto& s : shots)
	{
		_attacks.push_back(s);
	}
}

void Fran::Wave495::setStatus(const Vector2* _pos)
{
	time = 0;
	this->center_pos = (*_pos / vectorRate);

	for (int i = 0; i < maxShotNum; i++)
	{
		int angle = 60 * i;
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

void Fran::Wave495::setActive(bool _isActive)
{
	this->mIsActive = _isActive;

	for (auto& s : shots)
	{
		s->isActive = _isActive;
	}
}

void Fran::Wave495::checkActive(const StageChild* _stage)
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


//==============================================
//Kind4クラス
//==============================================
Fran::Kind4::Kind4(const Vector2* _pos, EnemyChild* _parent)
{
	parent = _parent;
	initialize(_pos);
}

Fran::Kind4::~Kind4()
{
	for (auto& s : shots)
	{
		SAFE_DELETE(s);
	}
	shots.clear();
	shots.shrink_to_fit();

	SAFE_DELETE(child1);
	SAFE_DELETE(child2);
	SAFE_DELETE(child3);
}

void Fran::Kind4::initialize(const Vector2* _pos)
{
	this->time = -60;
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

	child1 = new Childs(0, 0, parent, 45);
	child2 = new Childs(0, 0, parent, 45);
	child3 = new Childs(0, 0, parent, 0);
}

void Fran::Kind4::update()
{
	++time;
	if (time > 0)
	{
		for (auto& s : shots)
		{
			if (s->isActive)s->update();
		}
	}
	if (time > 120)
	{
		this->setActive(false);
		time = 0;
	}

	child1->update();
	child2->update();
	child3->update();
}

void Fran::Kind4::draw(const Vector2* _camera) const
{
	if (time > 0)
	{
		for (auto& s : shots)
		{
			s->draw(_camera);
		}
	}
	else
	{
		int draw_x = 320 + parent->getVector2()->x() - _camera->x();
		int draw_y = 240 + parent->getVector2()->y() - _camera->y();

		DrawCircle(draw_x, draw_y, (-time) * 3, PURPLE, false);
	}
	child1->draw(_camera);
	child2->draw(_camera);
	child3->draw(_camera);

}

void Fran::Kind4::addAttacks(vector<Attack*>& _attacks)
{
	//先にメモリを確保することで高速化
	_attacks.reserve(_attacks.size() + maxShotNum);

	for (auto& s : shots)
	{
		_attacks.push_back(s);
	}
	child1->addAttacks(_attacks);
	child2->addAttacks(_attacks);
	child3->addAttacks(_attacks);
}

void Fran::Kind4::setStatus(const Vector2* _pos)
{
	for (int i = 0; i < maxShotNum; i++)
	{
		shots[i]->setStatus_2args(*_pos, 90 * i, 3000);
	}

	child1->setStatus(_pos->raw_x - 50000, _pos->raw_y - 10000);
	child2->setStatus(_pos->raw_x + 50000, _pos->raw_y + 10000);
	child3->setStatus(_pos->raw_x + 100000, _pos->raw_y);
}

void Fran::Kind4::setActive(bool _isActive)
{
	this->mIsActive = _isActive;

	for (auto& s : shots)
	{
		s->isActive = _isActive;
	}
	child1->setActive(_isActive);
	child2->setActive(_isActive);
	child3->setActive(_isActive);
}

void Fran::Kind4::checkActive(const StageChild* _stage)
{
	if (!this->mIsActive)return;

	this->mIsActive = false;
	for (auto& s : shots)
	{
		StageChild::ChipType chipType = _stage->getChipType(*s->getVector2(), true);
		s->isActive = !_stage->isRigid_down(chipType);

		mIsActive |= s->isActive;
	}

	child1->checkActive(_stage);
	child2->checkActive(_stage);
	child3->checkActive(_stage);

	mIsActive |= child1->isActive();
	mIsActive |= child2->isActive();
	mIsActive |= child3->isActive();
}

//==============================================
//Kind4の内部Childsクラス
//==============================================
Fran::Kind4::Childs::Childs(int _x, int _y, EnemyChild* parent, int _phase):
init_phase(_phase)
{
	this->p = new Vector2(_x, _y, true);
	this->time = -60;
	this->mIsActive = false;

	this->dx = 0;
	this->dy = 0;

	int tmp = LoadDivGraph("Data/Image/Character/chip_fran.png", 32, 8, 4, 32, 64, images);
	assert(tmp != -1 && "フラン::Kind4::Childs画像読み込みエラー");

	shots.reserve(maxShotNum);
	for (int i = 0; i < maxShotNum; i++)
	{
		Shot* s_tmp = new Shot(parent, 0, 0, 0, 0, 50);
		s_tmp->setImage(GetRand(3) + 1);
		shots.push_back(s_tmp);
	}
}

Fran::Kind4::Childs::~Childs()
{
	SAFE_DELETE(p);
	for (auto& s : shots)
	{
		SAFE_DELETE(s);
	}
	shots.clear();
	shots.shrink_to_fit();

	for (int i = 0; i < 32; i++)
	{
		DeleteGraph(images[i]);
	}
}

void Fran::Kind4::Childs::update()
{
	++time;	
	if (time > 0)
	{
		if (time % 60 == 0)setDiffer();
		this->p->raw_x += dx;
		this->p->raw_y += dy;

		if (time > 0)for (auto& s : shots)if (s->isActive)s->update();
		if (time > 180)
		{
			this->setActive(false);
			time = 1;
		}
	}
}

void Fran::Kind4::Childs::draw(const Vector2* _camera) const
{
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();


	if (time > 0)
	{
		DrawCircle(draw_x, draw_y, 10, GREEN, true);
		for (auto& s : shots)
		{
			s->draw(_camera);
		}
	}
	else
	{
		DrawCircle(draw_x, draw_y, (-time) * 3, PURPLE, false);
	}
}

void Fran::Kind4::Childs::addAttacks(vector<Attack*>& _attacks)
{
	//先にメモリを確保することで高速化
	_attacks.reserve(_attacks.size() + maxShotNum);

	for (auto& s : shots)
	{
		_attacks.push_back(s);
	}
}

void Fran::Kind4::Childs::setStatus(int _x, int _y)
{
	if (time < 0)
	{
		this->p->raw_x = _x;
		this->p->raw_y = _y;
	}

	for (int i = 0; i < maxShotNum; i++)
	{
		shots[i]->setStatus_2args(Vector2(this->p->raw_x, this->p->raw_y, true), init_phase + 90 * i, 3000);
	}
}

void Fran::Kind4::Childs::setActive(bool _isActive)
{
	this->mIsActive = _isActive;
	if(time > 0)time = 0;

	for (auto& s : shots)
	{
		s->isActive = _isActive;
	}
}

void Fran::Kind4::Childs::checkActive(const StageChild* _stage)
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

void Fran::Kind4::Childs::setDiffer()
{
	int rand = GetRand(9);
	switch (rand)
	{
	case 0: { dx =    0; dy =    0; break; }
	case 1: { dx =    0; dy =    0; break; }
	case 2: { dx =    0; dy =    0; break; }
	case 3: { dx =    0; dy =    0; break; }
	case 4: { dx =  200; dy =  200; break; }
	case 5: { dx = -200; dy = -200; break; }
	case 6: { dx =  200; dy = -200; break; }
	case 7: { dx = -200; dy =  200; break; }
	case 8: { dx =  200; dy =    0; break; }
	case 9: { dx = -200; dy =    0; break; }
	//TODO 移動アニメーション
	}
}

//==============================================
//LockOnクラス
//==============================================
Fran::LockOn::LockOn(EnemyChild* _parent)
{
	this->parent = _parent;

	this->time = 0;
	this->mIsActive = false;
	image = LoadGraph("Data/Image/focus.png");
	assert(image != -1 && "focus.png読み込みエラー");

	//透明のショット
	shot = new Shot(parent, 0, 0, 0, 0, 50);
	shot->setImage(5);		
}

Fran::LockOn::~LockOn()
{
	parent = 0;
	SAFE_DELETE(shot);
	DeleteGraph(image);
}

void Fran::LockOn::update()
{
	++time;
	if (time < 120)this->p = *player;
	if (time > 180)shot->setStatus_2args(this->p, 0, 0);
	if (time > 190)
	{
		this->setActive(false);
		shot->isActive = false;
	}
}

void Fran::LockOn::draw(const Vector2* _camera) const
{
	int draw_x = 320 + p.x() - _camera->x();
	int draw_y = 240 + p.y() - _camera->y();

	if (time < 120)
	{
		draw_x += (int)((120 - time) * cosf(pi(time / 60.0f)));
		draw_y += (int)((120 - time) * sinf(pi(time / 60.0f)));
	}

	DrawRotaGraph(draw_x, draw_y, 1.0, pi(time / 90.0f), image, true);
}

void Fran::LockOn::addAttacks(vector<Attack*>& _attack)
{
	_attack.push_back(shot);
}

void Fran::LockOn::setStatus(const Vector2* _player)
{
	time = 0;
	this->player = _player;
	this->p = *_player;
}

void Fran::LockOn::setActive(bool _isActive)
{
	this->mIsActive = _isActive;
}

void Fran::LockOn::checkActive(const StageChild* _stage)
{
	
}




}
}
}