#include "Collision.h"

std::vector<GameObject*> Collision::objects = std::vector<GameObject*>();

Collision::CollisionSides Collision::GetCollisionSides(glm::mat4 transform, glm::vec2 size)
{
	return { transform[3].x,transform[3].x + size.x,transform[3].y + size.y,transform[3].y };
}

bool Collision::CheckCollision(CollisionSides a, CollisionSides b)
{
    //If the two objects are colliding with each other on the X axis
    bool collisionX =a.right >= b.left && b.right >= a.left;
    //If the two objects are colliding with each other on the Y axis
    bool collisionY = a.top >= b.bottom && b.top >= a.bottom;
    //return true if we are colliding in both axis
    return collisionX && collisionY;
}

GameObject* Collision::CheckCollisions(GameObject *obj)
{
    //Iterate over all the obejcts
    for (GameObject* object : objects) {
        //Check for collision
        if (CheckCollision(GetCollisionSides(obj->transform, obj->size), GetCollisionSides(object->transform, object->size)))
            return object;
    }
    //If there is no collision
    return NULL;
}
