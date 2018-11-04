#include "PlayerChild.h"

#include "..\Stages\StageChild.h"
#include "..\Collision.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {

PlayerChild::PlayerChild(int _x, int _y, float _move, float _jump, int _jumpCount, int _hp) :
Character(_hp, _x, _y, PLAYER_CHIP_WIDTH, PLAYER_CHIP_HEIGHT, true, _jump, _jumpCount, false),
maxMoveSpeed(_move)
{
	post_x = _x % MAP_WIDTH;
	post_y = _y % MAP_HEIGHT;
	this->camera = new Vector2(_x, _y);
	cameraLocked = false;

	initialize();
	assert(*mImage != -1 && "���@�摜�ǂݍ��݃G���[");
}

PlayerChild::~PlayerChild()
{
	SAFE_DELETE(camera);

	for (auto& a : attacks)
	{
		SAFE_DELETE(a);
	}
	attacks.clear();
	attacks.shrink_to_fit();
	for (int i = 0; i < 32; i++)
	{
		DeleteGraph(mImage[i]);
	}
}

void PlayerChild::initialize()
{
	this->moveSpeed = maxMoveSpeed;
	this->jumpPower = 0.0f;
	this->nowJumpCount = maxJumpCount;
	this->prePush = false;
	this->direction = false;
	this->animationTime = 0;
	this->animeNum = 0;
	this->animeCount = 0;
	this->onGround = false;
	this->onLadder = false;
	this->actionState = ACT_NORMAL;
	this->canMove = true;
	this->prePushC = false;
	this->stopDynamics = StopType::TYPE_NONE;
	this->ladderTime = 0;
	this->sinkedTime = 0;
	this->mTime = 0;
	this->lock = false;

	//�L������㒼��̂ݖ��G
	this->hpController.isMuteki = true;

	updateCamera();
}

void PlayerChild::draw() const
{
	int draw_x = MyData::CX + (p->x() - camera->x());
	int draw_y = MyData::CY + (p->y() - camera->y());
	if (actionState == ACT_SIT)draw_y += PLAYER_CHIP_HEIGHT / 4;

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage[animeNum], true, direction);
	
	draw_other();
	draw_changingAnimation(draw_x, draw_y);
}

//���@�����̏�ɂ����珰��y���W��Ԃ�
int PlayerChild::getFloorCoordinate()
{
	if (this->onGround)
	{
		return this->p->raw_y + PLAYER_CHIP_HEIGHT_RATE() / 2;
	}
	return 1 << 29;
}

void PlayerChild::moveCamera(int _dx, int _dy)
{
	camera->raw_x = max(0, min(MAP_WIDTH_RATE()  - 1000, camera->raw_x + _dx * vectorRate));
	camera->raw_y = max(0, min(MAP_HEIGHT_RATE() - 1000, camera->raw_y + _dy * vectorRate));
}

//================================================
//����protected�֐�
//================================================
void PlayerChild::standardAction(const StageChild* _stage)
{
	++mTime;
	this->hpController.isMuteki = mTime < 30;

	onGround = isOnGround(_stage);
	onLadder = isOnLadder(_stage);

	if (canMove)
	{
		in_right = Input_RIGHT();
		in_left  = Input_LEFT();
		in_up    = Input_UP();
		in_down  = Input_DOWN();
	}
	else
	{
		in_right = false;
		in_left  = false;
		in_up    = false;
		in_down  = false;
	}
	in_jump = Input_JUMP();

	actCheck();
	animation();

	move(_stage);
	updateCamera();
	changeCharacter(_stage);
	processDamage();
}

//�ύX�A�j���[�V�������I����ăL�����ύX�ł��邩�ǂ���
bool PlayerChild::canChangeCharacter()
{
	return animationTime > 30;
}



//================================================
//����private�֐�
//================================================

