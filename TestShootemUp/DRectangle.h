#pragma once

struct DRectangle // TODO Delete this
{
	DRectangle(float x, float y,float w, float h, float rot) : x(x), y(y), w(w), h(h), rotation(rot) {}
	float x, y;
	float w, h;
	float rotation;
};