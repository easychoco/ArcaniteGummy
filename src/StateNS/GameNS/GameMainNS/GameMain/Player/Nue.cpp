#include "Nue.h"

#include "..\..\..\..\..\KeyInput.h"

#include "Sakuya.h"
#include "Mokou.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Nue::Nue(int _x, int _y) : Nue(_x, _y, 100)
{

}

Nue::Nue(int _x, int _y, int _hp) : PlayerChild(_x, _y, 3.0f, 22.0f, 1, _hp)
{
	initialize();
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
	this->hpController.isMuteki = (actionState == ACT_SIT);

	//攻撃
	for (auto& a : attacks)
	{
		if (a->isActive)
		{
			a->update();
			a->checkActive(camera);
		}
	}

	if (Input_ATTACK() && actionState!=ACT_LADDER)attack();
	else attackTime = 0;
	


	if (Input_C() && !isUFO) {

		int tmp_x = (this->p->raw_x / CHIP_WIDTH_RATE() ) * CHIP_WIDTH + CHIP_WIDTH / 2;
		int tmp_y = (this->p->raw_y / CHIP_HEIGHT_RATE() ) * CHIP_HEIGHT + CHIP_HEIGHT / 2;
		ufo = new UFO(tmp_x, tmp_y);

		isUFO = true;
		this->next_dy = -CHIP_HEIGHT*vectorRate;
	}


	if (isUFO)updateUFO(_stage);
	

	if (canChangeCharacter())
	{
		animationTime = 0;
		int x = p->raw_x / MyData::vectorRate;
		int y = p->raw_y / MyData::vectorRate;


		int nextCharacter = _stage->getChangeableCharacter();

		if (nextCharacter & StageChild::ChangeableCharacter::CHARA_MOKOU)
			next = new Mokou(x, y, hpController.getHP());
		else if (nextCharacter & StageChild::ChangeableCharacter::CHARA_SAKUYA)
			next = new Sakuya(x, y, hpController.getHP());
	}
	return next;
}

void Nue::draw() const
{
	int draw_x = MyData::CX + (p->x() - camera->x());
	int draw_y = MyData::CY + (p->y() - camera->y());
	if (actionState == ACT_SIT)draw_y += PLAYER_CHIP_HEIGHT / 4;

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, ((direction) ? mImageL[animeNum] : mImageR[animeNum]), true, false);

	draw_other();
	draw_changingAnimation(draw_x, draw_y);

	//for Debug
	DrawBox(60, 20, 60 + hpController.getHP() * 5, 50, MyData::GREEN, true);
	//hpController.draw();
	if (isUFO)DrawFormatString(50, 160, WHITE, "UFO,DX%f,%f", ufo->getDX(), ufo->getDY());
DrawFormatString(50, 210, WHITE, "next%d,%d", next_dx, next_dy);
if(isUFO)DrawFormatString(50, 240, WHITE, "abs%d,%d", this->p->raw_x - ufo->getVector2()->raw_x, this->p->raw_y - ufo->getVector2()->raw_y);


}

//==============================================
//内部プライベート関数
//==============================================
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

//	DrawFormatString(20, 120, WHITE, "%d,%d", this->p->raw_x,this->p->raw_y);

}

void Nue::loadImage()
{
	//	mImage = LoadGraph("Data/Image/Nue.png");
	int tmp = LoadDivGraph("Data/Image/Character/chip_NueR.png", 32, 8, 4, 64, 64, mImageR, TRUE);
	assert(tmp != -1 && "ぬえR画像読み込みエラー");
	tmp = LoadDivGraph("Data/Image/Character/chip_NueL.png", 32, 8, 4, 64, 64, mImageL, TRUE);
	assert(tmp != -1 && "ぬえL画像読み込みエラー");
}

void Nue::animation()
{
	int num = 0;
	switch (actionState)
	{
	case ACT_WALK:num = 8 + (animeCount / 10) % 4; break;
	case ACT_RUN:num = 12 + (animeCount / 10) % 4; break;
	case ACT_SIT:num = 5; break;
	case ACT_ATTACK_UP:num = 4; break;
	case ACT_AIR:num = 1; break;
	case ACT_RUNJUMP:num = 1; break;
	case ACT_ATTACK_SIDE:num = 2; break;
	case ACT_ATTACK_SIDE_WALK:num = 16 + (animeCount / 10) % 4; break;
	case ACT_ATTACK_SIDE_RUN:num = 20 + (animeCount / 10) % 4; break;
	case ACT_ATTACK_UP_WALK:num = 24 + (animeCount / 10) % 4; break;
	case ACT_ATTACK_UP_RUN:num = 28 + (animeCount / 10) % 4; break;
	case ACT_LADDER:num = 3; break;
	default:animeCount = 0; break;
	}

	animeCount++;

	assert(!(num < 0 || 33 <= num) && "自機画像範囲外");
	animeNum = num;
}

void Nue::updateUFO(const StageChild* _stage)
{
	ufo->update(_stage);
	//UFOの上に乗る処理
	if (
		abs(this->p->raw_y - ufo->getVector2()->raw_y) < CHIP_HEIGHT_RATE()  *3/2&&
		abs(this->p->raw_x - ufo->getVector2()->raw_x) < CHIP_WIDTH_RATE() * 3 / 2
		)
	{
		warpCharacter(ufo->getVector2()->raw_x, ufo->getVector2()->raw_y - 48*vectorRate);
//		nowJumpCount = 0;

	}

	///////////////////ギミックと同じ///////////////

	if (ufo->onActiveArea(this->p))ufo->apply(this);

	if (ufo->rideOnGimmick(this->p))moveCharacter(ufo->getDX(), ufo->getDY());

	/////////////////////ここまで///////////////////


	if (!ufo->isActive)
	{
		isUFO = false;
		SAFE_DELETE(ufo);
	}
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
	//dy = 0;
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
	return
		abs(this->p->x() - _player->x()) <= MyData::CHIP_WIDTH &&
		(this->p->y() - _player->y()) / MyData::CHIP_HEIGHT == 1;
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
	dy = 0;
	if (direction == LEFT)dx = -3 * vectorRate;
	else if (direction == RIGHT)dx = 3 * vectorRate;

}






}
}
}