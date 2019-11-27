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
	
	

	//Making a rectangle using curves
	BezierCurve EntryPath();
	BezierCurve LeftUp();
	BezierCurve RightLeft();
	BezierCurve RightDown();
	BezierCurve LeftRight();
	//////////////////////////////////

	/// UnlimitedPath
	BezierCurve EntryPathUnlimited();
	BezierCurve RightCurveUnlimited();
	BezierCurve LeftCurveUnlimited();
	BezierCurve BackToEight();

	/////////////////////////////////
	void Sample(std::vector<Vector2>* sampledPath);
};