//�L�����ύX�A�j���[�V����
void PlayerChild::changeCharacter(const StageChild* _stage)
{
	if (Input_CHANGE() && mTime > 30 && _stage->canChangeCharacter(getThisCharacter(), true))
	{
		animationTime = max(animationTime, 1);
		stopDynamics = StopType::TYPE_CHANGE;

		//�ŏ��ɗ������������y�Đ�
		if (canMove)sound->playSound("change");
		canMove = false;
	}
	if (animationTime == 0)return;

	++animationTime;
}

void PlayerChild::draw_changingAnimation(int _draw_x, int _draw_y) const
{
	if (animationTime == 0)return;
	DrawCircle(_draw_x, _draw_y, animationTime * 2, MyData::WHITE);
}

void PlayerChild::processDamage()
{
	if (damaged)
	{
		++damagedTime;
		if (damagedTime < 3)
		{
			hittedAction();
			sound->playSound("damage");
		}
		if (damagedTime > 60)
		{
			damaged = false;
			damagedTime = 0;
		}
	}
}

void PlayerChild::hittedAction()
{
	//�m�b�N�o�b�N
	float dx = direction ? 10.0f : -10.0f;
	this->moveCharacter(dx, 0.0f);
}

//�ړ�
void PlayerChild::move(const StageChild* _stage)
{
	//�L������㒆�Ȃ�return
	if (animationTime > 0)return;

	int dx = next_dx;
	int dy = next_dy;

	next_dx = next_dy = 0;

	//���Ⴊ��ł�����height�𔼕��ɂ���
	if (actionState == ACT_SIT)
	{
		this->height = 32;
		this->collision->calcFromCenter = true;
	}
	else
	{
		this->height = 64;
		this->collision->calcFromCenter = false;
	}

	//����
	if (canMove && actionState != ACT_SIT)
	{
		if (in_right)
		{
			dx += (int)((moveSpeed + runCheck() * 2.0f) * vectorRate);
			direction = false;
		}
		if (in_left)
		{
			dx -= (int)((moveSpeed + runCheck() * 2.0f) * vectorRate);
			direction = true;
		}
	}

	if (isOnLesal(_stage))
	{
		damaged = false;
		hpController.damage(9999999);
	}

	//�n��ɂ���Ȃ�
	if (jumpPower == 0 && onGround)
	{
		nowJumpCount = 0;
	}


	//�͂����ɂ̂ڂ�
	if (onLadder)
	{
		ladderTime++;
		if (in_up)
		{
			dy -= (int)(moveSpeed * vectorRate + Input_DASH() * 3000);
			jumpPower = 0.0f;
			nowJumpCount = 0;
			direction = ladderTime % 10 == 0 ? !direction : direction;
		}

		if (in_down)
		{
			dy += (int)(moveSpeed * vectorRate + Input_DASH() * 3000);
			jumpPower = 0.0f;
			nowJumpCount = 0;
			direction = ladderTime % 10 == 0 ? !direction : direction;
		}
	}

	//�W�����v
	if (in_jump && !prePush && nowJumpCount < maxJumpCount)
	{
		sound->playSound("jump");
		jumpPower = maxJumpPower + runCheck()*3.0f;
		nowJumpCount++;
	}

	if (!in_jump)
	{
		jumpPower = 0.0f;
	}

	//�c�ړ�

	//�d�͂̒l
	//�͂����ɂ��邩�Cdy��0�łȂ�(moveCharacter���Ă΂�Ă���)�Ȃ�d�͂̒l��0
	int gravity_value = gravity() * (actionState != ACT_LADDER) * (dy == 0) * !onGround;
	if (jumpPower > 0.0f && onLadder)gravity_value = gravity();

	dy += gravity_value - jump();

	//dx�̌v�Z�Ɣ��f
	dx = getHorizontalDiffer(_stage, dx, dy < 0);

	//for Debug
	//if (Input_D() && in_right)dx = 20000;
	//if (Input_D() && in_left)dx = -20000;

	p->raw_x += dx;


	//dy�̌v�Z�Ɣ��f
	dy = dy < 0 ? getTopDiffer(_stage, dy, dx < 0) : getBottomDiffer(_stage, dy, dx < 0);
	


	//�V��ɓ���������
	if (abs(dy) <= 1000)jumpPower = 0;

	//for Debug
	//if (Input_D() && in_up) dy = -20000;
	//if (Input_D() && in_down) dy = 20000;

	p->raw_y += dy;

	p->raw_x = (p->raw_x + MAP_WIDTH_RATE()) % MAP_WIDTH_RATE();
	p->raw_y = (p->raw_y + MAP_HEIGHT_RATE()) % MAP_HEIGHT_RATE();


	//�G���A�Ԉړ�
	int dx_onScreen = p->x() - post_x;
	int dy_onScreen = p->y() - post_y;


	nextStageMove = StageChild::MOVE_NONE;
	if (abs(dx_onScreen) > MyData::MAP_WIDTH / 2)
	{
		if (dx_onScreen < 0)
		{
			if(p->x() < 32)nextStageMove = StageChild::MOVE_RIGHT;
		}
		else
		{
			if(p->x() > MAP_WIDTH - 32)nextStageMove = StageChild::MOVE_LEFT;
		}
		sound->stopSound("switch_time");
	}
	if (abs(dy_onScreen) > MyData::MAP_HEIGHT / 2)
	{
		if (dy_onScreen > 0)
		{
			if(p->y() > MAP_HEIGHT - 32)nextStageMove = StageChild::MOVE_UP;
		}
		else
		{
			if(p->y() < 32)nextStageMove = StageChild::MOVE_DOWN;
		}
		sound->stopSound("switch_time");
	}

	//�߂荞�݉��
	StageChild::ChipType thisType = _stage->getChipType(*p);
	if (thisType == StageChild::ChipType::TYPE_RIGID)
	{
		sinkedTime++;
	}
	else sinkedTime = 0;

	if (sinkedTime > 5)
	{
		if (in_right)this->p->raw_x -= 32000;
		else if (in_left)this->p->raw_x += 32000;
	}

	post_x = p->x();
	post_y = p->y();


	prePush = in_jump;
}

