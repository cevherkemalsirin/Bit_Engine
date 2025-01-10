#pragma once
#include <vector>
#include <Vector2D.h>

class Shape
{
protected:
	std::vector<Vector2D> points_;

public:

	virtual Vector2D GetCenter() const = 0;
	inline virtual std::vector<Vector2D> GetPoints() const { return points_; }
	void MoveBy(const Vector2D& offset);
	~Shape() {};

};

