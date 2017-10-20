#pragma once

#include "StateChild.h"


namespace StateNS {


class MusicRoom : public Child{
public:
	MusicRoom();
	~MusicRoom();
	void initialize();
	Child* update(GrandParent*);
	void draw() const;

private:
	int mBackImg;
	bool prePushUP,prePushDOWN;
	bool prePushOK;
	int nowSelect;
	int images[32];
	int time;
	int dx;
	int draw_x;
	void charmove();
	int animeNum;
	bool direction;
};




}