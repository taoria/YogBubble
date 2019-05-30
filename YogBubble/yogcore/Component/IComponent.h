#pragma once
#include "../IYogObject.h"
#include "../Entity/Entity.h"
enum COMPONENT_MARK{
	COMPONENT_FUNCTION,
	COMPONENT_RENDER,
	COMPONENT_PHYSICS,
	COMPONENT_NORMAL
};
struct YOG_DLL_EXPORT IComponent:public IYogObject{
	Entity* GetEntity();
	YID GetId() override;
	void SetId(YID id) override;
	virtual void OnUpdate();
	virtual COMPONENT_MARK GetComponentMark();
	std::string GetName() override;
	void SetName(std::string) override;
	void OnInit() override;
	void OnRelease() override;
	void AttachTo(Entity* entity);
	IComponent();
	YID id;
	Entity* entity;
};
