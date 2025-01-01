#pragma once
#include <vector>
#include <Vector2D.h>

class Shape
{
	std::vector<Vector2D> points_;

public:

	virtual Vector2D GetCenter() const = 0;
	virtual inline std::vector<Vector2D> GetPoints() const { return points_; }
	void MoveBy(const Vector2D& offset);
	~Shape() {};
};

