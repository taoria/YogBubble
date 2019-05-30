#pragma once
#include "../Manager/IYogManager.h"
#include <map>
#include "../Module/IYogModule.h"
class ModuleManager :public IYogManager{
protected:
	std::string m_manager_name;
	std::map<std::string, IYogModule*> m_modPool;
public:
	ModuleManager();
	void InitModule();
	void CallUpdate();
	~ModuleManager();
	YID GetId() override;
	void SetId(YID id) override;
	std::string GetName() override;
	void SetName(std::string) override;
	IYog* GetTargetFromName(std::string name) override;
	IYog* GetTargetFromName(std::wstring name) override;
	bool RegisterTargetByName(std::string name, IYog* target) override;
	bool RegisterTargetById(UINT yog_id, IYog* target) override;
	IYog* GetTargetFromId(UINT id) override;

};

