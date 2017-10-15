#include "Junko.h"
#include "Shot.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS{

	
bool Junko::imgLoad = false;
int Junko::images[8];


	
Junko::Junko(int _x, int _y) : 
EnemyChild(1000, _x, _y, 32, 32, false, true)
{
	loadImage();
	
	initialize();
}

Junko::~Junko()
{
	//DeleteGraph(mImage2);
}

void Junko::initialize()
{
	this->mTime = 0;
	this->init_attacks = false;
}

void Junko::update(const StageChild* _stage, const Vector2* _camera)
{
	if (!init_attacks)
	{
		s_a = new Shot_around(player, this);
		s_a->addAttacks(attacks);
		s_c = new Shot_cycle(player, this);
		s_c->addAttacks(attacks);

		init_attacks = true;
	}


	this->mDirection = player->raw_x > this->p->raw_x;

	//for Debug
	if (CheckHitKey(KEY_INPUT_Q))
	{
		s_c->setStatus(player);
		s_c->setActive(true);
		//s_a->setStatus(player);
		//s_a->setActive(true);
	}

	//for Debug
	if (CheckHitKey(KEY_INPUT_W))
	{
		s_c->setActive(false);
		s_c->setActive(false);
		//s_a->setActive(false);
		//s_a->setActive(false);
	}

	++mTime;

	if (s_a->isActive())
	{
		s_a->update();
		s_a->checkActive(_camera);
	}

	if (s_c->isActive())
	{
		s_c->update();
		s_c->checkActive(_camera);
	}

	standardAction(_stage);
}

void Junko::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	//if (!mIsAlive)return;


	//画面内にいなければreturn
	if (abs(p->raw_x - _camera->raw_x) > 480000 || abs(p->raw_y - _camera->raw_y) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, mDirection);
	draw_other(_camera);
}

void Junko::move(const StageChild* _stage, int& _dx, int& _dy)
{

}

void Junko::draw_other(const Vector2* _camera) const
{
	/*
	for (auto& a : attacks)
	{
		if (a->isActive)
		{
			a->draw(_camera);
		}
	}
	*/

	if (init_attacks)
	{
		if (s_c->isActive())s_c->draw(_camera);
		if (s_a->isActive())s_a->draw(_camera);
	}

	//for Debug
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawString(draw_x - 16, draw_y - 32, "純狐", BLUE);

	DrawFormatString(draw_x - 16, draw_y - 64, GREEN, "%d", hpController.getHP());
}


//==============================================
//内部プライベート関数
//==============================================
void Junko::loadImage()
{
	if (!imgLoad)
	{
		//TODO 書く
		//int tmp = LoadDivGraph("Data/Image/.png", 8, 8, 1, 32, 32, images);
		//assert(tmp != -1 && "Junko画像読み込みエラー");
	}
	imgLoad = true;
}


void Junko::hittedAction()
{

}

void Junko::attack(const StageChild* _stage)
{
	
}

//==============================================
//Shot_aroundクラス
//==============================================
Junko::Shot_around::Shot_around(const Vector2* _pos, EnemyChild* _parent)
{
	parent = _parent;
	initialize(_pos);
}

Junko::Shot_around::~Shot_around()
{
	SAFE_DELETE(shot1);
	SAFE_DELETE(shot2);
	SAFE_DELETE(shot3);
	SAFE_DELETE(shot4);
	SAFE_DELETE(shot5);
	SAFE_DELETE(shot6);
}

void Junko::Shot_around::initialize(const Vector2* _pos)
{
	time = 0;
	this->mIsActive = false;

	shot1 = new Shot(parent, _pos->raw_x, _pos->raw_y, 0, 0, 50);
	shot2 = new Shot(parent, _pos->raw_x, _pos->raw_y, 0, 0, 50);
	shot3 = new Shot(parent, _pos->raw_x, _pos->raw_y, 0, 0, 50);
	shot4 = new Shot(parent, _pos->raw_x, _pos->raw_y, 0, 0, 50);
	shot5 = new Shot(parent, _pos->raw_x, _pos->raw_y, 0, 0, 50);
	shot6 = new Shot(parent, _pos->raw_x, _pos->raw_y, 0, 0, 50);

	shot1->setImage(0);
	shot2->setImage(0);
	shot3->setImage(0);
	shot4->setImage(0);
	shot5->setImage(0);
	shot6->setImage(0);

	shot1->isActive = false;
	shot2->isActive = false;
	shot3->isActive = false;
	shot4->isActive = false;
	shot5->isActive = false;
	shot6->isActive = false;
}

