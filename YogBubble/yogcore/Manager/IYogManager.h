#pragma once
#include "../IYogObject.h"
interface YOG_DLL_EXPORT IYogManager : IYogObject{
	virtual IYog* GetTargetFromName(std::string name)=0;
	virtual IYog* GetTargetFromName(std::wstring name)=0;
	virtual bool RegisterTargetByName(std::string name, IYog* target)=0;
	virtual bool RegisterTargetById(UINT yog_id, IYog* target)=0;
	virtual IYog* GetTargetFromId(UINT id)=0;

	void OnInit() override;
	void OnRelease() override;
};



inline void IYogManager::OnInit() {
	
}

inline void IYogManager::OnRelease() {
}
