#include "Rarashi.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Rarashi::Rarashi(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32,1,1)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Rarashi画像読み込みエラー!");

	initialize();
};


Rarashi::~Rarashi()
{
	DeleteGraph(images);
}

void Rarashi::initialize()
{
	this->mDirection = false;
	this->moveSpeed = 3000;

	//無敵
	hpController.isMuteki = true;
}

void Rarashi::update(const StageChild* _stage,const Vector2* _camera)
{
	mTime++;
	standardAction(_stage);	
}

void Rarashi::move(const StageChild* _stage, int& _dx, int& _dy)
{
	_dy = getBottomDiffer(_stage, 4000, _dx < 0);

	//_dyが0でなかったら空中にいる
	if (_dy != 0)
	{
		/*ここをコメントアウトすると，がけで落ちる
		//右下のチップ
		RawVector2 pos = RawVector2(p->x() + 1, p->y() + 16);
		Stage::ChipType chipType_right = _stage->getChipType(pos, false);

		//左下のチップ
		pos = RawVector2(p->x() - 1, p->y() + 16);
		Stage::ChipType chipType_left = _stage->getChipType(pos, false);
		
		//右下と左下が壁と空中なら，崖なう
		//方向転換する
		if (
			(_stage->isRigid_down(chipType_right) && chipType_left == _stage->TYPE_BACK) ||
			(_stage->isRigid_down(chipType_left) && chipType_right == _stage->TYPE_BACK)
			)
		{
			_dy = 0;
			mDirection = !mDirection;
			moveSpeed = -moveSpeed;
		}
		else//*/
		{
			_dx = 0;
			return;
		}

	}

	_dx = getHorizontalDiffer(_stage, moveSpeed, _dy < 0);
	this->mDirection = _dx > 0;

	//_dxが0で壁にぶつかる
	if (_dx == 0)
	{
		_dy = 0;
		mDirection = !mDirection;
		moveSpeed = -moveSpeed;
	}

}


//==============================================
//内部プライベート関数
//==============================================

void Rarashi::hittedAction()
{
	DrawCircle(100, 200, 5, GREEN);
}



}
}
}