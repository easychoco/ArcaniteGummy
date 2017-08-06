#pragma once

#include "PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Mokou : public PlayerChild
{
public:
	Mokou(int, int);
	~Mokou();
	PlayerChild* update(const Stage*);

private:
	void initialize();
	void attack();
	void draw_other() const;
	virtual void loadImage() override;
	virtual void damagedAction() override { /* for Debug */ };
};


}
}
}