#include "GameEntity.h"

GameEntity::GameEntity(float x, float y)
{
	pos.x = x;
	pos.y = y;

	rotation = 0;

	active = true;

	parent = NULL;

	scale = Vec2_One;
}

GameEntity::~GameEntity()
{
	parent = NULL;
}

void GameEntity::Pos(Vector2 _pos)
{
	pos = _pos;
}

Vector2 GameEntity::Pos(Space space)
{
	if (space == local || parent == NULL)
	{
		return pos;
	}

	Vector2 parentScale = parent->Scale(world);
	Vector2 rotPosition = RotateVector(Vector2(pos.x * parentScale.x, pos.y * parentScale.y), parent->Rotation(local));

	return parent->Pos(world) + rotPosition;
}

void GameEntity::Rotation(float r)
{
	rotation = r;

	if (rotation > 360.0f)
	{
		int mul = rotation / 360.0f;
		rotation -= 360.0f * mul;
	}
	else if (rotation < 0.0f)
	{
		int mul = (rotation / 360.0f) - 1;
		rotation += 360 * mul;
	}
}

float GameEntity::Rotation(Space space)
{
	if (space == local || parent == NULL)
	{
		return rotation;
	}

	return parent->Rotation(world) + rotation;
}

void GameEntity::Scale(Vector2 _scale)
{
	scale = _scale;
}

Vector2 GameEntity::Scale(Space space)
{
	if (space == local || parent == NULL)
	{
		return scale;
	}

	Vector2 parentScale = parent->Scale(world);

	parentScale.x *= scale.x;
	parentScale.y *= scale.y;
	return parentScale;
}

void GameEntity::Active(bool _active)
{
	active = _active;
}

bool GameEntity::Active()
{
	return active;
}

void GameEntity::Parent(GameEntity* _parent)
{
	if (_parent == NULL)
	{
		pos = Pos(world);
		rotation = Rotation(world);
		scale = Scale(world);
	}
	else
	{
		if (parent != NULL)
		{
			Parent(NULL);
		}

		Vector2 parentScale = _parent->Scale(world);
		//Vector2 tempCalc = Pos(world) - _parent->Pos(world);
		pos = RotateVector(Pos(world) - _parent->Pos(world), -_parent->Rotation(world));
		pos.x /= parentScale.x;
		pos.y /= parentScale.y;

		rotation = rotation - _parent->Rotation(world);

		scale = Vector2(scale.x / parentScale.x, scale.y / parentScale.y);
	}

	parent = _parent;
}

GameEntity* GameEntity::Parent()
{
	return parent;
}

void GameEntity::Translate(Vector2 vec)
{
	
		pos += vec;
}

void GameEntity::Rotate(float amount)
{
	rotation += amount;
}

void GameEntity::Update()
{

}

void GameEntity::Render()
{

}


