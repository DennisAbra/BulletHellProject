#pragma once
#include "MathHelper.h"

class GameEntity
{
public:

	enum Space {local = 0, world = 1};

	GameEntity(float x = 0.0f, float y = 0.0f);
	~GameEntity();

	void Pos(Vector2 pos);
	Vector2 Pos(Space space = world);

	void Rotation(float rotation);
	float Rotation(Space space = world);

	void Scale(Vector2 _scale);
	Vector2 Scale(Space space = world);

	void Active(bool active);
	bool Active();

	void Parent(GameEntity* parent);
	GameEntity* Parent();

	virtual void Update();
	virtual void Render();

	void Translate(Vector2 vec);
	void Rotate(float amount);

private:

	Vector2 pos;
	float rotation;
	Vector2 scale;

	bool active;
	GameEntity* parent;
};