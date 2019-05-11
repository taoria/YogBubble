#pragma once
#include "../IYogObject.h"
#include "../Entity/Entity.h"
struct YOG_DLL_EXPORT IComponent:public IYogObject{
	Entity* GetEntity();
	YID GetId() override;
	void SetId(YID id) override;
	void OnUpdate();
	std::string GetName() override;
	void SetName(std::string) override;
	void OnInit() override;
	void OnRelease() override;
	void AttachTo(Entity* entity);
	IComponent();
	YID id;
	Entity* entity;
};
