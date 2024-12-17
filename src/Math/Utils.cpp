#include "Utils.h"

bool math::FEqual(float x, float y)
{
	return  fabsf(x - y) < EPSILON;
}

bool math::FEqualGreater(float x, float y)
{
	bool a = FEqual(x, y) || x > y;
	return FEqual(x, y) || x > y;
}

bool math::FEqualSmaller(float x, float y)
{
	return FEqual(x, y) || x < y;
}
