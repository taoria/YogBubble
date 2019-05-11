#pragma once
#include "../Manager/IYogManager.h"
#include <map>
#include "Config.h"

class ConfigManager :public IYogManager
{
protected:
	std::map<std::string, Config> configs;
public:
	ConfigManager();
	~ConfigManager();
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

