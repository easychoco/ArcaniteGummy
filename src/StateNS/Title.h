#pragma once

#include "StateChild.h"
#include <vector>

namespace StateNS {


class Title : public Child{
public:
	Title();
	Title(int,int);
	~Title();
	void initialize();
	Child* update(GrandParent*);
	void draw() const;
	Child* nextScene(int);

private:
	int mBackImg;
	int movie;
	int count = 0;
	bool pushZ, pushX, pushUP, pushDOWN;
	int step;
	int select;
	int fontHandle1, fontHandle2;
	bool goToNext;
	const std::vector<int> save;

	void plusStep(int);
	void pressZ_draw()const;
	void command_draw()const;
};




}