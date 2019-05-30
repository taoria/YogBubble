#include "GameEntity.h"
#include "../Component/IDrawComponent.h"
#include "TransformComponent.h"
#include "../Graphic/ModelComponent.h"
#include "IDAssigner.h"

GameEntity::GameEntity(){
	id = NEW_ENTITY_ID;
	AddComponent<ModelComponent>();
	AddComponent<TransformComponent>();
}
