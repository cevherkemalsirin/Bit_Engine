#include "Rectangle2D.h"

Rectangle2D::Rectangle2D():Rectangle2D(Vector2D::ZERO, Vector2D::ZERO)
{
	
}

Rectangle2D::Rectangle2D(const Vector2D& startP, const Vector2D& endP)
{
	points_.push_back(startP);
	points_.push_back(endP);
}

Rectangle2D::Rectangle2D(const Vector2D& topLeftP, unsigned int height, unsigned int width)
{
	points_.push_back(topLeftP);
	points_.push_back(Vector2D(topLeftP.GetX() + width - 1, topLeftP.GetY() + height - 1));
}

Vector2D Rectangle2D::GetCenter() const
{
	float midx = (GetTopLeftPoint().GetX() + GetBottomRightPoint().GetX()) / 2.0f;
	float midy = (GetBottomRightPoint().GetY() + GetTopLeftPoint().GetY()) / 2.0f;
	return Vector2D(midx, midy);
}


std::vector<Vector2D> Rectangle2D::GetPoints() const
{
	std::vector<Vector2D> newPoints;
	Vector2D topRightPoint = GetTopLeftPoint().GetX() + GetWidth() - 1;
	Vector2D bottomLeftPoint = GetTopLeftPoint().GetY() + GetHeight() - 1;
	newPoints.push_back(GetTopLeftPoint());
	newPoints.push_back(topRightPoint);
	newPoints.push_back(GetBottomRightPoint());
	newPoints.push_back(bottomLeftPoint);
	return newPoints;
}

float Rectangle2D::GetHeight() const
{
	return GetBottomRightPoint().GetY() - GetTopLeftPoint().GetY() + 1;
}

float Rectangle2D::GetWidth() const
{
	return GetBottomRightPoint().GetX() - GetTopLeftPoint().GetX() + 1;
}

float Rectangle2D::Area() const
{
	return GetHeight() * GetWidth();
}

bool Rectangle2D::Intersects(const Rectangle2D& targetRect) const
{
	return !(targetRect.GetBottomRightPoint().GetX() < GetTopLeftPoint().GetX()
		|| targetRect.GetBottomRightPoint().GetY() < GetTopLeftPoint().GetY()
        || targetRect.GetTopLeftPoint().GetX() > GetBottomRightPoint().GetX()
		|| targetRect.GetTopLeftPoint().GetY() > GetBottomRightPoint().GetY());
}

bool Rectangle2D::ContainsPoint(const Vector2D& point) const
{
	bool withinX = (point.GetX() < GetBottomRightPoint().GetX() && point.GetX() > GetTopLeftPoint().GetX());
	bool withinY = (point.GetY() < GetBottomRightPoint().GetY() && point.GetY() > GetTopLeftPoint().GetY());

	return (withinX && withinY);
}

void Rectangle2D::MoveTo(const Vector2D& targetPosition)
{
	//take height and width first since they will be give wrong values if we get them after
	//setting up the top left point of the rectangle
	float height = GetHeight();
	float width = GetWidth();
	SetTopLeftPoint(targetPosition);
	SetBottomRightPoint(Vector2D(GetTopLeftPoint().GetX() + width - 1, GetTopLeftPoint().GetY() + height - 1));
}

Rectangle2D Rectangle2D::Inset(const Rectangle2D& rect, const Vector2D& insetOffset)
{
	Vector2D newTopLeftP = rect.GetTopLeftPoint() + insetOffset;
	Vector2D newBottomRightP = rect.GetBottomRightPoint() - insetOffset;
	return Rectangle2D(newTopLeftP,newBottomRightP);
}
