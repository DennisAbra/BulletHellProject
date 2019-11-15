//#include "ObjectPooling.h"
//
//
//ObjectPooling* ObjectPooling::Instance = nullptr;
//Timer* timer;
//
//ObjectPooling::ObjectPooling() //cTor
//{
//
//}
//
//ObjectPooling::~ObjectPooling() 
//{
//	//entities[POOL_SIZE] = NULL;
//}
//
//GameEntity ObjectPooling::SpawnAfterTime(float spawnTime, std::string object) 
//{
//	spawnTime += timer->DeltaTime();
//
//	for (int i = 0; i < POOL_SIZE; i++)
//	{
//		//Search for GameEntity with the name of std::string object
//		//Spawn found object in the if statement
//		//If not found, throw an error
//	}
//
//	if (spawnTimer <= spawnTime) 
//	{
//		//Set the found object to active and reset spawnTimer to 0.
//		//return
//	}
//}
//
//void ObjectPooling::spawn(double x, double y, int lifeTime)
//{
//	//for (int i = 0; i < POOL_SIZE; i++)
//	//{
//	//	if (!entities[i].Active()) 
//	//	{
//	//		
//	//		entities[i].Active = false; //Inactive when spawned
//	//	}
//	//}
//}
//
//void ObjectPooling::animate()
//{
//
//}
