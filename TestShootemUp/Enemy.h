#pragma once
#include "AnimatedTexture.h"
#include "BezierPath.h"


class Enemy : public GameEntity
{
private:
	static std::vector<std::vector<Vector2>> paths;

	enum States { flyIn, formation, dive, dead };

	Timer* timer;

	Texture* texture;

	States currentState;

	int currentPath;
	int currentWaypoint;
	const float epsilon = 5.0f;

	float speed;

public:
	static void CreatePaths();
	Enemy(int path);
	Enemy(int path, std::string textureName);
	virtual ~Enemy();

	virtual void HandleFlyInState();
	virtual void HandleFormationState();
	virtual void HandleDiveState();
	virtual void HandleDeadState();

	void HandleStates();

	void Update();
	void Render();


};