void Junko::Shot_around::update()
{
	time++;
	if (time == 60)
	{
		shot1->setStatus_2args(Vector2::ZERO,   0, -2500);
		shot2->setStatus_2args(Vector2::ZERO,  60, -2500);
		shot3->setStatus_2args(Vector2::ZERO, 120, -2500);
		shot4->setStatus_2args(Vector2::ZERO, 180, -2500);
		shot5->setStatus_2args(Vector2::ZERO, 240, -2500);
		shot6->setStatus_2args(Vector2::ZERO, 300, -2500);
	}
	if (time > 60)
	{
		shot1->update();
		shot2->update();
		shot3->update();
		shot4->update();
		shot5->update();
		shot6->update();
	}
}

void Junko::Shot_around::draw(const Vector2* _camera) const
{
	shot1->draw(_camera);
	shot2->draw(_camera);
	shot3->draw(_camera);
	shot4->draw(_camera);
	shot5->draw(_camera);
	shot6->draw(_camera);
}

void Junko::Shot_around::addAttacks(vector<Attack*>& _attacks)
{
	_attacks.push_back(shot1);
	_attacks.push_back(shot2);
	_attacks.push_back(shot3);
	_attacks.push_back(shot4);
	_attacks.push_back(shot5);
	_attacks.push_back(shot6);
}

void Junko::Shot_around::setStatus(const Vector2* _pos)
{
	time = 0;
	shot1->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(  0)), _pos->raw_y + (int)(radius * sinf_degree(  0)), true), 0, 0);
	shot2->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree( 60)), _pos->raw_y + (int)(radius * sinf_degree( 60)), true), 0, 0);
	shot3->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(120)), _pos->raw_y + (int)(radius * sinf_degree(120)), true), 0, 0);
	shot4->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(180)), _pos->raw_y + (int)(radius * sinf_degree(180)), true), 0, 0);
	shot5->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(240)), _pos->raw_y + (int)(radius * sinf_degree(240)), true), 0, 0);
	shot6->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(300)), _pos->raw_y + (int)(radius * sinf_degree(300)), true), 0, 0);
}

void Junko::Shot_around::setActive(bool _isActive)
{
	this->mIsActive = _isActive;

	shot1->isActive = _isActive;
	shot2->isActive = _isActive;
	shot3->isActive = _isActive;
	shot4->isActive = _isActive;
	shot5->isActive = _isActive;
	shot6->isActive = _isActive;
}

void Junko::Shot_around::checkActive(const Vector2* _camera)
{
	shot1->checkActive(_camera);
	shot2->checkActive(_camera);
	shot3->checkActive(_camera);
	shot4->checkActive(_camera);
	shot5->checkActive(_camera);
	shot6->checkActive(_camera);
}


//==============================================
//Shot_cycleクラス
//==============================================
Junko::Shot_cycle::Shot_cycle(const Vector2* _pos, EnemyChild* _parent)
{
	parent = _parent;
	initialize(_pos);
}

Junko::Shot_cycle::~Shot_cycle()
{
	SAFE_DELETE(shot1);
	SAFE_DELETE(shot2);
	SAFE_DELETE(shot3);
	SAFE_DELETE(shot4);
	SAFE_DELETE(shot5);
	SAFE_DELETE(shot6);
}

void Junko::Shot_cycle::initialize(const Vector2* _pos)
{
	this->time = 0;
	this->angle = 0.0f;
	this->center_pos = parent->getVector2();
	this->mIsActive = false;

	shot1 = new Shot(parent, _pos->raw_x, _pos->raw_y, 0, 0, 50);
	shot2 = new Shot(parent, _pos->raw_x, _pos->raw_y, 0, 0, 50);
	shot3 = new Shot(parent, _pos->raw_x, _pos->raw_y, 0, 0, 50);
	shot4 = new Shot(parent, _pos->raw_x, _pos->raw_y, 0, 0, 50);
	shot5 = new Shot(parent, _pos->raw_x, _pos->raw_y, 0, 0, 50);
	//shot6 = new Shot(parent, _pos->raw_x, _pos->raw_y, 0, 0, 50);

	shot1->setImage(1);
	shot2->setImage(1);
	shot3->setImage(1);
	shot4->setImage(1);
	shot5->setImage(1);
	//shot6->loadImage("Data/Image/Junko_attack2.png");

	shot1->isActive = false;
	shot2->isActive = false;
	shot3->isActive = false;
	shot4->isActive = false;
	shot5->isActive = false;
	//shot6->isActive = false;
}

