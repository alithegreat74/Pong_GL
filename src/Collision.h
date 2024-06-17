#pragma once
#include "Renderer.h"
#include "GameObject.h"
#include <vector>

class GameObject; //Forward Declaration

namespace Collision {
	//All The collidable objects in the game 
	extern std::vector<GameObject*> objects;

	struct CollisionSides
	{
		float left, right, top, bottom;
	};
	//returns the positions of each sides of AABB
	CollisionSides GetCollisionSides(glm::mat4 transform, glm::vec2 size);

	bool CheckCollision(CollisionSides a, CollisionSides b);
	
	//Checks if an object is colliding with any game object in the the objects array
	GameObject* CheckCollisions(GameObject *obj);
}