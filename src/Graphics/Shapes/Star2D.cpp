#include "Star2D.h"
#include "Line2D.h"
#include "Utils.h"

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
