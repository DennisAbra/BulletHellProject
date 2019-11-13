#pragma once
#include "MathHelper.h"
#include <vector>


class BezierPath
{
private:
	std::vector<BezierCurve> curves;
	std::vector<int> samples;

public:
	BezierPath();
	~BezierPath();

	void AddCurve(BezierCurve curve, int sample);

	void Sample(std::vector<Vector2>* sampledPath);
};