void PlayerChild::updateCamera()
{
	//lock����Ă���update������return
	if (cameraLocked)return;

	//�J�����ʒu���X�V
	int tmp_x = p->raw_x / MyData::vectorRate;
	int tmp_y = p->raw_y / MyData::vectorRate;

	if (tmp_x % MyData::MAP_WIDTH  <                     MyData::CX)tmp_x = MyData::MAP_WIDTH * (tmp_x / MyData::MAP_WIDTH) + MyData::CX;
	if (tmp_x % MyData::MAP_WIDTH  > MyData::MAP_WIDTH - MyData::CX)tmp_x = MyData::MAP_WIDTH * (tmp_x / MyData::MAP_WIDTH) + MyData::MAP_WIDTH - MyData::CX;

	if (tmp_y % MyData::MAP_HEIGHT <                      MyData::CY)tmp_y = MyData::MAP_HEIGHT * (tmp_y / MyData::MAP_HEIGHT) + MyData::CY;
	if (tmp_y % MyData::MAP_HEIGHT > MyData::MAP_HEIGHT - MyData::CY)tmp_y = MyData::MAP_HEIGHT * (tmp_y / MyData::MAP_HEIGHT) + MyData::MAP_HEIGHT - MyData::CY;


	*camera = Vector2(tmp_x, tmp_y);
}

bool PlayerChild::isOnGround(const StageChild* _stage)
{
	//pos�̓L�����̍ŉ��[���ЂƂ�
	RawVector2 pos = RawVector2(p->raw_x, p->raw_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	StageChild::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate, true);


	//�E��Ɍ������΂߃u���b�N�Ȃ�
	if (chipType == StageChild::ChipType::TYPE_DOWN_SLANT_RIGHT)
	{
		next_dy += gravity();
		return true;
		//pos.pos_y -= (MyData::CHIP_WIDTH_RATE() - pos.pos_x % MyData::CHIP_WIDTH_RATE());
		//chipType = _stage->getChipType(pos / MyData::vectorRate, true);
	}

	//����Ɍ������΂߃u���b�N�Ȃ�
	else if (chipType == StageChild::ChipType::TYPE_DOWN_SLANT_LEFT)
	{
		next_dy += gravity();
		return true;
		//pos.pos_y -= p->raw_x % MyData::CHIP_WIDTH_RATE();
		//chipType = _stage->getChipType(pos / MyData::vectorRate, true);
	}

	return !(chipType & (StageChild::ChipType::TYPE_LESAL | StageChild::ChipType::TYPE_BACK | StageChild::ChipType::TYPE_LADDER));
}

