#pragma once
#include "IYogManager.h"
#include <map>

#define get_manager(a) dynamic_cast<IYogManager*>(YogManager::get_instance()->GetTargetFromName(a))


class  YOG_DLL_EXPORT YogManager :public IYogManager
{
private:
	static YogManager* yog_manager_;
protected:
	std::map<std::string, IYogManager*> manager_pool;
public:
	YogManager();
	~YogManager();
	UINT GetId() override;
	std::string GetName() override;

	void SetId(YID id) override;
	void SetName(std::string) override;
	void OnInit() override;
	void OnRelease() override;
	// void on_iterating_members() override;
	// void on_target_registered(IYog* target) override;
	IYog* GetTargetFromName(std::string name) override;
	IYog* GetTargetFromName(std::wstring name) override;
	bool RegisterTargetByName(std::string name, IYog* target) override;
	bool RegisterTargetById(UINT yog_id, IYog* target) override;
	IYog* GetTargetFromId(UINT id) override;

	static IYogManager* get_instance();
};

