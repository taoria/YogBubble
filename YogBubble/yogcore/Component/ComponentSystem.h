#pragma once
#include "../Manager/IYogManager.h"
#include "../Entity/Entity.h"
#include <map>
#include "../Manager/YogManager.h"
#include "../Component/IDrawComponent.h"
struct IComponent;
class ComponentSystem:public IYogManager{

private:
	std::vector<IDrawComponent*> drawComs;
	std::map<std::string, IComponent*> m_map;
	IYog* GetTargetFromName(std::string name) override;
	IYog* GetTargetFromName(std::wstring name) override;
	bool RegisterTargetById(UINT yog_id, IYog* target) override;
	IYog* GetTargetFromId(UINT id) override;
	bool RegisterTargetByName(std::string name, IYog* target) override;
public:

	YID GetId() override;
	void SetId(YID id) override;
	std::string GetName() override;
	void SetName(std::string) override;
	IComponent* GetComponentOfEntity(Entity* entity, std::string component);
	bool RegisterTargetOfEntity(Entity* entity, IComponent *com);
	std::vector<IComponent*> GetComponentList(Entity* entity);
	std::vector<IComponent*> GetComponentList();
	void CallForUpdate();
	void GCForEntity(Entity* entity);
	void GCForEntity();
	void CallForDraw();
	void CallForInit();
};
