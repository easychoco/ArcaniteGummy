#include "..\Player\PlayerChild.h"
#include "Rock.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Rock::Rock(){
	initialize();
}

Rock::~Rock()
{

}

void Rock::initialize()
{

}

void Rock::update(PlayerChild* _player)
{


}

void Rock::draw() const
{
	DrawFormatString(0, 20, MyData::WHITE, "Rock");
}


//==============================================
//�����v���C�x�[�g�֐�
//==============================================

//����Ȃ��̂͂Ȃ�



}
}
}