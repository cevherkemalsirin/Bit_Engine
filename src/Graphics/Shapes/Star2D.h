#pragma once
#include <stdint.h>
#include <vector>
#include <Vector2D.h>
#include "ILineShape.h"

class Line2D;

class Star2D: public ILineShape
{
	uint8_t numberOfSpikes_;
	float centerSpikeDist_;
	Vector2D center_;
	float spikeLength_;
	//n is a number how many steps jump to connect another spike
	uint8_t n_;
	std::vector<Line2D> lines_;
	//is david star kind or hollow star kid
	bool innersIntersect_;
	/* 
	*180 – 360n_/numberOfSpikes_ = 180(1 – 2n_/numberOfSpikes_) formula for inner angle 
	* 180(1 – 2(n_ – 1)/numberOfSpikes_) formula for outer angle
	*/
	void CreateStar();
	void ValidateSpikeNumber();

public:
	Star2D(const Vector2D& center) :Star2D(center, 5, 20.0f, 30.0f) {};
	Star2D(const Vector2D& center,
		uint8_t spikeNum = 5, 
		float centerSpikeDist = 20.0f, 
		float spikeLength = 30.0f);


	virtual std::vector<Line2D> GetLines() const override { return lines_; }
};

