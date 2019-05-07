#include "ComponentSystem.h"
#include "IComponent.h"

bool ComponentSystem::RegisterTargetByName(std::string name, IYog* target){

	return false;


}

IComponent* ComponentSystem::GetComponentOfEntity(Entity* entity, std::string component){
	char buffer[17];
	sprintf(buffer, "%d", entity->GetId());
	std::string str =component + buffer;
	return m_map[str];
}

bool ComponentSystem::RegisterTargetOfEntity(Entity* entity, IComponent* com){
	if (com == nullptr) {
		return false;
	}
	try {
		char buffer[17];
		sprintf(buffer, "%d", com->GetEntity()->GetId());
		std::string str = com->GetName() + buffer;
		m_map[str] = com;
	}
	catch (...) {

	}
	return true;
}
