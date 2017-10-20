#pragma once

#include "StateChild.h"


namespace StateNS {


class Config : public Child{
public:
	Config();
	~Config();
	void initialize();
	Child* update(GrandParent*);
	void draw() const;

private:
	int mBackImg;
	float volume;
	
	bool prePush;
	bool backFromConfig;
	bool nowKeyConfig;
	int nowInput;

	int configTime;


};




}