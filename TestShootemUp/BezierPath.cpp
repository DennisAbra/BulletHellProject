#include "BezierPath.h"

BezierPath::BezierPath()
{

}

BezierPath::~BezierPath()
{

}

void BezierPath::AddCurve(BezierCurve curve, int sample)
{
	curves.push_back(curve);
	samples.push_back(sample);
}

void BezierPath::Sample(std::vector<Vector2>* sampledPath)
{
	for (int i = 0; i < curves.size(); i++)
	{
		for (float t = 0; t <= 1.0f; t += (1.0f / samples[i]))
		{
			sampledPath->push_back(curves[i].CalculateCurvePoint(t));
		}
	}
}
