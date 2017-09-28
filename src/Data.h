#pragma once

#include "DXLib.h"
#include "Sound.h"

#include <cassert>
#include <array>
#include <vector>
#include <algorithm>

using std::array;
using std::vector;

//円周率
constexpr float Pi = 3.14159265358979f;


//deleteと0ポインタ
#define SAFE_DELETE(p){\
	delete (p);\
	(p) = 0;\
}

//delete[]と0ポインタ
#define SAFE_DELETE_ARRAY(p){\
	delete[] (p);\
	(p) = 0;\
}

//========================================
//円周率の計算(コンパイル時計算)
//========================================
constexpr float pi(float num)
{
	return Pi * num;
}


//========================================
//Data.cpp/hで使用する名前空間
//========================================
namespace MyData{

//マップチップ
//全体で同じものを使う
extern int MapChip[256];

//サウンド
extern Sound* sound;

//プレイヤーのチップサイズ
constexpr int PLAYER_CHIP_HEIGHT = 64;
constexpr int PLAYER_CHIP_WIDTH = 32;

//画面の中心座標
constexpr int CX = 320;
constexpr int CY = 240;

//マップ1つ分のサイズ(ピクセル数)
constexpr int MAP_WIDTH = 3200;
constexpr int MAP_HEIGHT = 1600;

//マップ1つ分のサイズ(チップ数)
constexpr int MAP_WIDTH_NUM = 100;
constexpr int MAP_HEIGHT_NUM = 50;

//マップチップのサイズ(ピクセル数)
constexpr int CHIP_WIDTH = 32;
constexpr int CHIP_HEIGHT = 32;

//1ピクセルをどれだけ拡張するか
constexpr int vectorRate = 1000;

//vectorRateを考慮しプレイヤーチップのサイズ
constexpr int PLAYER_CHIP_WIDTH_RATE() { return PLAYER_CHIP_WIDTH * vectorRate; }
constexpr int PLAYER_CHIP_HEIGHT_RATE() { return PLAYER_CHIP_HEIGHT * vectorRate; }

//vectorRateを考慮したマップチップのサイズ
constexpr int CHIP_WIDTH_RATE() { return CHIP_WIDTH * vectorRate; }
constexpr int CHIP_HEIGHT_RATE() { return CHIP_HEIGHT * vectorRate; }

//vectorRateを考慮したマップのサイズ
constexpr int MAP_WIDTH_RATE() { return MAP_WIDTH * vectorRate; }
constexpr int MAP_HEIGHT_RATE() { return MAP_HEIGHT * vectorRate; }

//マップのマスに合わせて調整
int fixToStageWidth(int _a);
int fixToStageHeight(int _a);

//マップのマスに合わせて調整
int fixToVectorWidth(int _a);
int fixToVectorHeight(int _a);



//色
const unsigned BLACK = GetColor(0, 0, 0);
const unsigned GLAY = GetColor(128, 128, 128);
const unsigned WHITE = GetColor(255, 255, 255);
const unsigned RED = GetColor(255, 0, 0);
const unsigned GREEN = GetColor(0, 255, 0);
const unsigned BLUE = GetColor(0, 0, 255);
const unsigned PURPLE = GetColor(255, 0, 255);

//すべての敵
enum AllEnemies
{
	ENE_USA,
	ENE_BALL,
	ENE_YACH,
	ENE_PIKA,
	ENE_POPPY,
	ENE_RARA,
	ENE_BROTH,

	BOSS_REISEN,

	ENE_NONE,
};

//ゲーム内に存在する全オブジェクト
//粒度は具体クラス単位
enum ObjectID
{
	ID_NONE,

	//Player
	P_MOKOU,
	P_SAKUYA,
	P_NUE,

	//Attack
	A_FIRE,
	A_KNIFE,
	A_SPEAR,

	//Enemy
	E_USAGI,
	E_BALOON,

	//MapChip
	M_BLOCK,

	//Gimmick
	G_BELT,
	G_SPRING,

	//DynamicGimmick
	DG_BLOCK
};


//整数値2次元ベクトル
//内部では座標をvectorRate倍して持っている
class Vector2
{

public:
	int raw_x, raw_y;

	Vector2() : Vector2(0, 0, false)
	{

	}
	Vector2(int _x, int _y) : Vector2(_x, _y, false)
	{

	}
	Vector2(int _x, int _y, bool useRawValue)
	{
		this->raw_x = _x;
		this->raw_y = _y;
		
		if (!useRawValue)
		{
			this->raw_x *= vectorRate;
			this->raw_y *= vectorRate;
		}
	}


	const int x() const { return (this->raw_x / vectorRate) % MAP_WIDTH; }
	const int y() const { return (this->raw_y / vectorRate) % MAP_HEIGHT; }
	const int pos_x() const { return this->raw_x % (MAP_WIDTH * vectorRate); }
	const int pos_y() const { return this->raw_y % (MAP_HEIGHT * vectorRate); }


	bool isZero() const
	{
		return *this == Vector2::ZERO;
	}

	Vector2& operator += (const Vector2& other)
	{
		return *this = *this + other;
	}
	Vector2& operator -= (const Vector2& other)
	{
		return *this = *this - other;
	}
	const Vector2 operator + (const Vector2& other)
	{
		return Vector2(raw_x + other.x(), raw_y + other.y());
	}
	const Vector2 operator - (const Vector2& other)
	{
		return Vector2(raw_x - other.x(), raw_y - other.y());
	}
	const Vector2 operator * (int other) const
	{
		return Vector2(raw_x * other, raw_y * other);
	}
	const Vector2 operator / (int other) const
	{
		return Vector2(this->raw_x / other, this->raw_y / other);
	}
	bool operator == (const Vector2& other) const
	{
		return (raw_x == other.x()) && (raw_y == other.y());
	}
	bool operator != (const Vector2& other) const
	{
		return !(*this == other);
	}

	
	static const Vector2 ZERO;
	static const Vector2 LEFT;
	static const Vector2 RIGHT;
	static const Vector2 UP;
	static const Vector2 DOWN;
};

class RawVector2
{
public:
	int pos_x, pos_y;
	RawVector2()
	{
		pos_x = pos_y = 0;
	}
	RawVector2(int _x, int _y)
	{
		pos_x = _x;
		pos_y = _y;
	}
	const RawVector2 operator + (const RawVector2& other)
	{
		return RawVector2(pos_x + other.pos_x, pos_y + other.pos_y);
	}
	const RawVector2 operator - (const RawVector2& other)
	{
		return RawVector2(pos_x - other.pos_x, pos_y - other.pos_y);
	}
	const RawVector2 operator * (int other) const
	{
		return RawVector2(pos_x * other, pos_y * other);
	}
	const RawVector2 operator / (int other) const
	{
		return RawVector2(this->pos_x / other, this->pos_y / other);
	}
	bool operator == (const RawVector2& other) const
	{
		return (pos_x == other.pos_x) && (pos_y == other.pos_y);
	}
	bool operator != (const RawVector2& other) const
	{
		return !(*this == other);
	}

};

//2点間の距離を得る, 重いから非推奨
float distance(int x1, int y1, int x2, int y2);
float distance(int x, int y, const Vector2*);
float distance(const Vector2*, const Vector2*);

}

using namespace MyData;
