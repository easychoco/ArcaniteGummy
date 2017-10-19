#pragma once

#include "StateNS\StateChild.h"

typedef StateNS::Child Child;


class Parent {
public:

	Parent();
	virtual ~Parent();
	void update();
	void draw() const;
	void initialize();

	void finishGame() { this->finish = true; }

	bool finish;

private:
	Child* mChild;
};