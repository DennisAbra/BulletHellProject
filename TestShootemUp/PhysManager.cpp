#include "PhysManager.h"

PhysManager* PhysManager::instance = nullptr;

PhysManager* PhysManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new PhysManager();
	}

	return instance;
}

void PhysManager::Release()
{
	delete instance;
	instance = nullptr;
}

void PhysManager::SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags)
{
	layerMasks[static_cast<unsigned int>(layer)] = std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(flags));
}

unsigned long PhysManager::RegisterEntity(PhysEntity* entity, CollisionLayers layer)
{
	collisionLayers[static_cast<unsigned int>(layer)].push_back(entity);
	lastId++;

	return lastId;
}

void PhysManager::UnregisterEntity(unsigned long id)
{
	bool found = false;
	for (int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers) && !found; i++)
	{
		for (int j = 0; j < collisionLayers[i].size() && !found; j++)
		{
			if (collisionLayers[i][j]->GetId() == id)
			{
				collisionLayers[i].erase(collisionLayers[i].begin() + j);
				found = true;
			}
		}
	}
}

PhysManager::PhysManager()
{
	lastId = 0;

	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++)
	{
		layerMasks[i] = std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(CollisionFlags::None));
	}
}

PhysManager::~PhysManager()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++)
	{
		collisionLayers[i].clear();
	}
}

void PhysManager::Update()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++)
	{
		for (unsigned int y = 0; y < static_cast<unsigned int>(CollisionLayers::MaxLayers); y++)
		{
			if (layerMasks[i].test(y) && i <= y)
			{
				for (unsigned int k = 0; k < collisionLayers[i].size(); k++)
				{
					for (unsigned int l = 0; l < collisionLayers[y].size(); l++)
					{
						if (collisionLayers[i][k]->CheckCollision(collisionLayers[y][l]))
						{
							collisionLayers[i][k]->Hit(collisionLayers[y][l]);
							collisionLayers[y][l]->Hit(collisionLayers[i][k]);
						}
					}
				}
			}
		}
	}
}


