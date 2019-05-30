#pragma once
#include <set>
#include "Collider.h"
#include "RigidBody.h"

class Physics{
public:
	static std::set<ICollider*> colliders;
	static std::set<RigidBody*> bodies;
};