bool PlayerChild::isOnLadder(const StageChild* _stage) const
{

	RawVector2 pos = RawVector2(p->raw_x, p->raw_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 - 1);
	StageChild::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate, true);

	return chipType == StageChild::ChipType::TYPE_LADDER || chipType == StageChild::ChipType::TYPE_LADDER_TOP;
}

bool PlayerChild::isOnLesal(const StageChild* _stage)
{
	RawVector2 pos = RawVector2(p->raw_x, p->raw_y + PLAYER_CHIP_HEIGHT_RATE() / 4);
	StageChild::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate, true);

	return chipType == StageChild::ChipType::TYPE_LESAL;
}

void PlayerChild::animation() 
{
	int num = 0;
	switch (actionState) 
	{
	case ACT_WALK:num = 8 + (animeCount / 10) % 4;break;
	case ACT_RUN:num = 12 + (animeCount / 10) % 4;break;
	case ACT_SIT:num = 5;break;
	case ACT_ATTACK_UP:num = 4;break;
	case ACT_AIR:num = 1; break;
	case ACT_RUNJUMP:num = 1; break;
	case ACT_ATTACK_SIDE:num = 2; break;
	case ACT_ATTACK_SIDE_WALK:num = 16 + (animeCount / 10) % 4; break;
	case ACT_ATTACK_SIDE_RUN:num = 20 + (animeCount / 10) % 4; break;
	case ACT_ATTACK_UP_WALK:num = 24 + (animeCount / 10) % 4; break;
	case ACT_ATTACK_UP_RUN:num = 28 + (animeCount / 10) % 4; break;
	case ACT_LADDER:num = 3;break;
	default:animeCount = 0;break;
	}

	animeCount++;

	assert(!(num < 0 || 33 <= num) && "���@�摜�͈͊O");
	animeNum = num;
}

void PlayerChild::actCheck()
{
	///////////////////////////////�߂��Ⴍ����l�X�g�ł��߂��//�ނނށ[��/////////////////
	ActionState preAction = actionState;
	if (onLadder)
	{
		if (in_up || in_down)
		{
			actionState = ACT_LADDER;
		}

		if (in_left || in_right)
		{
			actionState = ((onGround) ? ACT_WALK : ACT_LADDER);
		}


		if (onGround && !in_up)
		{
			actionState = ACT_NORMAL;
			if (in_down)
			{
				actionState = ACT_SIT;
			}
		}
	}
	else if (Input_ATTACK())
	{
		if (in_up) 
		{
			actionState = ACT_ATTACK_UP;
			if (in_left || in_right) 
			{
				actionState = ACT_ATTACK_UP_WALK;
				if(Input_DASH())actionState = ACT_ATTACK_UP_RUN;
			}
		}
		else 
		{
			actionState = ACT_ATTACK_SIDE;
			if (in_left || in_right)
			{
				actionState = ACT_ATTACK_SIDE_WALK;
				if (Input_DASH())actionState = ACT_ATTACK_SIDE_RUN;
			}
		}
	}
	else if (!onGround)
	{
		if (preAction == ACT_RUN || preAction==ACT_RUNJUMP)actionState = ACT_RUNJUMP;
		else actionState = ACT_AIR;
	}
	else if (in_down)
	{
		actionState = ACT_SIT;
	}
	else if (in_left || in_right)
	{
		actionState = ACT_WALK;
		if (Input_DASH())actionState = ACT_RUN;
	}
	else actionState = ACT_NORMAL;

	if (actionState != preAction)animeCount = 0;
}



}		
}
}