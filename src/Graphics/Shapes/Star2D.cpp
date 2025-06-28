#include "Star2D.h"
#include "Line2D.h"
#include "Utils.h"
#include "Rectangle2D.h"

Star2D::Star2D(const Vector2D& center, uint8_t spikeNum, float centerSpikeDist, float spikeLength) :
	numberOfSpikes_(spikeNum), centerSpikeDist_(centerSpikeDist), 
	spikeLength_(spikeLength), center_(center)
{
	ValidateSpikeNumber();
	n_ = (numberOfSpikes_ - 1) / 2;
	CreateStar();
}


void Star2D::CreateStar()
{
	//first line of the star is; left line part of the top first pike
	Vector2D firstLineEnd = Vector2D(center_.GetX(), center_.GetY() - centerSpikeDist_);
	Vector2D firstLineStart = Vector2D(center_.GetX(), firstLineEnd.GetY() - spikeLength_);
    
	Line2D firstLine{ firstLineStart, firstLineEnd };
	bool flipFlop = true;

	//radian
	float innerAngle = math::PI * (1.0f - ((2.0f * n_) / numberOfSpikes_));
	float outerAngle = math::PI * (1 - (2.0f * (n_ - 1)) / numberOfSpikes_);

	firstLine.Rotate(innerAngle / 2.0f, firstLine.GetPointStart());
	lines_.push_back(firstLine);
	Line2D nextLine = firstLine;

	for (int i = 1; i < (numberOfSpikes_ * 2); ++i)
	{
		
			//rotate the line by the amount of spike inner angle
			if (flipFlop)
			{
				nextLine.Rotate(-outerAngle, nextLine.GetPointEnd());
			}
			//rotate the line by the amount of spike outer degree
			else
			{
				nextLine.Rotate(innerAngle, nextLine.GetPointStart());
			}
			flipFlop = !flipFlop;
			lines_.push_back(nextLine);
	}

}

void Star2D::ValidateSpikeNumber()
{
	if (numberOfSpikes_ % 2 == 0)
	{
		--numberOfSpikes_;
	}

	if (numberOfSpikes_ < 3)
	{
		numberOfSpikes_ = 3;
	}
}


bool Star2D::ContainsPoint(const Vector2D& point) const
{
	uint8_t crossing{ 0 };
	for (const auto& line : lines_)
	{
		Vector2D sp = line.GetPointStart();
		Vector2D ep = line.GetPointEnd();
		line.Slope();

		if((sp.GetY() > point.GetY()) != (ep.GetY() > point.GetY())) // skips horizantal line
		{
			float crossX = sp.GetX() + (point.GetY() - sp.GetY()) * (ep.GetX() - sp.GetX()) / (ep.GetY() - sp.GetY());
			if (point.GetX() < crossX)
			{
				++crossing;
			}
		}

	}
	// if crossing is odd then it is inside of the star else it is outside of the star
	if(crossing % 2 == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

Rectangle2D Star2D::GetBoundingBox() const
{
	float minX = center_.GetX();
	float maxX = center_.GetX();
	float minY = center_.GetY();
	float maxY = center_.GetY();

	for (const auto& line : lines_) {
		const Vector2D& sp = line.GetPointStart();
		const Vector2D& ep = line.GetPointEnd();

		minX = std::min({minX, sp.GetX(), ep.GetX()});
		maxX = std::max({maxX, sp.GetX(), ep.GetX()});
		minY = std::min({minY, sp.GetY(), ep.GetY()});
		maxY = std::max({maxY, sp.GetY(), ep.GetY()});
	}

	Vector2D topLeft(minX, minY);
	Vector2D bottomRight(maxX, maxY);
	return Rectangle2D(topLeft, bottomRight);
}
