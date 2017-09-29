#include "Junko.h"
#include "Shot.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS{

	
	
Junko::Junko(int _x, int _y) : 
EnemyChild(1000, _x, _y, 32, 32)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Junko画像読み込みエラー!");

	initialize();
}

Junko::~Junko()
{
	DeleteGraph(mImage);
}

void Junko::initialize()
{
	this->mTime = 0;

	this->attack_around = false;

	//for Debug
	attacks.push_back(new Shot(this, 400000, 1480000, 180, 4000, 30));
}

void Junko::update(const StageChild* _stage, const Vector2* _camera)
{
	this->mDirection = player->raw_x > this->p->raw_x;

	//for Debug
	if (CheckHitKey(KEY_INPUT_Q))
	{
		if(!attack_around)s_a = new Shot_around(player, this);
		else s_a->setStatus(player);
		attack_around = true;
	}

	++mTime;

	for (auto& a : attacks)
	{
		if (a->isActive)
		{
			a->update();
			a->checkActive(_camera);
		}
	}
	standardAction(_stage);

	if(attack_around)s_a->update();
}

void Junko::move(const StageChild* _stage, int& _dx, int& _dy)
{

}

void Junko::draw_other(const Vector2* _camera) const
{
	for (auto& a : attacks)
	{
		if (a->isActive)
		{
			a->draw(_camera);
		}
	}

	if (attack_around)s_a->draw(_camera);

	//for Debug
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawString(draw_x - 16, draw_y - 32, "純狐", BLUE);

	//for Debug
	DrawFormatString(draw_x - 16, draw_y - 64, GREEN, "%d", hpController.getHP());
}


//==============================================
//内部プライベート関数
//==============================================
void Junko::hittedAction()
{

}

void Junko::attack(const StageChild* _stage)
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
	attacks.push_back(new Shot(this, this->p->raw_x, this->p->raw_y,  270, 3000, 30));
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
	SAFE_DELETE(p);
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

	//ステータスは現時点で適当
	shot1 = new Shot(parent, _pos->raw_x + (int)(radius * cosf_degree( 30)), _pos->raw_y + (int)(radius * sinf_degree( 30)),  30, -2500, 50);
	shot2 = new Shot(parent, _pos->raw_x + (int)(radius * cosf_degree( 90)), _pos->raw_y + (int)(radius * sinf_degree( 90)),  90, -2500, 50);
	shot3 = new Shot(parent, _pos->raw_x + (int)(radius * cosf_degree(150)), _pos->raw_y + (int)(radius * sinf_degree(150)), 150, -2500, 50);
	shot4 = new Shot(parent, _pos->raw_x + (int)(radius * cosf_degree(210)), _pos->raw_y + (int)(radius * sinf_degree(210)), 210, -2500, 50);
	shot5 = new Shot(parent, _pos->raw_x + (int)(radius * cosf_degree(270)), _pos->raw_y + (int)(radius * sinf_degree(270)), 270, -2500, 50);
	shot6 = new Shot(parent, _pos->raw_x + (int)(radius * cosf_degree(330)), _pos->raw_y + (int)(radius * sinf_degree(330)), 330, -2500, 50);
}

void Junko::Shot_around::update()
{
	time++;
	if (time > 120)
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

void Junko::Shot_around::addAttacks(vector<Attack*>&_attacks)
{

}

void Junko::Shot_around::setStatus(const Vector2* _pos)
{
	time = 0;
	shot1->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree( 30)), _pos->raw_y + (int)(radius * sinf_degree( 30)), true), 30, -2500);
	shot2->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree( 90)), _pos->raw_y + (int)(radius * sinf_degree( 90)), true), 90, -2500);
	shot3->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(150)), _pos->raw_y + (int)(radius * sinf_degree(150)), true),150, -2500);
	shot4->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(210)), _pos->raw_y + (int)(radius * sinf_degree(210)), true),210, -2500);
	shot5->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(270)), _pos->raw_y + (int)(radius * sinf_degree(270)), true),270, -2500);
	shot6->setStatus_2args(Vector2(_pos->raw_x + (int)(radius * cosf_degree(330)), _pos->raw_y + (int)(radius * sinf_degree(330)), true),330, -2500);

	/*
	shot1 = new Shot(parent, _pos->raw_x + (int)(radius * cosf_degree( 30)), _pos->raw_y + (int)(radius * sinf_degree( 30)),  30, -2500, 50);
	shot2 = new Shot(parent, _pos->raw_x + (int)(radius * cosf_degree( 90)), _pos->raw_y + (int)(radius * sinf_degree( 90)),  90, -2500, 50);
	shot3 = new Shot(parent, _pos->raw_x + (int)(radius * cosf_degree(150)), _pos->raw_y + (int)(radius * sinf_degree(150)), 150, -2500, 50);
	shot4 = new Shot(parent, _pos->raw_x + (int)(radius * cosf_degree(210)), _pos->raw_y + (int)(radius * sinf_degree(210)), 210, -2500, 50);
	shot5 = new Shot(parent, _pos->raw_x + (int)(radius * cosf_degree(270)), _pos->raw_y + (int)(radius * sinf_degree(270)), 270, -2500, 50);
	shot6 = new Shot(parent, _pos->raw_x + (int)(radius * cosf_degree(330)), _pos->raw_y + (int)(radius * sinf_degree(330)), 330, -2500, 50);
	*/
}



}
}
}