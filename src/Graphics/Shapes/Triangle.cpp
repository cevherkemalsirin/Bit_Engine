#include "Triangle.h"
#include "Utils.h"

Triangle::Triangle():Triangle(Vector2D::ZERO, Vector2D::ZERO, Vector2D::ZERO)
{
}

Triangle::Triangle(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2)
{
	GetPoints().push_back(p0);
	GetPoints().push_back(p1);
	GetPoints().push_back(p2);
}

Vector2D Triangle::GetCenter() const
{
	float midX = (GetP0().GetX() + GetP1().GetX() + GetP2().GetX()) / 3.0f;
	float midY = (GetP0().GetY() + GetP1().GetY() + GetP2().GetY() / 3.0f);
	return Vector2D(midX, midY);
}

float Triangle::Area() const
{
	Area(GetP0(), GetP1(), GetP2());
}

bool Triangle::ContainsPoint(const Vector2D& p) const
{
	float area1 = Area(GetP0(), GetP1(), p);
	float area2 = Area(GetP1(), GetP2(), p);
	float area3 = Area(GetP2(), GetP0(), p);
	return (area1 + area2 + area3) == Area();
}

float Triangle::Area(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2) const
{
	float area = (p0.GetX() * (p1.GetY() - p2.GetY()) +
		p1.GetX() * (p2.GetY() - p0.GetY()) +
		p2.GetX() * (p0.GetY() - p1.GetY())) / 2.0f;
	return fabs(area);
}
