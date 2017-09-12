#include "Nue.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "Mokou.h"


const int d_x[4] = { 0,1,0,-1 };
const int d_y[4] = { -1,0,1,0 };



namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Nue::Nue(int _x, int _y, int _hp) : PlayerChild(_x, _y, 5.0f, 25.0f, 1, _hp)
{
	initialize();
}

Nue::Nue(int _x, int _y) : Nue(_x, _y, 100)
{

}

Nue::~Nue()
{
	SAFE_DELETE(p);
	//SAFE_DELETE(ufo);
}

void Nue::initialize()
{
	//this->moveSpeed = 5.0f;
	loadImage();
	attackTime = 0;
	isUFO = false;
	
}

PlayerChild* Nue::update(const Stage* _stage)
{
	PlayerChild* next = this;

	standardAction(_stage);

	//攻撃
	for (auto& a : attacks)
	{
		if (a->isActive)
		{
			a->update();
			a->checkActive(camera);
		}
	}

	if (Input_ATTACK())
	{
		attack();
	}
	else
	{
		attackTime = 0;
	}
	if (isUFO)updateUFO(_stage);

	
	//for Debug
	if (canChangeCharacter())
	{
		animationTime = 0;
		int x = p->raw_x / MyData::vectorRate;
		int y = p->raw_y / MyData::vectorRate;
		next = new Mokou(x, y, hpController.getHP());
	}
	specialAction();
	return next;
}

int Nue::specialAction() {
	int x = 0;
	if (Input_C() && !isUFO) {
		ufo =new UFO((p->x()/CHIP_WIDTH+1)*CHIP_WIDTH-CHIP_WIDTH/2, (p->y() / CHIP_HEIGHT + 1)*CHIP_HEIGHT - CHIP_HEIGHT / 2);
		isUFO = true;
	}
	//prePushC = Input_C();
	return x;
}


//==============================================
//内部プライベート関数
//==============================================

void Nue::updateUFO(const Stage* _stage)
{
	ufo->update(_stage);

	//UFOの上に乗る処理
	if (abs(this->p->y() - ufo->getVector2()->y()) < CHIP_HEIGHT * 3 / 2 &&
		abs(this->p->x() - ufo->getVector2()->x()) < CHIP_WIDTH * 3 / 2)
	{
		this->warpCharacter(ufo->getVector2()->x(), ufo->getVector2()->y() - 48);
		nowJumpCount = 0;
		jumpPower = 0.0f;
	}

	///////////////////ギミックと同じ///////////////
	if (ufo->onActiveArea(this->getVector2()))
		ufo->apply(this);

	if (ufo->rideOnGimmick(this->getVector2()))
		this->moveCharacter(ufo->getDX(), ufo->getDY());
	/////////////////////ここまで///////////////////


	if (!ufo->isActive) {
		isUFO = false;
		delete ufo;
	}
}



void Nue::attack()
{
	if (attacks.size() == 0)
	{
		attacks.push_back(new Spear(0, 0, 32, 32, true));
		//attacks.push_back(new Spear(0, 0, 32, 32, true));
		//attacks.push_back(new Spear(0, 0, 32, 32, true));
	}

	++attackTime;
	//if (attackTime > 0)
	int new_pos = 32000 * ((direction) ? -1 : 1);

	attacks[0]->setStatus(Vector2(this->p->raw_x + new_pos * 1, this->p->raw_y, true), this->direction);
	//if (attackTime > 10)attacks[1]->setStatus(Vector2(this->p->raw_x + new_pos * 2, this->p->raw_y, true), this->direction);
	//if (attackTime > 20)attacks[2]->setStatus(Vector2(this->p->raw_x + new_pos * 3, this->p->raw_y, true), this->direction);

}

void Nue::draw_other() const
{
	for (const auto& a : attacks)
	{
		if (a->isActive)a->draw(camera);
	}

	if(isUFO)ufo->draw(camera);

	//for Debug
	DrawFormatString(0, 30, MyData::BLACK, "Nue");
}


void Nue::loadImage()
{
	//	mImage = LoadGraph("Data/Image/Nue.png");
	LoadDivGraph("Data/Image/Character/chip_Nue.png", 40, 8, 5, 32, 64, mImage, TRUE);
	assert(*mImage != -1 && "自機画像読み込みエラー");
}

//==============================================
//Spearクラス
//==============================================
Nue::Spear::Spear(int _x, int _y, int _w, int _h, bool _direction) :
	Attack(_x, _y, _w, _h, ObjectID::A_SPEAR)
{
	this->mTime = 0;
	mDirection = _direction;

	//for Debug
	this->damageValue = 20;

	mImage = LoadGraph("Data/Image/Spear.png");
	assert(mImage != -1 && "Spear画像読み込みエラー");
}

Nue::Spear::~Spear()
{
	DeleteGraph(mImage);
}

void Nue::Spear::update()
{
	mTime++;
	isActive = false;
}

void Nue::Spear::setStatus(Vector2 _pos, int direction)
{
	*(this->p) = _pos;
	this->mDirection = direction;

	isActive = true;

}

void Nue::Spear::hittedAction()
{
	//do nothing
}



///////////////////////////UFO/////////////////////////////

Nue::UFO::UFO(int _x, int _y) :
	DynamicGimmickChild(_x, _y, 1)
{
	this->width = (int)(32 * 3);
	this->height = (int)(32 * 1);

	initialize();
}

Nue::UFO::~UFO()
{
	DeleteGraph(mImage);
}

void Nue::UFO::initialize()
{
	loadImage();
	direction = -1;
	mTime = 0;
	isActive = true;
	isMove = false;



}

void Nue::UFO::update(const Stage* _stage)
{
	mTime++;
	move();
	standardMove(_stage);

	if (mTime > 300) isActive = false;

	
}

void Nue::UFO::draw(const Vector2* _camera) const
{
	if (mTime > 150 && mTime/10 % 2)return;

	standardDraw(_camera, p, mImage, mDirection);

	//for Debug
	DrawFormatString(0, 70, BLACK, "UFO: %d, %d", p->x(), p->y());

}

void Nue::UFO::apply(Character* _character)
{
	if (direction == -1)
	{
		if (Input_UP())direction = 0;
		else if (Input_RIGHT())direction = 1;
		else if (Input_DOWN())direction = 2;
		else if (Input_LEFT())direction = 3;
		mTime = 0;
	}


	//	else _character->moveCharacter(3.2f, 0.0f);
	this->isMove = true;
}

void Nue::UFO::hittedAction()
{
	/* do nothing */
}

void Nue::UFO::burnedAction()
{
	/* do nothing */
}

bool Nue::UFO::isOverlap(const Vector2* _player) const
{
	return standardOverLap(_player);
}

bool Nue::UFO::onActiveArea(const Vector2* _player) const
{
	return rideOnGimmick(_player);
}

//==============================================
//内部プライベート関数
//==============================================
void Nue::UFO::loadImage()
{
	this->mImage = LoadGraph("Data/Image/UFO.png");
	assert(mImage != -1 && "UFO画像読み込みエラー!");
}

void Nue::UFO::move()
{
	if (direction != -1) {
		dx = d_x[direction] * 3200;
		dy = d_y[direction] * 3200;
	}
}






}
}
}