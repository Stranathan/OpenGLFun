#include "physicsWorld.hpp"

void physicsWorld::addObjectToWorld(rigidBody* object)
{
}

void physicsWorld::removeObjectFromWorld(rigidBody* object)
{
}

// euler integration of newton's second law
void physicsWorld::physicsProcess(float deltaTime)
{
	for (rigidBody* obj : worldsRigidBodies) 
	{
		obj->accl += gravity; // F = mg = ma
		obj->vel += obj->accl * deltaTime; // v(t + deltaTime) = v(t) + a(t) * deltaTime
		obj->pos += obj->vel * deltaTime;
		obj->accl = glm::vec2(0.0f, 0.0f);
	}
}

void physicsWorld::startUp()
{
	// copy the rigid bodies from object manager
	/*unsigned int vertsArraySize = sizeof(unitTriangle) / sizeof(float);
	vertices.insert(vertices.begin(), &unitTriangle[0], &unitTriangle[vertsArraySize]);*/
}

physicsWorld::physicsWorld()
{
}

physicsWorld::~physicsWorld()
{
}
