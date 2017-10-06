#include "Nue.h"

#include "..\..\..\..\..\KeyInput.h"
#include "Mokou.h"
#include "..\Collision.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Nue::Nue(int _x, int _y, int _hp) : PlayerChild(_x, _y, 3.0f, 22.0f, 1, _hp)
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
	attacks.push_back(new Spear(this, 0, 0, direction));
	isUFO = false;
	
}

PlayerChild* Nue::update(const StageChild* _stage)
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

	if (Input_ATTACK())attack();
	else attackTime = 0;
	


	if (Input_C() && !isUFO) {

		int tmp_x = (p->raw_x / CHIP_WIDTH_RATE() + 1) * CHIP_WIDTH - CHIP_WIDTH / 2;
		int tmp_y = (p->raw_y / CHIP_HEIGHT_RATE() + 1) * CHIP_HEIGHT - CHIP_HEIGHT / 2;
		ufo = new UFO(tmp_x, tmp_y);

		isUFO = true;
		this->next_dy = -32*vectorRate;
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
	return next;
}



//==============================================
//内部プライベート関数
//==============================================

void Nue::updateUFO(const StageChild* _stage)
{
	ufo->update(_stage);

	//UFOの上に乗る処理
	if (
		abs(this->p->raw_y - ufo->getVector2()->raw_y) <= CHIP_HEIGHT_RATE() * 3 / 2 &&
		abs(this->p->raw_x - ufo->getVector2()->raw_x) <= CHIP_WIDTH_RATE() * 3 / 2
		)
	{
		//this->warpCharacter(ufo->getVector2()->x(), ufo->getVector2()->y() - 48);
		nowJumpCount = 0;
		jumpPower = 0.0f;
	}

	///////////////////ギミックと同じ///////////////
	if (ufo->onActiveArea(p))
		ufo->apply(this);

	if (ufo->rideOnGimmick(p))
		this->moveCharacter(ufo->getDX(), ufo->getDY());
	/////////////////////ここまで///////////////////


	if (!ufo->isActive) {
		isUFO = false;
		SAFE_DELETE(ufo);
	}
}



void Nue::attack()
{
	if(!attacks[0]->isActive)
		attacks[0]->setStatus(*p, this->direction);
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

}

void Nue::loadImage()
{
	//	mImage = LoadGraph("Data/Image/Nue.png");
	int tmp = LoadDivGraph("Data/Image/Character/chip_NueR.png", 32, 8, 4, 64, 64, mImage, TRUE);
	assert(tmp != -1 && "自機画像読み込みエラー");
}

//==============================================
//Spearクラス
//==============================================
Nue::Spear::Spear(const PlayerChild* _parent, int _x, int _y, bool _direction) :
Attack(_parent, _x, _y, 32, 32, ObjectID::A_SPEAR)
{
	this->mTime = 0;
	this->mDirection = _direction;
	this->isActive = false;

	//for Debug
	this->damageValue = 100;

	img1 = LoadGraph("Data/Image/Spear.png");
	img2 = LoadGraph("Data/Image/Spear2.png");
	assert(mImage != -1 && "Spear画像読み込みエラー");
}

Nue::Spear::~Spear()
{
	DeleteGraph(mImage);
}

void Nue::Spear::update()
{

	mTime++;
	if (mTime > 40)isActive = false;
	int d = 60 - 3 * abs(mTime - 20);

	if (Input_UP()) {
		mImage = img2;
		this->p->raw_y = parent_p->raw_y - (d + 30) * vectorRate;
		this->p->raw_x = parent_p->raw_x;

	}
	else {
		mImage = img1;
		if (mDirection)d = -d;
		this->p->raw_y = parent_p->raw_y;
		this->p->raw_x = parent_p->raw_x + d * vectorRate;
	}
}

void Nue::Spear::setStatus(Vector2 _pos, int direction)
{
	*(this->p) = _pos;
	this->mDirection = direction;

	mTime = 0;
	isActive = true;
	this->parent_p = this->parent->getVector2();

}

void Nue::Spear::hittedAction()
{
	//do nothing
}


//==============================================
//UFOクラス
//==============================================
Nue::UFO::UFO(int _x, int _y) :
DynamicGimmickChild(_x, _y, 1.0)
{
	this->width  = 96;
	this->height = 32;

	initialize();
}

Nue::UFO::~UFO()
{
	DeleteGraph(mImage);
}

void Nue::UFO::initialize()
{
	loadImage();
	direction = NONE;
	mTime = 0;
	isActive = true;
	isMove = false;
}

void Nue::UFO::update(const StageChild* _stage)
{
	mTime++;
	move();
	standardMove(_stage);

	if (mTime > 300) isActive = false;

	
}

void Nue::UFO::draw(const Vector2* _camera) const
{
	if (mTime > 150 && mTime / 10 % 2)return;

	DrawFormatString(20, 80, BLACK, "%d, %d", this->p->raw_x, this->p->raw_y);
	standardDraw(_camera, mImage, mDirection);


}

void Nue::UFO::apply(Character* _character)
{
	if (direction == NONE)
	{
		if (Input_RIGHT())direction = RIGHT;
		else if (Input_LEFT())direction = LEFT;
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
	if (direction == LEFT)dx = -3 * vectorRate;
	else if (direction == RIGHT)dx = 3 * vectorRate;
	dy = 0;
}






}
}
}