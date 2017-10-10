#pragma once

#include "..\DynamicGimmickChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Child;
class Block;

class SwitchWithBlock : public DynamicGimmickChild
{
public:
	//第3引数がないなら普通のスイッチ
	//第3引数が1なら押しっぱなしのスイッチ
	//第3引数が2より大きいなら時限式スイッチ(引数が制限時間(フレーム数 / 引数60で1秒))
	
	SwitchWithBlock(int x, int y);
	SwitchWithBlock(int x, int y, int notChangeable);
	SwitchWithBlock(int x, int y, int limitTime, bool notChangeable);
	~SwitchWithBlock();
	void initialize();
	void update(const StageChild*);
	void draw(const Vector2*) const;
	virtual void draw_front(const Vector2*) const {}
	void apply(Character*);

	void hittedAction() override;
	void burnedAction() override;
	bool isOverlap(const Vector2*) const override;

	bool onActiveArea(const Vector2*) const;
	void checkOnActiveArea(const Vector2* player) { this->onActiveArea(player); }
	StageChild::ChipType getChipType() const;

	//スイッチがonの時に現れるBlock
	vector<Block*> blocks_on;

	//スイッチがoffの時に現れるBlock
	vector<Block*> blocks_off;

	vector<Block*> getBlocks() { return ((isPushed) ? blocks_on : blocks_off); }

	//第2引数がtrueで， スイッチonの時に現れる
	//第2引数がfalseで，スイッチoffの時に現れる
	void push_block(Block* b, bool switch_on) { switch_on ? blocks_on.push_back(b) : blocks_off.push_back(b); }

private:
	bool isPushed;
	bool preOnActiveArea;
	mutable bool tmpOnActiveArea;
	int mTime;
	const int limitTime;
	const bool notChangeable;

	void loadImage();
};




}
}
}
