#pragma once
#include "Shape.h"
#include "ILineShape.h"

class Circle2D : public Shape, public ILineShape
{
	float radius_;

public:
	Circle2D():Circle2D(Vector2D::ZERO, 0.0f){}
	Circle2D(const Vector2D& center, float r);

	inline  Vector2D GetCenter() const { return points_[0]; };
	inline void SetCenter(const Vector2D center) { points_[0] = center; }
	inline float GetRadius() const { return radius_; }
	inline void SetRadius(float r) { radius_ = r; }

	virtual Rectangle2D GetBoundingBox() const override;
	 std::vector<Line2D> GetLines() const;

	bool Intersect(const Circle2D& otherCircle) const;
	virtual bool ContainsPoint(const Vector2D& point) const override;
};

