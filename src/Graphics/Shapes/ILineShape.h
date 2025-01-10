#pragma once
#include <vector>

class Line2D;

class ILineShape
{
public:
	virtual std::vector<Line2D> GetLines() const = 0;
};

