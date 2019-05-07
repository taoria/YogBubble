#include "IDrawComponent.h"
#include "../Entity/TransformComponent.h"

void IDrawComponent::OnDraw(){
	
}

Vec3& IDrawComponent::GetTransformPosition(){
	return GetEntity()->GetComponent<TransformComponent>()->position;
}

Vec3& IDrawComponent::GetRotationVector(){
	return GetEntity()->GetComponent<TransformComponent>()->rotation;
}
