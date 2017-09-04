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
	Converse(GameMain*, int convNum);
	~Converse();
	void initialize();
	Child* update(GameParent*);
	void draw() const;

private:
	int passageNum;
	GameMain* main;

	void nextPassage();


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