#pragma once

#include "DXLib.h"

#include <cassert>
#include <array>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>


using std::array;
using std::string;
using std::queue;
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
//zero divisionは回避していないから注意
//========================================
constexpr float pi(float num)
{
	return Pi * num;
}


//========================================
//Data.cpp/hで使用する名前空間
//========================================
namespace MyData{

//プレイヤーのチップサイズ
constexpr int PLAYER_CHIP_HEIGHT = 64;
constexpr int PLAYER_CHIP_WIDTH = 32;

//画面の中心座標
constexpr int CX = 320;
constexpr int CY = 240;

//マップのサイズ(ピクセル数)
constexpr int MAP_WIDTH = 960;
constexpr int MAP_HEIGHT = 640;

//マップのサイズ(チップ数)
constexpr int MAP_WIDTH_NUM = 30;
constexpr int MAP_HEIGHT_NUM = 20;

//マップチップのサイズ(ピクセル数)
constexpr int CHIP_WIDTH = 32;
constexpr int CHIP_HEIGHT = 32;

//1ピクセルをどれだけ拡張するか
constexpr int vectorRate = 1000;

//vectorRateを考慮したマップチップのサイズ
constexpr int PLAYER_CHIP_WIDTH_RATE() { return PLAYER_CHIP_WIDTH * vectorRate; }
constexpr int PLAYER_CHIP_HEIGHT_RATE() { return PLAYER_CHIP_HEIGHT * vectorRate; }

//vectorRateを考慮したマップチップのサイズ
constexpr int CHIP_WIDTH_RATE() { return CHIP_WIDTH * vectorRate; }
constexpr int CHIP_HEIGHT_RATE() { return CHIP_HEIGHT * vectorRate; }

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



//整数値2次元ベクトル
//内部では座標をvectorRate倍して持っている
class Vector2
{

public:
	int pos_x;
	int pos_y;

	Vector2() :
		Vector2(0, 0)
	{

	}
	Vector2(int _x, int _y)
	{
		this->pos_x = _x * vectorRate;
		this->pos_y = _y * vectorRate;
	}

	virtual int x() const { return this->pos_x / vectorRate; }
	virtual int y() const { return this->pos_y / vectorRate; }


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
		return Vector2(pos_x + other.x(), pos_y + other.y());
	}
	const Vector2 operator - (const Vector2& other)
	{
		return Vector2(pos_x - other.x(), pos_y - other.y());
	}
	const Vector2 operator * (int other) const
	{
		return Vector2(pos_x * other, pos_y * other);
	}
	const Vector2 operator / (int other) const
	{
		return Vector2(this->pos_x / other, this->pos_y / other);
	}
	bool operator == (const Vector2& other) const
	{
		return (pos_x == other.x()) && (pos_y == other.y());
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

}

using MyData::Vector2;
using MyData::RawVector2;
