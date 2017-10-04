#include "Usagi.h"
#include "..\Stages\StageChild.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS{

bool Usagi::imgLoad = false;
int Usagi::images[8];

Usagi::Usagi(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32)
{
	loadImage();

	initialize();
};


Usagi::~Usagi()
{
	//DeleteGraphはしない
}

void Usagi::initialize()
{
	this->mDirection = true;
	this->moveSpeed = 1000;

	this->mTime = 0;
}

void Usagi::update(const StageChild* _stage,const Vector2* _camera)
{
	actState = ENE_ACT_WALK;
	aTime++;
	mTime++;

	standardAction(_stage);
	mImage = images[actState * 2 + (aTime / 10) % 2];
}

void Usagi::move(const StageChild* _stage, int& _dx, int& _dy)
{
	_dx = getHorizontalDiffer(_stage, moveSpeed, _dy < 0);
	_dy = getBottomDiffer(_stage, 2000, _dx > 0);

	//自分の下のチップのChipTypeをゲット
	RawVector2 pos = RawVector2(p->x(), p->y() + CHIP_HEIGHT);
	StageChild::ChipType chipType_under = _stage->getChipType(pos, false);

	//自分の前のチップのChipTypeをゲット
	pos = RawVector2(p->x() + CHIP_WIDTH / 4 * ((mDirection) ? 1: -1), p->y() - CHIP_HEIGHT / 2);
	StageChild::ChipType chipType_front = _stage->getChipType(pos, false);

	//崖か壁で方向転換
	if( !( _stage->isRigid_down(chipType_under) || _stage->isSlant(chipType_under) ) || 
		chipType_front == StageChild::ChipType::TYPE_RIGID )
	{
		_dy = 0;
		mDirection = !mDirection;
		moveSpeed = -moveSpeed;
		this->p->raw_x += moveSpeed * 5;
	}
}


//==============================================
//内部プライベート関数
//==============================================
void Usagi::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Rarashi.png", 8, 8, 1, 32, 32, images);
		assert(tmp != -1 && "Usagi画像読み込みエラー");
	}
	imgLoad = true;
}

void Usagi::hittedAction()
{

}

}
}
}