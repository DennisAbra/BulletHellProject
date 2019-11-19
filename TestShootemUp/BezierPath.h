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

	//Easy to use curves
	BezierCurve TopUCurve();
	BezierCurve LeftUCurve();
	BezierCurve RightUCurve();

	BezierCurve TopLeftSCurve();
	BezierCurve TopRightSCurve();
	
	void Sample(std::vector<Vector2>* sampledPath);
};