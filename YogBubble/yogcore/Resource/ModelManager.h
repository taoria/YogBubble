#pragma once
#include "../Manager/IYogManager.h"
#include <map>
#include "ModelResource.h"
class ModelComponent;

//管理模型资源,注册模型
class YOG_DLL_EXPORT ModelManager:public IYogManager{
private:
	static ModelManager* manager;
	std::map<std::string, ModelResource*> m_map;
	bool RegisterTargetByName(std::string name, IYog* target) override;
	bool RegisterTargetById(UINT yog_id, IYog* target) override;
public:
	YID GetId() override;
	void SetId(YID id) override;
	std::string GetName() override;
	void SetName(std::string) override;
	IYog* GetTargetFromName(std::string name) override;
	IYog* GetTargetFromName(std::wstring name) override;
	void AddReference(ModelComponent* modelComponent,std::string modelName);
	bool RegisterModel(std::string file, std::string filepath);

	IYog* GetTargetFromId(UINT id) override;
	static ModelManager*  GetInstance();

};
