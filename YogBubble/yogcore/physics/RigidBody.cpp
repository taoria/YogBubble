#include "RigidBody.h"
#include "Physics.h"

std::string RigidBody::GetName(){
	return "RigidBody";
}

RigidBody::RigidBody(){
	Physics::bodies.insert(this);
}
