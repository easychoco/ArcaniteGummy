#include "Data.h"

namespace MyData{

int fixToStageWidth(int _a) { return ((_a > 0) ? _a : _a - CHIP_WIDTH) / CHIP_WIDTH * CHIP_WIDTH; }

int fixToStageHeight(int _a) { return ((_a > 0) ? _a : _a - CHIP_HEIGHT) / CHIP_HEIGHT * CHIP_HEIGHT; }


int fixToVectorWidth(int _a) { return ( (_a > 0) ? _a : _a - CHIP_WIDTH_RATE()  ) / CHIP_WIDTH_RATE() * CHIP_WIDTH_RATE(); }

int fixToVectorHeight(int _a) { return ( (_a > 0) ? _a : _a - CHIP_HEIGHT_RATE() ) / CHIP_HEIGHT_RATE() * CHIP_HEIGHT_RATE(); }

float distance(int x1, int y1, int x2, int y2)
{
	return hypotf((float)(x1 - x2), (float)(y1 - y2));
}

float distance(int x, int y, const Vector2* other)
{
	return distance(x, y, other->raw_x, other->raw_y);
}

float distance(const Vector2* self, const Vector2* other)
{
	return distance(self->raw_x, self->raw_y, other->raw_x, other->raw_y);
}

int MapChip[256] = {};
extern Sound* sound = Sound::getInstance();

const Vector2 Vector2::ZERO(0, 0);
const Vector2 Vector2::LEFT(-1, 0);
const Vector2 Vector2::RIGHT(1, 0);
const Vector2 Vector2::UP(0, -1);
const Vector2 Vector2::DOWN(0, 1);



}
