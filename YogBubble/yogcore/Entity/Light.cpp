#include "Light.h"
#include "TransformComponent.h"
#include "../Graphic/LightComponent.h"
#include "IDAssigner.h"
Light::Light(): Entity(){
	id = NEW_ENTITY_ID;
	AddComponent<TransformComponent>();
	AddComponent<LightComponent>();
	
}
