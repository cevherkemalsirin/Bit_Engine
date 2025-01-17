#pragma once
#include <vector>

class Line2D;
class Rectangle2D;

class ILineShape
{
public:
	virtual std::vector<Line2D> GetLines() const = 0;
	virtual Rectangle2D GetBoundingBox() const = 0;
	virtual bool ContainsPoint(const Vector2D& point) const = 0;
};

