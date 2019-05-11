#include "GameEntity.h"
#include "../Component/IDrawComponent.h"
#include "TransformComponent.h"
#include "../Graphic/ModelComponent.h"
GameEntity::GameEntity(){
	AddComponent<ModelComponent>();
	AddComponent<TransformComponent>();
}
