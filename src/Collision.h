#pragma once
#include "Renderer.h"
#include "GameObject.h"
#include <unordered_map>


namespace Collision {

	struct CollisionSides
	{
		float left, right, top, bottom;
	};

	CollisionSides GetCollisionSides(glm::mat4 transform, glm::vec2 size);

	bool CheckCollision(CollisionSides a, CollisionSides b);	
}