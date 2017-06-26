#pragma once

#include "PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Nue : public PlayerChild
{
public:
	Nue();
	~Nue();
	PlayerChild* update(const Stage*);

private:
	void initialize();
	void attack();
	void draw_other() const;
	virtual void loadImage() override;
};




}
}
}