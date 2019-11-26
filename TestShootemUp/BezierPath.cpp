#include "BezierPath.h"
#include "Graphics.h"
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

BezierCurve BezierPath::TopUCurve()
{
	return { Vector2(Graphics::screenWidth * 0 - 100, Graphics::screenHeight * 0), Vector2(Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.55f),
		Vector2(Graphics::screenWidth * 0.5f,  Graphics::screenHeight * 0.55f),Vector2(Graphics::screenWidth + 100, Graphics::screenHeight * 0.f) };
}

BezierCurve BezierPath::LeftUCurve()
{
	return { Vector2(Graphics::screenWidth * 0-100, Graphics::screenHeight * 0.2), Vector2(Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.55f),
		Vector2(Graphics::screenWidth * 0.5f,  Graphics::screenHeight * 0.55f),Vector2(Graphics::screenWidth * 1.f +100, Graphics::screenHeight * 0.f) };
}

BezierCurve BezierPath::RightUCurve()
{
	return BezierCurve();
}

BezierCurve BezierPath::TopLeftSCurve()
{
	return { Vector2((Graphics::screenWidth * 0)- 100, Graphics::screenHeight * 0.2f), Vector2(Graphics::screenWidth * 0.8f, Graphics::screenHeight * 0.2f),
		Vector2(Graphics::screenWidth * 0.2f,  Graphics::screenHeight * 0.8f),Vector2(Graphics::screenWidth +100, Graphics::screenHeight * 0.8f) };
}

BezierCurve BezierPath::TopRightSCurve()
{
	return { Vector2(Graphics::screenWidth * 1.f +100, Graphics::screenHeight * 0.2f), Vector2(Graphics::screenWidth * 0.2f, Graphics::screenHeight * 0.2f),
		Vector2(Graphics::screenWidth * 0.8f,  Graphics::screenHeight * 0.8f),Vector2(Graphics::screenWidth * 0.f -100, Graphics::screenHeight * 0.8f) };
}

#pragma region Box Path
//Entry Path for boss
BezierCurve BezierPath::EntryPath()
{
	return{ Vec2_Zero,Vec2_Left,Vec2_One,Vector2(150,150) };
}
///////////
BezierCurve BezierPath::LeftRight()
{
	return { Vector2(150,150) , Vec2_One,Vec2_One,Vector2(950,150)};
}
BezierCurve BezierPath::RightDown()
{
	return { Vector2(950,150) , Vec2_One,Vec2_One,Vector2(950,450) };
}
BezierCurve BezierPath::RightLeft()
{
	return { Vector2(950,450) , Vec2_One,Vec2_One,Vector2(150,450) };
}
BezierCurve BezierPath::LeftUp()
{
	return { Vector2(150,450) , Vec2_One,Vec2_One,Vector2(150,150) };

}

#pragma endregion

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