void Junko::Shot_cycle::update()
{
	if (time > 240)
	{
		this->setActive(false);
		return;
	}

	++time;
	angle += pi(1 / 45.0f);
	radius += 1000;
	
	shot1->setStatus_2args(Vector2(center_pos->raw_x + (int)(radius * cosf(angle + pi(0 / 3.0f))), center_pos->raw_y + (int)(radius * sinf(angle + pi(0 / 3.0f))), true), 0, 0);
	shot2->setStatus_2args(Vector2(center_pos->raw_x + (int)(radius * cosf(angle + pi(1 / 3.0f))), center_pos->raw_y + (int)(radius * sinf(angle + pi(1 / 3.0f))), true), 0, 0);
	shot3->setStatus_2args(Vector2(center_pos->raw_x + (int)(radius * cosf(angle + pi(2 / 3.0f))), center_pos->raw_y + (int)(radius * sinf(angle + pi(2 / 3.0f))), true), 0, 0);
	shot4->setStatus_2args(Vector2(center_pos->raw_x + (int)(radius * cosf(angle + pi(3 / 3.0f))), center_pos->raw_y + (int)(radius * sinf(angle + pi(3 / 3.0f))), true), 0, 0);
	shot5->setStatus_2args(Vector2(center_pos->raw_x + (int)(radius * cosf(angle + pi(4 / 3.0f))), center_pos->raw_y + (int)(radius * sinf(angle + pi(4 / 3.0f))), true), 0, 0);
	//shot6->setStatus_2args(Vector2(center_pos->raw_x + (int)(radius * cosf(angle + pi(5 / 3.0f))), center_pos->raw_y + (int)(radius * sinf(angle + pi(5 / 3.0f))), true), 0, 0);

	/*
	shot1->update();
	shot2->update();
	shot3->update();
	shot4->update();
	shot5->update();
	shot6->update();
	*/
}

void Junko::Shot_cycle::draw(const Vector2* _camera) const
{
	shot1->draw(_camera);
	shot2->draw(_camera);
	shot3->draw(_camera);
	shot4->draw(_camera);
	shot5->draw(_camera);
	//shot6->draw(_camera);
}

void Junko::Shot_cycle::addAttacks(vector<Attack*>& _attacks)
{
	_attacks.push_back(shot1);
	_attacks.push_back(shot2);
	_attacks.push_back(shot3);
	_attacks.push_back(shot4);
	_attacks.push_back(shot5);
	//_attacks.push_back(shot6);
}

void Junko::Shot_cycle::setStatus(const Vector2* _pos)
{
	time = 0;
	radius = first_radius;
	angle = 0.0f;

	shot1->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(30)), _pos->raw_y + (int)(radius * sinf_degree(30)), true), 0, 0);
	shot2->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(90)), _pos->raw_y + (int)(radius * sinf_degree(90)), true), 0, 0);
	shot3->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(150)), _pos->raw_y + (int)(radius * sinf_degree(150)), true), 0, 0);
	shot4->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(210)), _pos->raw_y + (int)(radius * sinf_degree(210)), true), 0, 0);
	shot5->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(270)), _pos->raw_y + (int)(radius * sinf_degree(270)), true), 0, 0);
	//shot6->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(330)), _pos->raw_y + (int)(radius * sinf_degree(330)), true), 0, 0);
}

void Junko::Shot_cycle::setActive(bool _isActive)
{
	this->mIsActive = _isActive;

	shot1->isActive = _isActive;
	shot2->isActive = _isActive;
	shot3->isActive = _isActive;
	shot4->isActive = _isActive;
	shot5->isActive = _isActive;
	//shot6->isActive = _isActive;
}

void Junko::Shot_cycle::checkActive(const Vector2* _camera)
{
	shot1->checkActive(_camera);
	shot2->checkActive(_camera);
	shot3->checkActive(_camera);
	shot4->checkActive(_camera);
	shot5->checkActive(_camera);
	//shot6->checkActive(_camera);
}



}
}
}