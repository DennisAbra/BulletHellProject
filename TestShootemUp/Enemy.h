#pragma once
#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "ObjectPooling.h"
#include "PhysEntity.h"

class Enemy : public PhysEntity
{

private:
	static std::vector<std::vector<Vector2>> paths;

	enum States { flyIn, inactive, dead };

	Timer* timer;


	States currentState;

	int currentPath;
	int currentWaypoint;
	const float epsilon = 5.0f;

	float speed;
	float accuTimer = 0;

	bool IgnoreCollisions() override;
	bool DEBUG_LINES = false;


public:
	Texture* texture;

	Vector2 startPos;
	static void CreatePaths();
	Enemy(int path);
	Enemy(int path, std::string textureName);
	virtual ~Enemy();

	virtual void HandleFlyInState();
	virtual void HandleInactiveState();
	virtual void HandleDeadState();

	void HandleStates();


	void Update();
	void Render();


};