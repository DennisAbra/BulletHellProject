#pragma once
#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "ObjectPooling.h"
#include "PhysEntity.h"
#include "Bullet.h"

class Enemy : public PhysEntity
{

protected:
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

	float invincibilityFrameTimer;
	float maxInvincibilityFrameTimer = 0.5f;

	bool wasHit = false;

	Vector2 firepoint;
	void HandleFiring();

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

	void Hit(PhysEntity* other) override;
	void Invincible();
	bool WasHit();
	bool invincible = false;
	bool isAlive = true;
	int health = 3;
	int maxHealth = 3;

	void Update();
	void Render();

	static const int MAX_BULLETS = 100;
	Bullet* bullets[MAX_BULLETS];


};