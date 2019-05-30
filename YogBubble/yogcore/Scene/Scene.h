#pragma once
#include "../IYog.h"
#include "../Entity/Entity.h"

class YOG_DLL_EXPORT Scene :public IYog{
private:

public:
	Scene();
	~Scene();
	std::vector<Entity*> gameEntities;
	bool Save(std::string sceneName);
	bool Load(std::string sceneName);
	void SceneAddEntity(Entity* entity);
	YID GetId() override;
	void SetId(YID id) override;
	std::string GetName() override;
	void SetName(std::string) override;
	void CleanScene();
};

