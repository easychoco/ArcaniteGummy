#pragma once

#include "GameMainChild.h"
#include "..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

class GameMain;

class Converse : public Child
{
public:
	Converse(GameMain*, int stageNum1,int stageNum2);
	~Converse();
	void initialize();
	Child* update(GameParent*);
	void draw() const;


private:
	int passageNum;
	GameMain* main;
	int stageNum;
	bool prePush;
	void nextPassage();
	string YennToCR(string);

	class Passage
	{
	public:
		Passage(string speaker, string passage);
		~Passage();
		void show() const;
	private:
		string speaker;
		string passage;
	};
	vector<Passage> allPassages;


};



}
}
}