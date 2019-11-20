#pragma once
#include "PhysEntity.h"
#include <bitset>

class PhysManager
{
public:
	enum class CollisionLayers
	{
		Friendly = 0,
		FriendlyProjectile,
		Hostile,
		HostileProjectile,

		MaxLayers
	};

	enum class CollisionFlags
	{
		None				 = 0x00,
		Friendly			 = 0x01,
		FriendlyProjectiles  = 0x02,
		Hostile				 = 0x04,
		HostileProjectile	 = 0x08
		
	};

	static PhysManager* Instance();
	static void Release();

	void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

	unsigned long RegisterEntity(PhysEntity* entity, CollisionLayers layer);

	void UnregisterEntity(unsigned long id);

	void Update();

private:
	static PhysManager* instance;

	std::vector<PhysEntity*> collisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

	std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> layerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

	unsigned long lastId;

	PhysManager();
	~PhysManager();

};


inline PhysManager::CollisionFlags operator|(PhysManager::CollisionFlags a, PhysManager::CollisionFlags b)
{
	return static_cast<PhysManager::CollisionFlags>(static_cast<unsigned int>(a)
		| static_cast<unsigned int> (b));
}


inline PhysManager::CollisionFlags operator&(PhysManager::CollisionFlags a, PhysManager::CollisionFlags b)
{
	return static_cast<PhysManager::CollisionFlags>(static_cast<unsigned int>(a)
		& static_cast<unsigned int> (b));
}
