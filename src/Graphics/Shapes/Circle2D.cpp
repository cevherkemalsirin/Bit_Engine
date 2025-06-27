#include "Circle2D.h"
#include "Line2D.h"
#include "rectangle2D.h"
#include "Utils.h"

Circle2D::Circle2D(const Vector2D& center, float r):radius_(r)
{
	points_.push_back(center);
}

Rectangle2D Circle2D::GetBoundingBox() const
{
	Vector2D topLeftPoint((GetCenter().GetX() - radius_ - 1), (GetCenter().GetY() - radius_ - 1));
	Vector2D bottomRightPoint(GetCenter().GetX() + radius_, GetCenter().GetY() + radius_);
	return Rectangle2D(topLeftPoint,bottomRightPoint);
}

std::optional<std::vector<Line2D>> Circle2D::GetLines() const
{
	return std::nullopt;
}

bool Circle2D::Intersect(const Circle2D& otherCircle) const
{
	float distance = GetCenter().DistanceTo(otherCircle.GetCenter());
	float radiusSum = GetRadius() + otherCircle.GetRadius();
	return math::FEqualSmaller(distance, radiusSum);
}

bool Circle2D::ContainsPoint(const Vector2D& point) const
{
	float distance = GetCenter().DistanceTo(point);
	return math::FEqualSmaller(distance, radius_);
}
