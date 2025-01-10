#include "Circle2D.h"
#include "Utils.h"

Circle2D::Circle2D(const Vector2D& center, float r):radius_(r)
{
	SetCenter(center);
}

bool Circle2D::Intersect(const Circle2D& otherCircle) const
{
	float distance = GetCenter().DistanceTo(otherCircle.GetCenter());
	float radiusSum = GetRadius() + otherCircle.GetRadius();
	return math::FEqualSmaller(radiusSum, distance);
}

bool Circle2D::Contains(const Vector2D& point) const
{
	float distance = GetCenter().DistanceTo(point);
	return math::FEqualSmaller(radius_, distance);
}
