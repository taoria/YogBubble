#include "Collider.h"

#include "Physics.h"
std::string ICollider::GetName(){
	return "Collider";
}

ICollider::ICollider(){
}

ICollider::~ICollider(){
}


std::string BallCollider::GetName(){
	return "BallCollider";
}

BallCollider::~BallCollider(){
	Physics::colliders.erase(this);
}

BallCollider::BallCollider(){
	Physics::colliders.insert(this);
	
}
